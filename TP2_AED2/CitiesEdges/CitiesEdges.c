#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CitiesEdges.h"

/*Head insert of CitiesEdges*/
CitiesEdges* InsertIncidence(CitiesEdges *lst, int id, double peso){
    CitiesEdges* new = (CitiesEdges*)malloc(sizeof(CitiesEdges));
    CitiesEdges *aux, *aux1;
    new->id = id;
    new->peso = peso;
    if (!lst || new->id < lst->id)
    {
        new->next_edge = lst;
        return new;
    }
    else {
        aux1 = lst;
        while (aux1->next_edge)
        {
            if (new->id == aux1->next_edge->id) {
                aux1->next_edge->peso = new->peso;
                return lst;
            }
            aux1 = aux1->next_edge;
        }
        aux = lst;
        while (aux->next_edge && new->id > aux->next_edge->id) {
            aux = aux->next_edge;
        }
        new->next_edge = aux->next_edge;
        aux->next_edge = new;
    }
    return lst;
}