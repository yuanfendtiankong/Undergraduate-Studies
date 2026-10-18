import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

# 确保目标保存目录存在
save_directory = r'D:\PycharmProjects\pythonProject\Pattern Recognition\picture\7.5'
os.makedirs(save_directory, exist_ok=True)  # 如果目录不存在，则创建它

# 图像路径
image_path = r'D:\PycharmProjects\pythonProject\Pattern Recognition\picture\test\mapleleaf.tif'  # 修改为你的图像文件路径

# 加载图像并转换为二值图
image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
if image is None:
    print("图像未能加载，请检查路径是否正确。")
    exit()

_, binary_image = cv2.threshold(image, 127, 255, cv2.THRESH_BINARY)

# 定义不同大小的结构元素
kernel_sizes = [5, 15, 30]
kernels = [cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (size, size)) for size in kernel_sizes]

# 应用形态学梯度
gradient_images = [cv2.morphologyEx(binary_image, cv2.MORPH_GRADIENT, kernel) for kernel in kernels]

# 可视化并保存结果
fig, axs = plt.subplots(1, len(kernel_sizes) + 1, figsize=(20, 5))
axs[0].imshow(binary_image, cmap='gray')
axs[0].set_title('Original Binary Image')
axs[0].axis('off')

for i, img in enumerate(gradient_images):
    axs[i+1].imshow(img, cmap='gray')
    axs[i+1].set_title(f'Gradient with {kernel_sizes[i]}x{kernel_sizes[i]} Kernel')
    axs[i+1].axis('off')
    # 保存每个图像
    plt.imsave(os.path.join(save_directory, f'gradient_{kernel_sizes[i]}x{kernel_sizes[i]}.png'), img, cmap='gray')

plt.show()
