'''
题目：
已知三角形两边及其夹角，求第三边长
'''
import numpy as np

edge1 = 3
edge2 = 4
degree = 90

edge3 = pow(pow(edge1, 2) + pow(edge2, 2) - 2 * edge1 * edge2 * np.cos(degree * np.pi / 180), 0.5)

print(edge3)