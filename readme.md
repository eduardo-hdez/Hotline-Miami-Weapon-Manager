# Hotline Miami Weapon Manager

Este proyecto simula un sistema de gestión y ordenamiento de un inventario de armas, inspirado en la serie de juegos Hotline Miami, que es uno de mis juegos favoritos. Me parece interesante poder controlar el inventario de armas del juego, ya que estas herramientas son clave en la experiencia de juego.

El programa permite al usuario cargar armas desde un archivo de texto, visualizar el inventario actual, agregar nuevas armas y ordenar la lista según diferentes criterios como nombre, tipo o exclusividad.

## Descripción del avance 1

En este primer avance se ha implementado lo siguiente:

- Clase `Weapon` para gestionar la información de las armas individuales, incluyendo atributos como nombre, tipo y exclusividad.
- Función para cargar el inventario de armas desde un archivo de texto.
- Implementación de un menú interactivo en consola que permite:
  - Mostrar el inventario actual.
  - Agregar nuevas armas al inventario.
  - Ordenar el inventario por nombre, tipo o exclusividad utilizando el algoritmo QuickSort.

## Instrucciones para compilar el avance de proyecto

Antes de compilar, debes moverte a la carpeta de "Avance 1" con el siguiente comando en la terminal:

`cd "Proyecto/Avance 1"`

Ejecuta el siguiente comando en la terminal:

`g++ main.cpp weapon.cpp -std=c++11 -o primer_avance`

## Instrucciones para ejecutar el avance de proyecto

Ejecuta el siguiente comando en la terminal:

`./primer_avance`

## Descripción de las entradas del avance de proyecto

El programa requiere un archivo de entrada llamado `weapons.txt`, que contiene la lista de armas en el siguiente formato:

| Nombre       | Tipo  | Exclusividad |
| ------------ | ----- | ------------ |
| Baseball Bat | Melee | Shared       |
| Lead Pipe    | Melee | Shared       |
| Katana       | Melee | HM1          |

Cada línea contiene los datos de un arma separados por comas:

- **nombre**: Nombre del arma.
- **tipo**: Categoría del arma (Melee, Firearm, Throwable).
- **exclusividad**: Indica si el arma aparece en Hotline Miami 1 (HM1), Hotline Miami 2 (HM2) o en ambos juegos (Shared).

Además del archivo de entrada, el programa permite al usuario agregar nuevas armas durante la ejecución, ingresando los datos directamente desde la consola. Se validan las entradas para asegurar el formato correcto y evitar duplicados en el inventario.

## Descripción de las salidas del avance de proyecto

El programa proporciona las siguientes salidas:

**1. Mostrar Inventario de Armas:**  
Al seleccionar esta opción, se listan todas las armas almacenadas en el inventario, mostrando los siguientes atributos para cada una:

- Nombre.
- Tipo.
- Exclusividad (indica si el arma aparece en Hotline Miami 1, Hotline Miami 2 o en ambos).

**2. Ordenar Inventario:**  
Al ordenar el inventario, se muestra la lista completa de armas organizadas de acuerdo con el atributo seleccionado:

- Nombre: Orden alfabético.
- Tipo: Orden alfabético por categoría.
- Exclusividad: Organiza según aparición en los juegos (Shared, HM1, HM2).

**3. Agregar Arma:**  
Permite al usuario ingresar una nueva arma al inventario mediante la consola, solicitando los datos correspondientes y validando que el formato sea correcto.

**4. Mensajes de confirmación y errores:**  
El programa proporciona retroalimentación al usuario mediante mensajes que incluyen:

- Confirmación de operaciones exitosas (ejemplo: "Weapon added successfully!").
- Mensajes de error (ejemplo: "Invalid Input.", "Invalid option, please try again.").

## Desarrollo de competencias

### SICT0301: Evalúa los componentes

#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

En mi proyecto, he implementado el algoritmo de ordenamiento **QuickSort** en la función `quickSort`, que se utiliza para ordenar el inventario de armas por nombre, tipo o exclusividad. El análisis de complejidad del algoritmo es el siguiente:

- **Complejidad temporal en el peor de los casos:** O(n^2). Esto ocurre cuando el pivote elegido es siempre el peor posible (por ejemplo, si la lista ya está ordenada o casi ordenada), lo que genera particiones muy desbalanceadas.
- **Complejidad temporal en el mejor de los casos:** O(n log n), cuando el pivote divide el conjunto en partes aproximadamente iguales en cada llamada recursiva.
- **Complejidad temporal en el caso promedio:** O(n log n), que es el rendimiento típico esperado para QuickSort en listas aleatorias o desordenadas.

Comparado con algoritmos como Bubble Sort, Selection Sort o Insertion Sort, que tienen complejidad O(n^2) en el peor caso, QuickSort es más eficiente para manejar volúmenes grandes o dinámicos de datos, lo cual es importante si el usuario decide agregar muchas armas al inventario en el futuro.

### SICT0302: Toma decisiones

#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

Para mi proyecto, decidí utilizar **QuickSort** debido a sus características específicas que lo hacen adecuado para el manejo del inventario de armas:

- QuickSort tiene una complejidad temporal promedio de O(n log n), lo que lo hace eficiente para listas con tamaños variables y potencialmente grandes, como el inventario que puede crecer si el usuario agrega más armas.
- Aunque su peor caso es O(n^2), este escenario es poco frecuente y puede mitigarse con una buena selección de pivote.
- QuickSort es un algoritmo que no requiere memoria adicional significativa, lo que es útil para la gestión eficiente de recursos en sistemas con memoria limitada.
- La implementación es sencilla y fácil de adaptar para ordenar por múltiples criterios (nombre, tipo, exclusividad) sin grandes modificaciones.

Al comparar con otros algoritmos como Merge Sort, que tiene complejidad garantizada O(n log n) y es estable, o Insertion Sort y Bubble Sort, que sólo son eficientes para listas parcialmente ordenadas, QuickSort representa un balance óptimo entre velocidad, memoria y facilidad de implementación para este proyecto.

En conclusión, QuickSort fue el más adecuado para mi proyecto debido a su rendimiento eficiente en la mayoría de los casos, flexibilidad para ordenar según distintos criterios y bajo consumo de memoria, cumpliendo con los objetivos planteados para la gestión dinámica del inventario.
