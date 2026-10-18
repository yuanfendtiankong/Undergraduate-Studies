import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

def ensure_dir(file_path):
    """确保目录存在，如果不存在则创建它"""
    if not os.path.exists(file_path):
        os.makedirs(file_path)

def motion_blur_kernel(length, angle):
    kernel = np.zeros((length, length))
    radians = np.deg2rad(angle + 90)  # +90 because the kernel is calculated from the top down
    x = int(length / 2 * np.cos(radians))
    y = int(length / 2 * np.sin(radians))
    cv2.line(kernel, (length//2 - x, length//2 - y), (length//2 + x, length//2 + y), 1, thickness=1)
    return kernel / kernel.sum()

def apply_motion_blur(image, kernel):
    """Apply motion blur kernel to an image"""
    return cv2.filter2D(image, -1, kernel)

def add_gaussian_noise(image, mean=0, var=0.01):
    """Add Gaussian noise to an image"""
    sigma = var**0.5
    gauss = np.random.normal(mean, sigma, image.shape).astype(np.float32)
    noisy = image.astype(np.float32) + gauss
    return np.clip(noisy, 0, 255).astype(np.uint8)

def cls_deblur(noisy_img, kernel, gamma):
    """Perform Constrained Least Squares deblurring of a noisy image"""
    kernel_fft = np.fft.fft2(kernel, s=noisy_img.shape[:2])
    kernel_fft_conj = np.conj(kernel_fft)
    P = np.pad(np.array([[0, -1, 0], [-1, -4, -1], [0, -1, 0]]), [(0, noisy_img.shape[0]-3), (0, noisy_img.shape[1]-3)], mode='constant')
    P_fft = np.fft.fft2(P)

    deblurred = np.zeros_like(noisy_img, dtype=np.float32)
    noisy_fft = np.fft.fft2(noisy_img)
    numerator = kernel_fft_conj * noisy_fft
    denominator = kernel_fft_conj * kernel_fft + gamma * np.abs(P_fft)**2
    result_fft = numerator / denominator
    result = np.fft.ifft2(result_fft)
    deblurred = np.abs(result)

    return np.clip(deblurred, 0, 255).astype(np.uint8)

if __name__ == '__main__':
    image_path = 'D://PycharmProjects//pythonProject//Pattern Recognition//picture//images.jpg'
    base_path = 'D://PycharmProjects//pythonProject//Pattern Recognition//picture//5.9'
    ensure_dir(base_path)  # 确保文件夹存在

    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)  # 以灰度模式读取图像

    kernel_size = 15
    angle = 60
    kernel = motion_blur_kernel(kernel_size, angle)
    blurred_image = apply_motion_blur(image, kernel)

    # 添加高斯噪声到模糊图像
    noisy_blurred_image = add_gaussian_noise(blurred_image)

    gamma = 0.01  # 正则化参数
    restored_image = cls_deblur(noisy_blurred_image, kernel, gamma)

    # 保存图像
    cv2.imwrite(os.path.join(base_path, 'original_image.png'), image)
    cv2.imwrite(os.path.join(base_path, 'noisy_blurred_image.png'), noisy_blurred_image)
    cv2.imwrite(os.path.join(base_path, 'restored_image.png'), restored_image)

    # 显示图像
    plt.figure(figsize=(16, 12))
    plt.subplot(131)
    plt.imshow(image, cmap='gray')
    plt.title("Original Image")
    plt.axis("off")

    plt.subplot(132)
    plt.imshow(noisy_blurred_image, cmap='gray')
    plt.title("Blurred + Gaussian Noise")
    plt.axis("off")

    plt.subplot(133)
    plt.imshow(restored_image, cmap='gray')
    plt.title("CLS Deblurred")
    plt.axis("off")

    plt.show()
