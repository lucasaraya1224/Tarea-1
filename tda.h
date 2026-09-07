#ifndef TDA_COLA_PRIORIDAD_H
#define TDA_COLA_PRIORIDAD_H

#include <time.h>
#include "tdas/list.h" // Se utiliza list.h directamente para evitar las definiciones multiples de queue.h

//las 3 prioridades diferentes para los tickets
typedef enum 
{
    BAJO,
    MEDIO,
    ALTO
} Prioridad;

//string auxiliar para mostrar las prioridades
extern const char* prioridadstr[];

//struct del ticket 
typedef struct ticket 
{
    int id;
    char descripcion[100];
    Prioridad prioridad;
    time_t registro;
    struct ticket* proximo;
} ticket;

//estructura del TDA que contiene las 3 colas
typedef struct {
    List* primero[3]; //definido de forma compatible para solucionar el error de enlazado
} sistemaTickets;

//inicializando los TDA de prioridad para el codigo
void inicializarSistema(sistemaTickets *st);
void registrarNuevoTicket(sistemaTickets *st, int id, const char* desc);
int cambiarPrioridadTicket(sistemaTickets *st, int id, Prioridad nueva_p);
ticket* atenderSiguienteTicket(sistemaTickets *st);
ticket* buscarTicketPorId(sistemaTickets *st, int id);
void liberarSistema(sistemaTickets *st);

#endif