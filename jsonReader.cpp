#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

// Function to check if the name is in the JSON data
bool isNameInJSON(const std::string& name, const json& jsonData) {
    for (const auto& person : jsonData) {
        if (person.find("name") != person.end() && person["name"] == name) {
            return true;
        }
    }
    return false;
}

// Function to get and display the full information of a person by name
void displayPersonInfo(const std::string& name, const json& jsonData) {
    for (const auto& person : jsonData) {
        if (person.find("name") != person.end() && person["name"] == name) {
            std::cout << "Name: " << person["name"] << "\n";
            std::cout << "Age: " << person["age"] << "\n";
            std::cout << "Address: " << person["address"] << "\n";
            std::cout << "Email: " << person["email"] << "\n";
            return;  // Stop searching after finding the person
        }
    }
}

int main() {
    // Open and read the JSON file
    std::ifstream jsonFile("data.json");
    if (!jsonFile.is_open()) {
        std::cerr << "Failed to open the JSON file." << std::endl;
        return 1;
    }

    // Parse the JSON data
    json jsonData;
    jsonFile >> jsonData;

    // Display a menu
    while (true) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Check if a person is in the JSON data\n";
        std::cout << "2. View all persons in the JSON data\n";
        std::cout << "3. Exit\n";
        int option;
        std::cin >> option;

        if (option == 1) {
            // Option 1: Check if a specific name is in the JSON data
            std::cout << "Enter a name: ";
            std::string name;
            std::cin.ignore();  // Consume the newline character
            std::getline(std::cin, name);

            if (isNameInJSON(name, jsonData["people"])) {
                std::cout << "The name '" << name << "' is in the JSON data. Here is the person's information:\n";
                displayPersonInfo(name, jsonData["people"]);
            } else {
                std::cout << "The name '" << name << "' is not in the JSON data." << std::endl;
            }
        } else if (option == 2) {
            // Option 2: View all persons in the JSON data
            std::cout << "Persons in the JSON data:\n";
            for (const auto& person : jsonData["people"]) {
                std::cout << "Name: " << person["name"] << "\n";
                std::cout << "Age: " << person["age"] << "\n";
                std::cout << "Address: " << person["address"] << "\n";
                std::cout << "Email: " << person["email"] << "\n";
                std::cout << "----------------------\n";
            }
        } else if (option == 3) {
            // Option 3: Exit the program
            break;
        } else {
            std::cout << "Invalid option. Please choose a valid option.\n";
        }
    }

    // Close the file when done
    jsonFile.close();

    return 0;
}
