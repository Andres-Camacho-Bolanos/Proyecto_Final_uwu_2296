//Se incluyen las bibliotecas estándar para C, además de string para poder manejarlos posteriormente.
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

/*
Documentación
    Authors: Camacho Bolaños Andrés, Corona Márquez Juan Carlos,
    Díaz Balbuena Daniel Alberto, Reyes Oliveros Ángel Esteban
    Date: 17/Mayo/2023
    Description: "Paisa System" Programa en lenguaje C que ayudará a la gestión
    de las órdenes en una taquería  
*/

/*Se define la struct principal, donde se van a almacenar los datos de las variables
que se utilizarán a lo largo de todo el código, además de uso de strings*/
typedef struct {
    char platillo[20];
    char nombre_cliente[50];
    int cantidad;
    float precio_total;
    int mesa;
}
Orden;
char platillo[20];

/*
Función: agregar_orden
Objetivo: permitir a los meseros ingresar los datos de cada orden de la taquería
*/
void agregar_orden(Orden* ordenes, int indice, int es_mesa) {
    char platillo[20], nombre_cliente[50];
    int cantidad;
    float precio_total, precio_unitario; /*Precio unitario hace referencia a la variable que almacena el precio individual por cada platillo o bebida, 
    mientras que Precio total va a almacenar la suma total de los precios según la cantidad que hayan pedido*/

    /*Estos mensajes representarán el cuerpo general del programa una vez que se seleccione ingresar una orden, 
    independientemente si se trata de consumo local o pedido a domicilio*/
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
    
           /*En este Switch case se va a colocar por casos el precio de cada platillo de acuerdo a cómo están ordenados en los printf del 
           cuerpo general en agregar orden. Lo que va a hacer es buscar el precio del platillo correspondiente*/
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
    
   /*Si el mesero selecciona consumo local, que en este caso funcionará como argumento en el main, 
   el programa va a pedir el número de mesa como dato adicional*/

    /*En este caso declaramos la variable mesa y la inicializamos en 0, con el fin de que el mesero seleccione 
    el número de aquella que sea asignada al cliente y el programa no permita que se repitan*/
    int mesa = 0;
    if (es_mesa) {
        printf("Ingrese el numero de mesa: ");
        scanf("%d", &mesa);
    }

    //Como se mencionó anteriormente, va a calcular el precio total de acuerdo a la cantidad y el tipo de platillo seleccionado
    precio_total = precio_unitario * cantidad;

    

   /*Se van a guardar los datos ingresados en la estructura de datos*/
    strcpy(ordenes[indice].platillo, platillo);

    strcpy(ordenes[indice].nombre_cliente, nombre_cliente);

    ordenes[indice].cantidad = cantidad;

    ordenes[indice].precio_total = precio_total;

    ordenes[indice].mesa = mesa;

}

/*
Función: consultar_precios
Objetivo: permitir a los meseros consultar el menú con los platillos disponibles y sus precios
*/

void consultar_precios() {

    printf("----- MENU -----\n");

    printf("1. Tacos (Pastor, Suadero, Campechano, Tripa) - $10.00\n");

    printf("2. Gorditas (Pastor, Suadero) - $25.00\n");

    printf("3. Gringas - $30.00\n");

    printf("4. Tortas (Pastor, Suadero) - $40.00\n");

    printf("5. Refresco: (Coca cola, Pepsi, Manzanita, Sangria, 7-UP) - $15.00\n");

}

/*Todos los datos ingresados previamente (en void agregar_orden) y que se guardaron en 
la estructura de datos, funcionarán como argumentos en esta nueva función, la cual se utilizará 
para generar archivos .csv
*/

void guardar_datos_csv(char* nombre_archivo, Orden* ordenes, int cantidad_ordenes) {

     /*Crear un nuevo archivo vacío o sobrescribir el existente con la información 
     que se vaya actualizando de la estructura de datos */
    FILE* archivo_csv = fopen(nombre_archivo, "w");

    if (archivo_csv == NULL) {

        printf("Error al abrir el archivo. %s.\n", nombre_archivo);

        return;

    }

     //Se va a escribir el encabezado para comprender a que corresponde cada dato
    fprintf(archivo_csv, "Platillo,Nombre cliente,Cantidad,Precio total,Mesa\n");

  //Se van a escribir los datos de cada orden en una nueva línea del archivo .csv
    
/*En este caso la variable del contador se declaró afuera, ya que el compilador 
marcaba errores por la versión que se estaba utilizando*/ 
  int i;  

  for (i = 0; i < cantidad_ordenes; i++) {

        fprintf(archivo_csv, "%s,%s,%d,%.2f", ordenes[i].platillo, ordenes[i].nombre_cliente, ordenes[i].cantidad, ordenes[i].precio_total);

  // Si la orden está en una mesa, se va a agregar el número de mesa al final de la línea
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

//Esta será nuestra función principal
int main() {
    Orden mesa[5];
    Orden domicilio[5];
    int opcion, tipo_orden, n_mesa; //Se declaran variables que definirán si el tipo de órden es para llevar o en domicilio
    int num_ordenes_mesa = 0, num_ordenes_domicilio = 0; //Ambos se inicializan en 0, con tal de que el personal del Paisa no tenga sobrecapacidad

    /*Estos mensajes constituyen el cuerpo principal del programa al ejecutarlo, 
    con el fin de que el mesero sepa qué opción seleccionar de acuerdo a lo que pida el cliente*/   
    printf("Taqueria El Paisa.inc.\n");
    printf("Todos los derechos estan reservados.\n");
    printf("Bienvenido. ¿Que desea hacer?\n");
    printf("1. Registrar orden en mesa.\n");
    printf("2. Registrar orden para llevar.\n");
    printf("3. Consultar menu y precios.\n");
    printf("4. Salir del programa.\n");

    do { /*Este bucle realizará una instrucción de acuerdo a la opción seleccionada. 
    Mientras no se seleccione 4, el programa seguirá abierto*/
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) { //Se limitan el numero de ordenes que se pueden tener al mismo tiempo
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

