/**
 * @brief Запись логов в журнал с указанным уровнем важности
 *
 *
 */


#include <string>
#include <unordered_map>
#pragma once

namespace logwriter
{
    const char *const LOG_TIME_FORMAT = "%Y-%m-%d %H:%M:%S";
    const std::string NO_TIME = "<TIME>";

    /// @brief Доступные уровни логирования
    struct LoggerLevels
    {
        std::string INFO = "INFO";
        std::string WARN = "WARN";
        std::string ERROR = "ERROR";
        std::unordered_map<std::string, int> mapped{{INFO, 10}, {WARN, 20}, {ERROR, 30}};
    } loggerLevels;

    class LogWriter
    {
    private:
        std::string fileName;
        std::string defaultLogLevel = loggerLevels.INFO;

    public:
        LogWriter(std::string fileName, std::string defaultLogLvl);
        ~LogWriter();

        std::string getLogLevel();
        std::string setLogLevel(std::string logLvl);
        bool isLogLevel(std::string logLvl);

        void logMessage(std::string msg);
        void logMessage(std::string message, std::string logLvl);
        void logMessage(std::string message, std::string logLvl, std::string fTime);

        std::string getFormattedTime();
    };

}
