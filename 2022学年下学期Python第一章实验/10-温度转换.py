'''
问题：
如何利用 Python 程序进行摄氏度与华氏度的转换？
'''

celsius = int(input("请输入摄氏度："))
farhenheit = celsius * 1.8 + 32

farhenheit = str(farhenheit)
print("华氏度为：" + farhenheit)