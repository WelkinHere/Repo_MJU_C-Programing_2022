'''
题目：
统计一个字符中的每一个字符在另一个字符串中出现的次数
'''

string1 = 'asd'
string2 = 'asdqweasdqwasdqwe'
cacheNum = 0

for cache1 in string1:
    for cache2 in string2:
        if cache1 == cache2:
            cacheNum += 1
    print(cache1, ':', cacheNum)
    cacheNum = 0