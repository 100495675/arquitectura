# Add to this list all files related to imgsoa library
add_library(imgsoa
imagesoa.cpp
resize.cpp
max_level.cpp
cut_freq.cpp
compress.cpp
#other2.cpp
)
target_link_libraries(imgsoa PRIVATE common gtest)
# Use this line only if you have dependencies from this library to GSL
# target_link_libraries (imgsoa PRIVATE common Microsoft.GSL::GSL)