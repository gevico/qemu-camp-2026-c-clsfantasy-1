#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/../exercises/20_mybash"

cat > /tmp/mybash_mytrans.txt <<'EOF'
Code empowers individuals to be creators in
EOF

cat > /tmp/mybash_mywc.txt <<'EOF'
and and and and and and and and and and and the the the the the the the the the the skilled just just just
EOF

printf '%s
' \
  'myfile bin/mybash' \
  'myfile obj/myfile/myfile.o' \
  'mysed s/unix/linux/ "unix is opensource. unix is free os."' \
  'mytrans /tmp/mybash_mytrans.txt' \
  'mywc /tmp/mybash_mywc.txt' \
  'exit' | ./bin/mybash
