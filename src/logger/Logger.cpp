#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

#include "Logger.h"

// Could just use spdlog.

std::vector<LogEntry> Logger::messages;

std::string CurrentDateTimeString() {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
    return output;
}

void Logger::Log(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG: [" + CurrentDateTimeString() + "] - " + message;

    std::cout << "\e[0;92m" << logEntry.message << "\033[0m" << std::endl; 

    messages.push_back(logEntry);
}

void Logger::Err(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "ERR: [" + CurrentDateTimeString() + "] - " + message;
    std::cerr << "\033[31m" << logEntry.message << "\033[0m" << std::endl;    

    messages.push_back(logEntry);
}
