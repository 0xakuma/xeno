#include "xeno-pal.hpp"

namespace xeno
{
    namespace pal
    {
        Logger::Logger()
        {
            // Initialize logger settings
            m_logFile.open("xeno_log.txt", std::ios::out | std::ios::app);
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

        Logger::log(const std::string &message, LogLevel level)
        {
            std::lock_guard<std::mutex> lock(m_logMutex);
            if (m_logFile.is_open())
            {
                m_logFile << timestamp() << " [" << levelToString(level) << "] " << message << std::endl;
                // Also print to console if you want:
                std::cout << timestamp() << " [" << levelToString(level) << "] " << message << std::endl;
            }
        }

        Logger::logInfo(const std::string &message)
        {
            log(message, LogLevel::Info);
        }

        Logger::logWarning(const std::string &message)
        {
            log(message, LogLevel::Warning);
        }

        Logger::logError(const std::string &message)
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