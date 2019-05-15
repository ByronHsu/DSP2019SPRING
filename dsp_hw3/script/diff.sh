for i in {1..10};
do
    echo "Diff $i.txt"
    colordiff result1/$i.txt result2/$i.txt
done

for i in {1..10};
do
    echo "Diff $i.txt"
    colordiff result3/$i.txt result2/$i.txt
done