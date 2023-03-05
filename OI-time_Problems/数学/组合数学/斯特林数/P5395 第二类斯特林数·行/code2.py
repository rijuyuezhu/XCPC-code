P = 167772161
phi = P-1
a = [2, 5]
def check(x) :
    if pow(x, phi, P) != 1 :
        return False
    for t in a :
        if pow(x, phi // t, P) == 1 :
            return False
    return True

for i in range(1, P) :
    if check(i) :
        print(i)
        break
