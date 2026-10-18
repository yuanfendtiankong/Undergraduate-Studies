# 定义原始的灰度图像矩阵
original_matrix = [
    [1, 3, 7, 3],
    [2, 6, 0, 6],
    [8, 2, 6, 5],
    [9, 2, 6, 0]
]

# 水平镜像
def horizontal_mirror(matrix):
    return [row[::-1] for row in matrix]

# 垂直镜像
def vertical_mirror(matrix):
    return matrix[::-1]

# 水平且垂直镜像
def horizontal_vertical_mirror(matrix):
    return horizontal_mirror(vertical_mirror(matrix))

# 计算各种镜像
h_mirror = horizontal_mirror(original_matrix)
v_mirror = vertical_mirror(original_matrix)
hv_mirror = horizontal_vertical_mirror(original_matrix)

# 打印原始矩阵和各种镜像结果
print("原始矩阵:")
for row in original_matrix:
    print(row)
print("\n水平镜像结果:")
for row in h_mirror:
    print(row)
print("\n垂直镜像结果:")
for row in v_mirror:
    print(row)
print("\n水平且垂直镜像结果:")
for row in hv_mirror:
    print(row)
