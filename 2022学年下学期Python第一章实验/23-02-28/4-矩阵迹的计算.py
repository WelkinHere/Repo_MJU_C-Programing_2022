'''
问题：
计算矩阵的迹
'''

import numpy as np
import random

cache = 0

inputCache = int(input("请输入要随机生成的矩阵大小："))
inputMin = int(input("请输入随机生成数字的最小范围："))
inputMax = int(input("请输入随机生成数字的最大范围："))

# 随机生成一个 5x5 的矩阵
matrix = np.random.randint(inputMin, inputMax, (5, 5))

for i in range(5):
    cache += matrix[i, i]

print("生成的矩阵：\n")
print(matrix)

print("矩阵的迹：")
print(cache)
