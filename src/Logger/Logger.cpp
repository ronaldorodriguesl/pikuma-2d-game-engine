#include "Logger.h"
#include <iostream>
#include <ctime>

std::vector<LogEntry> Logger::messages;

std::string CurrentDateTimeToString()
{
    std::time_t now = std::time(nullptr);
    char buffer[26];
    std::strftime(buffer, sizeof(buffer), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
    return buffer;
}

void Logger::Log(const std::string &message)
{
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG: [" + CurrentDateTimeToString() + "]: " + message;

    std::cout << "\033[32m" << logEntry.message << "\033[0m" << std::endl;

    messages.push_back(logEntry);
}

void Logger::Err(const std::string &message)
{
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "ERR: [" + CurrentDateTimeToString() + "]: " + message;

    std::cerr << "\033[31m" << logEntry.message << "\033[0m" << std::endl;

    messages.push_back(logEntry);
}
