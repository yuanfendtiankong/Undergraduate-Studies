import cv2
from matplotlib import pyplot as plt

def global_thresholding(image_path, threshold):
    # 读取图像
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)  # 直接以灰度模式读取图像

    # 应用全局阈                                                                                                          值
    _, thresh_img = cv2.threshold(img, threshold, 255, cv2.THRESH_BINARY)

    # 显示原始图像和阈值处理后的图像
    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    plt.imshow(img, cmap='gray')
    plt.title('Original Image')
    plt.axis('off')

    plt.subplot(1, 2, 2)
    plt.imshow(thresh_img, cmap='gray')
    plt.title('Thresholded Image')
    plt.axis('off')

    plt.show()

    # 返回处理后的图像
    return thresh_img

# 调用函数
image_path = 'D:\\PycharmProjects\\pythonProject\\Pattern Recognition\\picture\\8.5\\paopao.jpg'
thresholded_image = global_thresholding(image_path, 189)  # 假设阈值为127
