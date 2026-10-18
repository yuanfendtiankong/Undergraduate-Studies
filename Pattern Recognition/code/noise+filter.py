import cv2
import numpy as np

# 读取图像(灰度图像)
image = cv2.imread('D:\\PycharmProjects\\pythonProject\\Pattern Recognition\\picture\\albert-einstein.jpg', cv2.IMREAD_GRAYSCALE)

# 确保图像不为空
if image is None:
    print("图像读取失败，请检查路径。")
    exit()

# 噪声
def add_gaussian_noise(image, mean=0, sigma=25):
    """
    向图像添加高斯噪声
    :param image: 原始图像
    :param mean: 高斯噪声的均值
    :param sigma: 高斯噪声的标准差
    :return: 添加噪声后的图像
    """
    # 检查图像是否为灰度（即只有两个维度）
    if len(image.shape) == 2:
        row, col = image.shape
        # 生成高斯噪声
        gauss = np.random.normal(mean, sigma, (row, col))
        gauss = gauss.reshape(row, col)
    else:
        row, col, ch = image.shape
        # 生成高斯噪声
        gauss = np.random.normal(mean, sigma, (row, col, ch))
        gauss = gauss.reshape(row, col, ch)

    # 添加噪声并确保像素值在0到255之间
    noisy_image = image + gauss
    noisy_image = np.clip(noisy_image, 0, 255).astype(np.uint8)
    return noisy_image

# 椒盐噪声
def add_salt_and_pepper_noise(image, salt_prob=0.01, pepper_prob=0.01):
    """
    向图像添加椒盐噪声
    :param image: 输入的原始图像
    :param salt_prob: 盐（亮）噪声的比例
    :param pepper_prob: 胡椒（暗）噪声的比例
    :return: 添加噪声后的图像
    """
    # 复制图像以避免修改原始图像
    noisy_image = np.copy(image)

    # 添加盐噪声
    num_salt = np.ceil(salt_prob * image.size)
    coords = [np.random.randint(0, i - 1, int(num_salt))
              for i in image.shape]
    noisy_image[coords[0], coords[1]] = 1

    # 添加胡椒噪声
    num_pepper = np.ceil(pepper_prob * image.size)
    coords = [np.random.randint(0, i - 1, int(num_pepper))
              for i in image.shape]
    noisy_image[coords[0], coords[1]] = 0

    return noisy_image

# 均值滤波
def mean_filter(image, kernel_size=3):
    height, width = image.shape
    border = kernel_size // 2
    filtered_image = np.zeros((height, width), dtype=np.uint8)

    for y in range(border, height - border):
        for x in range(border, width - border):
            sum_pixels = np.sum(image[y - border:y + border + 1, x - border:x + border + 1])
            filtered_image[y, x] = sum_pixels // (kernel_size * kernel_size)
    return filtered_image

# 中值滤波
def median_filter(image, kernel_size=3):
    height, width = image.shape
    border = kernel_size // 2
    filtered_image = np.zeros((height, width), dtype=np.uint8)

    for y in range(border, height - border):
        for x in range(border, width - border):
            # 获取邻域内的像素值
            kernel = image[y - border:y + border + 1, x - border:x + border + 1]
            median_value = np.median(kernel)
            filtered_image[y, x] = int(median_value)
    return filtered_image

# 库函数 均值滤波
def apply_mean_filter(image, kernel_size=(5, 5)):
    """
    对图像应用均值滤波
    :param image: 输入图像
    :param kernel_size: 滤波器的大小
    :return: 滤波后的图像
    """
    return cv2.blur(image, kernel_size)

# 库函数 中值滤波
def apply_median_filter(image, kernel_size=5):
    """
    对图像应用中值滤波
    :param image: 输入图像
    :param kernel_size: 滤波器的大小，必须是奇数
    :return: 滤波后的图像
    """
    return cv2.medianBlur(image, kernel_size)


# 高斯噪声，均值滤波
gaosi_image = add_gaussian_noise(image)
gaosi_image_mean_filter = mean_filter(gaosi_image)
# gaosi_image_mean_filter = apply_mean_filter(gaosi_image)

# 椒盐噪声，中值滤波
salt_and_pepper_noise_img = add_salt_and_pepper_noise(image)
salt_and_pepper_noise_mean_filter = median_filter(salt_and_pepper_noise_img)
# salt_and_pepper_noise_mean_filter = apply_mean_filter(salt_and_pepper_noise_img)


# 保存一下
# noise
save_path = '/Pattern Recognition/picture/noise/'
cv2.imwrite(save_path + 'gaosi_image.jpg', gaosi_image)
cv2.imwrite(save_path + 'gaosi_image_mean_filter.jpg', gaosi_image_mean_filter)
cv2.imwrite(save_path + 'salt_and_pepper_noise.jpg', salt_and_pepper_noise_img)
cv2.imwrite(save_path + 'salt_and_pepper_noise_median_filter.jpg', salt_and_pepper_noise_mean_filter)




