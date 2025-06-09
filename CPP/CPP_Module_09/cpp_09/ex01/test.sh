#!/bin/bash

echo "Running RPN Tests..."

pass_count=0
fail_count=0

remove_colors() {
  # Remove códigos ANSI (ex: \033[1;32m)
  echo "$1" | sed -r 's/\x1B\[[0-9;]*[JKmsu]//g'
}

run_test() {
  input="$1"
  expected="$2"
  raw_output=$(./RPN "$input" 2>&1)
  result=$(remove_colors "$raw_output")

  if [[ "$expected" == "Error" ]]; then
    if [[ "$result" == Error* ]]; then
      echo -e "\e[32m[PASS]\e[0m \"$input\" -> $result"
      ((pass_count++))
    else
      echo -e "\e[31m[FAIL]\e[0m \"$input\" -> Got: $result | Expected: $expected"
      ((fail_count++))
    fi
  else
    if [ "$result" == "$expected" ]; then
      echo -e "\e[32m[PASS]\e[0m \"$input\" -> $result"
      ((pass_count++))
    else
      echo -e "\e[31m[FAIL]\e[0m \"$input\" -> Got: $result | Expected: $expected"
      ((fail_count++))
    fi
  fi
}

run_test "8 9 * 9 - 9 - 9 - 4 - 1 +" "42"
run_test "7 7 * 7 -" "42"
run_test "1 2 * 2 / 2 * 2 4 - +" "0"
run_test "(1 + 1)" "Error"
run_test "3 +" "Error"
run_test "2 0 /" "Error"

echo
echo -e "\e[34mTest Summary: $pass_count passed, $fail_count failed.\e[0m"
