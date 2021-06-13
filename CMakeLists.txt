project(SIMDBenchmark)

set(CMAKE_CXX_FLAGS "-O3 -march=native")

add_subdirectory(benchmark)

# adding the Google_Tests_run target
add_executable(Google_benchmarks_run main.cpp)
target_include_directories(Google_benchmarks_run PUBLIC benchmark/include libsimdpp)
target_link_libraries(Google_benchmarks_run benchmark::benchmark)
