from PIL import Image
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

# 创建一个512x512的图像，灰度值为0（黑色）
img = np.zeros((512, 512), dtype=np.uint8)

# 在中央定义一个200x200的正方形，灰度值设置为255（白色）
start = (512 - 200) // 2  # 计算正方形开始的位置
end = start + 200  # 计算正方形结束的位置
img[start:end, start:end] = 255

# 使用Pillow库创建图像并保存
image = Image.fromarray(img)
#image.save("centered_square.png")

#image = Image.open("centered_square.png")  # 确保这里的路径指向你的图像文件

# 使用matplotlib显示图像
plt.imshow(image, cmap='gray')  # cmap='gray'确保以灰度模式显示
plt.axis('off')  # 不显示坐标轴
plt.show()
