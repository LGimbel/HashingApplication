#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream> // for file handling

void removePart(std::unordered_map<std::string, int> &PartsMap, const std::string &partName) {
    auto it = PartsMap.find(partName);
    if (it != PartsMap.end()) {
        PartsMap.erase(it);
        std::cout << "Part '" << partName << "' removed successfully.\n";
    } else {
        std::cout << "Part '" << partName << "' not found. Please Try Again.\n";
    }
}

// function to export data to file
void exportToFile(const std::unordered_map<std::string, int> &PartsMap, const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cout << "Error opening file '" << filename << "' for writing.\n";
        return;
    }
    for (const auto &entry: PartsMap) {
        outfile << entry.first << " " << entry.second << "\n"; // write part name and number to file
    }
    outfile.close(); // close the file
    std::cout << "Data exported to file '" << filename << "' successfully.\n";
}

// function to import data from file
void importFromFile(std::unordered_map<std::string, int> &PartsMap, const std::string &filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cout << "Error opening file '" << filename << "' for reading.\n";
        return;
    }
    PartsMap.clear(); // clears existing data before importing to avoid duplicates; remove if merging data is preferred
    std::string partName;
    int partNumber;
    while (infile >> partName >> partNumber) {
        PartsMap[partName] = partNumber; // read part name and number from file and add to map
    }
    infile.close(); // close the file
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

// Function to display all parts
void displayAllParts(const std::unordered_map<std::string, int> &PartsMap) {
    if (PartsMap.empty()) {
        std::cout << "No parts available to display.\n";
        return;
    }
    std::cout << "All parts:\n";
    for (const auto &entry: PartsMap) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
    //note for the future when printing pairs you can use structured bindings which would just be const auto &[first, second]:
}


//menu
void menu() {
    std::unordered_map<std::string, int> partsMap;
    // remember to pass a reference to this map to the functions that will manipulate it.
    int choice = 0, value = 0;
    std::string partName;
    bool hasSaved = true, exit = false;
    auto const menu =
            "Please choose one of the following:\n1.Add Part\n2.Remove Part\n3.Search for Part by Name\n4.Display All Parts\n5.Populate Random Parts\n"
            "6.Import from File\n7.Export to File\n8.Exit\n";
    while (!exit) {
        std::cout << menu;
        std::cin >> choice;
        std::cin.ignore();
        //cin.ignore consumes the newline left in the input buffer from previous input needed for the use of getline.
        switch (choice) {
            case 1: {
                // Add Part
                std::cout << "Please enter the name of the part:\n";
                std::getline(std::cin, partName); // allows part names with spaces delimits on \n
                if (partName.empty()) {
                    std::cout << "Part name cannot be empty. Please try again.\n";
                    break;
                }
                //TODO add part function and get part number
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
                //TODO search part function
                std::cout << "Enter the name of the part to search for:\n";
                std::getline(std::cin, partName); // allows part names with spaces delimits on \n
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
                if (value <= 0) {
                    std::cout << "Please enter a positive number.\n";
                    break;
                }
                //TODO populate random parts function to make value random parts
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
                        exportToFile(partsMap, "partsdata.txt"); // save to file
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
