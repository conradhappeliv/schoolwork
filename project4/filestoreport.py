# Conrad Appel
# MATH 3316
# 2 Dec 2014

import glob
import os
from subprocess import Popen, PIPE

outfile = open('./reportcode.txt', 'w+')

outfile.write('Appendix A: Code Output\n')
outfile.write('-----------------------\n\n')
for app in ['./test_int.out', './test_adapt.out', './carbon.out', './application.out']:
    print app
    outfile.write('`' + app + '`\n\n')
    process = Popen(app, stdout=PIPE)
    for line in iter(process.stdout.readline, b''):
        outfile.write('    '+line)
    outfile.write('\n\n\n')


outfile.write('Appendix B: Code\n')
outfile.write('----------------\n\n')
for filename in sorted(glob.glob('./*.*')):
    if not (filename.endswith('.py') or filename.endswith('.cpp')):
        continue
    if filename == './mat.cpp' or filename == './filestoreport.py' or filename == './composite_Gauss2.cpp':
        continue
    print filename
    outfile.write('`' + filename + '`\n\n')
    with open(filename) as f:
        line = f.readline()
        while line != '':
            outfile.write('    '+line)
            line = f.readline()
    outfile.write('\n\n\n')

outfile.write('Appendix C: Plots\n')
outfile.write('-----------------\n\n')
counter = 1
for filename in sorted(glob.glob('./*.png')):
    print filename
    outfile.write('![](' + os.getcwd() + filename[1:] + ')\n')
    outfile.write('Figure ' + str(counter) + ':\n\n')
    counter += 1

outfile.close()