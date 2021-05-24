#include <benchmark/benchmark.h>

namespace memory_allocators {

static void ExampleBenchmark(benchmark::State &state) {
    for (auto _ : state) {
    }
}

BENCHMARK(ExampleBenchmark);

};
