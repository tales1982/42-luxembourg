#!/bin/bash

echo "=== BSQ Tests ==="
echo

total=0
passed=0

for i in 1 2 3 4 5 6; do
    total=$((total + 1))
    echo "= Test $i ========================================"
    if [ -f "test${i}.stdin" ]; then
        ./programa < "test${i}.stdin" > "user_output_test${i}" 2>&1
        if [ -f "test${i}.expected" ]; then
            if diff -q "user_output_test${i}" "test${i}.expected" > /dev/null 2>&1; then
                echo "Diff OK :D"
                passed=$((passed + 1))
            else
                echo "Diff KO :("
                diff -U 3 "user_output_test${i}" "test${i}.expected" | cat -e
            fi
        else
            echo "Output:"
            cat "user_output_test${i}"
            passed=$((passed + 1))
        fi
    else
        echo "Test file not found"
    fi
    echo
done

echo "Grade: $passed/$total"
