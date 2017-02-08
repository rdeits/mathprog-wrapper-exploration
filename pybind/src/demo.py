import sys
sys.path.append("../build/pybind-demo-prefix/src/pybind-demo-build")

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
print(np.sum(xy).getValue())
print(expressions.NumVariables(xy))

xy_plus_one = xy + 1
print([x.getValue() for x in xy_plus_one])

xy_two = expressions.TwoNewVariables()
print(xy_two)
print(expressions.SumTwoVariables(xy_two))
