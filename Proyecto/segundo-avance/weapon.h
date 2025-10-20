/*
weapon.h
Author: Eduardo Hernández Alonso - A01707225
 */

 #ifndef WEAPON_H
 #define WEAPON_H
 
 #include <string>
 #include <vector>
 #include <sstream>
 #include <iostream>
 
 class Weapon {
 private:
     std::string name;
     std::string type;
     std::string exclusivity;
 
 public:
     Weapon(const std::string& line) {
         std::stringstream ss(line);
         std::getline(ss, name, ',');
         std::getline(ss, type, ',');
         std::getline(ss, exclusivity, ',');
     }
 
     void showFile() const {
         std::cout << "Weapon: " << name << " | Type: " << type
                   << " | Exclusivity: " << exclusivity << std::endl;
     }
 
     std::string getName() const { return name; }
     std::string getType() const { return type; }
     std::string getExclusivity() const { return exclusivity; }
 };
 
 void showWeapons(const std::vector<Weapon>& weapons);
 void loadWeapons(const std::string& filename, std::vector<Weapon>& weapons);
 
 void quickSort(std::vector<Weapon>& weapons, int low, int high, int sortType);
 int partition(std::vector<Weapon>& weapons, int low, int high, int sortType);
 
 #endif