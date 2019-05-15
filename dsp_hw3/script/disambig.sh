for i in {1..10};
do
    echo "Disambig testdata/$i.txt to result/$i.txt"
    ./srilm-1.5.10/bin/macosx/disambig -text testdata/$i.txt -map ZhuYin-Big5.map -lm bigram.lm -order 2 > result1/$i.txt;
done