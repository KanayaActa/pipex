#!/bin/bash

# tests.sh

# Exit immediately if a command exits with a non-zero status.
set -e

# Colors for better readability
GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m" # No Color

# Path to pipex executable
PIPEX=./pipex

# Temporary files for testing
TMP_OUT_PIPEX="tmp_pipex_out"
TMP_OUT_SHELL="tmp_shell_out"

# Temporary files for error messages
TMP_ERR_PIPEX="tmp_pipex_err"
TMP_ERR_SHELL="tmp_shell_err"

# Function to clean up temporary files
cleanup() {
    rm -f "$TMP_OUT_PIPEX" "$TMP_OUT_SHELL" "$TMP_ERR_PIPEX" "$TMP_ERR_SHELL" infile
}
trap cleanup EXIT

# Create 'infile' with sample content
echo "This is a sample input file for pipex testing." > infile
echo "pattern line 1" >> infile
echo "pattern line 2" >> infile
echo "another line without pattern" >> infile

# Function to run a single test case
# Arguments:
#   $1: Description of the test
#   $2: Command to run with pipex
#   $3: Equivalent shell command
run_test() {
    local description="$1"
    local pipex_cmd="$2"
    local shell_cmd="$3"

    echo -e "${description}..."

    # Run pipex
    eval "$pipex_cmd" 1> "$TMP_OUT_PIPEX" 2> "$TMP_ERR_PIPEX"
    PIPEX_EXIT=$?

    # Run shell command
    eval "$shell_cmd" 1> "$TMP_OUT_SHELL" 2> "$TMP_ERR_SHELL"
    SHELL_EXIT=$?

    # Compare exit statuses
    if [ "$PIPEX_EXIT" -ne "$SHELL_EXIT" ]; then
        echo -e "${RED}✗ Exit status mismatch (pipex: $PIPEX_EXIT, shell: $SHELL_EXIT)${NC}"
        echo "Pipex stderr:"
        cat "$TMP_ERR_PIPEX"
        echo "Shell stderr:"
        cat "$TMP_ERR_SHELL"
        exit 1
    fi

    # Compare stdout
    if ! diff -q "$TMP_OUT_PIPEX" "$TMP_OUT_SHELL" > /dev/null; then
        echo -e "${RED}✗ Output mismatch${NC}"
        echo "Differences in stdout:"
        diff "$TMP_OUT_PIPEX" "$TMP_OUT_SHELL"
        exit 1
    fi

    # Compare stderr
    if ! diff -q "$TMP_ERR_PIPEX" "$TMP_ERR_SHELL" > /dev/null; then
        echo -e "${RED}✗ Stderr mismatch${NC}"
        echo "Differences in stderr:"
        diff "$TMP_ERR_PIPEX" "$TMP_ERR_SHELL"
        exit 1
    fi

    echo -e "${GREEN}✓ Passed${NC}"
}

# Test Cases

echo -e "${GREEN}=== Basic Functionality Tests ===${NC}"

# Test 1: Simple ls | wc
run_test "Test 1: ls | wc" \
    "$PIPEX infile \"ls -l\" \"wc -l\" $TMP_OUT_PIPEX" \
    "< infile ls -l | wc -l > $TMP_OUT_SHELL"

# Test 2: grep existing pattern | wc -w
run_test "Test 2: grep 'pattern' | wc -w" \
    "$PIPEX infile \"grep 'pattern'\" \"wc -w\" $TMP_OUT_PIPEX" \
    "< infile grep 'pattern' | wc -w > $TMP_OUT_SHELL"

echo -e "${GREEN}=== Error Handling Tests ===${NC}"

# Test 3: Non-existent infile
run_test "Test 3: Non-existent infile" \
    "$PIPEX nonexistent \"ls -l\" \"wc -l\" $TMP_OUT_PIPEX" \
    "< nonexistent ls -l | wc -l > $TMP_OUT_SHELL"

# Test 4: Invalid command
run_test "Test 4: Invalid command" \
    "$PIPEX infile \"invalidcmd\" \"wc -l\" $TMP_OUT_PIPEX" \
    "< infile invalidcmd | wc -l > $TMP_OUT_SHELL"

# Test 5: Permission denied for outfile
echo -e "${GREEN}=== Test 5: Permission denied for outfile ===${NC}"

# Create a file and remove write permissions
touch tmp_no_write
chmod -w tmp_no_write

echo "Running Test 5: Permission denied for outfile..."

# Execute pipex
$PIPEX infile "ls -l" "wc -l" tmp_no_write 1> "$TMP_OUT_PIPEX" 2> "$TMP_ERR_PIPEX"
PIPEX_EXIT=$?

# Execute shell command
< infile ls -l | wc -l > tmp_no_write 1> "$TMP_OUT_SHELL" 2> "$TMP_ERR_SHELL"
SHELL_EXIT=$?

# Compare exit statuses
if [ "$PIPEX_EXIT" -ne "$SHELL_EXIT" ]; then
    echo -e "${RED}✗ Exit status mismatch (pipex: $PIPEX_EXIT, shell: $SHELL_EXIT)${NC}"
    echo "Pipex stderr:"
    cat "$TMP_ERR_PIPEX"
    echo "Shell stderr:"
    cat "$TMP_ERR_SHELL"
    # Restore permissions and clean up before exiting
    chmod +w tmp_no_write
    rm tmp_no_write
    exit 1
fi

# Compare stdout
if ! diff -q "$TMP_OUT_PIPEX" "$TMP_OUT_SHELL" > /dev/null; then
    echo -e "${RED}✗ Output mismatch${NC}"
    echo "Differences in stdout:"
    diff "$TMP_OUT_PIPEX" "$TMP_OUT_SHELL"
    # Restore permissions and clean up before exiting
    chmod +w tmp_no_write
    rm tmp_no_write
    exit 1
fi

# Compare stderr
if ! diff -q "$TMP_ERR_PIPEX" "$TMP_ERR_SHELL" > /dev/null; then
    echo -e "${RED}✗ Stderr mismatch${NC}"
    echo "Differences in stderr:"
    diff "$TMP_ERR_PIPEX" "$TMP_ERR_SHELL"
    # Restore permissions and clean up before exiting
    chmod +w tmp_no_write
    rm tmp_no_write
    exit 1
fi

echo -e "${GREEN}✓ Test 5 Passed${NC}"

# Restore permissions and clean up
chmod +w tmp_no_write
rm tmp_no_write

echo -e "${GREEN}=== All tests passed successfully! ===${NC}"
