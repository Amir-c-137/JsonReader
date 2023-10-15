// there is an error while running the program on my windos os, i guess its about json file path in my windows
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <algorithm> // for std::transform

using json = nlohmann::json;

// Function to check if the name is in the JSON data (case-insensitive)
bool isNameInJSON(const std::string& name, const json& jsonData) {
    // Convert the name to lowercase for case-insensitive comparison
    std::string lowercaseName = name;
    std::transform(lowercaseName.begin(), lowercaseName.end(), lowercaseName.begin(), ::tolower);

    for (const auto& person : jsonData) {
        if (person.find("name") != person.end()) {
            std::string personName = person["name"];
            // Convert the person's name to lowercase for comparison
            std::transform(personName.begin(), personName.end(), personName.begin(), ::tolower);

            if (personName == lowercaseName) {
                return true;
            }
        }
    }
    return false;
}

// Function to get and display the full information of a person by name (case-insensitive)
void displayPersonInfo(const std::string& name, const json& jsonData) {
    // Convert the name to lowercase for case-insensitive comparison
    std::string lowercaseName = name;
    std::transform(lowercaseName.begin(), lowercaseName.end(), lowercaseName.begin(), ::tolower);

    for (const auto& person : jsonData) {
        if (person.find("name") != person.end()) {
            std::string personName = person["name"];
            // Convert the person's name to lowercase for comparison
            std::transform(personName.begin(), personName.end(), personName.begin(), ::tolower);

            if (personName == lowercaseName) {
                std::cout << "ID: " << person["id"] << "\n"; // Display the ID
                std::cout << "Name: " << person["name"] << "\n";
                std::cout << "Age: " << person["age"] << "\n";
                std::cout << "Address: " << person["address"] << "\n";
                std::cout << "Email: " << person["email"] << "\n";
                return;  // Stop searching after finding the person
            }
        }
    }
}

// Function to save JSON data to a file
void saveJSONToFile(const json& jsonData, const std::string& filename) {
    std::ofstream jsonFile(filename);
    jsonFile << jsonData.dump(4); // 4 spaces for indentation
    jsonFile.close();
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
        std::cout << "1. Check if a person is in the JSON data\n";
        std::cout << "2. View all persons in the JSON data\n";
        std::cout << "3. Modify and Update Data\n";
        std::cout << "4. Exit\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Choose an option: ";
        int option;
        std::cin >> option;
        std::cout << "\n";

        if (option == 1) {
            // Option 1: Check if a specific name is in the JSON data (case-insensitive)
            std::cout << "Enter a name: ";
            std::string name;
            std::cin.ignore();  // Consume the newline character
            std::getline(std::cin, name);

            if (isNameInJSON(name, jsonData["people"])) {
                std::cout << "----------------------------------------\n";
                std::cout << "The name '" << name << "' is in the JSON data. Here is the person's information:\n";
                displayPersonInfo(name, jsonData["people"]);
                std::cout << "----------------------------------------\n";

            } else {
                std::cout << "----------------------------------------\n";
                std::cout << "The name '" << name << "' is not in the JSON data." << std::endl;
                std::cout << "----------------------------------------\n";
            }
        } else if (option == 2) {
            // Option 2: View all persons in the JSON data
            std::cout << "Persons in the JSON data:\n";
            for (const auto& person : jsonData["people"]) {
                std::cout << "ID: " << person["id"] << "\n"; // Display the ID
                std::cout << "Name: " << person["name"] << "\n";
                std::cout << "Age: " << person["age"] << "\n";
                std::cout << "Address: " << person["address"] << "\n";
                std::cout << "Email: " << person["email"] << "\n";
                std::cout << "----------------------------------------\n";
            }
        } else if (option == 3) {
            // Option 3: Modify and Update Data
            int modifyOption;
            std::cout << "1. Add a person\n";
            std::cout << "2. Remove a person\n";
            std::cout << "3. Edit a person\n";
            std::cout << "4. Back to the main menu\n";
            std::cout << "Choose an option: ";
            std::cin >> modifyOption;

            if (modifyOption == 1) {
                // Option: Add a person
                std::string name, address, email;
                int age;

                std::cout << "Enter the name: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                std::cout << "Enter the age: ";
                std::cin >> age;

                std::cout << "Enter the address: ";
                std::cin.ignore();
                std::getline(std::cin, address);

                std::cout << "Enter the email: ";
                std::cin >> email;

                // Find the highest ID and add 1 for the new person
                int highestID = 0;
                for (const auto& person : jsonData["people"]) {
                    if (person.find("id") != person.end()) {
                        int personID = person["id"];
                        highestID = std::max(highestID, personID);
                    }
                }

                // Create a new person JSON object with the next ID
                json newPerson = {
                    {"id", highestID + 1},
                    {"name", name},
                    {"age", age},
                    {"address", address},
                    {"email", email}
                };

                jsonData["people"].push_back(newPerson);

                // Save the updated data to the file
                saveJSONToFile(jsonData, "data.json");
                std::cout << "Person added to the JSON data.\n";
            } else if (modifyOption == 2) {
                // Option: Remove a person
                std::cout << "Enter the ID of the person to remove: ";
                int idToRemove;
                std::cin >> idToRemove;

                // Find and remove the person with the specified ID
                for (auto it = jsonData["people"].begin(); it != jsonData["people"].end(); ++it) {
                    if (it->find("id") != it->end() && (*it)["id"] == idToRemove) {
                        jsonData["people"].erase(it);
                        saveJSONToFile(jsonData, "data.json");
                        std::cout << "Person with ID " << idToRemove << " removed from the JSON data.\n";
                        break;  // Break after the first match
                    }
                }
            } else if (modifyOption == 3) {
                // Option: Edit a person
                std::cout << "Enter the ID of the person to edit: ";
                int idToEdit;
                std::cin >> idToEdit;

                // Find and edit the person with the specified ID
                for (auto& person : jsonData["people"]) {
                    if (person.find("id") != person.end() && person["id"] == idToEdit) {
                        std::cout << "Enter the new name: ";
                        std::string newName;
                        std::cin.ignore();
                        std::getline(std::cin, newName);
                        person["name"] = newName;

                        std::cout << "Enter the new age: ";
                        int newAge;
                        std::cin >> newAge;
                        person["age"] = newAge;

                        std::cout << "Enter the new address: ";
                        std::string newAddress;
                        std::cin.ignore();
                        std::getline(std::cin, newAddress);
                        person["address"] = newAddress;

                        std::cout << "Enter the new email: ";
                        std::string newEmail;
                        std::cin >> newEmail;
                        person["email"] = newEmail;

                        saveJSONToFile(jsonData, "data.json");
                        std::cout << "Person with ID " << idToEdit << " updated in the JSON data.\n";
                        break;  // Break after the first match
                    }
                }
            } else if (modifyOption == 4) {
                // Option: Back to the main menu
                continue;
            } else {
                std::cout << "Invalid modification option. Please choose a valid option.\n";
            }
        } else if (option == 4) {
            // Option 4: Exit the program
            break;
        } else {
            std::cout << "Invalid option. Please choose a valid option.\n";
        }
    }

    // Close the file when done
    jsonFile.close();

    return 0;
}
