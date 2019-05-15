echo "Segment corpus.txt"
./separator_big5.pl corpus.txt > corpus_seg.txt

# for i in {1..10};
# do
#     echo "Segment testdata/$i.txt"
#     ./separator_big5.pl tmp/unseg_data/$i.txt > testdata/$i.txt;
# done