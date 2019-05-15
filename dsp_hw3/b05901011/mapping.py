import sys

f_r =  open(sys.argv[1], 'r', encoding = 'big5hkscs')
data = f_r.readlines()
Map = {}
for x in data:
    w, zs = x.split()
    zs = zs.split('/')
    Map[w] = set([w])
    for z in zs:
        if z[0] not in Map:
            Map[z[0]] = set([w])
        else:
            Map[z[0]].add(w)

f_w = open(sys.argv[2], "w", encoding = 'big5hkscs')

for (a, b) in Map.items():
    s = a + ' ' + ' '.join(b) + '\n'
    f_w.write(s)