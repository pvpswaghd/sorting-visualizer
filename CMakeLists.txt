cmake_minimum_required(VERSION 3.28)
project(visualizer CXX)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_compile_definitions(ImDrawIdx=unsigned)
add_compile_definitions(IMGUI_DISABLE_OBSOLETE_FUNCTIONS)

add_subdirectory(dependency)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/WX /MP /permissive-)
else()
    message(FATAL_ERROR "You either do not have Microsoft Visual C++, or you are not using Windows. Please make sure you have the above before you proceed.")
endif()

find_package(Threads REQUIRED)
add_executable(visualizer 
    src/Algorithm.cpp
    src/main.cpp
    src/BubbleSort.cpp
    src/HeapSort.cpp
    src/Setup.cpp
    src/Sound.cpp
    src/Thread.cpp
)

target_include_directories(visualizer PRIVATE include)

target_link_libraries(visualizer PRIVATE sfml-audio sfml-graphics ImGui-SFML::ImGui-SFML ImPlot::ImPlot Threads::Threads)

