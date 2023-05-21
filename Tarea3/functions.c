#include "functions.h"
#include "treemap.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAXCHAR 30

void mostrar_menu()
{   
    puts("-----------------------------------------------");
    puts("Bienvenido al programa, Ingrese una opcion:");
    puts("-----------------------------------------------");
    printf("1. Agregar tarea\n");
    printf("2. Definir precedencia entre tareas\n");
    printf("3. Mostrar tareas pendientes\n");
    printf("4. Marcar tarea como realizada\n");
    printf("5. Salir\n");
    puts("-----------------------------------------------");
}

int esta_presente(TreeMap *mapa, char *nombreTarea)
{
    Tarea *tareaActual = (Tarea *)firstTreeMap(mapa);
    
    while (tareaActual != NULL)
    {
        if (strcmp(tareaActual->nombre, nombreTarea) == 0)
        {
            return 1;
        }
        tareaActual = (Tarea *)nextTreeMap(mapa);
    }

    return 0;
}

void agregarTarea(TreeMap *mapa, char *nombreTarea, char* prioridad)
{
    Tarea *nuevaTarea = (Tarea *)malloc(sizeof(Tarea));

    if(esta_presente(mapa, nombreTarea) == 1)
    {
        system("cls");
        puts("La tarea ya se encuentra en el sistema, intente otra vez");
        system("pause");
    }

    strcpy(nuevaTarea->nombre, nombreTarea);
    strcpy(nuevaTarea->prioridad, prioridad);
    nuevaTarea->lista_precedencia = createList();

    insertTreeMap(mapa, nuevaTarea->prioridad, nuevaTarea);

    return;
}

Tarea* buscar_tarea(TreeMap *mapa, char *precedencia)
{
    Tarea *tarea_aux = (Tarea*) firstTreeMap(mapa);
    
    while (tarea_aux != NULL)
    {
        if (strcmp(precedencia, tarea_aux->nombre) == 0)
        {
            return tarea_aux;
        }
        tarea_aux = (Tarea *)nextTreeMap(mapa);
    }

    return NULL;
}

void definirPrecedencia(TreeMap *mapa, char *nombreTarea, char* precedencia)
{
    if(strcmp(nombreTarea, precedencia) == 0)
    {
        puts("No se puede definir una tarea como precedente de si misma, intentelo otra vez");
        system("pause");
        return;
    }

    if (esta_presente(mapa, nombreTarea) == 1 || esta_presente(mapa, precedencia) == 1)
    {   
        Tarea *tareaAux = buscar_tarea(mapa, nombreTarea);
        Tarea *tarea_precedente = buscar_tarea(mapa, precedencia);

        if (tareaAux == NULL || tarea_precedente == NULL)
        {
            system("cls");
            puts("La tarea o la tarea precedente no se encuentran en el sistema, intente otra vez");

            system("pause");
            return;
        }

        pushBack(tareaAux->lista_precedencia, tarea_precedente);
        printf("Se ha definido la tarea %s como precedente de la tarea %s\n", tarea_precedente->nombre, tareaAux->nombre);
        puts("");

        return;
    }else{
        puts("La tarea o la tarea precedente no se encuentran en el sistema, intente otra vez");
        system("pause");
    }
}

void mostrar(Tarea* tarea)
{
    printf("Nombre: %s - Prioridad: %s \n", tarea->nombre, tarea->prioridad);
    Tarea *precedenteAux = (Tarea *)firstList(tarea->lista_precedencia);
    
    while (precedenteAux != NULL)
    {
        printf("%s ", precedenteAux);
        precedenteAux = (Tarea *)nextList(tarea->lista_precedencia);
    }
    printf("\n");
    
}

int estaEnLista(List *lista, Tarea *tarea)
{
    Tarea* tarea_actual = (Tarea*) firstList(lista);
    while(tarea_actual != NULL)
    {   
        if(strcmp(tarea_actual->nombre,tarea->nombre) == 0) return 1;

        tarea_actual = (Tarea*) nextList(lista);
    }

    return 0;
}

void mostrarListaPrece(List *list)
{
    Tarea* actual = (Tarea*) firstList(list);

    printf("[");
    while(actual != NULL)
    {
        printf(" %s", actual->nombre);
        
        actual = (Tarea*) nextList(list);
    }
    printf("]");
}


