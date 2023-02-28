'''
问题：
用户输入一个三位自然数，计算并输出其佰位、十位和个位上的数字。
'''

inputCache = input("请输入一个三位自然数：")
inputCache = int(inputCache)
if inputCache > 999:
    print("Error.")
if inputCache < 100:
    print("Error.")
else:
    storage = None
    i = 0
    while i < 3:
        storage = inputCache % 10
        print(storage)
        inputCache = inputCache // 10
        i += 1
