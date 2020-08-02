import sys 
words = ['auto', 'bool', 'case', 'char', 'const', 'continue', 'default', 'do', 'double', 'else', 'enum', 'extern', 'float', 'for', 'goto', 'if', 'int', 'long', 'register', 'return', 'short', 'signed', 'sizeof', 'static', 'struct', 'switch', 'template', 'union', 'unsigned', 'void', 'volatile', 'while']
conversion = {'b': 2, 'd': 4, 'f': 6, 'g': 7, 'h': 8, 'j': 10, 'k': 11, 'l': 12, 'n': 14, 'p': 16, 'q': 17, 't': 20, 'v': 22, 'w': 23, 'y': 25, 'z': 5}

answer = {}
for o in range(5):
	print(o)
	for u in range(5):
		for x in range(5):		
			for i in range(5):
				for a in range(5):
					for m in range(5):
						for c in range(5):
							for s in range(5):
								for i in range(5):
									for e in range(5):
										for r in range(5):
											for word in words:
												sum = 0
												for ch in word:
													if ch in conversion.keys():
														sum += conversion[ch]
													elif ch == 'o':
														sum += o
													elif ch == 'i':
														sum += i
													elif ch == 'a':
														sum += a
													elif ch == 'm':
														sum += m
													elif ch == 'c':
														sum += c
													elif ch == 's':
														sum += s
													elif ch == 'i':
														sum += i
													elif ch == 'e':
														sum += e
													elif ch == 'r':
														sum += r
												if sum % 32 in answer.keys():
													answer.clear()
													break
												answer[sum % 32] = word

											if len(answer) == 32:
												print(o, i, a, m, c, s, i, e, r, answer)
												sys.exit(0)
											else:
												answer.clear()


