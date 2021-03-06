import subprocess
from pathlib import Path
import json
import re

p = Path('.')
library = list(p.glob('**/*.cpp'))
test = list(p.glob('**/*.test.cpp'))

d = {}
d['library'] = []
for l in library:
    if l not in test:
        if 'library-checker-problems' not in str(l):
            d['library'].append('/' + str(l))

d['test'] = ['/' + str(t) for t in test]

for t in test:
    ignore = False
    with open(str(t)) as f:
        s = f.read()
        if '#define IGNORE' in s:
            ignore = True

    if ignore:
        continue

    proc1 = subprocess.Popen(
        ["g++", "-I", ".", "-MD", "-MF", "/dev/stdout", "-MM",
         str(t)],
        stdout=subprocess.PIPE)
    out1, _ = proc1.communicate()
    proc2 = subprocess.Popen(
        ["sed", "1s/[^:].*: // ; s/\\\\$//"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE)
    out2, _ = proc2.communicate(input=out1)
    l = out2.decode('utf-8').split(' ')
    l.remove(str(t))
    u = [s.replace('\n', '') for s in l if s != '\n']
    v = [re.sub(r'.*\.\./', '/', s) for s in u]
    d['/' + str(t)] = v

    for s in v:
        if not s in d:
            d[s] = []
        d[s].append('/' + str(t))

for val in d.values():
    val.sort()

print(json.dumps(d, indent=2))
