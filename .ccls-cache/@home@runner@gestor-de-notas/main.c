#include <stdio.h>

void agregarNota() {
    char nota[1000];
    printf("Ingrese la nota: ");
    fgets(nota, sizeof(nota), stdin);

    FILE *archivo = fopen("notas.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "%s\n", nota);
    fclose(archivo);
    printf("Nota agregada exitosamente.\n");
}

void mostrarNotas() {
    char nota[1000];
    FILE *archivo = fopen("notas.txt", "r");
    if (archivo == NULL) {
        printf("Aún no hay notas.\n");
        return;
    }

    printf("Notas:\n");
    int contador = 1;
    while (fgets(nota, sizeof(nota), archivo) != NULL) {
        printf("%d. %s", contador, nota);
        contador++;
    }

    fclose(archivo);
}

void editarNota() {
    mostrarNotas();
    int seleccion;
    printf("Seleccione el número de la nota que desea editar: ");
    scanf("%d", &seleccion);
    getchar(); 

    FILE *archivo = fopen("notas.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    FILE *temporal = fopen("temporal.txt", "w");
    if (temporal == NULL) {
        printf("Error al abrir el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    char nota[1000];
    int contador = 1;
    while (fgets(nota, sizeof(nota), archivo) != NULL) {
        if (contador == seleccion) {
            printf("Ingrese la nueva versión de la nota: ");
            fgets(nota, sizeof(nota), stdin);
            fprintf(temporal, "%s", nota);
        } else {
            fprintf(temporal, "%s", nota);
        }
        contador++;
    }

    fclose(archivo);
    fclose(temporal);

    remove("notas.txt");
    rename("temporal.txt", "notas.txt");

    printf("Nota editada exitosamente.\n");
}

void eliminarNota() {
    mostrarNotas();
    int seleccion;
    printf("Seleccione el número de la nota que desea eliminar: ");
    scanf("%d", &seleccion);
    getchar(); 

    FILE *archivo = fopen("notas.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    FILE *temporal = fopen("temporal.txt", "w");
    if (temporal == NULL) {
        printf("Error al abrir el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    char nota[1000];
    int contador = 1;
    while (fgets(nota, sizeof(nota), archivo) != NULL) {
        if (contador != seleccion) {
            fprintf(temporal, "%s", nota);
        }
        contador++;
    }

    fclose(archivo);
    fclose(temporal);

    remove("notas.txt");
    rename("temporal.txt", "notas.txt");

    printf("Nota eliminada exitosamente.\n");
}

int main() {
    int opcion;

    do {
        printf("\nGestor de Notas\n");
        printf("1. Agregar nota\n");
        printf("2. Mostrar notas\n");
        printf("3. Editar nota\n");
        printf("4. Eliminar nota\n");
        printf("5. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarNota();
                break;
            case 2:
                mostrarNotas();
                break;
            case 3:
                editarNota();
                break;
            case 4:
                eliminarNota();
                break;
            case 5:
                printf("Gracias por utilizar el gestor de notas.\n");
                break;
            default:
                printf("Opción inválida. Por favor, seleccione una opción válida.\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}
