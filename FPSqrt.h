#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include <cmath>
#include "comvars.h"

class FPSqrtFixture : public benchmark::Fixture {
 public:
  static const int maxSize = 16384;
  const int width = 4;
  static float vec_a[maxSize];
  static float result[maxSize];

  static void SetUp() {

  }

  static void TearDown() {

  }
 private:
};
float FPSqrtFixture::vec_a[maxSize];
float FPSqrtFixture::result[maxSize];

BENCHMARK_DEFINE_F(FPSqrtFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=4) {
            float32<4> xmmA = load(vec_a + i);
            float32<4> xmmC = sqrt(xmmA);
            store(result + i, xmmC);
        }
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK_REGISTER_F(FPSqrtFixture, SIMDTest)->RangeMultiplier(2)->Range(2, 1<<14);

BENCHMARK_DEFINE_F(FPSqrtFixture, ScalarTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for(int i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(result[i] = std::sqrt(vec_a[i]));
        }
    }
}
BENCHMARK_REGISTER_F(FPSqrtFixture, ScalarTest)->RangeMultiplier(2)->Range(2, 1<<14);
