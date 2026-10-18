import cv2
import numpy as np
from matplotlib import pyplot as plt

def moving_average_and_adaptive_threshold(image_path, kernel_size):
    # 读取图像
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)  # 直接以灰度模式读取图像

    # 创建平均滤波器核
    kernel = np.ones((kernel_size, kernel_size), np.float32) / (kernel_size**2)

    # 应用移动平均滤波器
    smoothed_img = cv2.filter2D(img, -1, kernel)

    # 应用自适应阈值
    adaptive_thresh = cv2.adaptiveThreshold(smoothed_img, 255, cv2.ADAPTIVE_THRESH_MEAN_C,
                                            cv2.THRESH_BINARY, 11, 5)

    # 显示原始图像、滤波后的图像和自适应阈值处理后的图像
    plt.figure(figsize=(18, 6))
    plt.subplot(1, 3, 1)
    plt.imshow(img, cmap='gray')
    plt.title('Original Image')
    plt.axis('off')

    plt.subplot(1, 3, 2)
    plt.imshow(smoothed_img, cmap='gray')
    plt.title('Smoothed Image')
    plt.axis('off')

    plt.subplot(1, 3, 3)
    plt.imshow(adaptive_thresh, cmap='gray')
    plt.title('Adaptive Threshold Image')
    plt.axis('off')

    plt.show()

    # 返回处理后的图像
    return adaptive_thresh

# 调用函数
image_path = 'D:\\PycharmProjects\\pythonProject\\Pattern Recognition\\picture\\8.7\\moving_threshold.jpg'  # 确保路径正确，使用双反斜杠或原始字符串
smoothed_and_thresholded_image = moving_average_and_adaptive_threshold(image_path, 3)  # 使用5*5的核
