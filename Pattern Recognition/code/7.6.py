import cv2
import numpy as np
import matplotlib.pyplot as plt

# 载入图像
file_path = 'D:\PycharmProjects\pythonProject\Pattern Recognition\picture\\test\\hole.jpg'
image = cv2.imread(file_path, cv2.IMREAD_GRAYSCALE)

# 确保图像读取成功
if image is None:
    raise ValueError("无法读取图像，请检查文件路径。")

# 二值化图像 - 注意这里我们将洞的颜色视为白色，背景为黑色
_, binary_image = cv2.threshold(image, 127, 255, cv2.THRESH_BINARY)

# 找到所有的洞（白色区域）
contours, _ = cv2.findContours(binary_image, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

# 创建一个全黑的图像用于绘制填充后的结果
filled_image = np.zeros_like(binary_image)

# 遍历找到的每个轮廓，并用白色填充
for contour in contours:
    cv2.drawContours(filled_image, [contour], -1, 255, -1)

# 可视化结果
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.imshow(binary_image, cmap='gray')
plt.title('Original Binary Image')
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(filled_image, cmap='gray')
plt.title('Filled Image')
plt.axis('off')

# Save the filled image
output_path = 'D:\\PycharmProjects\\pythonProject\\Pattern Recognition\\picture\\7.6\\filled_image.jpg'
cv2.imwrite(output_path, filled_image)

plt.show()


