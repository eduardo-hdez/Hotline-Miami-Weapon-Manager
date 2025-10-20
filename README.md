# Hotline Miami Weapon Manager

Este proyecto simula un sistema de gestión y ordenamiento de un inventario de armas, inspirado en la serie de juegos Hotline Miami, que es uno de mis juegos favoritos. Me parece interesante poder controlar el inventario de armas del juego, ya que estas herramientas son clave en la experiencia de juego.

El programa permite al usuario cargar armas desde un archivo de texto, visualizar el inventario, agregar nuevas armas, buscar armas específicas, eliminar armas, filtrar por categorías y ordenar la lista según diferentes criterios utilizando estructuras de datos eficientes.

---

## Descripción del avance 1

En este primer avance se ha implementado lo siguiente:

- Clase `Weapon` para gestionar la información de las armas individuales, incluyendo atributos como nombre, tipo y exclusividad.
- Función para cargar el inventario de armas desde un archivo de texto.
- Implementación de un menú interactivo en consola que permite:
  - Mostrar el inventario actual.
  - Agregar nuevas armas al inventario.
  - Ordenar el inventario por nombre, tipo o exclusividad utilizando el algoritmo QuickSort.

## Descripción del avance 2

En este segundo avance se implementó:

- **Cambio de estructura de datos:** De `std::vector` a `std::map<std::string, Weapon>` para mejorar la eficiencia de búsquedas y eliminaciones.
- **Nuevas funcionalidades:**
  - Búsqueda de armas por nombre con complejidad $O(\log n)$.
  - Eliminación de armas del inventario con complejidad $O(\log n)$.
  - Filtrado de armas por tipo (Melee, Firearm, Throwable).
  - Filtrado de armas por exclusividad (Shared, HM1, HM2).
  - Estadísticas del inventario mostrando contadores por categoría.
- **Análisis de complejidad completo:** Documentación detallada de la complejidad temporal de todas las operaciones en comentarios del código.

### Cambios sobre el primer avance

- **Mejoras en la interfaz de usuario:**
  - Implementación de normalización automática de mayúsculas/minúsculas.
  - El programa acepta entradas como "melee", "MELEE" o "Melee" indistintamente.
  - Eliminadas las opciones "yes/no" para regresar al menú.
  - El programa regresa automáticamente al menú después de cada operación.

---

## Instrucciones para compilar el avance de proyecto

Antes de compilar, debes moverte a la carpeta del segundo avance con el siguiente comando en la terminal:

```bash
cd "proyecto/segundo-avance"
```

Ejecuta el siguiente comando en la terminal:

```bash
g++ main.cpp weapon.cpp -std=c++11 -o segundo_avance
```

## Instrucciones para ejecutar el avance de proyecto

Ejecuta el siguiente comando en la terminal:

```bash
./segundo_avance
```

---

## Descripción de las entradas del avance de proyecto

El programa requiere un archivo de entrada llamado `weapons.txt`, que debe estar en la misma carpeta que el ejecutable. El archivo contiene la lista de armas en formato CSV:

| Nombre       | Tipo      | Exclusividad |
| ------------ | --------- | ------------ |
| Baseball Bat | Melee     | Shared       |
| Lead Pipe    | Melee     | Shared       |
| Shotgun      | Firearm   | Shared       |
| Katana       | Melee     | HM1          |
| 9mm          | Firearm   | HM2          |
| Brick        | Throwable | HM1          |

Cada línea contiene los datos de un arma separados por comas:

- **Nombre:** Nombre del arma (se usa como identificador único).
- **Tipo:** Categoría del arma. Valores válidos: `Melee`, `Firearm`, `Throwable`.
- **Exclusividad:** Indica en qué juego aparece. Valores válidos: `Shared` (ambos juegos), `HM1` (Hotline Miami 1), `HM2` (Hotline Miami 2).

Además del archivo de entrada, el programa permite al usuario:

- **Agregar nuevas armas** ingresando datos desde la consola.
- **Buscar armas** por nombre.
- **Eliminar armas** del inventario.
- Las entradas se validan automáticamente y aceptan cualquier combinación de mayúsculas/minúsculas.

