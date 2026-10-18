import numpy as np
import matplotlib.pyplot as plt

# 图像矩阵
image_matrix = np.array([
    [1, 3, 2, 6],
    [1, 2, 3, 4],
    [2, 4, 0, 2],
    [4, 2, 2, 3]
])



# 灰度级为8
histogram_8_levels = np.bincount(image_matrix.flatten(), minlength=8)

# 画图
plt.bar(range(8), histogram_8_levels, color='gray', align='center')
plt.title('Grayscale Histogram with 8 Levels')
plt.xlabel('Grayscale Value')
plt.ylabel('Pixel Count')
plt.xlim(0, 7)  # Limit x-axis to 7 for 8 gray levels (0-7)
plt.xticks(range(8))  # Set x-ticks to show each gray level
plt.show()

# Returning the histogram array for 8 gray levels for inspection
histogram_8_levels
