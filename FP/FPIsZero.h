#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include "../comvars.h"

class FPIsZeroFixture : public benchmark::Fixture {
 public:
  static const int maxSize = 16384;
  static const int width = 4;
  static float vec_a[maxSize];
  static float vec_zero[maxSize];
  static float result[maxSize];

  static void SetUp() {

  }

  static void TearDown() {

  }
};
float FPIsZeroFixture::vec_a[maxSize];
float FPIsZeroFixture::vec_zero[maxSize];
float FPIsZeroFixture::result[maxSize];

BENCHMARK_DEFINE_F(FPIsZeroFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=width) {
            float32<width> xmmA = load(vec_a + i);
            float32<width> xmmB = load(vec_zero + i);
            mask_float32<width> xmmC = cmp_eq(xmmA, xmmB);
            store(result + i, xmmC.unmask());
        }
    }
}
BENCHMARK_REGISTER_F(FPIsZeroFixture, SIMDTest)->RangeMultiplier(2)->Range(8, 1<<14);

BENCHMARK_DEFINE_F(FPIsZeroFixture, ScalarTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for(int i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(result[i] = vec_a[i] == vec_zero[i]);
        }
    }
}
BENCHMARK_REGISTER_F(FPIsZeroFixture, ScalarTest)->RangeMultiplier(2)->Range(8, 1<<14);
