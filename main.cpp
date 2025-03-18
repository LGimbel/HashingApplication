#include <iostream>
#include <unordered_map>
#include <string>

//menu
void menu() {
    std::unordered_map<std::string, int> PartsMap;
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
                //TODO remove part function
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

                break;
            }

            case 4: {
                // Display All Parts
                //TODO display all parts function
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
                //TODO import from file function
                break;
            }

            case 7: {
                // Export to File
                //TODO export to file function
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
                        //TODO call export to file function
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
