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

    // Prompt the user for a name
    std::cout << "Enter a name: ";
    std::string name;
    std::getline(std::cin, name);

    // Check if the provided name is in the JSON data
    if (isNameInJSON(name, jsonData["people"])) {
        std::cout << "The name '" << name << "' is in the JSON data." << std::endl;
    } else {
        std::cout << "The name '" << name << "' is not in the JSON data." << std::endl;
    }

    // Close the file when done
    jsonFile.close();

    return 0;
}
