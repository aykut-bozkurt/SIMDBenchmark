cmake_minimum_required(VERSION 3.5.0)
project(SIMDBenchmark)

add_subdirectory(benchmark)

include(libsimdpp/cmake/SimdppMultiarch.cmake)
simdpp_get_runnable_archs(RUNNABLE_ARCHS)
message("Supported libsimdpp archs are ${RUNNABLE_ARCHS}")

include(cmake/FastestAvailableArch.cmake)
set_fastest_available_x86archs(RUNNABLE_ARCHS)

add_executable(Google_benchmarks_run main.cpp)
target_include_directories(Google_benchmarks_run PUBLIC benchmark/include libsimdpp)
target_link_libraries(Google_benchmarks_run benchmark::benchmark)
