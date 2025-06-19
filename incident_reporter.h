#pragma once
#include <string>
#include <vector>

class IncidentReporter {
public:
    void run();

private:
    void showMenu();
    void captureIncident();
    void viewIncidents();
    void clearIncidents();

    void saveToFile(const std::string& data);
    std::string generateTimestamp();
    std::string generateID();

    std::string promptInput(const std::string& message);
    std::vector<std::string> promptMultipleInputs(const std::string& message);
    std::string selectCategory();
};
