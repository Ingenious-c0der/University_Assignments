#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

int main() {
    // Configure logging
    std::ofstream logFile("event_log.txt");
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return 1;
    }

    // Sample log entries
    std::vector<std::string> logEntries = {
        "Error: Failed to connect to database",
        "Info: User login successful",
        "Warning: Disk space is low",
        "Error: Database server is down",
        "Info: User logout"
    };

    // Define event patterns to correlate
    std::regex errorPattern("Error: (.+)");
    std::regex infoPattern("Info: (.+)");
    std::regex warningPattern("Warning: (.+)");

    // Process log entries and correlate events
    for (const std::string& logEntry : logEntries) {
        logFile << logEntry << std::endl;

        std::smatch match;
        if (std::regex_match(logEntry, match, errorPattern)) {
            std::string errorMessage = match[1];
            std::cout << "Correlated Error Event: " << errorMessage << std::endl;
        }

        if (std::regex_match(logEntry, match, infoPattern)) {
            std::string infoMessage = match[1];
            std::cout << "Correlated Info Event: " << infoMessage << std::endl;
        }

        if (std::regex_match(logEntry, match, warningPattern)) {
            std::string warningMessage = match[1];
            std::cout << "Correlated Warning Event: " << warningMessage << std::endl;
        }
    }

    // Close the log file
    logFile.close();

    return 0;
}