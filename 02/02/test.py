import subprocess

result = subprocess.run(['./main', '100', '10'], stdout=subprocess.PIPE)
assert((result.stdout)==b'nullptr')
assert(result.returncode == 0)
print('test 1 done')


result = subprocess.run(['./main', '52', '123'], stdout=subprocess.PIPE)
assert((result.stdout)==b'52')
assert(result.returncode == 0)
print('test 2 done')

result = subprocess.run(['./main', '100', '10000', '1'], stdout=subprocess.PIPE)
print(result.stdout)
# assert(result.returncode != 0)
print('test 3 done')