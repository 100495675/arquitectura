#!/bin/bash

resize_normal() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-resize100x200.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="200"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/expected/deer-small-resize100x200.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}



resize_invalid_width() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-resize-invalid.ppm"
    local OPERATION="resize"
    local WIDTH="-100"
    local HEIGHT="200"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize width: -100"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_invalid_height() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-resize-invalid.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="-200"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize height: -200"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_missing_file() {
    local INPUT_FILE="$2/input/nonexistent.ppm"
    local OUTPUT_FILE="$2/output/nonexistent-resize.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="200"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error opening file: $2/input/nonexistent.ppm"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_string_width() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-resize-invalid.ppm"
    local OPERATION="resize"
    local WIDTH="abc"
    local HEIGHT="200"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize width: abc"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_string_height() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-resize-invalid.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="xyz"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize height: xyz"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

# falta la imagen de 1x1
resize_unico_pixel() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-resize-1x1.ppm"
    local OPERATION="resize"
    local WIDTH="1"
    local HEIGHT="1"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_FILE="$2/expected/deer-small-resize-1x1.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

resize_cero_width() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-resize-zero-width.ppm"
    local OPERATION="resize"
    local WIDTH="0"
    local HEIGHT="100"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize width: 0"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

resize_cero_height() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-resize-zero-height.ppm"
    local OPERATION="resize"
    local WIDTH="100"
    local HEIGHT="0"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $WIDTH $HEIGHT"

    local EXPECTED_ERROR="Error: Invalid resize height: 0"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}