cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.25)
project(pdf)

include(FetchContent)
FetchContent_Declare(xpdf
        URL      https://dl.xpdfreader.com/xpdf-4.04.tar.gz
)


FetchContent_MakeAvailable(xpdf)
message($<TARGET_OBJECTS:xpdf_objs>)
include_directories(${xpdf_SOURCE_DIR})
include_directories(${xpdf_SOURCE_DIR}/goo)
include_directories(${xpdf_BINARY_DIR})

find_package(ZLIB)

find_library(PAPER_LIBRARY
        NAMES paper libpaper
        PATH_SUFFIXES lib64 lib
        )

add_executable(pdfservice
        main.cpp
        ${xpdf_SOURCE_DIR}/xpdf/TextOutputDev.cc
        PdfExtractor.h PdfExtractor.cpp)
target_link_libraries(pdfservice goo_objs xpdf_objs fofi_objs)
