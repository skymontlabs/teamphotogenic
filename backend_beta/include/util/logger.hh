#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>

class Logger {
public:
    Logger(const std::string& fileName) : logFile(fileName, std::ios::app) {
        if (!logFile.is_open()) {
            throw std::runtime_error("Unable to open log file: " + fileName);
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void Log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mu);
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        logFile << std::ctime(&now_c) << ": " << message << std::endl;
    }

private:
    std::ofstream logFile;
    std::mutex mu;
};

// Example usage
int main() {
    try {
        Logger logger("app_log.txt");

        logger.Log("Application started");
        // ... rest of the application logic
        logger.Log("Application finished");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
