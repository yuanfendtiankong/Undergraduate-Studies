import cv2
import numpy as np

# 二值图像数据
binary_image_data = np.array([
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0],
    [0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0],
    [0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0],
    [0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0],
    [0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0],
    [0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0],
    [0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0],
    [0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0],
    [0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
], dtype=np.uint8)

# 找到图像轮廓
contours, _ = cv2.findContours(binary_image_data, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# 提取第一个轮廓
contour = contours[0]

# 计算区域面积
area = np.sum(binary_image_data)
# area = cv2.contourArea(contour)

# 计算周长
perimeter = cv2.arcLength(contour, True)

nonzero_indices = np.nonzero(binary_image_data)

# 计算质心
cx = np.mean(nonzero_indices[1])  # 列坐标的平均值
cy = np.mean(nonzero_indices[0])  # 行坐标的平均值
# 计算外接矩形
x, y, w, h = cv2.boundingRect(contour)

# 计算圆形度
circularity = (4.0 * np.pi * area) / (perimeter ** 2)

# 计算矩形度
rectangularity = area / (w * h)

# 计算长宽比
aspect_ratio = w / h

# 打印结果
print("面积:", area)
print("周长:", perimeter)
print("质心 (cx, cy):", (cx, cy))
print("外接图形 (x, y, w, h):", (x, y, w, h))

print("圆形度:", circularity)
print("矩形度:", rectangularity)
print("长宽比", aspect_ratio)
