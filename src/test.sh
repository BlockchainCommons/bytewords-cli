#!/bin/bash

# Echo any provided arguments.
# [ $# -gt 0 ] && echo "#:$# 1:$1 2:$2 3:$3"

BYTEWORDS="${1:-bytewords}"

test1()
{
  assertEquals $'fund inch jazz jazz jowl back each mint epic calm' \
    "$(${BYTEWORDS} -o standard $'Hello\n')"

  assertEquals $'fund-inch-jazz-jazz-jowl-back-each-mint-epic-calm' \
    "$(${BYTEWORDS} -o uri $'Hello\n')"

  assertEquals $'fdihjzjzjlbkehmteccm' \
    "$(${BYTEWORDS} -o minimal $'Hello\n')"

  # shunit2 trims the newline from the end of the result we compare against
  assertEquals $'Hello' \
    "$(${BYTEWORDS} -o bin $'Hello\n')"

  assertEquals $'48656c6c6f0a' \
    "$(${BYTEWORDS} -o hex $'Hello\n')"
}

test2()
{
  assertEquals $'fund inch jazz jazz jowl back each mint epic calm' \
    "$(${BYTEWORDS} -i minimal -o standard fdihjzjzjlbkehmteccm)"

  assertEquals $'fund-inch-jazz-jazz-jowl-back-each-mint-epic-calm' \
    "$(${BYTEWORDS} -i minimal -o uri fdihjzjzjlbkehmteccm)"

  assertEquals $'fdihjzjzjlbkehmteccm' \
    "$(${BYTEWORDS} -i minimal -o minimal fdihjzjzjlbkehmteccm)"

  # shunit2 trims the newline from the end of the result we compare against
  assertEquals $'Hello' \
    "$(${BYTEWORDS} -i minimal -o bin fdihjzjzjlbkehmteccm)"

  assertEquals $'48656c6c6f0a' \
    "$(${BYTEWORDS} -i minimal -o hex fdihjzjzjlbkehmteccm)"
}

# Eat all command-line arguments before calling shunit2.
shift $#
if [ "$(uname)" == "Darwin" ]; then
. /usr/local/bin/shunit2
elif [ "$(uname)" == "Linux" ]; then
# Linux
. shunit2
# TODO no shunit2 on windows/msys2/mingw64 platform
fi
