/*
weapon.h
Author: Eduardo Hernández Alonso - A01707225
 */

 #ifndef WEAPON_H
 #define WEAPON_H
 
 #include <string>
 #include <vector>
 #include <map>
 #include <sstream>
 #include <iostream>
 
class Weapon {
private:
    std::string name;
    std::string type;
    std::string exclusivity;
    int loadOrder;  // Orden en que fue cargada desde el archivo

public:
    /*
    Constructor por default - Inicializa un objeto Weapon vacío.
    Complejidad de tiempo: O(1)
    Descripción: Inicializa todos los atributos con valores por default.
     */
    Weapon() : name(""), type(""), exclusivity(""), loadOrder(0) {}
    
    /*
    Constructor parametrizado - Crea un objeto Weapon a partir de una línea CSV.
    Complejidad de tiempo: O(m) donde m es la longitud de la línea.
    Descripción: Usa stringstream y getline para parsear la línea CSV.
     */
    Weapon(const std::string& line, int order = 0) {
        std::stringstream ss(line);
        std::getline(ss, name, ',');
        std::getline(ss, type, ',');
        std::getline(ss, exclusivity, ',');
        loadOrder = order;
    }

    /*
    showFile() - Muestra la información del arma en consola.
    Complejidad de tiempo: O(1)
    Descripción: Imprime strings previamente almacenados.
     */
    void showFile() const {
        std::cout << "Weapon: " << name << " | Type: " << type
                  << " | Exclusivity: " << exclusivity << std::endl;
    }

    /*
    Getters - Retornan los atributos del objeto.
    Complejidad de tiempo: O(1)
    Descripción: Acceso directo a atributos almacenados.
     */
    std::string getName() const { return name; }
    std::string getType() const { return type; }
    std::string getExclusivity() const { return exclusivity; }
    int getLoadOrder() const { return loadOrder; }
};
 
// Funciones para trabajar con std::map
void showWeapons(const std::map<std::string, Weapon>& weaponMap);
void loadWeapons(const std::string& filename, std::map<std::string, Weapon>& weaponMap);
void saveWeapons(const std::string& filename, const std::map<std::string, Weapon>& weaponMap);
Weapon* searchWeapon(std::map<std::string, Weapon>& weaponMap, const std::string& name);
 bool removeWeapon(std::map<std::string, Weapon>& weaponMap, const std::string& name);
 void filterByType(const std::map<std::string, Weapon>& weaponMap, const std::string& type);
 void filterByExclusivity(const std::map<std::string, Weapon>& weaponMap, const std::string& exclusivity);
 void showStatistics(const std::map<std::string, Weapon>& weaponMap);
 
 // Función auxiliar para convertir mapa a vector (para QuickSort)
 std::vector<Weapon> mapToVector(const std::map<std::string, Weapon>& weaponMap);
 
 // Funciones de ordenamiento
 void quickSort(std::vector<Weapon>& weapons, int low, int high, int sortType);
 int partition(std::vector<Weapon>& weapons, int low, int high, int sortType);
 
 #endif