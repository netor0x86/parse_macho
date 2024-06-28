cmake_minimum_required(VERSION 3.27)
project(parse_macho C)

set(CMAKE_C_STANDARD 23)

add_executable(parse_macho main.c
        macho/macho.c
        macho/macho.h
        macho/macho64.c
        macho/macho64.c
        endian/endian.c
        endian/endian.h
)

find_library(CAPSTONE_LIBRARY NAMES libcapstone.a PATHS /usr/local/Cellar/capstone/5.0.1/lib)
find_library(GLIB_LIBRARY NAMES libglib-2.0.a PATHS /usr/local/Cellar/glib/2.80.3/lib)

target_link_libraries(parse_macho PRIVATE ${CAPSTONE_LIBRARY} ${GLIB_LIBRARY})
#target_include_directories(parse_macho PRIVATE ${GLIB_INCLUDE_DIRS})
include_directories(/usr/local/include /usr/local/include/glib-2.0 /usr/local/Cellar/glib/2.80.3/lib/glib-2.0/include)