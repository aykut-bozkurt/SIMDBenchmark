#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include "../comvars.h"

class FPGTFixture : public benchmark::Fixture {
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
};
float FPGTFixture::vec_a[maxSize];
float FPGTFixture::vec_b[maxSize];
float FPGTFixture::result[maxSize];

BENCHMARK_DEFINE_F(FPGTFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));
    init_vector(vec_b, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=4) {
            float32<4> xmmA = load(vec_a + i);
            float32<4> xmmB = load(vec_b + i);
            mask_float32<4> xmmC = cmp_gt(xmmA, xmmB);
            store(result + i, xmmC.unmask());
        }
    }
}
BENCHMARK_REGISTER_F(FPGTFixture, SIMDTest)->RangeMultiplier(2)->Range(4, 1<<14);

BENCHMARK_DEFINE_F(FPGTFixture, ScalarTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));
    init_vector(vec_b, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for(int i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(result[i] = vec_a[i] > vec_b[i]);
        }
    }
}
BENCHMARK_REGISTER_F(FPGTFixture, ScalarTest)->RangeMultiplier(2)->Range(4, 1<<14);

