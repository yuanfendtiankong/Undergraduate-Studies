import numpy as np


def calculate_glcm(matrix, d, angle):
    max_val = np.max(matrix)
    glcm = np.zeros((max_val + 1, max_val + 1), dtype=int)

    # 设置移动的方向
    offset = {
        45: (-1, 1)  # 45度，左上方向
    }
    row_offset, col_offset = offset[angle]

    rows, cols = matrix.shape
    for i in range(rows):
        for j in range(cols):
            new_i, new_j = i + row_offset, j + col_offset
            if 0 <= new_i < rows and 0 <= new_j < cols:
                glcm[matrix[i, j], matrix[new_i, new_j]] += 1

    # 针对对称性，增加相反方向的计数
    if row_offset != 0 or col_offset != 0:  # 确保不是0度或180度
        for i in range(rows):
            for j in range(cols):
                new_i, new_j = i - row_offset, j - col_offset
                if 0 <= new_i < rows and 0 <= new_j < cols:
                    glcm[matrix[i, j], matrix[new_i, new_j]] += 1

    return glcm


image_matrix = np.array([
    [0, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 1, 1],
    [2, 2, 2, 2, 3, 3],
    [2, 2, 2, 2, 3, 3]
])

glcm_matrix = calculate_glcm(image_matrix, 1, 45)

print("共生矩阵 (GLCM) for d=1, angle=45°:")
print(glcm_matrix)
