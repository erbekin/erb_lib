//
// Created by github.com/erbekin on 27.05.2025.
//

#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>
#include <chrono>

namespace erb::coreutils {
    enum class LogLevel {
        TRACE = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    class Logger {
    public:
        // Singleton access
        static Logger &instance();
        // Non-copyable
        Logger(const Logger &) = delete;

        Logger &operator=(const Logger &) = delete;
        // Configuration
        void set_level(LogLevel level);

        void set_output_file(const std::string &filename);

        void set_console_output(bool enabled);

        void set_pattern(const std::string &pattern); // For future: custom formatting

        // Logging methods
        void trace(const std::string &message);

        void debug(const std::string &message);

        void info(const std::string &message);

        void warn(const std::string &message);

        void error(const std::string &message);

        void fatal(const std::string &message);

        // Template methods for formatted logging
        template<typename... Args>
        void trace(const std::string &format, Args &&... args);

        template<typename... Args>
        void debug(const std::string &format, Args &&... args);

        template<typename... Args>
        void info(const std::string &format, Args &&... args);

        template<typename... Args>
        void warn(const std::string &format, Args &&... args);

        template<typename... Args>
        void error(const std::string &format, Args &&... args);

        template<typename... Args>
        void fatal(const std::string &format, Args &&... args);

        // Flush logs
        void flush();

    private:
        Logger() = default;

        ~Logger();

        void log(LogLevel level, const std::string &message);

        static std::string format_message(LogLevel level, const std::string &message);

        static std::string level_to_string(LogLevel level);

        static std::string current_timestamp();

        LogLevel min_level_ = LogLevel::INFO;
        bool console_output_ = true;
        std::unique_ptr<std::ofstream> file_stream_;
        std::mutex mutex_;
    };

    // Template implementations
    template<typename... Args>
    void Logger::trace(const std::string &format, Args &&... args) {
        if (min_level_ <= LogLevel::TRACE) {
            std::ostringstream oss;
            format_string(oss, format, std::forward<Args>(args)...);
            log(LogLevel::TRACE, oss.str());
        }
    }

    template<typename... Args>
    void Logger::debug(const std::string &format, Args &&... args) {
        if (min_level_ <= LogLevel::DEBUG) {
            std::ostringstream oss;
            format_string(oss, format, std::forward<Args>(args)...);
            log(LogLevel::DEBUG, oss.str());
        }
    }

    template<typename... Args>
    void Logger::info(const std::string &format, Args &&... args) {
        if (min_level_ <= LogLevel::INFO) {
            std::ostringstream oss;
            format_string(oss, format, std::forward<Args>(args)...);
            log(LogLevel::INFO, oss.str());
        }
    }

    template<typename... Args>
    void Logger::warn(const std::string &format, Args &&... args) {
        if (min_level_ <= LogLevel::WARN) {
            std::ostringstream oss;
            format_string(oss, format, std::forward<Args>(args)...);
            log(LogLevel::WARN, oss.str());
        }
    }

    template<typename... Args>
    void Logger::error(const std::string &format, Args &&... args) {
        if (min_level_ <= LogLevel::ERROR) {
            std::ostringstream oss;
            format_string(oss, format, std::forward<Args>(args)...);
            log(LogLevel::ERROR, oss.str());
        }
    }

    template<typename... Args>
    void Logger::fatal(const std::string &format, Args &&... args) {
        if (min_level_ <= LogLevel::FATAL) {
            std::ostringstream oss;
            format_string(oss, format, std::forward<Args>(args)...);
            log(LogLevel::FATAL, oss.str());
        }
    }

    // Helper function for string formatting
    template<typename T>
    void format_string(std::ostringstream &oss, const std::string &format, T &&value) {
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            oss << format.substr(0, pos) << std::forward<T>(value) << format.substr(pos + 2);
        } else {
            oss << format;
        }
    }

    template<typename T, typename... Args>
    void format_string(std::ostringstream &oss, const std::string &format, T &&value, Args &&... args) {
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            oss << format.substr(0, pos) << std::forward<T>(value);
            std::string remaining = format.substr(pos + 2);
            format_string(oss, remaining, std::forward<Args>(args)...);
        } else {
            oss << format;
        }
    }

    // Convenience macros
#define ERB_TRACE(...) erb::core::Logger::instance().trace(__VA_ARGS__)
#define ERB_DEBUG(...) erb::core::Logger::instance().debug(__VA_ARGS__)
#define ERB_INFO(...) erb::core::Logger::instance().info(__VA_ARGS__)
#define ERB_WARN(...) erb::core::Logger::instance().warn(__VA_ARGS__)
#define ERB_ERROR(...) erb::core::Logger::instance().error(__VA_ARGS__)
#define ERB_FATAL(...) erb::core::Logger::instance().fatal(__VA_ARGS__)
} // erb::coreutils

