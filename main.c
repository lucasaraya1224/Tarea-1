#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tda.h"
#include "tdas/list.h"
#include "tdas/extra.h"

//funcion auxiliar para imprimir
void imprimirTicket(ticket* t) 
{
    char buffer_hora[26];
    struct tm* tm_info = localtime(&t->registro);
    strftime(buffer_hora, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    
    printf("ID: %d | Prioridad: %-5s | Registro: %s | Descripcion: %s\n", 
           t->id, prioridadstr[t->prioridad], buffer_hora, t->descripcion);
}

//muestra lista de tickets pendientes usando el orden de la cola
void mostrarListaPendientes(sistemaTickets *st)
{
    limpiarPantalla();
    puts("LISTA DE TICKETS PENDIENTES\n");

    int contador = 0;
    for (int i = 2; i >= 0; i--) {
        List *listaInterna = st->primero[i];
        for (ticket *t = list_first(listaInterna); t != NULL; t = list_next(listaInterna)) 
        {
            imprimirTicket(t);
            contador++;
        }
    }

    if (contador == 0) 
    {
        puts("no hay tickets pendientes en el sistema\n");
    }
    presioneTeclaParaContinuar();
}

int main() {
    sistemaTickets st;
    inicializarSistema(&st);

    char opcion;
    do {
        limpiarPantalla();
        puts("SISTEMA DE GESTION DE TICKETS\n");
        puts("1) registrar ticket.");
        puts("2) asignar prioridad a ticket.");
        puts("3) mostrar lista de tickets pendientes.");
        puts("4) procesar siguiente ticket.");
        puts("5) buscar ticket por ID.");
        puts("6) salir");
        printf("Ingrese su opcion: ");
        scanf("%c", &opcion);
        getchar(); // Captura salto de línea

        int idInput, pInput;
        char descInput[100];

        switch (opcion) {
            case '1':
                limpiarPantalla();
                puts("registrar Ticket\n");
                printf("ingrese ID unico del ticket:");
                scanf("%d", &idInput);
                getchar();
                printf("ingrese descripcion del problema:");
                fgets(descInput, sizeof(descInput), stdin);
                descInput[strcspn(descInput, "\n")] = '\0';
                
                registrarNuevoTicket(&st, idInput, descInput);
                printf("\nticket %d registrado (prioridad por defecto: bajo)\n", idInput);
                presioneTeclaParaContinuar();
                break;

            case '2':
                limpiarPantalla();
                puts("asignar prioridad a ticket");
                printf("ingrese el ID del ticket:");
                scanf("%d", &idInput);
                printf("seleccione prioridad (0: Bajo, 1: Medio, 2: Alto): ");
                scanf("%d", &pInput);
                getchar();

                if (pInput >= 0 && pInput <= 2) {
                    if (cambiarPrioridadTicket(&st, idInput, (Prioridad)pInput)) 
                    {
                        printf("\nprioridad del ticket %d cambiada a '%s'\n", idInput, prioridadstr[pInput]);
                    } else {
                        printf("\nel ID de ticket %d no existe\n", idInput);
                    }
                } else {
                    puts("\nrango de prioridad invalido.");
                }
                presioneTeclaParaContinuar();
                break;

            case '3':
                mostrarListaPendientes(&st);
                break;

            case '4':
                limpiarPantalla();
                puts("procesar siguiente ticket\n");
                ticket *atendido = atenderSiguienteTicket(&st);
                if (atendido != NULL) 
                {
                    puts("atendiendo ticket"); 
                    imprimirTicket(atendido);
                    free(atendido);
                } else {
                    puts("no hay tickets pendientes por procesar");
                }
                presioneTeclaParaContinuar();
                break;

            case '5':
                limpiarPantalla();
                puts("buscar ticket por ID");
                printf("ingrese el ID a buscar:");
                scanf("%d", &idInput);
                getchar();

                ticket *encontrado = buscarTicketPorId(&st, idInput);
                if (encontrado != NULL)
                {
                    puts("\ndetalles del Ticket");
                    imprimirTicket(encontrado);
                } else {
                    printf("\nel ticket con ID %d no existe\n", idInput);
                }
                presioneTeclaParaContinuar();
                break;

            case '6':
                puts("liberando recursos y saliendo");
                break;

            default:
                puts("opcion no valida, intente nuevamente");
                presioneTeclaParaContinuar();
        }
    } while (opcion != '6');

    liberarSistema(&st);
    return 0;
}