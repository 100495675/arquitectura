#!/bin/bash

cut_freq_invalid_negative() {
    local INPUT_FILE="photo.ppm"
    local OUTPUT_FILE="out.ppm"
    local OPERATION="cutfreq"
    local FREQUENCY="-1"
    local COMMAND="../imtool-aos/imtool-aos $INPUT_FILE $OUTPUT_FILE $OPERATION $FREQUENCY"

    local EXPECTED_ERROR="Error: Invalid cutfreq: -1"

    test_error "$1" "$COMMAND" "$EXPECTED_ERROR"
}