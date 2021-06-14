#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include "../comvars.h"

class FPMulFixture : public benchmark::Fixture {
 public:
  static const int maxSize = 16384;
  const int width = 4;
  static float vec_a[maxSize];
  static float vec_b[maxSize];
  static float result[maxSize];

  static void SetUp() {

  }

  static void TearDown() {

  }
 private:
};
float FPMulFixture::vec_a[maxSize];
float FPMulFixture::vec_b[maxSize];
float FPMulFixture::result[maxSize];

BENCHMARK_DEFINE_F(FPMulFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));
    init_vector(vec_b, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=4) {
            float32<4> xmmA = load(vec_a + i);
            float32<4> xmmB = load(vec_b + i);
            float32<4> xmmC = mul(xmmA, xmmB);
            store(result + i, xmmC);
        }
    }
}
BENCHMARK_REGISTER_F(FPMulFixture, SIMDTest)->RangeMultiplier(2)->Range(4, 1<<14);

BENCHMARK_DEFINE_F(FPMulFixture, ScalarTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));
    init_vector(vec_b, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for(int i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(result[i] = vec_a[i] * vec_b[i]);
        }
    }
}
BENCHMARK_REGISTER_F(FPMulFixture, ScalarTest)->RangeMultiplier(2)->Range(4, 1<<14);
