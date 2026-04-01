cmake_minimum_required(VERSION 3.30)

project(meojson-ng LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Build testing" ON)

add_library(meojson INTERFACE)
target_include_directories(meojson INTERFACE include)

if(BUILD_TESTING)
  file(GLOB testing_src test/*.cpp test/*.h test/*.hpp)
  add_executable(testing ${testing_src})
  target_compile_definitions(testing PRIVATE MEOJSON_FS_PATH_EXTENSION
                                             MEOJSON_KEEP_FLOATING_PRECISION)
  target_link_libraries(testing meojson)
  if(NOT (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC"
          OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))
    target_compile_options(testing PRIVATE -Wno-unused-variable
                                           -Wno-unused-but-set-variable)
  endif()

  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${json_headers})
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${testing_src})
endif()
