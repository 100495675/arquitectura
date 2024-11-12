#!/bin/bash

resize_normal_1() {
    local INPUT_FILE="$2/../images/input/deer-large.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/resize-deer-large-1000.ppm"
    local OPERATION="resize"
    local WIDTH="1000"
    local HEIGHT="1000"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/../images/expected/resize/deer-large-1000.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

resize_normal_2() {
    local INPUT_FILE="$2/../images/input/deer-large.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/resize-deer-large-100.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="100"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/../images/expected/resize/deer-large-100.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

resize_normal_3() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/resize-deer-small-100.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="100"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/../images/expected/resize/deer-small-100.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

resize_normal_4() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/resize-deer-small-1000.ppm"
    local OPERATION="resize"
    local WIDTH="1000"
    local HEIGHT="1000"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/../images/expected/resize/deer-small-1000.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

resize_normal_5() {
    local INPUT_FILE="$2/../images/input/lake-large.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/resize-lake-large-1000.ppm"
    local OPERATION="resize"
    local WIDTH="1000"
    local HEIGHT="1000"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/../images/expected/resize/lake-large-1000.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

resize_normal_6() {
    local INPUT_FILE="$2/../images/input/lake-large.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/resize-lake-large-100.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="100"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/../images/expected/resize/lake-large-100.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

resize_normal_7() {
    local INPUT_FILE="$2/../images/input/lake-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/resize-lake-small-100.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="100"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/../images/expected/resize/lake-small-100.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

resize_normal_8() {
    local INPUT_FILE="$2/../images/input/lake-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/resize-lake-small-1000.ppm"
    local OPERATION="resize"
    local WIDTH="1000"
    local HEIGHT="1000"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/../images/expected/resize/lake-small-1000.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

resize_invalid_width() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/deer-small-resize-invalid.ppm"
    local OPERATION="resize"
    local WIDTH="-100"
    local HEIGHT="200"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize width: -100"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_invalid_height() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/deer-small-resize-invalid.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="-200"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize height: -200"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_missing_file() {
    local INPUT_FILE="$2/../images/input/nonexistent.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/nonexistent-resize.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="200"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error opening file: $2/../images/input/nonexistent.ppm"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_string_width() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/deer-small-resize-invalid.ppm"
    local OPERATION="resize"
    local WIDTH="abc"
    local HEIGHT="200"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize width: abc"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_string_height() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/deer-small-resize-invalid.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="xyz"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize height: xyz"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_cero_width() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/deer-small-resize-zero-width.ppm"
    local OPERATION="resize"
    local WIDTH="0"
    local HEIGHT="100"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize width: 0"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_cero_height() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/soa-output/deer-small-resize-zero-height.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="0"
    local COMMAND="../imtool-soa/imtool-soa $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize height: 0"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}