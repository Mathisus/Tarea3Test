#ifndef functions_h
#define functions_h
#define MAXCHAR 30

#include "treemap.h"
#include "list.h"

typedef struct 
{
    char prioridad[MAXCHAR];;
    char nombre[MAXCHAR];
    List *lista_precedencia;
} Tarea;

void mostrar_menu();

void agregarTarea(TreeMap *mapa, char *nombreTarea, char* prioridad);

void definirPrecedencia(TreeMap *mapa, char *nombreTarea, char* nombreTareaPrecedente);

void mostrarTareasPendientes(TreeMap *mapa);

void tareaRealizada(TreeMap *mapa, char *nombreTarea);

#endif