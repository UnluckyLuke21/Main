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

        if val is a:
            aRef.append(key)
        if val is b:
            bRef.append(key)

    if len(aRef) == 0:
        raise ValueError('cannot swap first argument')
    if len(bRef) == 0:
        raise ValueError('cannot swap second argument')

    for ref in aRef:
        globals()[ref] = b
    for ref in bRef:
        globals()[ref] = a


o1 = Obj1(1,2)
o2 = Obj2(3)

print(o1.a, o1.b)
print(o2.x)

swapGlobal(o1, o2)

print(o1.x)
print(o2.a, o2.b)