import sklearn.metrics as metrics
import joblib
from sklearn import datasets
from skimage.feature import hog
from sklearn.svm import LinearSVC
import numpy as np
import os, math, cv2, struct
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 设置字体为SimHei支持中文显示
plt.rcParams['axes.unicode_minus'] = False  # 正确显示负号

def load_mnist(path, labelfile, datafile):
    label_path = os.path.join(path, labelfile)
    image_path = os.path.join(path, datafile)

    with open(label_path, 'rb') as lbpath:
        magic, n = struct.unpack('>II', lbpath.read(8))
        labels = np.fromfile(lbpath, dtype=np.uint8)
    with open(image_path, 'rb') as imgpath:
        magic, num, rows, cols = struct.unpack('>IIII', imgpath.read(16))
        images = np.fromfile(imgpath, dtype=np.uint8).reshape(len(labels), 784)

    return images, labels

# 修正路径问题，使用原始字符串或双反斜杠
r = r"D:\PycharmProjects\pythonProject\Pattern Recognition\page\MNIST\raw"

features, labels = load_mnist(r, 'train-labels-idx1-ubyte', 'train-images-idx3-ubyte')
features = features[0:6000, :]
labels = labels[0:6000]
print('训练集行数：%d，列数：%d' % (features.shape[0], features.shape[1]))

x = np.array(features[0, :])
x = x.reshape([28, 28])
plt.imshow(x, cmap="gray_r")
plt.show()




r = r"D:\PycharmProjects\pythonProject\Pattern Recognition\page\MNIST\raw"
testfeatures0, testlabels0 = load_mnist(r, 't10k-labels-idx1-ubyte', 't10k-images-idx3-ubyte')
testfeatures = testfeatures0[0:6000, :]
testlabels = testlabels0[0:6000]
list_hog_fd = []
for feature in features:
    fd = hog(feature.reshape((28, 28)),  # 提取HOG特征
             orientations=9,
             pixels_per_cell=(14, 14),
             cells_per_block=(1, 1),
             visualize=False)
    list_hog_fd.append(fd)
hog_features = np.array(list_hog_fd, 'float64')
# print(hog_features.shape)

# 提取测试集HOG特征
list_hog_tfd = []
for testfeature in testfeatures:
    tfd = hog(testfeature.reshape((28, 28)),  # 提取HOG特征
              orientations=9,
              pixels_per_cell=(14, 14),
              cells_per_block=(1, 1),
              visualize=False)
    list_hog_tfd.append(tfd)
hog_testfeatures = np.array(list_hog_tfd, 'float64')

# 使用SVM支持向量机分类器进行分类
# 建立并训练SVM模型
svm_model = LinearSVC()  # 建立SVM模型
svm_model.fit(hog_features, labels)  # 训练SVM模型

# 测试SVM模型测试单个图像，输出结果为图像所属类别
testnumber = svm_model.predict(hog_testfeatures)
SVMscore = svm_model.score(hog_testfeatures, testlabels)
# print("测试集第一个图像数字是:", testnumber[0])
# print("HOG+SVM分类精度:", SVMscore)  # 平均分类精度




print("---------混淆矩阵------------")
print(metrics.confusion_matrix(testlabels, testnumber))  # 混淆矩阵
print("--------分类评估报告----------")
print(metrics.classification_report(testlabels, testnumber))