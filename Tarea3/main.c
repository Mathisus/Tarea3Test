#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"
#include "list.h"
#include "treemap.h"
#include <unistd.h>
#define MAXCHAR 30

int lower_than_string(void* key1, void* key2)
{
    char* k1 = (char *)key1;
    char* k2 = (char *)key2;
    if (strcmp(k1, k2) < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void ingresar_valor(char *value, char* mostrarT)
{
    puts("-------------------------------");
    printf("%s\n", mostrarT);
    puts("-------------------------------");

    scanf("%30[^\n]s", value);

    while (getchar() != '\n');
}

int main()
{
    TreeMap *tareas = createTreeMap(lower_than_string, NULL, NULL, NULL);
    while(1)
    {
        mostrar_menu();
        int opcion;
        scanf("%d", &opcion);

        while (getchar() != '\n');

        char nombreTarea[MAXCHAR];
        char prioridad[MAXCHAR];
        char precedencia[MAXCHAR];

        switch (opcion)
        {
        case 1:
            system("cls");

            ingresar_valor(nombreTarea, "Ingrese el nombre de la tarea");
            ingresar_valor(prioridad, "Ingrese la prioridad de la tarea");

            agregarTarea(tareas, nombreTarea, prioridad);

            puts("");
            puts("Tarea agregada con exito");
            puts("");

            system("pause");
            system("cls");
            break;

        case 2:

            system("cls");
            ingresar_valor(nombreTarea, "Ingrese el nombre de la tarea");
            ingresar_valor(precedencia, "Ingrese la tarea de la cual depende");

            definirPrecedencia(tareas, nombreTarea, precedencia);

            system("pause");
            system("cls");

            break;

        case 3:
            system("cls");

            mostrarTareasPendientes(tareas);

            system("cls");
            break;

        case 4:
            system("cls");

            ingresar_valor(nombreTarea, "Ingrese el nombre de la tarea");

            tareaRealizada(tareas, nombreTarea);

            system("cls");
            break;
        
        case 5:

            system("cls");
            printf("Cerrando programa... ^^\n");
            sleep(1);
            system("cls");
            exit(0);
            break;
            
        default:
            system("cls");
            puts("Opcion invalida, intente otra vez");
            system("pause");
            system("cls");
            break;
        }
        
    }



}