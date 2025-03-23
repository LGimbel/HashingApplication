#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>  
#include <random>    

// Function to add a part with a random integer as its part number
void addPart(std::unordered_map<std::string, int> &PartsMap, const std::string &partName) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000); // Random numbers between 1 and 1000
    int partNumber = distrib(gen);
    PartsMap[partName] = partNumber;
    std::cout << "Part '" << partName << "' added with random number: " << partNumber << "\n";
}

// Function to populate the map with a given number of random parts
void populateRandomParts(std::unordered_map<std::string, int> &PartsMap, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000);
    for (int i = 0; i < count; i++) {
        std::string partName = "RandPart_" + std::to_string(i + 1);
        int partNumber = distrib(gen);
        PartsMap[partName] = partNumber;
        std::cout << "Added " << partName << " with number " << partNumber << "\n";
    }
}

// Function to remove a part from the map by name
void removePart(std::unordered_map<std::string, int> &PartsMap, const std::string &partName) {
    auto it = PartsMap.find(partName);
    if (it != PartsMap.end()) {
        PartsMap.erase(it);
        std::cout << "Part '" << partName << "' removed successfully.\n";
    } else {
        std::cout << "Part '" << partName << "' not found. Please Try Again.\n";
    }
}

// Function to export data to a file
void exportToFile(const std::unordered_map<std::string, int> &PartsMap, const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cout << "Error opening file '" << filename << "' for writing.\n";
        return;
    }
    for (const auto &entry: PartsMap) {
        outfile << entry.first << " " << entry.second << "\n";
    }
    outfile.close();
    std::cout << "Data exported to file '" << filename << "' successfully.\n";
}

// Function to import data from a file
void importFromFile(std::unordered_map<std::string, int> &PartsMap, const std::string &filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cout << "Error opening file '" << filename << "' for reading.\n";
        return;
    }
    PartsMap.clear();  // Clear existing data to avoid duplicates; remove if merging is desired.
    std::string partName;
    int partNumber;
    while (infile >> partName >> partNumber) {
        PartsMap[partName] = partNumber;
    }
    infile.close();
    std::cout << "Data imported from file '" << filename << "' successfully.\n";
}

// Function to search for a part by name
void searchPart(const std::unordered_map<std::string, int> &PartsMap, const std::string &partName) {
    auto it = PartsMap.find(partName);
    if (it != PartsMap.end()) {
        std::cout << "Part found: " << it->first << " - " << it->second << "\n";
    } else {
        std::cout << "Part '" << partName << "' not found.\n";
    }
}

// Function to display all parts in the map
void displayAllParts(const std::unordered_map<std::string, int> &PartsMap) {
    if (PartsMap.empty()) {
        std::cout << "No parts available to display.\n";
        return;
    }
    std::cout << "All parts:\n";
    for (const auto &entry: PartsMap) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
}

// Menu function for user interaction
void menu() {
    std::unordered_map<std::string, int> partsMap;
    int choice = 0, value = 0;
    std::string partName;
    bool hasSaved = true, exit = false;
    const std::string menuText =
            "Please choose one of the following:\n"
            "1. Add Part\n"
            "2. Remove Part\n"
            "3. Search for Part by Name\n"
            "4. Display All Parts\n"
            "5. Populate Random Parts\n"
            "6. Import from File\n"
            "7. Export to File\n"
            "8. Exit\n";
    while (!exit) {
        std::cout << menuText;
        std::cin >> choice;
        std::cin.ignore(); // Consume the newline left in the input buffer
        switch (choice) {
            case 1: {
                // Add Part
                std::cout << "Please enter the name of the part:\n";
                std::getline(std::cin, partName); // Allows part names with spaces
                if (partName.empty()) {
                    std::cout << "Part name cannot be empty. Please try again.\n";
                    break;
                }
                addPart(partsMap, partName);
                hasSaved = false;
                break;
            }
            case 2: {
                // Remove Part
                std::cout << "Enter the name of the part to remove:\n";
                std::getline(std::cin, partName);
                if (partName.empty()) {
                    std::cout << "Part name cannot be empty. Please try again.\n";
                    break;
                }
                removePart(partsMap, partName);
                hasSaved = false;
                break;
            }
            case 3: {
                // Search for Part by Name
                std::cout << "Enter the name of the part to search for:\n";
                std::getline(std::cin, partName);
                if (partName.empty()) {
                    std::cout << "Part name cannot be empty. Please try again.\n";
                    break;
                }
                searchPart(partsMap, partName);
                break;
            }
            case 4: {
                // Display All Parts
                displayAllParts(partsMap);
                break;
            }
            case 5: {
                // Populate Random Parts
                std::cout << "How many random parts would you like to add?\n";
                std::cin >> value;
                std::cin.ignore(); // consume newline
                if (value <= 0) {
                    std::cout << "Please enter a positive number.\n";
                    break;
                }
                populateRandomParts(partsMap, value);
                hasSaved = false;
                break;
            }
            case 6: {
                // Import from File
                importFromFile(partsMap, "partsdata.txt");
                hasSaved = true;
                break;
            }
            case 7: {
                // Export to File
                exportToFile(partsMap, "partsdata.txt");
                hasSaved = true;
                break;
            }
            case 8: {
                // Exit
                if (!hasSaved) {
                    std::cout << "You have unsaved changes. Do you want to save before exiting? (y/n): ";
                    char saveChoice;
                    std::cin >> saveChoice;
                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        exportToFile(partsMap, "partsdata.txt");
                    }
                }
                exit = true;
                std::cout << "Thank you for using the parts management system." << std::endl;
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
