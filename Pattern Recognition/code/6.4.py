import numpy as np

# 定义原始的灰度图像矩阵
original_matrix = np.array([
    [1, 3, 7, 3],
    [2, 6, 0, 6],
    [8, 2, 6, 5],
    [9, 2, 6, 0]
])

# 水平镜像
horizontal_mirror = np.fliplr(original_matrix)

# 垂直镜像
vertical_mirror = np.flipud(original_matrix)

# 计算水平且垂直镜像：先垂直后水平
horizontal_vertical_mirror = np.fliplr(vertical_mirror)

# 打印原始矩阵和各种镜像结果
print("原始矩阵:")
for row in original_matrix:
    print(row)
print("\n水平镜像结果:")
for row in horizontal_mirror:
    print(row)
print("\n垂直镜像结果:")
for row in vertical_mirror:
    print(row)
print("\n水平且垂直镜像结果:")
for row in horizontal_vertical_mirror:
    print(row)

