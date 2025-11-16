/*
weapon.cpp
Author: Eduardo Hernández Alonso - A01707225
 */

 #include "weapon.h"
 #include <fstream>
 #include <algorithm>
 
 /*
 showWeapons(const std::map<std::string, Weapon>& weaponMap) - Muestra todas las armas del inventario.
 Complejidad de tiempo:
 - Mejor caso: O(1) si el inventario está vacío.
 - Caso promedio: O(n log n)
 - Peor caso: O(n log n)
 Descripción: Convierte el mapa a vector, ordena por loadOrder y muestra en orden original del archivo.
  */
 void showWeapons(const std::map<std::string, Weapon>& weaponMap) {
     if (weaponMap.empty()) {
         std::cout << "The inventory is empty." << std::endl;
         return;
     }
     
     std::vector<Weapon> weapons;
     for (const auto& pair : weaponMap) {
         weapons.push_back(pair.second);
     }
     
     std::sort(weapons.begin(), weapons.end(), [](const Weapon& a, const Weapon& b) {
         return a.getLoadOrder() < b.getLoadOrder();
     });
     
     for (const auto& weapon : weapons) {
         weapon.showFile();
     }
 }
 
 /*
 loadWeapons(const std::string& filename, std::map<std::string, Weapon>& weaponMap) - Carga las armas desde un archivo de texto.
 Complejidad de tiempo:
 - Mejor caso: O(n log n) donde n es el número de líneas en el archivo.
 - Caso promedio: O(n log n)
 - Peor caso: O(n log n)
 Descripción: Abre el archivo y lee línea por línea. Cada línea se convierte en un objeto Weapon y se inserta en el mapa.
 Cada inserción en el mapa toma O(log n) debido a que utiliza un árbol balanceado internamente.
 El mapa automáticamente mantiene las armas ordenadas por nombre y previene duplicados.
  */
void loadWeapons(const std::string& filename, std::map<std::string, Weapon>& weaponMap) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open the file: " << filename << std::endl;
        return;
    }
    std::string line;
    int order = 0;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Weapon weapon(line, order++);
            weaponMap[weapon.getName()] = weapon;
        }
    }
    file.close();
}

/*
saveWeapons(const std::string& filename, const std::map<std::string, Weapon>& weaponMap) - Guarda las armas a un archivo de texto.
Complejidad de tiempo:
- Mejor caso: O(n log n) donde n es el número de armas en el inventario.
- Caso promedio: O(n log n)
- Peor caso: O(n log n)
Descripción: Convierte el mapa a vector y ordena por loadOrder para mantener el orden original del archivo.
Las armas nuevas agregadas por el usuario aparecerán al final. Luego escribe cada arma en formato CSV.
 */
void saveWeapons(const std::string& filename, const std::map<std::string, Weapon>& weaponMap) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open the file for writing: " << filename << std::endl;
        return;
    }
    
    // Convertir mapa a vector y ordenar por loadOrder
    std::vector<Weapon> weapons;
    for (const auto& pair : weaponMap) {
        weapons.push_back(pair.second);
    }
    
    std::sort(weapons.begin(), weapons.end(), [](const Weapon& a, const Weapon& b) {
        return a.getLoadOrder() < b.getLoadOrder();
    });
    
    // Escribir cada arma en formato CSV
    for (const auto& weapon : weapons) {
        file << weapon.getName() << "," 
             << weapon.getType() << "," 
             << weapon.getExclusivity() << std::endl;
    }
    
    file.close();
}

