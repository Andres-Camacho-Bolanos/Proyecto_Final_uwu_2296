#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char platillo[20];
    char nombre_cliente[50];
    int cantidad;
    float precio_total;
    int mesa;
}
Orden;
char platillo[20];
void agregar_orden(Orden* ordenes, int indice, int es_mesa) {
    char platillo[20], nombre_cliente[50];
    int cantidad;
    float precio_total, precio_unitario;

    printf("Ingrese el platillo:\n");
    printf("1. Tacos (Pastor, Suadero, Campechano, Tripa).\n");
    printf("2. Gorditas (Pastor, Suadero).\n");
    printf("3. Gringas.\n");
    printf("4. Tortas (Pastor, Suadero).\n");
    printf("5. Refresco: (Coca cola, Pepsi, Manzanita, Sangria, 7-UP).\n");
    scanf("%s", platillo);

    printf("Ingrese el nombre del cliente: ");
    scanf("%s", nombre_cliente);

    printf("Ingrese la cantidad: ");
    scanf("%d", &cantidad);
    
        // Buscar el precio del platillo
    switch(platillo[0]) {
        case '1':
            precio_unitario = 10.00;
            break;
        case '2':
            precio_unitario = 25.00;
            break;
        case '3':
            precio_unitario = 30.00;
            break;
        case '4':
            precio_unitario = 40.00;
            break;
        case '5':
            precio_unitario = 15.00;
            break;
        default:
            printf("Platillo no válido\n");
            return;
    }
    
    // Pedir el número de mesa solo para las órdenes en mesa
    int mesa = 0;
    if (es_mesa) {
        printf("Ingrese el numero de mesa: ");
        scanf("%d", &mesa);
    }

    // Calcular el precio total

    precio_total = precio_unitario * cantidad;

    

    // guardar los datos ingresados en la estructura

    strcpy(ordenes[indice].platillo, platillo);

    strcpy(ordenes[indice].nombre_cliente, nombre_cliente);

    ordenes[indice].cantidad = cantidad;

    ordenes[indice].precio_total = precio_total;

    ordenes[indice].mesa = mesa;

}

void consultar_precios() {

    printf("----- MENU -----\n");

    printf("1. Tacos (Pastor, Suadero, Campechano, Tripa) - $10.00\n");

    printf("2. Gorditas (Pastor, Suadero) - $25.00\n");

    printf("3. Gringas - $30.00\n");

    printf("4. Tortas (Pastor, Suadero) - $40.00\n");

    printf("5. Refresco: (Coca cola, Pepsi, Manzanita, Sangria, 7-UP) - $15.00\n");

}

void guardar_datos_csv(char* nombre_archivo, Orden* ordenes, int cantidad_ordenes) {

    // Crear un nuevo archivo vacío o sobrescribir el existente

    FILE* archivo_csv = fopen(nombre_archivo, "w");

    if (archivo_csv == NULL) {

        printf("Error al abrir el archivo. %s.\n", nombre_archivo);

        return;

    }

    // Escribir el encabezado

    fprintf(archivo_csv, "Platillo,Nombre cliente,Cantidad,Precio total,Mesa\n");

    // Escribir los datos de cada orden en una nueva línea del archivo

  int i;  

  for (i = 0; i < cantidad_ordenes; i++) {

        fprintf(archivo_csv, "%s,%s,%d,%.2f", ordenes[i].platillo, ordenes[i].nombre_cliente, ordenes[i].cantidad, ordenes[i].precio_total);

        // Si la orden está en una mesa, agregar el número de mesa al final de la línea

        if (ordenes[i].mesa > 0) {

            fprintf(archivo_csv, ",%d\n", ordenes[i].mesa);

        } else {

            fprintf(archivo_csv, "\n");

        }

    }

    // Cerrar el archivo

    fclose(archivo_csv);

}
/* añadiendo la funcion principal donde se llamará a las funciones previamente declaradas*/

int main() {
    Orden mesa[5];
    Orden domicilio[5];
    int opcion, tipo_orden, n_mesa;
    int num_ordenes_mesa = 0, num_ordenes_domicilio = 0;

    printf("Taqueria El Paisa.inc.\n");
    printf("Todos los derechos estan reservados.\n");
    printf("Bienvenido. ¿Que desea hacer?\n");
    printf("1. Registrar orden en mesa.\n");
    printf("2. Registrar orden para llevar.\n");
    printf("3. Consultar menu y precios.\n");
    printf("4. Salir del programa.\n");

    do {
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: // mesa
                if (num_ordenes_mesa == 5) {
                    printf("Lo sentimos, no se pueden registrar mas ordenes en mesa.\n");
                } else {
                    agregar_orden(mesa, num_ordenes_mesa, 1);
                    num_ordenes_mesa++;
                    guardar_datos_csv("ordenes_locales.csv", mesa, num_ordenes_mesa);
                }
                break;

            case 2: // domicilio
                if (num_ordenes_domicilio == 5) {
                    printf("Lo sentimos, no se pueden registrar mas ordenes para llevar.\n");
                } else {
                    agregar_orden(domicilio, num_ordenes_domicilio, 0);
                    num_ordenes_domicilio++;
                    guardar_datos_csv("domicilio.csv", domicilio, num_ordenes_domicilio);
                }
                break;

            case 3:
                consultar_precios();
                break;

            case 4:
                guardar_datos_csv("ordenes_locales.csv", mesa, num_ordenes_mesa);
                guardar_datos_csv("domicilio.csv", domicilio, num_ordenes_domicilio);
                printf("Gracias por utilizar el programa.\n");
                break;

            default:
                printf("Opcion no valida. Por favor seleccione una opcion valida.\n");
                break;
        }
    } while (opcion != 4);

    return 0;
}

