/*
main.cpp
Author: Eduardo Hernández Alonso - A01707225
 */

#include "weapon.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
    std::vector<Weapon> weapons;
    loadWeapons("weapons.txt", weapons);

    std::string backToMenu = "yes";
    int option;

    while (backToMenu == "yes") {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "WEAPON SELECTOR\n";
        std::cout << "Main menu:\n";
        std::cout << "1) Show inventory\n";
        std::cout << "2) Add weapon\n";
        std::cout << "3) Sort inventory\n";
        std::cout << "4) Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> option;

        if (option == 1) {
            std::cout << "\nINVENTORY--------------------------\n";
            showWeapons(weapons);

        } else if (option == 2) {
            std::string name, type, exclusivity;
            std::cout << "\nADD WEAPON--------------------\n";
            std::cout << "Add a new weapon to the inventory:\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter the weapon name (The first letter MUST be a capital letter): ";
            std::getline(std::cin, name);
            std::cout << "Enter the type (Melee/Firearm/Throwable) (The first letter MUST be a capital letter): ";
            std::getline(std::cin, type);
            std::cout << "Enter the exclusivity (Shared/HM1/HM2) (Write the exclusivity type as it's shown): ";
            std::getline(std::cin, exclusivity);

            std::string line = name + "," + type + "," + exclusivity;
            weapons.push_back(Weapon(line));
            std::cout << "\nWeapon added successfully!\n";

        } else if (option == 3) {
            std::string sortAgain = "yes";
            int sortCriterion;
            while (sortAgain == "yes") {
                std::cout << "\nSORT INVENTORY----------------------\n";
                std::cout << "1) By name\n";
                std::cout << "2) By type\n";
                std::cout << "3) By exclusivity\n";
                std::cout << "Choose the sorting type: ";
                std::cin >> sortCriterion;

                if (sortCriterion >= 1 && sortCriterion <= 3) {
                    quickSort(weapons, 0, weapons.size() - 1, sortCriterion);
                    std::cout << "\nInventory sorted!" << std::endl;
                    showWeapons(weapons);
                } else {
                    std::cout << "\nInvalid input.\n";
                }

                if (backToMenu != "no") {
                    std::cout << "Do you want to sort again? (yes/no): ";
                    std::cin >> sortAgain;
                }
            }

        } else if (option == 4) {
            backToMenu = "no";

        } else {
            std::cout << "Invalid option, please try again.\n";
        }

        if (backToMenu != "no" && option != 4) {
            std::cout << "\nDo you want to return to the menu? (yes/no): ";
            std::cin >> backToMenu;
        }
    }

    std::cout << "\nThank you for using the Hotline Miami Weapon Selector.\n";
    return 0;
}