## Descripción de las salidas del avance de proyecto

El programa proporciona las siguientes salidas:

### 1. Mostrar Inventario (Opción 1)

Lista todas las armas en el orden original del archivo `weapons.txt`, mostrando:

- Nombre del arma
- Tipo
- Exclusividad

### 2. Agregar Arma (Opción 2)

Solicita al usuario:

- Nombre del arma (normalizado automáticamente)
- Tipo (validado contra opciones válidas: Melee/Firearm/Throwable)
- Exclusividad (validada contra opciones válidas: Shared/HM1/HM2)

Muestra confirmación: `✓ Weapon added successfully!`

### 3. Buscar Arma por Nombre (Opción 3)

Solicita el nombre del arma y muestra:

- `✓ Weapon found:` seguido de los detalles del arma, o
- `✗ Weapon not found: [nombre]` si no existe

### 4. Eliminar Arma (Opción 4)

Solicita el nombre del arma y muestra:

- `✓ Weapon removed successfully: [nombre]`, o
- `✗ Weapon not found: [nombre]` si no existe

### 5. Filtrar por Tipo (Opción 5)

Muestra todas las armas de un tipo específico:

- Melee (armas cuerpo a cuerpo)
- Firearm (armas de fuego)
- Throwable (armas arrojadizas)

### 6. Filtrar por Exclusividad (Opción 6)

Muestra todas las armas de una exclusividad específica:

- Shared (aparecen en ambos juegos)
- HM1 (solo en Hotline Miami 1)
- HM2 (solo en Hotline Miami 2)

### 7. Ordenar Inventario (Opción 7)

Ordena y muestra el inventario según:

- **Por nombre:** Orden alfabético (usa QuickSort)
- **Por tipo:** Agrupa por Firearm, Melee, Throwable (usa QuickSort)
- **Por exclusividad:** Agrupa por HM1, HM2, Shared (usa QuickSort)

Muestra: `✓ Inventory sorted!` seguido del inventario ordenado.

### 8. Mostrar Estadísticas (Opción 8)

Muestra un resumen del inventario:

```
=== WEAPON STATISTICS ===
Total weapons: 52

By Type:
  Melee: 28
  Firearm: 17
  Throwable: 7

By Exclusivity:
  Shared: 25
  HM1: 11
  HM2: 26
```

### 9. Salir (Opción 9)

Muestra mensaje de despedida y termina el programa.

---

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

En mi proyecto, he implementado el algoritmo de ordenamiento **QuickSort** en la función `quickSort`, que se utiliza para ordenar el inventario de armas por nombre, tipo o exclusividad. El análisis de complejidad del algoritmo es el siguiente:

- **Complejidad temporal en el peor de los casos:** $O(n^2)$. Esto ocurre cuando el pivote elegido es siempre el peor posible (por ejemplo, si la lista ya está ordenada o casi ordenada), lo que genera particiones muy desbalanceadas.
- **Complejidad temporal en el mejor de los casos:** $O(n \log n)$, cuando el pivote divide el conjunto en partes aproximadamente iguales en cada llamada recursiva.
- **Complejidad temporal en el caso promedio:** $O(n \log n)$, que es el rendimiento típico esperado para QuickSort en listas aleatorias o desordenadas.

Comparado con algoritmos como Bubble Sort, Selection Sort o Insertion Sort, que tienen complejidad $O(n^2)$ en el peor caso, QuickSort es más eficiente para manejar volúmenes grandes o dinámicos de datos, lo cual es importante si el usuario decide agregar muchas armas al inventario en el futuro.

#### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.

En el segundo avance, he implementado la estructura de datos **std::map<std::string, Weapon>** y documentado el análisis de complejidad de sus operaciones principales:

**Operaciones implementadas y su complejidad:**

- **Búsqueda por nombre:** $O(\log n)$
- **Inserción de arma:** $O(\log n)$
- **Eliminación de arma:** $O(\log n)$
- **Filtrado por tipo/exclusividad:** $O(n)$
- **Carga desde archivo:** $O(n \log n)$
- **Estadísticas:** $O(n)$

