n=int(input())
valu=[]
name=[]
for i in range(n):
    name1=input()
    no=float(input())
    name.append(name1)
    valu.append(no)
    lowest = valu[0] 
    lowest2= None
    ans=[]
    for item in valu[1:]:      
        if item < lowest:  
            lowest2 = lowest 
            lowest = item  
        elif lowest2 == None or lowest2 > item:  
            lowest2 = item 
    for item in range(len(valu)):
        if(valu[item]==lowest2):
            ans.append(name[item])
ans.sort()            
for item in range(len(ans)):
    print(ans[item])        
