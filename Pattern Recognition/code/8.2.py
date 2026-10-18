import numpy as np
import cv2
from matplotlib import pyplot as plt

# 读取图像
img_path = 'D:\\PycharmProjects\\pythonProject\\Pattern Recognition\\picture\\8.2\\coin.jpg'
img = cv2.imread(img_path)

# 将图像转换为灰度图
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# 应用阈值处理进行二值化
ret, thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

# 创建形态学操作的核
kernel = np.ones((3,3), np.uint8)

# 应用开运算去噪声
opening = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel, iterations=2)

# 应用膨胀操作确定背景区域
sure_bg = cv2.dilate(opening, kernel, iterations=3)

# 使用距离变换确定前景区域
dist_transform = cv2.distanceTransform(opening, cv2.DIST_L2, 5)
ret, sure_fg = cv2.threshold(dist_transform, 0.7 * dist_transform.max(), 255, 0)

# 确定未知区域
sure_fg = np.uint8(sure_fg)
unknown = cv2.subtract(sure_bg, sure_fg)

# 连通区域标记
ret, markers = cv2.connectedComponents(sure_fg)
markers = markers + 1
markers[unknown == 255] = 0

# 应用分水岭算法分割前景和背景
markers = cv2.watershed(img, markers)
img[markers == -1] = [255, 255, 255]  # 边界标记为白色

# 设置图像显示
plt.figure(figsize=(20, 5))  # 设定图像大小
plt.subplot(1, 4, 1)
plt.imshow(cv2.cvtColor(cv2.imread(img_path), cv2.COLOR_BGR2RGB))
plt.title('Original Image')
plt.axis('off')

plt.subplot(1, 4, 2)
plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
plt.title('Segmented Image')
plt.axis('off')

plt.subplot(1, 4, 3)
plt.imshow(sure_fg, cmap='gray')
plt.title('Foreground')
plt.axis('off')

plt.subplot(1, 4, 4)
plt.imshow(dist_transform, cmap='gray')
plt.title('Distance Transform')
plt.axis('off')

plt.show()