Cada función está documentada con su análisis de complejidad en los comentarios del código, indicando mejor caso, caso promedio y peor caso, junto con la descripción de por qué tiene esa complejidad.

### SICT0302: Toma decisiones

#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

Para mi proyecto, decidí utilizar **QuickSort** debido a sus características específicas que lo hacen adecuado para el manejo del inventario de armas:

- QuickSort tiene una complejidad temporal promedio de $O(n \log n)$, lo que lo hace eficiente para listas con tamaños variables y potencialmente grandes, como el inventario que puede crecer si el usuario agrega más armas.
- Aunque su peor caso es $O(n^2)$, este escenario es poco frecuente y puede mitigarse con una buena selección de pivote.
- QuickSort es un algoritmo que no requiere memoria adicional significativa, lo que es útil para la gestión eficiente de recursos en sistemas con memoria limitada.
- La implementación es sencilla y fácil de adaptar para ordenar por múltiples criterios (nombre, tipo, exclusividad) sin grandes modificaciones.

Al comparar con otros algoritmos como Merge Sort, que tiene complejidad garantizada $O(n \log n)$ y es estable, o Insertion Sort y Bubble Sort, que sólo son eficientes para listas parcialmente ordenadas, QuickSort representa un balance óptimo entre velocidad, memoria y facilidad de implementación para este proyecto.

En conclusión, QuickSort fue el más adecuado para mi proyecto debido a su rendimiento eficiente en la mayoría de los casos, flexibilidad para ordenar según distintos criterios y bajo consumo de memoria, cumpliendo con los objetivos planteados para la gestión dinámica del inventario.

#### Selecciona una estructura de datos adecuada al problema y la usa correctamente.

Para el segundo avance, seleccioné **std::map<std::string, Weapon>** como estructura de datos principal. Esta decisión está fundamentada en las necesidades específicas del gestor de inventario de Hotline Miami:

**Por qué std::map es adecuado para este problema específico:**

En un gestor de inventario de videojuego, las operaciones más frecuentes son:

- **Buscar armas por nombre:** El jugador quiere saber si tiene una arma específica
- **Verificar duplicados:** No se debe tener dos armas con el mismo nombre
- **Eliminar armas:** Al usar un arma o perderla en el juego

El `std::map` es ideal porque:

- Usa el nombre del arma como clave única, garantizando que no haya duplicados automáticamente
- Permite búsquedas rápidas $O(\log n)$ por nombre
- Facilita la eliminación eficiente $O(\log n)$ cuando el jugador usa o pierde un arma
- Para ordenar por otros criterios (tipo, exclusividad) se puede convertir temporalmente a vector y usar QuickSort

### SICT0303: Implementa acciones científicas

#### Implementa mecanismos para consultar información de las estructuras correctos.

He implementado mecanismos de consulta sobre el `std::map` que permiten al usuario interactuar con el inventario:

**Mecanismos implementados:**

1. **Búsqueda por nombre** - `searchWeapon()`

   - Busca un arma específica en $O(\log n)$
   - Disponible en la opción 3 del menú

2. **Filtrado por tipo** - `filterByType()`

   - Muestra todas las armas de un tipo (Melee, Firearm, Throwable)
   - Disponible en la opción 5 del menú

3. **Filtrado por exclusividad** - `filterByExclusivity()`

   - Muestra armas según su aparición en los juegos (Shared, HM1, HM2)
   - Disponible en la opción 6 del menú

4. **Estadísticas del inventario** - `showStatistics()`
   - Cuenta y muestra totales por categoría
   - Disponible en la opción 8 del menú

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

He implementado la función `loadWeapons()` que carga correctamente las armas desde el archivo al `std::map`:

**Implementación:**

La función abre el archivo `weapons.txt`, lee línea por línea, parsea cada línea en formato CSV usando el constructor de `Weapon`, e inserta cada arma en el map usando el nombre como clave. También mantiene un contador de orden para preservar la secuencia original del archivo.

El mecanismo maneja correctamente 52 armas del archivo y tiene complejidad $O(n \log n)$ debido a las `n` inserciones en el map.