List *crearListaTareas(TreeMap * mapa)
{   
    Tarea *tareaAux = (Tarea *) firstTreeMap(mapa);
    List *listaTareas = createList();

    while (tareaAux != NULL)
    {

        Tarea* precedencia_actual = (Tarea*) firstList(tareaAux->lista_precedencia);

        if(precedencia_actual == NULL)
        {   
            if(estaEnLista(listaTareas, tareaAux) == 0) 
            {   
                pushBack(listaTareas, tareaAux);
            }
        }
        else 
        { 
            while(precedencia_actual != NULL)
            {
                if(estaEnLista(listaTareas, precedencia_actual) == 0)
                {     
                    pushBack(listaTareas, precedencia_actual);
                }
                precedencia_actual = (Tarea*) nextList(tareaAux->lista_precedencia);
            }

            if(estaEnLista(listaTareas, tareaAux) == 0)
            {   
                pushBack(listaTareas, tareaAux);
            }
        }
        tareaAux = (Tarea*) nextTreeMap(mapa);
    }

    return listaTareas;
}


void mostrar_desordenadas(TreeMap *map) //funcion que verifica los errores
{
    Tarea *actual = (Tarea*) firstTreeMap(map);

    while(actual != NULL)
    {
        printf("Tarea %s\n", actual->nombre);
        
        actual = (Tarea*) nextTreeMap(map);
    }

    system("pause");
}

void mostrarTareasPendientes(TreeMap *mapa)
{
    if(firstTreeMap(mapa) == NULL)
    {
        printf("No existe tarea alguna, intente nuevamente\n");
        return;
    }

    List *llenar_lista = crearListaTareas(mapa);
    Tarea* tarea_actual = (Tarea *) firstList(llenar_lista);
    
    puts("---------------------------------------------------------");
    puts("Estas son las tareas que quedan por hacer ordenadas por prioridad y precedencia");
    puts("---------------------------------------------------------");
    printf("\n");

    int cont=1;

    while(tarea_actual != NULL)
    {   
        printf("%d.-Nombre: %s --- Prioridad: %s ",cont, tarea_actual->nombre, tarea_actual->prioridad);

        cont++;
        
        if(firstList(tarea_actual->lista_precedencia) != NULL)
        {   
            printf("Precedente: ");
            mostrarListaPrece(tarea_actual->lista_precedencia);
        }
        printf("\n");
        tarea_actual = nextList(llenar_lista);
    }
    printf("\n");
    puts("---------------------------------------------------------");
    system("pause");
    system("cls");
}


/*void tareaRealizada(TreeMap *mapa, char* tarea)
{
    if(esta_presente(mapa, tarea) == 0)
    {
        puts("La tarea no se encuentra en el sistema, intente otra vez");
        system("pause");
        return;
    }   
    Tarea* tareaAux = firstTreeMap(mapa);

    while(tareaAux != NULL)
    {   
        Tarea* precedenciaActual = firstList(tareaAux->lista_precedencia);
        if(firstList(tareaAux->lista_precedencia) != NULL)
        {   
            while(precedenciaActual != NULL)
            {
                if(strcmp(precedenciaActual->nombre,tarea) == 0)
                {
                    popactual(tareaAux->lista_precedencia);
                }
                precedenciaActual = nextList(tareaAux->lista_precedencia);
            }
        }

        tareaAux = nextTreeMap(mapa);
    }
    buscar_tarea(mapa, tarea);
    eraseTreeMap(mapa);
    puts("La tarea ha sido marcada como completada exitosamente");
}*/

void tareaRealizada(TreeMap* mapa, char* tarea)
{
    if (!esta_presente(mapa, tarea))
    {
        puts("La tarea no se encuentra en el sistema, intente otra vez");
        system("pause");
        return;
    }

    // Verificar si hay tareas en la lista de precedencia de otras tareas
    Tarea* tareaAux = firstTreeMap(mapa);
    while (tareaAux != NULL)
    {
        Tarea* precedenciaActual = firstList(tareaAux->lista_precedencia);
        while (precedenciaActual != NULL)
        {
            if (strcmp(precedenciaActual->nombre, tarea) == 0)
            {
                puts("No se puede marcar la tarea como completada. Existen tareas en espera de esta tarea.");
                system("pause");
                return;
            }
            precedenciaActual = nextList(tareaAux->lista_precedencia);
        }
        tareaAux = nextTreeMap(mapa);
    }

    // Eliminar la tarea y actualizar las listas de precedencia
    eraseTreeMapNode(mapa, tarea, NULL);

    // Eliminar la tarea de las listas de precedencia de otras tareas
    tareaAux = firstTreeMap(mapa);
    while (tareaAux != NULL)
    {
        Tarea* precedenciaActual = firstList(tareaAux->lista_precedencia);
        while (precedenciaActual != NULL)
        {
            if (strcmp(precedenciaActual->nombre, tarea) == 0)
            {
                popactual(tareaAux->lista_precedencia);
                break;
            }
            precedenciaActual = nextList(tareaAux->lista_precedencia);
        }
        tareaAux = nextTreeMap(mapa);
    }


    puts("La tarea ha sido marcada como completada exitosamente");
    system("pause");
}

