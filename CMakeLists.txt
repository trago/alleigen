cmake_minimum_required(VERSION 3.5)
project(allegro_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(PkgConfig)
find_package(Eigen3 REQUIRED)
pkg_check_modules(ALLEGRO REQUIRED allegro-5.0 allegro_main-5.0
        allegro_color-5.0 allegro_image-5.0)

include_directories(${ALLEGRO_INCLUDEDIR} ${EIGEN3_INCLUDE_DIR})
link_directories(${ALLEGRO_LIBRARY_DIRS})

set(SOURCE_FILES main.cpp allegro_utils.h allegro_utils.cc)
set(SOURCE_read_image read_image.cc allegro_utils.h allegro_utils.cc)

add_executable(allegro_test ${SOURCE_FILES})
target_link_libraries(allegro_test ${ALLEGRO_LIBRARIES})

add_executable(read_image ${SOURCE_read_image})
target_link_libraries(read_image ${ALLEGRO_LIBRARIES})