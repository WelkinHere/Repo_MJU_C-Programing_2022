'''
问题：
鸡兔同笼问题。假设共有鸡、兔30只，脚90只，问鸡、兔各有多少只？
'''

sumItem = 30
sumFeet = 90

for i in range(30):
    if 2 * i + 4 * (30 - i) == 90:
        print("鸡有%d只，兔有%d只" % (i, 30 - i))
        break