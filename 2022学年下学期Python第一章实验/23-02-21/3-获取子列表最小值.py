'''
题目：
获取子列表最小值
'''

data = [1, 5 ,6, 7, 5, 2, 3]
cacheMin = 9999999999999999999

for cache in data:
    if cacheMin > cache:
        cacheMin = cache

print(cacheMin)