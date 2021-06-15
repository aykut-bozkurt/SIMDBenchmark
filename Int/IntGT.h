#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include "../comvars.h"

class IntGTFixture : public benchmark::Fixture {
 public:
  static const int maxSize = 16384;
  static const int width = 4;
  static int vec_a[maxSize];
  static int vec_b[maxSize];
  static int result[maxSize];

  static void SetUp() {

  }

  static void TearDown() {

  }
};
int IntGTFixture::vec_a[maxSize];
int IntGTFixture::vec_b[maxSize];
int IntGTFixture::result[maxSize];

BENCHMARK_DEFINE_F(IntGTFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));
    init_vector(vec_b, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=width) {
            int32<width> xmmA = load(vec_a + i);
            int32<width> xmmB = load(vec_b + i);
            mask_int32<width> xmmC = cmp_gt(xmmA, xmmB);
            store(result + i, xmmC.unmask());
        }
    }
}
BENCHMARK_REGISTER_F(IntGTFixture, SIMDTest)->RangeMultiplier(2)->Range(8, 1<<14);

BENCHMARK_DEFINE_F(IntGTFixture, ScalarTest)(benchmark::State& state) {
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
BENCHMARK_REGISTER_F(IntGTFixture, ScalarTest)->RangeMultiplier(2)->Range(8, 1<<14);
