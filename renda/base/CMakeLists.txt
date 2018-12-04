

aux_source_directory(. DIR_BASE_SRCS)

add_library(base ${DIR_BASE_SRCS} TimeStamp.cpp Date.h Date.cpp)
