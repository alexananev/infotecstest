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
        std::transform(logLvl.begin(), logLvl.end(), logLvl.begin(), ::toupper);
        auto myIt = loggerLevels.mapped.find(logLvl);
        if (myIt != loggerLevels.mapped.end())
        {
            return true;
        }
        return false;
    }

    LogWriter::LogWriter(std::string fileName, std::string defaultLogLvl)
    {
        this->fileName = fileName;
        this->defaultLogLevel = this->setLogLevel(defaultLogLvl);
        std::ofstream fout(this->fileName);
        if (fout.is_open())
        {
            std::cout << "Successfully created log file at " << fileName << ". Default log level set to "
                      << this->defaultLogLevel << std::endl;
        }
        else
        {
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
        std::time_t t = std::time(nullptr);
        char formatted[128];

        if (std::strftime(formatted, sizeof(formatted), LOG_TIME_FORMAT, std::localtime(&t)))
        {
            return formatted;
        }

        return NO_TIME;
    }

    std::string LogWriter::setLogLevel(std::string logLvl)
    {
        std::transform(logLvl.begin(), logLvl.end(), logLvl.begin(), ::toupper);
        if (this->isLogLevel(logLvl))
        {
            this->defaultLogLevel = logLvl;
        }
        return this->defaultLogLevel;
    }

    void LogWriter::logMessage(std::string msg)
    {
        this->logMessage(msg, this->defaultLogLevel, this->getFormattedTime());
    }

    void LogWriter::logMessage(std::string msg, std::string logLvl)
    {
        this->logMessage(msg, logLvl, this->getFormattedTime());
    }

    void LogWriter::logMessage(std::string msg, std::string logLvl, std::string fTime)
    {
        std::transform(logLvl.begin(), logLvl.end(), logLvl.begin(), ::toupper);
        if (this->isLogLevel(logLvl))
        {
            if (loggerLevels.mapped[logLvl] >= loggerLevels.mapped[this->defaultLogLevel])
            {
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
            // this->logMessage(msg, loggerLevels.mapped[logLvl]);
        }
        else
        {
            std::ofstream fout(this->fileName, std::ios::app);
            if (fout.is_open())
            {
                fout << "[<TIME>]: UNDEFINED: "
                     << msg << std::endl;
            }
            else
            {
                std::cout << "Cannot open log file." << std::endl;
            }
            fout.close();
        }
    }

    void LogWriter::logMessage(std::string msg, int logLvl)
    {
    }
}