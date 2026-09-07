# sistema de gestion de tickets de soporte tecnico

aplicacion modular interactiva desarrollada en c para la administracion eficiente de tickets corporativos utilizando un tipo de dato abstracto (tda) fundamentado en colas de prioridad multiple(3)

# aestructura del codigo
el codigo utiliza para su estructura las tda list y queue
- estructuralmente, cada elemento de tipo ticket utiliza un enlace denominado proximo para apuntar secuencialmente al elemento posterior en memoria.
- se implementaron 3 colas independientes para lograr una resolucion estable

# como compilar y ejecutar

ejecute el siguiente comando en la terminal:

gcc tdas/*.c tda.c main.c -o tarea1 && ./tarea1

# informe de operacion (nivel bueno)
todas las funcionalidades operan correctamente bajo las siguientes condiciones evaluadas:

1. registrar ticket: almacena los campos de texto, asigna la estampa de tiempo real unix mediante time.h y preestablece la urgencia en bajo
2. asignar prioridad: utiliza busquedas abstractas seguras. extrae el nodo mediante list_popcurrent y lo reinserta al fondo de la nueva fila correspondiente, valida ids inexistentes.
3. mostrar lista: despliega de manera ordenada y legible todos los tickets del sistema desde el nivel alto al bajo
4. procesar siguiente: extrae y visualiza el ticket que se situa a la cabeza del arreglo prioritario con un manejo eficiente de memoria dinamico
5. buscar ticket: recorre las listas estructurales sin desorganizar ni romper el flujo de espera de los usuarios

# ejemplo de uso paso a paso

asi es como se ve la interaccion con el menu en la terminal basado en la estructura de la interfaz:

1. registrar un nuevo ticket: SISTEMA DE GESTION DE TICKETS

1) registrar ticket
2) asignar prioridad a ticket
3) mostrar lista de tickets pendientes
4) procesar siguiente ticket
5) buscar ticket por ID
6) salir
Ingrese su opcion: 1

registrar Ticket

ingrese ID unico del ticket: 101
ingrese descripcion del problema:problema de conexion wifi

ticket 101 registrado (prioridad por defecto: bajo)
Presione una tecla para continuar

2. cambiar la prioridad del ticket a alto:
SISTEMA DE GESTION DE TICKETS

Ingrese su opcion: 2

asignar prioridad a ticket
ingrese el ID del ticket:101
seleccione prioridad (0: Bajo, 1: Medio, 2: Alto): 2

prioridad del ticket 101 cambiada a 'Alto'
Presione una tecla para continuar

3. mostrar la lista de tickets pendientes:
SISTEMA DE GESTION DE TICKETS

Ingrese su opcion: 3

LISTA DE TICKETS PENDIENTES

ID: 101 | Prioridad: Alto  | Registro: 2026-09-xx xx:xx:xx | Descripcion: problema de conexion wifi
Presione una tecla para continuar

4. procesar el ticket mas urgente para atenderlo:
SISTEMA DE GESTION DE TICKETS

Ingrese su opcion: 4

procesar siguiente ticket

atendiendo ticket
ID: 101 | Prioridad: Alto  | Registro: 2026-09-xx xx:xx:xx | Descripcion: problema de conexion wifi
Presione una tecla para continuar

5. buscar un ticket por id y desplegar sus detalles:
SISTEMA DE GESTION DE TICKETS

Ingrese su opción: 5

buscar ticket por ID
ingrese el ID a buscar:101

detalles del Ticket
ID: 101 | Prioridad: Alto  | Registro: 2026-09-xx xx:xx:xx | Descripción: problema de conexion wifi
Presione una tecla para continuar...

6. liberar los recursos del sistema y salir de la aplicacion:
SISTEMA DE GESTION DE TICKETS

Ingrese su opción: 6

liberando recursos y saliendo