'''
问题：
计算两点间曼哈顿距离
'''

inputPos1x = input("请输入第一个点的 x 坐标：")
inputPos1y = input("请输入第一个点的 y 坐标：")
inputPos2x = input("请输入第二个点的 x 坐标：")
inputPos2y = input("请输入第二个点的 y 坐标：")

inputPos1x = int(inputPos1x)
inputPos1y = int(inputPos1y)
inputPos2x = int(inputPos2x)
inputPos2y = int(inputPos2y)

result = abs(inputPos1x - inputPos2x) + abs(inputPos1y - inputPos2y)

print(result)
