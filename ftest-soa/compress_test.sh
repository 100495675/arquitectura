#!/bin/bash

compress_normal_1() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/deer-small.cppm"
    local OPERATION="compress"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION"

    local EXPECTED_FILE="$2/../images/expected/compress/deer-small.cppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

compress_normal_2() {
    local INPUT_FILE="$2/../images/input/lake-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/lake-small.cppm"
    local OPERATION="compress"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION"

    local EXPECTED_FILE="$2/../images/expected/compress/lake-small.cppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}