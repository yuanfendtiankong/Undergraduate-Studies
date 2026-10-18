import numpy as np
from skimage.metrics import structural_similarity as ssim


def calculate_similarity_metrics(f1, f2):
    """
    计算两幅图像之间的MSE、PSNR和SSIM。

    参数:
    - f1: 第一幅图像的像素矩阵。
    - f2: 第二幅图像的像素矩阵。

    返回:
    - mse: 均方误差。
    - psnr: 峰值信噪比。
    - ssim: 结构相似性指数。
    """
    # 计算MSE
    mse = np.mean((f1 - f2) ** 2)

    # 计算PSNR，最大像素值假定为3（由于灰度级L=4）
    max_i = 3
    psnr = 10 * np.log10(max_i ** 2 / mse)

    # 给定的参数
    K1 = 0.01
    K2 = 0.03
    L = 4  # 灰度级L=4，但是对于SSIM计算中使用的L应该是最大像素值，这里是3
    LL = L - 1

    # 计算C1和C2
    C1 = (K1 * LL) ** 2
    C2 = (K2 * LL) ** 2
    C3 = C2 / 2

    ## 均值
    Ux = np.mean(f1)
    Uy = np.mean(f2)
    ## 标准差
    s1 = np.std(f1, ddof=1)
    s2 = np.std(f2, ddof=1)
    ## 协方差
    covariance = np.sum((f1 - Uy) * (f2 - Ux)) / (4 * 4 - 1)

    L_value = ((2 * Ux * Uy) + C1) / (Ux ** 2 + Uy ** 2 + C1)
    C_value = (2 * s1 * s2 + C2) / (s1 ** 2 + s2 ** 2 + C2)
    S_value = (covariance + C3) / (s1 * s2 + C3);

    ssim = L_value * C_value * S_value

    return mse, psnr, ssim


# 定义图像f1和f2
f1 = np.array([
    [1, 1, 1, 1],
    [1, 0, 2, 1],
    [1, 2, 0, 1],
    [1, 1, 1, 1]
])

f2 = np.array([
    [1, 1, 1, 1],
    [1, 1, 1, 1],
    [1, 1, 1, 1],
    [1, 1, 1, 1]
])

# 计算并打印相似度指标
mse, psnr, ssim = calculate_similarity_metrics(f1, f2)
print(f"MSE: {mse:.4f}")
print(f"PSNR: {psnr:.4f} dB")
print(f"SSIM: {ssim:.4f}")
