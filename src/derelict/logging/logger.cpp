#include <derelict/logging/logger.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace derelict {

    std::shared_ptr<spdlog::logger> Logger::coreLogger;

    void Logger::Init() {
        std::vector<spdlog::sink_ptr> sinks;

        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        // sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/app.log", true));

        for (auto& sink : sinks) {
            sink->set_pattern("[%T] [%^%l%$] [%s:%# %!] %v");
        }

        coreLogger = std::make_shared<spdlog::logger>("ENGINE", begin(sinks), end(sinks));

        spdlog::register_logger(coreLogger);
        coreLogger->set_level(spdlog::level::trace);
        coreLogger->flush_on(spdlog::level::err);
    }
}
