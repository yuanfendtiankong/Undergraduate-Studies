import numpy as np
# 原始图像矩阵
a = np.array([
    [1, 1, 1, 1, 3],
    [1, 1, 1, 3, 7],
    [1, 1, 3, 7, 7],
    [1, 3, 7, 1, 7],
    [3, 7, 7, 7, 7]
])

# 初始化结果矩阵，大小与原图像相同
filtered_a = np.zeros_like(a, dtype=float)


# 补零扩展
padded_a = np.pad(a, pad_width=1, mode='constant', constant_values=0)
# print(padded_a)

# # 3x3均值滤波
for i in range(0, padded_a.shape[0] - 2):
    for j in range(0, padded_a.shape[1] - 2):
        # 计算当前3x3区域的平均值
        mean_value = (np.mean(padded_a[i:i+3, j:j+3]))
        # 更新结果矩阵
        filtered_a[i, j] = np.around(mean_value, decimals=1)

# print(filtered_a)
# print('\n')
for row in filtered_a:
    for val in row:
        print(f"{val:.1f}", end=' ')
    print()  # 换行，以便每行打印完成后开始新的一行


