Ans1-echo "HELLO"


Ans2-for a in {1..50}
do
    echo $((2*$a-1))
done

Ans3-read PERSON
echo "Welcome $PERSON"

Ans4-for a in {1..50}
do
    echo $a
done

Ans5-read x
read y
echo $((x+y))
echo $((x-y))
echo $((x*y))
echo $((x/y))

Ans6-read  x
read  y
if [ $x -gt $y ]
then
    echo "X is greater than Y"
elif [ $x -lt $y ]
then
    echo "X is less than Y"
else
    echo "X is equal to Y"
fi

Ans7-read  a
if [[ $a == Y || $a == y ]]
then
    echo "YES"
else
    echo "NO"
fi

Ans8-read a
read b
read c
if  [[ $a != $b && $b != $c ]]
then
    echo "SCALENE"
elif [[ ($a == $b && $b != $c && $a != $c) || ($a != $b && $b != $c && $a == $c) || ($a != $b && $b == $c && $a != $c) ]]
then
    echo "ISOSCELES"
else
    echo "EQUILATERAL"
fi

Ans9-read n
printf "%.3f\n" `echo "$n" | bc -l`


Ans10-read n
sum=0
for ((i=1;i<=n;i++))
do
    read x
    sum=$((sum+x))
done
avg=$sum/$n
printf "%0.3f" `echo "$avg" | bc -l`
