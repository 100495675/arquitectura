# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in img−aos
add_executable(utest-imgsoa
imagesoa_test.cpp
imagesoa_max_level_test.cpp
imagesoa_resize_test.cpp
imagesoa_cut_freq_test.cpp
imageaos_compress_test.cpp)
# Library dependencies
target_link_libraries (utest-imgsoa
PRIVATE
imgsoa
common
GTest::gtest_main
Microsoft.GSL::GSL)

add_test(NAME utest-imgsoa COMMAND utest-imgsoa)