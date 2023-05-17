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
