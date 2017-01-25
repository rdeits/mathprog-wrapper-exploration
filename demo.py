import sys
sys.path.append("build")

import example
import numpy as np

# print(example.getInverse(np.array([[1,2],[3,4]])))

c = example.MyClass("hello")
print(c)
print(c.getName())

v = example.factory()
print(v)
vec = np.array([v[i] for i in range(len(v))])
print(vec)
print(np.sum(vec).getName())

print(v[0])
print(v[0].getName())

x = np.array([1.0, 2, 3])
print(example.mysum(x))

myclass_array = np.array([example.MyClass("hello"), example.MyClass("world")])
print(np.sum(myclass_array).getName())

