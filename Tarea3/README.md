# Readme de la Tarea 3, "Recordatorios"

Este es un programa de gestión de tareas que te permite agregar tareas, definir dependencias entre ellas y marcar tareas como completadas. Se utilizaron TDA's mapa y lista.

---

**Importante**

*Para interactuar con el programa, abrir el archivo "tarea3.exe"

---

Ademas de las estructruras predefinidas para TDA, utlizé una estructura para almacenar las tareas:

---
typedef struct 
{
    char prioridad[MAXCHAR];;
    char nombre[MAXCHAR];
    List *lista_precedencia;
} Tarea;
---

**Opciones del Programa**

- **Opción 1: Agregar tarea (nombre, prioridad)** 
El usuario ingresa el nombre de una tarea y su prioridad (un número entero). La aplicación agrega la tarea a la lista de tareas por hacer.

- **Opción 2: Establecer precedencia entre tareas (tarea1, tarea2)** 
El usuario ingresa los nombres de dos tareas existentes. La aplicación establece que la tarea1 debe realizarse antes que la tarea2.

- **Opción 3: Mostrar tareas por hacer** 
La aplicación muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.

- **Opción 4: Marcar tarea como completada (nombre)** El usuario ingresa el nombre de una tarea. La aplicación marca la tarea como completada y la elimina de la lista de tareas por hacer. Si la tarea tiene relaciones de precedencia, se debe colocar una advertencia: “¿estás seguro que desea eliminar la tarea?”

---

**Funciones Principales**

- **mostrar_menu()**
Esta función muestra el menú de opciones disponibles en el programa.

- **esta_presente(TreeMap *mapa, char *nombreTarea)**
Verifica si una tarea dada por su nombre está presente en el mapa de tareas. Devuelve 1 si la tarea está presente y 0 si no lo está.

- **agregarTarea(TreeMap *mapa, char *nombreTarea, char* prioridad)**
Agrega una nueva tarea al mapa de tareas. Verifica si la tarea ya está presente antes de agregarla. Si la tarea ya existe, muestra un mensaje de error. La función recibe el nombre y la prioridad de la tarea como parámetros.

- **buscar_tarea(TreeMap *mapa, char *precedencia)**
Busca una tarea en el mapa de tareas dado su nombre. Devuelve un puntero a la tarea encontrada o NULL si no se encuentra.

- **definirPrecedencia(TreeMap *mapa, char *nombreTarea, char* precedencia)**
Define una tarea como precedente de otra en el mapa de tareas. Verifica si ambas tareas están presentes en el sistema antes de establecer la relación de precedencia. Si alguna de las tareas no se encuentra, muestra un mensaje de error.

- **mostrar(Tarea* tarea)**
Muestra la información de una tarea dada. Muestra el nombre de la tarea, su prioridad y las tareas que tiene como precedentes.

- **estaEnLista(List *lista, Tarea *tarea)**
Verifica si una tarea dada se encuentra en una lista dada. Devuelve 1 si la tarea está en la lista y 0 si no lo está.

- **mostrarListaPrece(List *list)**
Muestra en pantalla la lista de precedentes de una tarea. Recorre la lista de precedentes y muestra el nombre de cada tarea.

- **crearListaTareas(TreeMap *mapa)**
Crea una lista de tareas ordenadas según su precedencia. Recorre el mapa de tareas y agrega las tareas sin precedentes al inicio de la lista. Luego, agrega las tareas precedentes a continuación. Devuelve la lista de tareas.

- **mostrar_desordenadas(TreeMap *map)**
Esta función es utilizada para verificar errores y muestra en pantalla todas las tareas del mapa de tareas sin ningún orden en particular.

- **mostrarTareasPendientes(TreeMap *map)**
Muestra las tareas pendientes ordenadas por prioridad y precedencia. Utiliza la función crearListaTareas para obtener una lista de tareas ordenadas y las muestra en pantalla junto con su prioridad y precedentes.

- **tareaRealizada(TreeMap *mapa, char* tarea)**
Marca una tarea como realizada en el mapa de tareas. Verifica si la tarea está presente en el sistema antes de marcarla como realizada. Además, elimina las referencias a esta tarea en las listas de precedencia de otras tareas.

---

**Estructuras de Datos Utilizadas**

- **TreeMap**
Un mapa ordenado que almacena las tareas. La clave es la prioridad de la tarea y el valor es un puntero a la estructura de la tarea.

- **List**
Esta estructura de datos se utiliza para almacenar las tareas precedentes de cada tarea. Cada tarea tiene una lista enlazada que contiene las tareas que deben completarse antes de poder realizar esa tarea en particular. La lista se utiliza para mantener un seguimiento de las dependencias entre las tareas.

**Evaluación Personal**

Nombre: Matias Reyes Pizarro
___________________________________________________________________________________________________
| Participación | Responsabilidad | Comunicación | Calidad de trabajo | Trabajo en equipo | TOTAL |
|   20          |    20           |     20       |          15        |        20         |  95   |

(Creo que no era necesario pero mejor que sobre a que falte)