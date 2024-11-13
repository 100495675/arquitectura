#!/bin/bash

dir=$(dirname $0)
mkdir -p "$dir/../images/soa-output"

source $dir/test_utils.sh
source $dir/args_test.sh
source $dir/info_test.sh
source $dir/maxlevel_test.sh
source $dir/resize_test.sh
source $dir/compress_test.sh
source $dir/cut_freq_test.sh

failed_tests=()

run_test args_0
run_test args_1
run_test args_2

run_test info_normal
run_test info_too_many_args

run_test max_level_normal_uint8_1
run_test max_level_normal_uint8_2
run_test max_level_normal_uint16_1
run_test max_level_normal_uint16_2
run_test maxlevel_not_enough_args
run_test maxlevel_too_many_args
run_test maxlevel_negativo
run_test maxlevel_demasiado_grande
run_test maxlevel_string
run_test maxlevel_limite
run_test maxlevel_zero

run_test resize_normal_1
run_test resize_normal_2
run_test resize_normal_3
run_test resize_normal_4
run_test resize_normal_5
run_test resize_normal_6
run_test resize_normal_7
run_test resize_normal_8
run_test resize_invalid_width
run_test resize_invalid_height
run_test resize_missing_file
run_test resize_string_width
run_test resize_string_height
run_test resize_cero_width
run_test resize_cero_height

run_test cut_freq_normal_1
run_test cut_freq_normal_2
run_test cut_freq_zero
run_test cut_freq_invalid_negative
run_test cut_freq_demasiados_colores
run_test cut_freq_string_value

run_test compress_normal_1
run_test compress_normal_2

#rm -rf "$dir/../images/soa-output"

summary