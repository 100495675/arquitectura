# Add to this list all files related to imgaos library
add_library(imgsoa
imagesoa.cpp
max_level.cpp
resize.cpp
cut_freq.cpp
compress.cpp
#other1.cpp
#other2.cpp
)
target_link_libraries(imgaos PRIVATE common gtest)
# Use this line only if you have dependencies from this library to GSL
# target_link_libraries (imgaos PRIVATE common Microsoft.GSL::GSL)