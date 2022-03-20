# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html
cmake_minimum_required(VERSION 3.10.2)

project("myapplication")
message(“hello， 开始测试cmake代码了哦...”)

add_library( # Sets the name of the library.
        native-lib
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        native-lib.cpp)

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

include_directories(base model util)

add_library(
        base-lib
        SHARED
        base/base.cpp
)

add_library(
        dynamic-lib
        SHARED
        util/dynamic.cpp
        base/jvm.cpp
)

target_link_libraries( # Specifies the target library.
        native-lib
        base-lib
        dynamic-lib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

target_link_libraries( # Specifies the target library.
        dynamic-lib
        base-lib
        ${log-lib})

message(“hello， 测试cmake代码结束...”)