#!/bin/bash
# E2E_test.sh

# Compile program
gcc ~/Project-Profun/project/project.c ~/Project-Profun/project/main.c -o patient_app

# Run program with test input and save to actual_output.txt
./patient_app < ~/Project-Profun/tests/test_input.txt > ~/Project-Profun/tests/actual_output.txt

# Compare actual output with expected output
if diff -q ~/Project-Profun/tests/actual_output.txt ~/Project-Profun/tests/expect_output.txt > /dev/null; then
    echo "✅ E2E Test Passed!"
else
    echo "❌ E2E Test Failed!"
    diff -u ~/Project-Profun/tests/expect_output.txt ~/Project-Profun/tests/actual_output.txt
fi
