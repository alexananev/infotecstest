#include "logwriter.hpp"

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>

namespace logwriter
{
    bool LogWriter::isLogLevel(std::string logLvl)
    {
        /// Приводим к верхнему регистру
        std::transform(logLvl.begin(), logLvl.end(), logLvl.begin(), ::toupper);
        /// Ищем лог в доступных уровнях логирования
        auto myIt = loggerLevels.mapped.find(logLvl);
        if (myIt != loggerLevels.mapped.end())
        {
            return true;
        }
        return false;
    }

    LogWriter::LogWriter(std::string fileName, std::string defaultLogLvl)
    {
        /// устанавливаем параметры
        this->fileName = fileName;
        this->defaultLogLevel = this->setLogLevel(defaultLogLvl);

        /// Проверяем возможность создания файла лога
        std::ofstream fout(this->fileName);
        if (fout.is_open())
        {
            std::cout << "Successfully created log file at " << fileName << ". Default log level set to "
                      << this->defaultLogLevel << std::endl;
        }
        else
        {
            /// если не удалось - завершаем программу
            throw std::runtime_error("File not opened");
        }
        fout.close();
    }

    std::string LogWriter::getLogLevel()
    {
        return this->defaultLogLevel;
    }

    std::string LogWriter::getFormattedTime()
    {
        /// Получаем время
        std::time_t t = std::time(nullptr);
        char formatted[128];

        /// И записываем его в строку
        if (std::strftime(formatted, sizeof(formatted), LOG_TIME_FORMAT, std::localtime(&t)))
        {
            return formatted;
        }

        return NO_TIME;
    }

    std::string LogWriter::setLogLevel(std::string logLvl)
    {
        std::transform(logLvl.begin(), logLvl.end(), logLvl.begin(), ::toupper);

        /// Если передан валидный уровень лога, перезаписываем его
        if (this->isLogLevel(logLvl))
        {
            this->defaultLogLevel = logLvl;
        }
        return this->defaultLogLevel;
    }

    void LogWriter::logMessage(std::string msg)
    {
        /// Если уровень важности сообщения не передан, записываем с уровнем по умолчанию
        this->logMessage(msg, this->defaultLogLevel, this->getFormattedTime());
    }

    void LogWriter::logMessage(std::string msg, std::string logLvl)
    {
        this->logMessage(msg, logLvl, this->getFormattedTime());
    }

    void LogWriter::logMessage(std::string msg, std::string logLvl, std::string fTime)
    {
        /// Проверяем валидность уровня важности сообщения
        std::transform(logLvl.begin(), logLvl.end(), logLvl.begin(), ::toupper);
        if (this->isLogLevel(logLvl))
        {
            /// Проверяем не низкий ли уровень у сообщения
            if (loggerLevels.mapped[logLvl] >= loggerLevels.mapped[this->defaultLogLevel])
            {
                /// Проверяем, открылся ли файл лога, и записываем сообщение
                std::ofstream fout(this->fileName, std::ios::app);
                if (fout.is_open())
                {
                    fout << "[" << fTime << "] " << logLvl << ": "
                         << msg << std::endl;
                }
                else
                {
                    std::cout << "Cannot open log file." << std::endl;
                }
                fout.close();
            }
        }
        else
        {
            /// Если передан невалидный уровень лога, пишем под UNDEFINED
            std::ofstream fout(this->fileName, std::ios::app);
            if (fout.is_open())
            {
                fout << "[" << fTime << "] " << "UNDEFINED: "
                     << msg << std::endl;
            }
            else
            {
                std::cout << "Cannot open log file." << std::endl;
            }
            fout.close();
        }
    }

}