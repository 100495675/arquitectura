run_test() {
    local test_function=$1
    local test_name="$test_function"
    local dir=$(dirname $0)
    echo "Running test: $test_name"
    if $test_function "$test_name" "$dir"; then
        echo "Test passed: $test_name"
    else
        failed_tests+=("$test_name")
    fi
    echo
}

summary() {
    if [ ${#failed_tests[@]} -gt 0 ]; then
        echo "Test Summary:"
        echo "================"
        echo "Failed tests:"
        for test in "${failed_tests[@]}"; do
            echo "- $test"
        done
        echo
        echo "Total failed tests: ${#failed_tests[@]}"
        exit 1
    fi

    exit 0
}

compare_strings() {
    local expected="$2"
    local actual="$3"
    local type="$4"

    if [ "$actual" != "$expected" ]; then
        echo -e "\033[0;31mTest '$1' failed.\033[0m"
        echo "______________________"
        echo "Expected $type:"
        echo "\"$expected\""
        echo "______________________"
        echo "Actual $type:"
        echo "\"$actual\""
        echo "______________________"
        return 1
    fi

    return 0
}

compare_output() {
    compare_strings "$1" "$2" "$3" "output"
}

compare_error() {
    compare_strings "$1" "$2" "$3" "error"
}

compare_files() {
    local expected_file="$2"
    local output_file="$3"

    if [ -z "$expected_file" ]; then
        # No expected file, nothing to compare
        return 0
    fi

    if [ ! -f "$output_file" ]; then
        echo -e "\033[0;31mTest '$1' failed.\033[0m"
        echo "______________________"
        echo "Output file not found:"
        echo "\"$output_file\""
        echo "______________________"
        return 1
    fi

    local file_size=$(stat -c %s "$expected_file")
    local diff=$(cmp -l "$expected_file" "$output_file" 2>stderr.txt | wc -l) 
    local error=$(cat stderr.txt)
    rm stderr.txt

    if [ ! -z "$error" ]; then
        echo -e "\033[0;31mTest '$1' failed.\033[0m"
        echo "______________________"
        echo "Error opening the files:"
        echo "$error"
        echo "______________________"
        return 1
    fi
    
    local diff_percentage=$((diff * 100 * 100 / file_size))
    if [ "$diff_percentage" -gt 66 ]; then # 0.66% de diferencia
        echo -e "\033[0;31mTest '$1' failed.\033[0m"
        echo "______________________"
        echo "Number of different bytes: $diff"
        local decimal=$(printf "%02d" $((diff_percentage % 100)))
        echo "Difference percentage: $((diff_percentage / 100)).$decimal%"
        echo "______________________"
        return 1
    fi
    return 0
}

test() {
    local TEST_NAME="$1"

    local COMMAND="$2"

    local EXPECTED_FILE="$3"
    local EXPECTED_OUTPUT="$4"
    local EXPECTED_ERROR="$5"
    local OUTPUT_FILE="$6"

    local OUTPUT=$(eval "$COMMAND" 2>stderr.txt)
    local ERROR=$(cat stderr.txt)
    rm stderr.txt

    if ! compare_error "$1" "$EXPECTED_ERROR" "$ERROR"; then
        return 1
    fi

    if ! compare_output "$1" "$EXPECTED_OUTPUT" "$OUTPUT"; then
        return 1
    fi

    if ! compare_files "$1" "$EXPECTED_FILE" "$OUTPUT_FILE"; then     
        return 1
    fi

    return 0
}

test_output() {
    local COMMAND="$2"
    local EXPECTED_OUTPUT="$3"

    test "$1" "$COMMAND" "" "$EXPECTED_OUTPUT" "" ""
}

test_error() {
    local COMMAND="$2"
    local EXPECTED_ERROR="$3"

    test "$1" "$COMMAND" "" "" "$EXPECTED_ERROR" ""
}

test_file() {
    local COMMAND="$2"
    local EXPECTED_FILE="$3"
    local OUTPUT_FILE="$4"

    test "$1" "$COMMAND" "$EXPECTED_FILE" "" "" "$OUTPUT_FILE"
}