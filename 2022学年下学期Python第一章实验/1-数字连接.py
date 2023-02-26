'''
题目：
把列表中若干介于 [0, 9] 之间的数字连接成为大整数，前面的数字作为高位，后面的数字作为低位。
'''

allNum = [3, 6, 5, 4, 8, 7]
total = 0

for cache in allNum:
    total *= 10
    total += cache

print(total)