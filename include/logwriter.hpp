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
    /// @brief форматирование времени записи лога
    const char *const LOG_TIME_FORMAT = "%Y-%m-%d %H:%M:%S";
    /// @brief заглушка если время получить не удалось
    const std::string NO_TIME = "<TIME>";

    /// @brief Доступные уровни логирования
    struct LoggerLevels
    {
        std::string INFO = "INFO";
        std::string WARN = "WARN";
        std::string ERROR = "ERROR";
        /// @brief Сопоставление уровню лога числа для их сравнения
        std::unordered_map<std::string, int> mapped{{INFO, 10}, {WARN, 20}, {ERROR, 30}};
    } loggerLevels;

    /// @brief Класс логгера для записи в файл
    class LogWriter
    {
    private:
        /// @brief Параметры логгера - имя файла лога и уровень лога по умолчанию
        std::string fileName;
        std::string defaultLogLevel = loggerLevels.INFO;

    public:
        LogWriter(std::string fileName, std::string defaultLogLvl);
        ~LogWriter();

        /// @brief геттер уровня лога по умолчанию
        /// @return возвращает уровень лога в виде текста
        std::string getLogLevel();

        /// @brief сеттер уровня лога по умолчанию
        /// @param logLvl - уровень лога в виде теста
        /// @return возвращает уровень лога в виде текста
        std::string setLogLevel(std::string logLvl);

        /// @brief Является ли строка валидным уровнем лога
        /// @param logLvl - уровень лога в виде теста
        bool isLogLevel(std::string logLvl);

        /// @brief Залогировать сообщение
        /// @param msg - строка сообщения
        void logMessage(std::string msg);

        /// @brief Залогировать сообщение с указанным уровнем лога
        /// @param message - строка сообщения
        /// @param logLvl - уровень важности сообщения
        void logMessage(std::string message, std::string logLvl);

        /// @brief Залогировать сообщение с указанным уровнем лога и временем
        /// @param message - строка сообщения
        /// @param logLvl - уровень важности сообщения
        /// @param fTime - отформатированная строка времени для записи в лог
        void logMessage(std::string message, std::string logLvl, std::string fTime);

        /// @brief Получить текущее время в формате LOG_TIME_FORMAT
        /// @return отформатированное время
        std::string getFormattedTime();
    };

}