/*
searchWeapon(std::map<std::string, Weapon>& weaponMap, const std::string& name) - Busca un arma por nombre.
 Complejidad de tiempo:
 - Mejor caso: O(log n)
 - Caso promedio: O(log n)
 - Peor caso: O(log n)
 Descripción: Utiliza la función find del mapa que implementa búsqueda eficiente en árbol balanceado.
 Retorna un puntero al arma si existe, nullptr si no existe.
  */
 Weapon* searchWeapon(std::map<std::string, Weapon>& weaponMap, const std::string& name) {
     auto it = weaponMap.find(name);
     if (it != weaponMap.end()) {
         return &(it->second);
     }
     return nullptr;
 }
 
 /*
 removeWeapon(std::map<std::string, Weapon>& weaponMap, const std::string& name) - Elimina un arma por nombre.
 Complejidad de tiempo:
 - Mejor caso: O(log n)
 - Caso promedio: O(log n)
 - Peor caso: O(log n)
 Descripción: Utiliza la función erase del mapa que busca y elimina el elemento en tiempo O(log n).
 Retorna true si se eliminó, false si no existía.
  */
 bool removeWeapon(std::map<std::string, Weapon>& weaponMap, const std::string& name) {
     return weaponMap.erase(name) > 0;
 }
 
 /*
 filterByType(const std::map<std::string, Weapon>& weaponMap, const std::string& type) - Filtra armas por tipo.
 Complejidad de tiempo:
 - Mejor caso: O(n)
 - Caso promedio: O(n)
 - Peor caso: O(n)
 Descripción: Recorre todo el mapa y muestra solo las armas que coinciden con el tipo especificado.
  */
 void filterByType(const std::map<std::string, Weapon>& weaponMap, const std::string& type) {
     bool found = false;
     for (const auto& pair : weaponMap) {
         if (pair.second.getType() == type) {
             pair.second.showFile();
             found = true;
         }
     }
     if (!found) {
         std::cout << "No weapons found with type: " << type << std::endl;
     }
 }
 
 /*
 filterByExclusivity(const std::map<std::string, Weapon>& weaponMap, const std::string& exclusivity) - Filtra armas por exclusividad.
 Complejidad de tiempo:
 - Mejor caso: O(n)
 - Caso promedio: O(n)
 - Peor caso: O(n)
 Descripción: Recorre todo el mapa y muestra solo las armas que coinciden con la exclusividad especificada.
  */
 void filterByExclusivity(const std::map<std::string, Weapon>& weaponMap, const std::string& exclusivity) {
     bool found = false;
     for (const auto& pair : weaponMap) {
         if (pair.second.getExclusivity() == exclusivity) {
             pair.second.showFile();
             found = true;
         }
     }
     if (!found) {
         std::cout << "No weapons found with exclusivity: " << exclusivity << std::endl;
     }
 }
 
 /*
 showStatistics(const std::map<std::string, Weapon>& weaponMap) - Muestra estadísticas del inventario.
 Complejidad de tiempo:
 - Mejor caso: O(n)
 - Caso promedio: O(n)
 - Peor caso: O(n)
 Descripción: Recorre todo el mapa una vez contando armas por tipo y exclusividad.
  */
 void showStatistics(const std::map<std::string, Weapon>& weaponMap) {
     int totalWeapons = weaponMap.size();
     int melee = 0, firearm = 0, throwable = 0;
     int shared = 0, hm1 = 0, hm2 = 0;
     
     for (const auto& pair : weaponMap) {
         // Contar por tipo
         if (pair.second.getType() == "Melee") melee++;
         else if (pair.second.getType() == "Firearm") firearm++;
         else if (pair.second.getType() == "Throwable") throwable++;
         
         // Contar por exclusividad
         if (pair.second.getExclusivity() == "Shared") shared++;
         else if (pair.second.getExclusivity() == "HM1") hm1++;
         else if (pair.second.getExclusivity() == "HM2") hm2++;
     }
     
     std::cout << "\n=== WEAPON STATISTICS ===" << std::endl;
     std::cout << "Total weapons: " << totalWeapons << std::endl;
     std::cout << "\nBy Type:" << std::endl;
     std::cout << "  Melee: " << melee << std::endl;
     std::cout << "  Firearm: " << firearm << std::endl;
     std::cout << "  Throwable: " << throwable << std::endl;
     std::cout << "\nBy Exclusivity:" << std::endl;
     std::cout << "  Shared: " << shared << std::endl;
     std::cout << "  HM1: " << hm1 << std::endl;
     std::cout << "  HM2: " << hm2 << std::endl;
 }
 
 /*
 mapToVector(const std::map<std::string, Weapon>& weaponMap) - Convierte el mapa a un vector.
 Complejidad de tiempo:
 - Mejor caso: O(n)
 - Caso promedio: O(n)
 - Peor caso: O(n)
 Descripción: Recorre el mapa y copia cada arma al vector. Necesario para usar QuickSort con otros criterios.
  */
 std::vector<Weapon> mapToVector(const std::map<std::string, Weapon>& weaponMap) {
     std::vector<Weapon> vec;
     for (const auto& pair : weaponMap) {
         vec.push_back(pair.second);
     }
     return vec;
 }
 
 /*
 compare(const Weapon& a, const Weapon& b, int sortType) - Compara dos objetos Weapon según el criterio de ordenamiento.
 Complejidad de tiempo:
 - O(1) siempre, ya que solo compara cadenas de texto breves almacenadas.
 Descripción: Compara usando getName, getType o getExclusivity dependiendo del tipo de sort.
  */
 bool compare(const Weapon& a, const Weapon& b, int sortType) {
     if (sortType == 1) {
         return a.getName() < b.getName();
     } else if (sortType == 2) {
         return a.getType() < b.getType();
     } else {
         return a.getExclusivity() < b.getExclusivity();
     }
 }
 
 /*
 partition(std::vector<Weapon>& weapons, int low, int high, int sortType) - Reordena el vector usando un pivote para quicksort.
 Complejidad de tiempo:
 - Mejor caso: O(n)
 - Caso promedio: O(n)
 - Peor caso: O(n)
 Descripción: Recorre una vez el segmento, colocando los elementos menores al pivote a la izquierda y los mayores a la derecha.
  * Se usa el último elemento (índice high) como pivote por simplicidad y facilidad de implementación.
  */
 int partition(std::vector<Weapon>& weapons, int low, int high, int sortType) {
     Weapon pivot = weapons[high];
     int i = low - 1;
     for (int j = low; j < high; j++) {
         if (compare(weapons[j], pivot, sortType)) {
             i++;
             std::swap(weapons[i], weapons[j]);
         }
     }
     std::swap(weapons[i + 1], weapons[high]);
     return i + 1;
 }
 
 /*
 quickSort(std::vector<Weapon>& weapons, int low, int high, int sortType) - Ordena el vector usando quicksort recursivo.
 Complejidad de tiempo:
 - Mejor caso: O(n log n)
 - Caso promedio: O(n log n)
 - Peor caso: O(n^2), que ocurre si el pivote siempre es el menor o mayor elemento.
 Descripción: Divide y conquista el arreglo ordenando recursivamente los subarreglos definidos por el pivote.
  */
 void quickSort(std::vector<Weapon>& weapons, int low, int high, int sortType) {
     if (low < high) {
         int piv = partition(weapons, low, high, sortType);
         quickSort(weapons, low, piv - 1, sortType);
         quickSort(weapons, piv + 1, high, sortType);
     }
 }
 