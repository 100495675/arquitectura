#!/bin/bash

max_level_normal_uint8_1() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/aos-output/maxlevel-deer-small.ppm"
    local OPERATION="maxlevel"
    local LEVEL="255"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_FILE="$2/../images/expected/maxlevel/deer-small-255.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

max_level_normal_uint8_2() {
    local INPUT_FILE="$2/../images/input/lake-small.ppm"
    local OUTPUT_FILE="$2/../images/aos-output/maxlevel-lake-small-255.ppm"
    local OPERATION="maxlevel"
    local LEVEL="255"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_FILE="$2/../images/expected/maxlevel/lake-small-255.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

max_level_normal_uint16_1() {
    local INPUT_FILE="$2/../images/input/deer-small.ppm"
    local OUTPUT_FILE="$2/../images/aos-output/maxlevel-deer-small-65535.ppm"
    local OPERATION="maxlevel"
    local LEVEL="65535"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_FILE="$2/../images/expected/maxlevel/deer-small-65535.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

max_level_normal_uint16_2() {
    local INPUT_FILE="$2/../images/input/lake-small.ppm"
    local OUTPUT_FILE="$2/../images/aos-output/maxlevel-lake-small-65535.ppm"
    local OPERATION="maxlevel"
    local LEVEL="65535"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_FILE="$2/../images/expected/maxlevel/lake-small-65535.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

maxlevel_not_enough_args() {
    local INPUT_FILE="photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION"

    local EXPECTED_ERROR="Error: Invalid number of extra arguments for maxlevel: 0"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

maxlevel_too_many_args() {
    local INPUT_FILE="photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="100"
    local EXTRA="100"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL $EXTRA"

    local EXPECTED_ERROR="Error: Invalid number of extra arguments for maxlevel: 2"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

maxlevel_negativo() {
    local INPUT_FILE="photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="-1"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_ERROR="Error: Invalid maxlevel: -1"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

 maxlevel_demasiado_grande() {
    local INPUT_FILE="photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="70000"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_ERROR="Error: Invalid maxlevel: 70000"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

maxlevel_string() {
    local INPUT_FILE="photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="copy"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_ERROR="Error: Invalid maxlevel: copy"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

maxlevel_limite() {
    local INPUT_FILE="$2/../images/input/image-large.ppm"
    local OUTPUT_FILE="$2/../images/aos-output/image-maxlevel-65536.ppm"
    local OPERATION="maxlevel"
    local LEVEL="65536"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_ERROR="Error: Invalid maxlevel: 65536"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}


maxlevel_zero() {
    local INPUT_FILE="photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="0"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_ERROR="Error: Invalid maxlevel: 0"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

