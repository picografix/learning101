n=int(input()) 
user=[]
for i in range(n):
    user.append(list(map(str,input().split()))) 
value=input() 
for j in range(n):
    if user[j][0]==value:
        sum=float(user[j][1])+float(user[j][2])+float(user[j][3])
avg=sum/3 
print("%.2f" %avg)