/*
main.cpp
Author: Eduardo Hernández Alonso - A01707225
 */

 #include "weapon.h"
 #include <iostream>
 #include <limits>
 #include <string>
 #include <vector>
 #include <algorithm>
 #include <cctype>
 
// Convierte una cadena a formato de nombre propio.
 std::string toProperCase(const std::string& str) {
     if (str.empty()) {
        return str;
    }
     std::string result = str;
     result[0] = std::toupper(result[0]);
     for (size_t i = 1; i < result.length(); i++) {
         result[i] = std::tolower(result[i]);
     }
     return result;
 }
 
 
 // Convierte una cadena completa a mayúsculas.
 std::string toUpperCase(const std::string& str) {
     std::string result = str;
     std::transform(result.begin(), result.end(), result.begin(), ::toupper);
     return result;
 }
 
 int main() {
     std::vector<Weapon> weapons;
     loadWeapons("weapons.txt", weapons);
 
     int option;
     bool running = true;
 
     while (running) {
         std::cout << "\n-----------------------------------" << std::endl;
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
            std::cout << "Enter the weapon name: ";
            std::getline(std::cin, name);
            
            // Valida el tipo de arma
            bool validType = false;
            while (!validType) {
                std::cout << "Enter the type (Melee/Firearm/Throwable): ";
                std::getline(std::cin, type);
                type = toProperCase(type);
                
                if (type == "Melee" || type == "Firearm" || type == "Throwable") {
                    validType = true;
                } else {
                    std::cout << "Invalid type! Please enter exactly: Melee, Firearm, or Throwable\n";
                }
            }
            
            // Valida la exclusividad
            bool validExclusivity = false;
            while (!validExclusivity) {
                std::cout << "Enter the exclusivity (Shared/HM1/HM2): ";
                std::getline(std::cin, exclusivity);
                std::string exclusivityUpper = toUpperCase(exclusivity);
                
                if (exclusivityUpper == "SHARED") {
                    exclusivity = "Shared";
                    validExclusivity = true;
                } else if (exclusivityUpper == "HM1") {
                    exclusivity = "HM1";
                    validExclusivity = true;
                } else if (exclusivityUpper == "HM2") {
                    exclusivity = "HM2";
                    validExclusivity = true;
                } else {
                    std::cout << "Invalid exclusivity! Please enter exactly: Shared, HM1, or HM2\n";
                }
            }

            name = toProperCase(name);
            std::string line = name + "," + type + "," + exclusivity;
            weapons.push_back(Weapon(line));
            std::cout << "\nWeapon added successfully!\n";
 
         } else if (option == 3) {
             int sortCriterion;
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
 
         } else if (option == 4) {
             running = false;
 
         } else {
             std::cout << "Invalid option, please try again.\n";
         }
     }
 
     std::cout << "\nThank you for using the Hotline Miami Weapon Selector.\n";
     return 0;
 }