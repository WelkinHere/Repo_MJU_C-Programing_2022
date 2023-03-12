'''
题目：
计算前n个自然数的阶乘之和
'''

import math

n = int(input('请输入一个正整数：'))
sum = 0

for i in range(n):
    sum += math.factorial(i)

print(sum)