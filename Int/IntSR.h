#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include "../comvars.h"

class IntSRFixture : public benchmark::Fixture {
 public:
  static const int maxSize = 16384;
  static const int width = 4;
  static int vec_a[maxSize];
  static int shiftBy;
  static int result[maxSize];

  static void SetUp() {

  }

  static void TearDown() {

  }
};
int IntSRFixture::vec_a[maxSize];
int IntSRFixture::shiftBy = 5;
int IntSRFixture::result[maxSize];

BENCHMARK_DEFINE_F(IntSRFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=width) {
            int32<width> xmmA = load(vec_a + i);
            int32<width> xmmC = shift_r(xmmA, shiftBy);
            store(result + i, xmmC);
        }
    }
}
BENCHMARK_REGISTER_F(IntSRFixture, SIMDTest)->RangeMultiplier(2)->Range(8, 1<<14);

BENCHMARK_DEFINE_F(IntSRFixture, ScalarTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for(int i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(result[i] = vec_a[i] >> shiftBy);
        }
    }
}
BENCHMARK_REGISTER_F(IntSRFixture, ScalarTest)->RangeMultiplier(2)->Range(8, 1<<14);
