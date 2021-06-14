#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include "../comvars.h"

class FPReduceFixture : public benchmark::Fixture {
 public:
  static const int maxSize = 16384;
  const int width = 4;
  static float vec_a[maxSize];
  static int acc;

  static void SetUp() {

  }

  static void TearDown() {

  }
};
float FPReduceFixture::vec_a[maxSize];
int FPReduceFixture::acc = 0;

BENCHMARK_DEFINE_F(FPReduceFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=4) {
            float32<4> xmmA = load(vec_a + i);
            benchmark::DoNotOptimize(acc += reduce_add(xmmA));
        }
    }
}
BENCHMARK_REGISTER_F(FPReduceFixture, SIMDTest)->RangeMultiplier(2)->Range(4, 1<<14);

BENCHMARK_DEFINE_F(FPReduceFixture, ScalarTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for(int i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(acc += vec_a[i]);
        }
    }
}
BENCHMARK_REGISTER_F(FPReduceFixture, ScalarTest)->RangeMultiplier(2)->Range(4, 1<<14);
