#include <iostream>
#include <string>
#include <future>
#include "logwriter.hpp"

int main(int argc, char *argv[])
{
    /// Проверяем наличие аргументов командной строки для запуска
    if (argc < 3)
    {
        std::cout << "Недостаточно параметров запуска приложения. Ожидается 3, получено " << argc << std::endl;
        return 0;
    }

    /// Инициализируем логгер
    logwriter::LogWriter *logger = new logwriter::LogWriter(argv[1], argv[2]);

    /// Цикл считывания сообщений. Т.к. не описан явно формат входных данных, просто бесконечный цикл
    /// с прерыванием при получении сообщения END_OF_LOG
    while (1)
    {
        std::string msg;
        std::getline(std::cin, msg);
        if (msg == "END_OF_LOG")
        {
            break;
        }

        /// Не задан формат сообшения, предположил "LOGLV|logmsg", где первый 5 символов уровень лога (с заполнением пробелом, т.е. "INFO ")
        /// затем '|', затем само сообщение.
        /// Здесь выделяем уровень лога
        std::string logLvl = (msg[4] == ' ' ? msg.substr(0, 4) : msg.substr(0, 5));
        /// Проверяем формат сообщения и является ли уровень лога в сообщении валидным
        if (msg.length() > 6 && msg[5] == '|' && logger->isLogLevel(logLvl))
        {
            /// Если ок, запускаем асинхронно, разделив уровень лога и сам лог
            auto futureLog = std::async(std::launch::async, static_cast<void (logwriter::LogWriter::*)(std::string, std::string)>(&logwriter::LogWriter::logMessage), logger, msg.substr(6, msg.length() - 6), logLvl);
        }
        else
        {
            /// Иначе считаем все сообщение логом
            auto futureLog = std::async(std::launch::async, static_cast<void (logwriter::LogWriter::*)(std::string)>(&logwriter::LogWriter::logMessage), logger, msg);
        }
    }
    return 0;
}
