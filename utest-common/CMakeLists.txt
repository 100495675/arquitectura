# Executable for all unit tests with list of sources
# For example, you may have one ∗_test.cpp for each ∗.cpp in common
add_executable(utest-common
progargs_test.cpp
binaryio_test.cpp
parsebinary_test.cpp
validatefile_test.cpp
colors_test.cpp
sizes_test.cpp
pixel_test.cpp
)
# Library dependencies
target_link_libraries (utest-common
PRIVATE
common
GTest::gtest_main
Microsoft.GSL::GSL)

add_test(NAME utest-common COMMAND utest-common)