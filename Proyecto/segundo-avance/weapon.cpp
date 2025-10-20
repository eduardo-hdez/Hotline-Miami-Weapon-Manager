/*
weapon.cpp
Author: Eduardo Hernández Alonso - A01707225
 */

 #include "weapon.h"
 #include <fstream>
 
 /*
 showWeapons(const std::vector<Weapon>& weapons) - Muestra todas las armas del inventario.
 Complejidad de tiempo:
 - Mejor caso: O(1) si el inventario está vacío.
 - Caso promedio: O(n)
 - Peor caso: O(n)
 Descripción: Si el inventario está vacío, muestra un mensaje. De lo contrario, recorre cada arma e imprime sus datos.
  */
 void showWeapons(const std::vector<Weapon>& weapons) {
     if (weapons.empty()) {
         std::cout << "The inventory is empty." << std::endl;
     } else {
         for (const auto& weapon : weapons) {
             weapon.showFile();
         }
     }
 }
 
 /*
 loadWeapons(const std::string& filename, std::vector<Weapon>& weapons) - Carga las armas desde un archivo de texto.
 Complejidad de tiempo:
 - Mejor caso: O(n)
 - Caso promedio y peor caso: O(n), donde n es el número de líneas/armas en el archivo.
 Descripción: Abre el archivo y lee línea por línea. Cada línea se convierte en un objeto Weapon y se inserta en el vector.
  */
 void loadWeapons(const std::string& filename, std::vector<Weapon>& weapons) {
     std::ifstream file(filename);
     if (!file.is_open()) {
         std::cout << "Could not open the file: " << filename << std::endl;
         return;
     }
     std::string line;
     while (std::getline(file, line)) {
         if (!line.empty())
             weapons.push_back(Weapon(line));
     }
     file.close();
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
 