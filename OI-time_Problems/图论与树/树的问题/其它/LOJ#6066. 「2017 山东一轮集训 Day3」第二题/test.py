def isPrime(x) :
    i = 2
    while i * i <= x :
        if x % i == 0 :
            return False
        i = i + 1
    return True

if __name__ == '__main__' :
    t = int(input())
    while True :
        if isPrime(t) :
            print(t)
            break
        t = t + 1
