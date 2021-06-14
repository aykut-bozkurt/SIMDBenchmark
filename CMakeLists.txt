cmake_minimum_required(VERSION 3.5.0)
project(SIMDBenchmark)

add_subdirectory(benchmark)

include(libsimdpp/cmake/SimdppMultiarch.cmake)
simdpp_get_runnable_archs(RUNNABLE_ARCHS)
message("Supported libsimdpp archs are ${RUNNABLE_ARCHS}")

set(AVX_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})
set(SSE2_RUNNABLE_ARCHS ${RUNNABLE_ARCHS})

list(FILTER AVX_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_AVX.*")
list(LENGTH AVX_RUNNABLE_ARCHS AVX_TOTAL_ARCH)

list(FILTER SSE2_RUNNABLE_ARCHS INCLUDE REGEX ".*X86_SSE2.*")
list(LENGTH SSE2_RUNNABLE_ARCHS SSE2_TOTAL_ARCH)

if(${AVX_TOTAL_ARCH} GREATER 0)
    message("AVX instructions will be used.")
    add_definitions(-DSIMDPP_ARCH_X86_AVX)
elseif(${SSE2_TOTAL_ARCH} GREATER 0)
    message("SSE2 instructions will be used.")
    add_definitions(-DSIMDPP_ARCH_X86_SSE2)
endif()

add_executable(Google_benchmarks_run main.cpp)
target_include_directories(Google_benchmarks_run PUBLIC benchmark/include libsimdpp)
target_link_libraries(Google_benchmarks_run benchmark::benchmark)
