import numpy as np
# 原始图像矩阵
a = np.array([
    [1, 1, 1, 1, 3],
    [1, 1, 1, 3, 7],
    [1, 1, 3, 7, 7],
    [1, 3, 7, 1, 7],
    [3, 7, 7, 7, 7]
])

# 使用np.pad进行边界复制方式扩展
padded_a_replicate = np.pad(a, pad_width=1, mode='edge')

# 初始化中值滤波结果矩阵，大小与原图像相同
median_filtered_a = np.zeros_like(a, dtype=float)

# 3x3中值滤波
for i in range(0, padded_a_replicate.shape[0] - 2):
    for j in range(0, padded_a_replicate.shape[1] - 2):
        # 计算当前3x3区域的中值
        median_value = np.median(padded_a_replicate[i:i+3, j:j+3])
        # 更新结果矩阵
        median_filtered_a[i, j] = median_value

# print(median_filtered_a)
for row in median_filtered_a:
    for val in row:
        print(f"{val:.1f}", end=' ')
    print()  # 换行，以便每行打印完成后开始新的一行