cmake_minimum_required(VERSION 2.8.3)
project(i18nText)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(OpenCV REQUIRED)
find_package(Freetype REQUIRED)

SET(CMAKE_CXX_FLAGS "-O2 -std=c++11")
SET(CMAKE_EXE_LINKER_FLAGS "-v")

include_directories(/usr/include/freetype2)
add_library(i18nText src/i18nText.cpp)

add_executable(
    i18nTextTest
    main.cpp
)

target_link_libraries(i18nTextTest i18nText ${FREETYPE_LIBRARIES} ${OpenCV_LIBS})

