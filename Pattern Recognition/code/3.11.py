import cv2
import matplotlib.pyplot as plt
import numpy as np

def make_PSF(kernel_size=15, angle=60):
    PSF = np.diag(np.ones((kernel_size)))
    angle = angle + 45
    M = cv2.getRotationMatrix2D((kernel_size/2, kernel_size/2), angle, 1)
    PSF = cv2.warpAffine(PSF, M, (kernel_size, kernel_size), flags=cv2.INTER_CUBIC)
    PSF = PSF / PSF.sum()
    return PSF

def extension_PSF(image0, PSF0):
    imgh, imgw, _ = image0.shape
    h, w = PSF0.shape
    PSF = np.zeros((imgh, imgw))
    PSF[:h, :w] = PSF0
    return PSF

def make_blurred(img, PSF):
    blurred = np.zeros_like(img)
    for i in range(3):  # 对每个颜色通道处理
        input_fft = np.fft.fft2(img[:,:,i])
        PSF_fft = np.fft.fft2(PSF, s=img[:,:,i].shape)
        blurred_channel = np.fft.ifft2(input_fft * PSF_fft)
        blurred[:,:,i] = np.abs(blurred_channel)
    return blurred

def CLS(img, PSF, a):
    result = np.zeros_like(img)
    H_fft = np.fft.fftshift(np.fft.fft2(PSF, s=img[:,:,0].shape))
    P = np.array([[0, 1, 0], [1, -4, 1], [0, 1, 0]])
    P = extension_PSF(img, P)
    P_fft = np.fft.fft2(P, s=img[:,:,0].shape)
    for i in range(3):  # 对每个颜色通道处理
        input_fft = np.fft.fft2(img[:,:,i])
        PSF_fft = np.conj(H_fft) / (np.abs(H_fft)**2 + a * np.abs(P_fft)**2)
        deblurred_channel = np.fft.ifft2(input_fft * PSF_fft)
        result[:,:,i] = np.abs(deblurred_channel)
    return result

if __name__ == '__main__':
    image = cv2.imread('D://PycharmProjects//pythonProject//Pattern Recognition//picture//albert-einstein.jpg')
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)  # 转换为RGB格式
    plt.figure(figsize=(8,6))
    plt.subplot(131)
    plt.axis("off")
    plt.title("Original Image")
    plt.imshow(image)

    PSF = make_PSF(15, 60)
    PSF = extension_PSF(image, PSF)
    blurred = make_blurred(image, PSF)
    blurred_noise = blurred + 0.1 * blurred.std() * np.random.standard_normal(blurred.shape)
    plt.subplot(132)
    plt.axis("off")
    plt.title("Blurred and Noise")
    plt.imshow(blurred_noise.astype('uint8'))

    result = CLS(blurred_noise, PSF, 0.01)
    plt.subplot(133)
    plt.axis("off")
    plt.title("CLS Deblurred")
    plt.imshow(result.astype('uint8'))
    plt.show()
