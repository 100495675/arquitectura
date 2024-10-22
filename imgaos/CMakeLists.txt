# Add to this list all files related to imgaos library
add_library(imgaos
imageaos.cpp
imageaos_resize.cpp
imageaos_max_level.cpp
imageaos_cut_freq.cpp
#other2.cpp
)
target_link_libraries(imgaos PRIVATE common)
# Use this line only if you have dependencies from this library to GSL
# target_link_libraries (imgaos PRIVATE common Microsoft.GSL::GSL)
target_link_libraries (imgaos PRIVATE gtest)