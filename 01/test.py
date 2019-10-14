import subprocess

result = subprocess.run(['./main', '2+2'], stdout=subprocess.PIPE)
assert((result.stdout)==b'4')
assert(result.returncode == 0)
print('test 1 done')


result = subprocess.run(['./main', '5+2'], stdout=subprocess.PIPE)
assert((result.stdout)==b'7')
assert(result.returncode == 0)
print('test 2 done')

result = subprocess.run(['./main', '2+2+'], stdout=subprocess.PIPE)
assert(result.returncode != 0)
print('test 3 done')

result = subprocess.run(['./main', '2+2*2'], stdout=subprocess.PIPE)
assert((result.stdout)==b'6')
assert((result.returncode)==0)
print('test 4 done')

result = subprocess.run(['./main', '(2+2)*2'], stdout=subprocess.PIPE)
assert((result.stdout)==b'8')
assert((result.returncode)==0)
print('test 5 done')

result = subprocess.run(['./main', '(-2+2)*2'], stdout=subprocess.PIPE)
assert((result.stdout)==b'0')
assert((result.returncode)==0)
print('test 6 done')

result = subprocess.run(['./main', '(1-2+2)*2+3/10*1'], stdout=subprocess.PIPE)
assert((result.stdout)==b'2')
assert((result.returncode)==0)
print('test 7 done')

result = subprocess.run(['./main', '(----1-2+2)*2+3/10*1'], stdout=subprocess.PIPE)
assert((result.stdout)==b'2')
assert((result.returncode)==0)
print('test 8 done')


result = subprocess.run(['./main', '----1-2+2)*2+3/10*1'], stdout=subprocess.PIPE)
assert((result.returncode)!=0)
print('test 9 done')


result = subprocess.run(['./main', '2+*2'], stdout=subprocess.PIPE)
assert((result.returncode)!=0)
print('test 10 done')

result = subprocess.run(['./main', '(2*(2+2))*3+(4*(-1)+1)'], stdout=subprocess.PIPE)
assert((result.returncode)==0)
assert((result.stdout)==b'21')
print('test 11 done')

result = subprocess.run(['./main', "2 + 3 * 4 - -2"], stdout=subprocess.PIPE)
assert((result.returncode)==0)
assert((result.stdout)==b'16')
print('test 12 done')
