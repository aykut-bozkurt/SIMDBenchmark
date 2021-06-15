#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include "../comvars.h"

class IntShuffleFixture : public benchmark::Fixture {
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
int IntShuffleFixture::vec_a[maxSize];
int IntShuffleFixture::vec_b[maxSize];
int IntShuffleFixture::result[maxSize];

BENCHMARK_DEFINE_F(IntShuffleFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));
    init_vector(vec_b, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=width) {
            int32<width> xmmA = load(vec_a + i);
            //int32<width> xmmC = permute4<vec_b[0],vec_b[1],vec_b[2],vec_b[3]>(xmmA);
            //store(result + i, xmmC);
        }
    }
}
BENCHMARK_REGISTER_F(IntShuffleFixture, SIMDTest)->RangeMultiplier(2)->Range(8, 1<<14);

BENCHMARK_DEFINE_F(IntShuffleFixture, ScalarTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));
    init_vector(vec_b, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for(int i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(result[i] = vec_a[vec_b[i]]);
        }
    }
}
BENCHMARK_REGISTER_F(IntShuffleFixture, ScalarTest)->RangeMultiplier(2)->Range(8, 1<<14);
