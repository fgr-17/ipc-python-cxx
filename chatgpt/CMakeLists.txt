cmake_minimum_required(VERSION 2.8)

set(app_name DisplayImage)

project( ${app_name} )
add_executable( ${app_name} send.cpp )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( ${app_name} ${OpenCV_LIBS} )

find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED IMPORTED_TARGET gstreamer-1.0)
message("GSTREAMER_FOUND:" ${GSTREAMER_FOUND})
message("GSTREAMER_LINK_LIBRARIES: " ${GSTREAMER_LINK_LIBRARIES})

target_link_libraries(${app_name} ${GSTREAMER_LINK_LIBRARIES})
target_link_libraries(${app_name} -lrt)

target_include_directories(${app_name} PRIVATE  ${GSTREAMER_INCLUDE_DIRS})
