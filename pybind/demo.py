import sys
sys.path.append("build")

import expressions
import numpy as np

x = expressions.Variable("x")
y = expressions.Variable("y")
print(x, y)

e1 = x + y
print(e1.getValue())
e2 = e1 + 3
print(e2.getValue())
e3 = e1 + (x + 1 + y)
print(e3.getValue())

xy = expressions.NewVariables()
print(xy)
xyarr = np.array([xy[i] for i in range(len(xy))])
print(xyarr)
print(np.sum(xyarr).getValue())

xyarr_plus_one = xyarr + 1
print([x.getValue() for x in xyarr_plus_one])
