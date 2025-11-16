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
 
/*
toProperCase(const std::string& str) - Convierte una cadena a formato de nombre propio (primera letra mayúscula, resto minúsculas).
Complejidad de tiempo:
- Mejor caso: O(1) si la cadena está vacía.
- Caso promedio: O(m) donde m es la longitud de la cadena.
- Peor caso: O(m)
Descripción: Recorre la cadena carácter por carácter aplicando los cambios.
La primera letra se convierte a mayúscula y el resto a minúsculas.
 */
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
 
 
/*
toUpperCase(const std::string& str) - Convierte una cadena completa a mayúsculas.
Complejidad de tiempo:
- Mejor caso: O(m) donde m es la longitud de la cadena.
- Caso promedio: O(m)
- Peor caso: O(m)
Descripción: Usa std::transform para recorrer toda la cadena aplicando toupper a cada carácter.
 */
 std::string toUpperCase(const std::string& str) {
     std::string result = str;
     std::transform(result.begin(), result.end(), result.begin(), ::toupper);
     return result;
 }
 
/*
main() - Función principal del programa. Gestiona el menú interactivo del inventario de armas.
Complejidad de tiempo:
- Inicialización: O(n log n) para cargar n armas del archivo (loadWeapons)
- Por cada iteración del menú (depende de la opción seleccionada):
  * Opción 1 (Show inventory): O(n log n) - showWeapons ordena por loadOrder
  * Opción 2 (Add weapon): O(m + n) - búsqueda de maxOrder O(n), inserción O(log n)
  * Opción 3 (Search weapon): O(m + log n) - búsqueda en mapa O(log n)
  * Opción 4 (Remove weapon): O(m + log n) - eliminación del mapa O(log n)
  * Opción 5 (Filter by type): O(n) - recorre todas las armas
  * Opción 6 (Filter by exclusivity): O(n) - recorre todas las armas
  * Opción 7 (Sort inventory): O(n log n) en promedio, O(n²) peor caso - QuickSort
  * Opción 8 (Show statistics): O(n) - cuenta armas por categoría
  * Opción 9 (Exit): O(n log n) - saveWeapons ordena y escribe todas las armas
- Mejor caso general: O(n log n) si solo se carga y sale inmediatamente
- Caso promedio: O(k * n log n) donde k es el número de operaciones realizadas
- Peor caso: O(k * n²) si se realizan múltiples sorts con pivotes inadecuados

Donde:
- n = número de armas en el inventario
- m = longitud promedio de los strings (nombres, tipos)
- k = número de operaciones realizadas por el usuario

Descripción: El programa carga el inventario una vez al inicio con complejidad O(n log n).
Luego entra en un loop interactivo donde el usuario puede realizar múltiples operaciones.
La operación más costosa es el ordenamiento (opción 7) con O(n log n) en promedio y O(n²) 
en el peor caso si QuickSort elige pivotes inadecuados. Al salir, guarda el inventario 
actualizado con complejidad O(n log n). La complejidad total depende del número y tipo 
de operaciones que el usuario realice.
 */
 int main() {
     std::map<std::string, Weapon> weaponInventory;
     loadWeapons("weapons.txt", weaponInventory);
 
     int option;
     bool running = true;
 
     while (running) {
         std::cout << "\n==========================================" << std::endl;
         std::cout << "       HOTLINE MIAMI WEAPON SELECTOR\n";
         std::cout << "==========================================" << std::endl;
         std::cout << "Main menu:\n";
         std::cout << "1) Show inventory\n";
         std::cout << "2) Add weapon\n";
         std::cout << "3) Search weapon by name\n";
         std::cout << "4) Remove weapon\n";
         std::cout << "5) Filter by type\n";
         std::cout << "6) Filter by exclusivity\n";
         std::cout << "7) Sort inventory\n";
         std::cout << "8) Show statistics\n";
         std::cout << "9) Exit\n";
         std::cout << "Choose an option: ";
         std::cin >> option;
 
         if (option == 1) {
             std::cout << "\n===== INVENTORY =====\n";
             showWeapons(weaponInventory);
 

        } else if (option == 2) {
            std::string name, type, exclusivity;
            std::cout << "\n===== ADD WEAPON =====\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter the weapon name: ";
            std::getline(std::cin, name);
            name = toProperCase(name);
            
            if (weaponInventory.count(name) > 0) {
                std::cout << "Warning: A weapon with this name already exists. It will be replaced.\n";
            }
            
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

            // Encontrar el máximo loadOrder actual para asignar el siguiente
            int maxOrder = 0;
            for (const auto& pair : weaponInventory) {
                if (pair.second.getLoadOrder() > maxOrder) {
                    maxOrder = pair.second.getLoadOrder();
                }
            }
            
            std::string line = name + "," + type + "," + exclusivity;
            weaponInventory[name] = Weapon(line, maxOrder + 1);
            std::cout << "\n✓ Weapon added successfully!\n";
 
         } else if (option == 3) {
             std::string searchName;
             std::cout << "\n===== SEARCH WEAPON =====\n";
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Enter the weapon name to search: ";
             std::getline(std::cin, searchName);
             searchName = toProperCase(searchName);
             
             Weapon* found = searchWeapon(weaponInventory, searchName);
             if (found != nullptr) {
                 std::cout << "\n✓ Weapon found:\n";
                 found->showFile();
             } else {
                 std::cout << "\n✗ Weapon not found: " << searchName << "\n";
             }
 
         } else if (option == 4) {
             std::string removeName;
             std::cout << "\n===== REMOVE WEAPON =====\n";
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Enter the weapon name to remove: ";
             std::getline(std::cin, removeName);
             removeName = toProperCase(removeName);
             
             if (removeWeapon(weaponInventory, removeName)) {
                 std::cout << "\n✓ Weapon removed successfully: " << removeName << "\n";
             } else {
                 std::cout << "\n✗ Weapon not found: " << removeName << "\n";
             }
 
         } else if (option == 5) {
             std::string filterType;
             std::cout << "\n===== FILTER BY TYPE =====\n";
             std::cout << "1) Melee\n";
             std::cout << "2) Firearm\n";
             std::cout << "3) Throwable\n";
             std::cout << "Choose type: ";
             int typeChoice;
             std::cin >> typeChoice;
             
             if (typeChoice == 1) filterType = "Melee";
             else if (typeChoice == 2) filterType = "Firearm";
             else if (typeChoice == 3) filterType = "Throwable";
             else {
                 std::cout << "Invalid option.\n";
                 continue;
             }
             
             filterByType(weaponInventory, filterType);
 
         } else if (option == 6) {
             std::string filterExcl;
             std::cout << "\n===== FILTER BY EXCLUSIVITY =====\n";
             std::cout << "1) Shared\n";
             std::cout << "2) HM1\n";
             std::cout << "3) HM2\n";
             std::cout << "Choose exclusivity: ";
             int exclChoice;
             std::cin >> exclChoice;
             
             if (exclChoice == 1) filterExcl = "Shared";
             else if (exclChoice == 2) filterExcl = "HM1";
             else if (exclChoice == 3) filterExcl = "HM2";
             else {
                 std::cout << "Invalid option.\n";
                 continue;
             }
             
             filterByExclusivity(weaponInventory, filterExcl);
 
         } else if (option == 7) {
             int sortCriterion;
             std::cout << "\n===== SORT INVENTORY =====\n";
             std::cout << "1) By name (alphabetically)\n";
             std::cout << "2) By type\n";
             std::cout << "3) By exclusivity\n";
             std::cout << "Choose the sorting criterion: ";
             std::cin >> sortCriterion;
 
             if (sortCriterion >= 1 && sortCriterion <= 3) {
                 // Convertir map a vector
                 std::vector<Weapon> weaponVec = mapToVector(weaponInventory);
                 
                 // Usar QuickSort
                 quickSort(weaponVec, 0, weaponVec.size() - 1, sortCriterion);
                 
                 std::cout << "\n✓ Inventory sorted!\n";
                 for (const auto& weapon : weaponVec) {
                     weapon.showFile();
                 }
             } else {
                 std::cout << "\nInvalid input.\n";
             }
 
        } else if (option == 8) {
            showStatistics(weaponInventory);

        } else if (option == 9) {
            // Guardar el inventario antes de salir
            saveWeapons("weapons_updated.txt", weaponInventory);
            std::cout << "\n✓ Inventory saved to weapons_updated.txt\n";
            running = false;

        } else {
            std::cout << "\n✗ Invalid option, please try again.\n";
        }
     }
 
     std::cout << "\n======================================\n";
     std::cout << "Thank you for using the Hotline Miami Weapon Selector!\n";
     std::cout << "======================================\n";
     return 0;
 }