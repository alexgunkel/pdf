cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.25)
project(pdf-service)

set(CURL_VERSION 7.79.1)
set(XPDF_VERSION 4.04)

include(FetchContent)
FetchContent_Declare(xpdf
        URL      https://dl.xpdfreader.com/xpdf-${XPDF_VERSION}.tar.gz
        URL_HASH SHA224=d08af26e0d084da07da2c660dbc00ffa6422d2bb6b724c107fb18e70
)

FetchContent_Declare(pistache
        GIT_REPOSITORY https://github.com/pistacheio/pistache.git
        GIT_TAG a68ad0902d2cfc23f69fc16e26747ac77bc2f123)

FetchContent_MakeAvailable(xpdf pistache)

include_directories(${xpdf_SOURCE_DIR})
include_directories(${xpdf_SOURCE_DIR}/goo)
include_directories(${xpdf_BINARY_DIR})
include_directories(${pistache_SOURCE_DIR}/include)
include_directories(${curl_SOURCE_DIR}/include)
include_directories(${curl_BINARY_DIR}/lib)

find_package(ZLIB)

find_library(PAPER_LIBRARY
        NAMES paper libpaper
        PATH_SUFFIXES lib64 lib
        )

find_package(CURL REQUIRED)

add_executable(pdfservice
        main.cpp
        ${xpdf_SOURCE_DIR}/xpdf/TextOutputDev.cc
        PdfExtractor.h PdfExtractor.cpp RequestHandler.h RequestHandler.cpp Downloader.h Downloader.cpp)
target_link_libraries(pdfservice PRIVATE ${CURL_LIBRARIES} goo_objs xpdf_objs fofi_objs pistache)

add_executable(downloader
        download.cpp
        ${xpdf_SOURCE_DIR}/xpdf/TextOutputDev.cc
        PdfExtractor.h PdfExtractor.cpp  Downloader.h Downloader.cpp)
target_link_libraries(downloader PRIVATE ${CURL_LIBRARIES} goo_objs xpdf_objs fofi_objs)
