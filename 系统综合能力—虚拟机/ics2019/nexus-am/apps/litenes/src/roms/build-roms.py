#!/usr/bin/env python3

import os

roms = []

for (root, dirs, files) in os.walk('rom'):
  for f in files:
    if f.endswith('.nes'):
      name = f.split('.')[0]
      if not os.path.exists('gen/%s.c' % (name)):
        os.system('xxd -i "%s/%s" > "gen/%s.c"' % (root, f, name))
      roms.append(name)

for (root, dirs, files) in os.walk('gen'):
  for f in files:
    if f.endswith('.c') and f.split('.')[0] not in roms:
      os.remove('%s/%s' % (root, f))

def h_file():
  for name in roms:
    yield 'extern unsigned char rom_%s_nes[];' % (name)
  yield '''
struct rom {
  const char *name;
  void *body;
};

struct rom roms[] = {'''
  for name in roms:
    yield '  { .name = "%s", .body = rom_%s_nes, },' % (name, name)
  yield '};'

  yield 'int nroms = %d;' % (len(roms))


with open('gen/roms.h', 'w') as fp:
  for line in h_file():
    fp.write(line)
    fp.write('\n')
