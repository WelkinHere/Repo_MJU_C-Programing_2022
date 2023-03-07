'''
题目：
计算给定数据的几何平均数，即 n 个数字连乘结果的 n 次方根
'''

data = [1, 2, 3, 4, 5, 6, 7]

total= 1
for i in data:
    total *= i

print(pow(total, 1/len(data)))