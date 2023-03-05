P = 612321329
B = 21313
while True :
    s = input()
    ans = 0
    for ch in s :
        ans = (ans * B + ord(ch)) % P
    print(ans)
