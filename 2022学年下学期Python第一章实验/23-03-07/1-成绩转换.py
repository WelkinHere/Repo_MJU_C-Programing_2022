'''
题目：
利用多分支选择结构将成绩从百分制转换为等级制。
'''

score = int(input('请输入成绩：'))

if score >= 90:
    print("A    优秀")
elif score >= 80:
    print("B    良好")
elif score >= 70:
    print("C    中等")
elif score >= 60:
    print("D    及格")
else:
    print("F    不及格")