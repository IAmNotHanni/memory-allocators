#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

int main(int /*argc*/, char */*argv*/[]) {
    spdlog::init_thread_pool(8192, 2);

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("memory-allocators.log", true);
    auto allocators_log =
        std::make_shared<spdlog::async_logger>("memory-allocators", spdlog::sinks_init_list{console_sink, file_sink},
                                               spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    allocators_log->set_level(spdlog::level::trace);
    allocators_log->set_pattern("%Y-%m-%d %T.%f %^%l%$ %5t [%-10n] %v");
    allocators_log->flush_on(spdlog::level::debug);

    spdlog::set_default_logger(allocators_log);

    spdlog::info("Hello, memory!");

    // TODO: Implement!
}
