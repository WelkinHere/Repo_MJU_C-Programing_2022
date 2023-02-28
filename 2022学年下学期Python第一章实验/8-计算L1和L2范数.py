'''
问题：
计算向量的 L1 和 L2 范数
'''

n = int(input('请输入向量的维数：'))
result1 = 0
result2 = 0

for i in range(n):
    print_i = str(i + 1)
    cache = int(input("请输入第" + print_i + "维的距离："))
    result1 += abs(cache)
    result2 += pow(cache, 2)

result2 = pow(result2, 0.5)

print_result1 = str(result1)
print_result2 = str(result2)
print("L1: " + print_result1)
print("L2: " + print_result2)
