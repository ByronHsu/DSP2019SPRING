import sys
FILE1 = 'testing_answer.txt'
FILE2 = 'c_cpp/result1.txt'
pred = []
gt = []
with open(FILE1) as f:
    pred = f.read().split('\n')

with open(FILE2) as f:
    gt = f.read().split('\n')
    gt = [x.split(' ')[0] for x in gt]

count = 0
for i in range(len(pred)):
    if pred[i] == gt[i]:
        count += 1

print('acc = {}'.format(count / len(pred)))