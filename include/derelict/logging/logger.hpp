#pragma once
#include <memory>
#include <spdlog/spdlog.h>

namespace derelict {

    class Logger {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
            return coreLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
    };

#define logTrace(...)  ::derelict::Logger::GetCoreLogger()->log( \
spdlog::source_loc{__FILE__, __LINE__, __func__},            \
spdlog::level::trace, __VA_ARGS__)

#define logDebug(...)  ::derelict::Logger::GetCoreLogger()->log( \
spdlog::source_loc{__FILE__, __LINE__, __func__},            \
spdlog::level::debug, __VA_ARGS__)

#define logInfo(...)   ::derelict::Logger::GetCoreLogger()->log( \
spdlog::source_loc{__FILE__, __LINE__, __func__},            \
spdlog::level::info, __VA_ARGS__)

#define logWarn(...)   ::derelict::Logger::GetCoreLogger()->log( \
spdlog::source_loc{__FILE__, __LINE__, __func__},            \
spdlog::level::warn, __VA_ARGS__)

#define logError(...)  ::derelict::Logger::GetCoreLogger()->log( \
spdlog::source_loc{__FILE__, __LINE__, __func__},            \
spdlog::level::err, __VA_ARGS__)

#define logFatal(...)  ::derelict::Logger::GetCoreLogger()->log( \
spdlog::source_loc{__FILE__, __LINE__, __func__},            \
spdlog::level::critical, __VA_ARGS__)

}
