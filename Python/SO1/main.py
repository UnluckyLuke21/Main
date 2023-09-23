class Obj1:

    def __init__(self, a, b):
        self.a = a
        self.b = b

    def sum(self):
        return self.a+self.b

class Obj2:

    def __init__(self, x):
        self.x = x

    def power(self, p):
        return self.x**p

#----------------------------------

def swapGlobal(a, b):
    aRef = []
    bRef = []

    for key, val in globals().items():
        print(f"Key: {key}, Val: {val}")


o1 = Obj1(1,2)
o2 = Obj2(3)

swapGlobal(o1, o2)