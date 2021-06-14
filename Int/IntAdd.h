#pragma once

#include <benchmark/benchmark.h>
#include <simdpp/simd.h>
#include "../comvars.h"
#include <iostream>

class IntAddFixture : public benchmark::Fixture {
    public:
        static const int maxSize = 16384;
        const int width = 4;
        static int vec_a[maxSize];
        static int vec_b[maxSize];
        static int result[maxSize];

        static void SetUp() {

        }

        static void TearDown() {

        }
};
int IntAddFixture::vec_a[maxSize];
int IntAddFixture::vec_b[maxSize];
int IntAddFixture::result[maxSize];

BENCHMARK_DEFINE_F(IntAddFixture, SIMDTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));
    init_vector(vec_b, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for (int i=0; i<state.range(0); i+=4) {
            int32<4> xmmA = load(vec_a + i);
            int32<4> xmmB = load(vec_b + i);
            int32<4> xmmC = add(xmmA, xmmB);
            store(result + i, xmmC);
        }
    }
}
BENCHMARK_REGISTER_F(IntAddFixture, SIMDTest)->RangeMultiplier(2)->Range(4, 1<<14);

BENCHMARK_DEFINE_F(IntAddFixture, ScalarTest)(benchmark::State& state) {
    init_vector(vec_a, state.range(0));
    init_vector(vec_b, state.range(0));

    using namespace simdpp;
    for (auto _ : state)
    {
        for(int i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(result[i] = vec_a[i] + vec_b[i]);
        }
    }
}
BENCHMARK_REGISTER_F(IntAddFixture, ScalarTest)->RangeMultiplier(2)->Range(4, 1<<14);
