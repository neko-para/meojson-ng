cmake_minimum_required(VERSION 3.30)

project(meojson-ng LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/utf-8)
endif()
if(APPLE)
  set(CMAKE_OSX_SYSROOT
      "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.2.sdk"
  )
endif()

option(BUILD_TESTING "Build testing" ON)

add_library(meojson INTERFACE)
target_include_directories(meojson INTERFACE include)

add_library(meojson_module STATIC)
target_include_directories(meojson_module INTERFACE include)
target_link_libraries(meojson_module PRIVATE meojson)
target_sources(meojson_module PUBLIC FILE_SET module TYPE CXX_MODULES FILES
                                     src/json.cppm)
set_target_properties(meojson_module PROPERTIES CXX_SCAN_FOR_MODULES ON)

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

  add_executable(test_module src/test_module.cpp)
  target_link_libraries(test_module PRIVATE meojson_module)
  set_target_properties(test_module PROPERTIES CXX_SCAN_FOR_MODULES ON)
endif()
