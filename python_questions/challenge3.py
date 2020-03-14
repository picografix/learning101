n=int(input()) 
arr=[] 
def insert():
    arr.insert(int(ar[1]),int(ar[2]))
def append():
    arr.append(int(ar[1]))
def remove():
    arr.remove(int(ar[1]))
for i in range(n): 
    ar=list(map(str,input().split()))
    if ar[0]=='insert':
       insert()
    elif ar[0]=='append':
        append()
    elif ar[0]=='pop':
        arr.pop()
    elif ar[0]=='print':
        print(arr)
    elif ar[0]=='reverse':
        arr.reverse()
    elif ar[0]=='remove':
       remove()
    elif ar[0]=='sort':
        arr.sort()