#include "xeno-pal.hpp"
#include <chrono>
#include <iostream>

namespace xeno
{
    namespace pal
    {
        Logger::Logger(const std::string &filename) : m_logFile(filename, std::ios::out | std::ios::app)
        {
            if (!m_logFile.is_open())
            {
                throw std::runtime_error("Failed to open log file.");
            }
        }

        Logger::~Logger()
        {
            if (m_logFile.is_open())
            {
                m_logFile.close();
            }
        }

        void Logger::log(const std::string &message, LogLevel level)
        {
            std::lock_guard<std::mutex> lock(m_logMutex);
            if (m_logFile.is_open())
            {
                // m_logFile << timestamp() << " [" << levelToString(level) << "] " << message << std::endl;
                // Also print to console if you want:
                // std::cout << timestamp() << " [" << levelToString(level) << "] " << message << std::endl;
            }
        }

        void Logger::logInfo(const std::string &message)
        {
            log(message, LogLevel::Info);
        }

        void Logger::logWarning(const std::string &message)
        {
            log(message, LogLevel::Warning);
        }

        void Logger::logError(const std::string &message)
        {
            log(message, LogLevel::Error);
        }
        void Logger::flush()
        {
            std::lock_guard<std::mutex> lock(m_logMutex);
            if (m_logFile.is_open())
            {
                m_logFile.flush();
            }
        }
    }
}