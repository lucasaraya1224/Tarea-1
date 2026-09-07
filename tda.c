#include "tda.h" // Comilla de cierre corregida
#include "tdas/list.h"
#include <stdlib.h>
#include <string.h>

const char* prioridadstr[] = {"Bajo", "Medio", "Alto"};

//inicializa las 3 colas independientes usando queue_create
void inicializarSistema(sistemaTickets *st) 
{
    for (int i = 0; i < 3; i++) 
        st->primero[i] = list_create();
}

//registra un nuevo ticket en la cola BAJO
void registrarNuevoTicket(sistemaTickets *st, int id, const char* desc) 
{
    ticket *nuevo = (ticket *)malloc(sizeof(ticket));
    if (nuevo == NULL) return;

    nuevo->id = id;
    strcpy(nuevo->descripcion, desc);
    nuevo->prioridad = BAJO; //prioridad baja por defecto
    nuevo->registro = time(NULL); //hora de registro actual
    nuevo->proximo = NULL;

    //encola en la prioridad indicada
    list_pushBack(st->primero[BAJO], nuevo);
}

//busca un ticket en el sistema, lo extrae y lo pone en su nueva prioridad
int cambiarPrioridadTicket(sistemaTickets *st, int id, Prioridad nueva_p) 
{
    ticket *ticketExtraido = NULL;

    //recorre las colas para buscar y extraer el elemento con list_popCurrent
    for (int i = 0; i < 3; i++) 
    {
        List *listaInterna = st->primero[i];
        for (ticket *t = list_first(listaInterna); t != NULL; t = list_next(listaInterna)) 
        {
            if (t->id == id) 
            {
                ticketExtraido = (ticket *)list_popCurrent(listaInterna);
                break;
            }
        }
        if (ticketExtraido != NULL) break;
    }

    //si se encontro, actualiza e inserta en la nueva cola
    if (ticketExtraido != NULL)
    {
        ticketExtraido->prioridad = nueva_p;
        list_pushBack(st->primero[nueva_p], ticketExtraido);
        return 1;
    }
    return 0;
}

//selecciona y remueve el ticket en base a la prioridad
ticket* atenderSiguienteTicket(sistemaTickets *st) 
{
    for (int i = 2; i >= 0; i--) 
    {
        ticket *atender = (ticket *)list_first(st->primero[i]);
        if (atender != NULL) 
            return (ticket *)list_popFront(st->primero[i]);
    }
    return NULL;
}

//busca el ticket para visualizar sus detalles sin modificar nada
ticket* buscarTicketPorId(sistemaTickets *st, int id) 
{
    for (int i = 0; i < 3; i++) 
    {
        List *listaInterna = st->primero[i];
        for (ticket *t = list_first(listaInterna); t != NULL; t = list_next(listaInterna)) 
            if (t->id == id) 
                return t;
    }
    return NULL;
}

//limpia el sistema para evitar fugas de memoria
void liberarSistema(sistemaTickets *st)
{
    for (int i = 0; i < 3; i++)
    {
        list_clean(st->primero[i]);
        free(st->primero[i]);
    }
}