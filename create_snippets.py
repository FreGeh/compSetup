# credit - https://github.com/the-tourist/algo
# use with 'python3 create_snippets.py'

import os
import json
import sys

snippets = {}

for subdir in os.walk('data'):
  if subdir[0] == '.' or '.git' in subdir[0]:
    continue
  for filename in subdir[2]:
    print(f'found {filename}', file=sys.stderr)
    if filename.count('.') != 1:
      print(f'found more than one dot in {filename}', file=sys.stderr)
      continue
    name, extension = filename.split('.')
    if (name == '' or extension == ''): continue
    if extension != 'cpp': continue

    if name in snippets:
      print(f'error: duplicate snippet {name}', file=sys.stderr)
      exit(0)

    path = subdir[0] + '/' + filename
    with open(path, 'r') as f:
      snippet = {
        "prefix": name,
        "body": [line.rstrip() for line in f.readlines()],
        "description": name
      }
      snippets[name] = snippet

    print(f'generated snippet {name}', file=sys.stderr)

os.makedirs(".vscode", exist_ok=True)
with open(".vscode/cpp.code-snippets", "w") as f:
    f.write(json.dumps(snippets, indent=2))

print('done', file=sys.stderr)