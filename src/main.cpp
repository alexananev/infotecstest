#include <iostream>
#include <string>
#include "logwriter.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Недостаточно параметров запуска приложения. Ожидается 3, получено " << argc << std::endl;
        return 0;
    }
    logwriter::LogWriter *logger = new logwriter::LogWriter(argv[1], argv[2]);

    
    while (1)
    {
        std::string msg;
        std::getline(std::cin, msg);
        if (msg == "END_OF_LOG")
        {
            break;
        }

        std::string logLvl = (msg[4] == ' ' ? msg.substr(0, 4) : msg.substr(0, 5));
        if (msg.length() > 6 && msg[5] == '|' && logger->isLogLevel(logLvl))
        {
            logger->logMessage(msg.substr(6, msg.length() - 6), logLvl);
        }
        else
        {
            logger->logMessage(msg);
        }
    }
    return 0;
}
