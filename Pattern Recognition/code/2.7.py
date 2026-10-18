import numpy as np
from PIL import Image
import numpy as np

# 计算图像的平均灰度值函数
def calculate_average_grayscale(image_path):
    """计算图像的平均灰度值。

    参数:
        image_path (str): 图像文件的路径。

    返回:
        float: 图像的平均灰度值。
    """
    # 使用Pillow库加载图像
    img = Image.open(image_path)

    # 将图像转换为灰度
    img_gray = img.convert('L')

    # 将灰度图像转换为NumPy数组
    img_array = np.array(img_gray)

    # 计算平均灰度值
    average_grayscale = np.mean(img_array)

    return average_grayscale

# 使用示例
# image_path = 'centered_square.png'  # 替换为你的图像文件路径
# average_gray = calculate_average_grayscale(image_path)
# print(f'图像的平均灰度值为: {average_gray}')


# 计算例题的灰度值
image_matrix = np.array([
    [2, 4, 5, 6],
    [3, 1, 5, 3],
    [6, 2, 2, 2]
])

# Calculate the average grayscale value
average_grayscale = np.mean(image_matrix)
print(f'图像的平均灰度值为: {average_grayscale}')