def count_substring(string, sub_string):
    t=len(string)
    c=0;
    for i in range(t+1):
        for j in range(i,t+1):
            if string[i:j] == sub_string:
                c=c+1

    return c

if __name__ == '__main__':
    string = input().strip()
    sub_string = input().strip()
    
    count = count_substring(string, sub_string)
    print(count)