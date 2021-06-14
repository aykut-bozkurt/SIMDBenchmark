# SIMDBenchmark
Benchmark app for simd operations given by libsimdpp and nonSIMD equivalent operations

### Third party Libraries
https://github.com/google/benchmark is licenced under [Apache License](benchmark/LICENSE).

https://github.com/p12tic/libsimdpp is licenced under [Boost Software License - Version 1.0](libsimdpp/LICENSE_1_0.txt).

### Build requirements
CMake

### How to Build
Pick a Release profile and build ***Google_benchmarks_run*** target after cmake project is loaded.
Unless you select Release build, benchmark results are far from reality.

### Which Instruction Set Will Be Used?
While loading cmake project source file, instruction set will be detected automataically based on your architecture. It will choose the fastest available instruction set on your hardware.
AVX, SSE2 or loop if none supported