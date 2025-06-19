#include "incident_reporter.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdlib>

void IncidentReporter::run() {
    while (true) {
        showMenu();
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") captureIncident();
        else if (choice == "2") viewIncidents();
        else if (choice == "3") clearIncidents();
        else if (choice == "4") break;
        else std::cout << "Invalid choice.\n";
    }
}

void IncidentReporter::showMenu() {
    std::cout << "\n=== Secure Incident Reporter ===\n"
              << "1. Report an Incident\n"
              << "2. View Reports\n"
              << "3. Clear All Reports (Admin)\n"
              << "4. Exit\n"
              << "Choose: ";
}

void IncidentReporter::captureIncident() {
    std::string name = promptInput("Enter your name (or leave blank for anonymous):");
    std::string type = selectCategory();
    std::string description = promptInput("Enter description of the incident:");
    auto mediaFiles = promptMultipleInputs("Enter media file path (type 'done' to finish):");

    std::string timestamp = generateTimestamp();
    std::string reportID = generateID();

    std::ostringstream report;
    report << "\n--- Incident Report ---\n"
           << "ID: " << reportID << "\n"
           << "Time: " << timestamp
           << "Reporter: " << (name.empty() ? "Anonymous" : name) << "\n"
           << "Type: " << type << "\n"
           << "Description: " << description << "\n"
           << "Media Files:\n";

    for (const auto& file : mediaFiles)
        report << "  - " << file << "\n";

    std::cout << "\nReview your report:\n" << report.str()
              << "\nSave this report? (y/n): ";
    std::string confirm;
    std::getline(std::cin, confirm);

    if (tolower(confirm[0]) == 'y') {
        saveToFile(report.str());
        std::cout << "✅ Report saved successfully.\n";
    } else {
        std::cout << "❌ Report discarded.\n";
    }
}

std::string IncidentReporter::promptInput(const std::string& message) {
    std::string input;
    std::cout << message << "\n> ";
    std::getline(std::cin, input);
    return input;
}

std::vector<std::string> IncidentReporter::promptMultipleInputs(const std::string& message) {
    std::vector<std::string> inputs;
    std::string input;
    while (true) {
        std::cout << message << "\n> ";
        std::getline(std::cin, input);
        if (input == "done") break;
        if (!input.empty()) inputs.push_back(input);
    }
    return inputs;
}

std::string IncidentReporter::selectCategory() {
    std::vector<std::string> categories = {
        "Theft", "Vandalism", "Harassment", "Suspicious Activity", "Other"
    };
    std::cout << "Select Incident Type:\n";
    for (size_t i = 0; i < categories.size(); ++i)
        std::cout << i + 1 << ". " << categories[i] << "\n";

    int index;
    while (true) {
        std::cout << "> ";
        std::cin >> index;
        std::cin.ignore();
        if (index >= 1 && index <= categories.size()) return categories[index - 1];
        std::cout << "Invalid selection. Try again.\n";
    }
}

std::string IncidentReporter::generateTimestamp() {
    std::time_t now = std::time(nullptr);
    return std::string(std::ctime(&now));
}

std::string IncidentReporter::generateID() {
    static int counter = 1000 + rand() % 999;
    return "IR" + std::to_string(counter++);
}

void IncidentReporter::saveToFile(const std::string& data) {
    std::ofstream file("incidents.txt", std::ios::app);
    if (file.is_open()) {
        file << data << "\n";
        file.close();
    } else {
        std::cerr << "Error: Cannot save to file.\n";
    }
}

void IncidentReporter::viewIncidents() {
    std::ifstream file("incidents.txt");
    if (file.is_open()) {
        std::cout << "\n=== Saved Reports ===\n";
        std::string line;
        while (std::getline(file, line))
            std::cout << line << "\n";
        file.close();
    } else {
        std::cerr << "No incident reports found.\n";
    }
}

void IncidentReporter::clearIncidents() {
    std::string confirm = promptInput("Are you sure you want to delete all reports? (admin use only) (y/n):");
    if (tolower(confirm[0]) == 'y') {
        std::ofstream file("incidents.txt", std::ios::trunc);
        if (file.is_open()) {
            file.close();
            std::cout << "All reports have been deleted.\n";
        }
    } else {
        std::cout << "Aborted.\n";
    }
}
