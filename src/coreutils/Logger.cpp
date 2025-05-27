//
// Created by github.com/erbekin on 27.05.2025.
//

#include "erb/coreutils/Logger.hpp"

#include <iomanip>
#include <iostream>
namespace erb::coreutils {
    Logger & Logger::instance() {
        static Logger instance;
        return instance;
    }

    void Logger::set_level(const LogLevel level) {
        std::lock_guard<std::mutex> lock{mutex_};
        min_level_ = level;
    }

    void Logger::set_output_file(const std::string &filename) {
        std::lock_guard<std::mutex> lock{mutex_};
        file_stream_ = std::make_unique<std::ofstream>(filename, std::ios::app);
        if (!file_stream_->is_open()) {
            std::cerr << "Failed to open file " << filename << " for writing." << std::endl;
            file_stream_.reset();
        }
    }

    void Logger::set_console_output(const bool enabled) {
        std::lock_guard<std::mutex> lock{mutex_};
        console_output_ = enabled;
    }

    void Logger::set_pattern(const std::string &pattern) {
        // @TODO Implement this later on
    }

    void Logger::trace(const std::string &message) {
        log(LogLevel::TRACE, message);
    }

    void Logger::debug(const std::string &message) {
        log(LogLevel::DEBUG, message);
    }

    void Logger::info(const std::string& message) {
        log(LogLevel::INFO, message);
    }

    void Logger::warn(const std::string& message) {
        log(LogLevel::WARN, message);
    }

    void Logger::error(const std::string& message) {
        log(LogLevel::ERROR, message);
    }

    void Logger::fatal(const std::string& message) {
        log(LogLevel::FATAL, message);
    }

    void Logger::flush() {
        std::lock_guard<std::mutex> lock{mutex_};
        if (console_output_) {
            std::cout.flush();
            std::cerr.flush();
        }
        if (file_stream_ && file_stream_->is_open()) {
            file_stream_->flush();
        }
    }

    Logger::~Logger() {
        flush();
    }

    void Logger::log(LogLevel level, const std::string &message) {
        if (level < min_level_) {
            return;
        }
        std::lock_guard<std::mutex> lock{mutex_};
        std::string formatted_message = format_message(level, message);

        // Console output
        if (console_output_) {
            if (level >= LogLevel::ERROR) {
                std::cerr << formatted_message << std::endl;
            } else {
                std::cout << formatted_message << std::endl;
            }
        }

        // File output
        if (file_stream_ && file_stream_->is_open()) {
            *file_stream_ << formatted_message << std::endl;
        }
    }

    std::string Logger::format_message(const LogLevel level, const std::string &message) {
        std::ostringstream oss;
        oss << "[" << current_timestamp() << "] "
            << "[" << level_to_string(level) << "] "
            << message;
        return oss.str();
    }

    std::string Logger::level_to_string(const LogLevel level) {
        switch (level) {
            case LogLevel::TRACE: return "TRACE";
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO ";
            case LogLevel::WARN:  return "WARN ";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }

    // @TODO Dont use localtime
    std::string Logger::current_timestamp() {
        const auto now = std::chrono::system_clock::now();
        const auto time_t = std::chrono::system_clock::to_time_t(now);
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        oss << "." << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }
} // erb::coreutils
