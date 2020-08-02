import re
import subprocess
import numpy as np

table = np.zeros((3, 3, 3))

for i in range(10000):
	result = list(map(float, re.findall(r'\d+(?:\.\d+)?', str(subprocess.run(['./hw6_2_3'], stdout = subprocess.PIPE)))))
	for i in range(3):
		for j in range(3):
			table[0][i][j] = (table[0][i][j] + result[4 + i * 3 + j])
			table[1][i][j] = (table[1][i][j] + result[13 + i * 3 + j])
			table[2][i][j] = (table[2][i][j] + result[23 + i * 3 + j])

print('after first insertion')
print('bst', table[0][0][0] / 10000, table[0][0][1] / 10000, table[0][0][2] / 10000)
print('avl', table[0][1][0] / 10000, table[0][1][1] / 10000, table[0][1][2] / 10000)
print('rb', table[0][2][0] / 10000, table[0][2][1] / 10000, table[0][2][2] / 10000)

print("after removal")
print('bst', table[1][0][0] / 10000, table[1][0][1] / 10000, table[1][0][2] / 10000)
print('avl', table[1][1][0] / 10000, table[1][1][1] / 10000, table[1][1][2] / 10000)
print('rb', table[1][2][0] / 10000, table[1][2][1] / 10000, table[1][2][2] / 10000)

print("after 2nd insertion")
print('bst', table[2][0][0] / 10000, table[2][0][1] / 10000, table[2][0][2] / 10000)
print('avl', table[2][1][0] / 10000, table[2][1][1] / 10000, table[2][1][2] / 10000)
print('rb', table[2][2][0] / 10000, table[2][2][1] / 10000, table[2][2][2] / 10000)