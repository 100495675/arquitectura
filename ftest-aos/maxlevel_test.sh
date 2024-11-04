#!/bin/bash

maxlevel_normal() { 
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/maxlevel-deer-small-65535.ppm"
    local OPERATION="maxlevel"
    local LEVEL="65535"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_FILE="$2/expected/maxlevel/deer-small-65535.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

maxlevel_not_enough_args() {
    local INPUT_FILE="$photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION"

    local EXPECTED_ERROR="Error: Invalid number of extra arguments for maxlevel: 0"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

maxlevel_too_many_args() {
    local INPUT_FILE="$photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="100"
    local EXTRA="100"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL $EXTRA"

    local EXPECTED_ERROR="Error: Invalid number of extra arguments for maxlevel: 2"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

maxlevel_negativo() {
    local INPUT_FILE="$photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="-1"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_ERROR="Error: Invalid maxlevel: -1"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

 maxlevel_demasiado_grande() {
    local INPUT_FILE="$photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="70000"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_ERROR="Error: Invalid maxlevel: 70000"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

maxlevel_string() {
    local INPUT_FILE="$photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="copy"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_ERROR="Error: Invalid maxlevel: copy"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

# Falta el archivo deer-small-maxlevel1.ppm
maxlevel_min_value() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-maxlevel1.ppm"
    local OPERATION="maxlevel"
    local LEVEL="1"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_FILE="$2/expected/deer-small-maxlevel1.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

# Falta el archivo deer-small-maxlevel65535.ppm
maxlevel_max_value() {
    local INPUT_FILE="$2/input/deer-small.ppm"
    local OUTPUT_FILE="$2/output/deer-small-maxlevel65535.ppm"
    local OPERATION="maxlevel"
    local LEVEL="65535"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_FILE="$2/expected/deer-small-maxlevel65535.ppm"

    test_file "$1" "$COMMAND" "$EXPECTED_FILE" "$OUTPUT_FILE"
}

maxlevel_zero() {
    local INPUT_FILE="$photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="maxlevel"
    local LEVEL="0"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $LEVEL"

    local EXPECTED_ERROR="Error: Invalid maxlevel: 0"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}

