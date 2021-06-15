#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include "../comvars.h"

class IntIsZeroFixture : public benchmark::Fixture {
 public:
  static const int maxSize = 16384;
  static const int width = 4;
  static int vec_a[maxSize];
  static int vec_zero[maxSize];
  static int result[maxSize];

  static void SetUp() {

  }

  static void TearDown() {

  }
};
int IntIsZeroFixture::vec_a[maxSize];
int IntIsZeroFixture::vec_zero[maxSize];
int IntIsZeroFixture::result[maxSize];

BENCHMARK_DEFINE_F(IntIsZeroFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=width) {
            int32<width> xmmA = load(vec_a + i);
            int32<width> xmmB = load(vec_zero + i);
            mask_int32<width> xmmC = cmp_eq(xmmA, xmmB);
            store(result + i, xmmC.unmask());
        }
    }
}
BENCHMARK_REGISTER_F(IntIsZeroFixture, SIMDTest)->RangeMultiplier(2)->Range(8, 1<<14);

BENCHMARK_DEFINE_F(IntIsZeroFixture, ScalarTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for(int i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(result[i] = vec_a[i] == vec_zero[i]);
        }
    }
}
BENCHMARK_REGISTER_F(IntIsZeroFixture, ScalarTest)->RangeMultiplier(2)->Range(8, 1<<14);
