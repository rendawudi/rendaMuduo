

aux_source_directory(. DIR_BASE_SRCS)

add_library(base ${DIR_BASE_SRCS} TimeStamp.cpp Date.h Date.cpp CurrentThread.h CurrentThread.cpp Mutex.h noncopyable.h Condition.h Condition.cpp Atomic.h)
