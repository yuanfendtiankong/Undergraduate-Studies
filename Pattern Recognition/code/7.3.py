import cv2
import numpy as np
import matplotlib.pyplot as plt
import os
import matplotlib

# 确保目标保存目录存在
save_directory = r'D:\PycharmProjects\pythonProject\Pattern Recognition\picture\7.3'
os.makedirs(save_directory, exist_ok=True)

# 图像路径
image_path = r'D:\PycharmProjects\pythonProject\Pattern Recognition\picture\test\mask2.jpg'  # 修改为你的图像文件路径

# 加载图像并转换为二值图
image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
if image is None:
    print("图像未能加载，请检查路径是否正确。")
    exit()

_, binary_image = cv2.threshold(image, 127, 255, cv2.THRESH_BINARY)

# 定义圆形结构元素
kernel_size = 33  # 结构元素的大小
kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (kernel_size, kernel_size))

# 膨胀操作
dilated_image = cv2.dilate(binary_image, kernel, iterations=1)

# 腐蚀操作
eroded_image = cv2.erode(binary_image, kernel, iterations=1)

# 开运算
opening_image = cv2.morphologyEx(binary_image, cv2.MORPH_OPEN, kernel)

# 闭运算
closing_image = cv2.morphologyEx(binary_image, cv2.MORPH_CLOSE, kernel)

# 设置中文字体
matplotlib.rcParams['font.family'] = 'SimHei'
matplotlib.rcParams['font.size'] = 12
matplotlib.rcParams['axes.unicode_minus'] = False  # 解决负号问题

# 可视化所有结果
fig, axs = plt.subplots(1, 5, figsize=(20, 4))
titles = ['原图', '膨胀', '腐蚀', '开运算', '闭运算']
images = [binary_image, dilated_image, eroded_image, opening_image, closing_image]

for i, (img, title) in enumerate(zip(images, titles)):
    axs[i].imshow(img, cmap='gray')
    axs[i].set_title(title)
    axs[i].axis('off')

# 保存图像
plt.savefig(os.path.join(save_directory, 'morphology_operations.png'))
plt.show()
