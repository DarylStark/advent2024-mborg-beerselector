cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
list(APPEND kconfigs "${CMAKE_SOURCE_DIR}/Kconfig")
project(Advent2024-ESP-BeerSelector)
