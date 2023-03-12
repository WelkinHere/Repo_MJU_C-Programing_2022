'''
题目：
判断一个数是否为素数
'''

num = int(input('请输入一个正整数：'))
flag = 0

for i in range(2, num - 1):
    if num % i == 0:
        print("%d不是素数" % num)
        flag = 1
        break
    
if flag == 0:
    print("%d是素数" % num)