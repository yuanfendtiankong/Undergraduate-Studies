import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

# 确保目标保存目录存在
save_directory = r'D:\PycharmProjects\pythonProject\Pattern Recognition\picture\7.1'
os.makedirs(save_directory, exist_ok=True)  # 如果目录不存在，则创建它

# 图像路径
image_path = r'D:\PycharmProjects\pythonProject\Pattern Recognition\picture\test\wirebond-mask.tif'

# 加载图像
image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
if image is None:
    print("图像未能加载，请检查路径是否正确。")
    exit()

# 二值化图像
_, binary_image = cv2.threshold(image, 127, 255, cv2.THRESH_BINARY)

# 定义腐蚀操作的函数
def erode_image(img, kernel_size):
    kernel = np.ones((kernel_size, kernel_size), np.uint8)  # 创建结构元素
    eroded_image = cv2.erode(img, kernel, iterations=1)  # 应用腐蚀操作
    return eroded_image

# 应用不同大小的结构元素
sizes = [11, 15, 45]
eroded_images = [erode_image(binary_image, size) for size in sizes]

# 保存腐蚀后的图像
for i, img in enumerate(eroded_images):
    file_path = os.path.join(save_directory, f'eroded_{sizes[i]}x{sizes[i]}.png')
    cv2.imwrite(file_path, img)
    print(f'Image saved to {file_path}')  # 打印保存位置

# 可视化结果
fig, axs = plt.subplots(1, len(sizes)+1, figsize=(20, 5))
axs[0].imshow(binary_image, cmap='gray')
axs[0].set_title('Original Binary Image')
axs[0].axis('off')

for i, img in enumerate(eroded_images):
    axs[i+1].imshow(img, cmap='gray')
    axs[i+1].set_title(f'Eroded with {sizes[i]}x{sizes[i]} Kernel')
    axs[i+1].axis('off')

plt.show()
