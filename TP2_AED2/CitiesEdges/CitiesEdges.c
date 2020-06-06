#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CitiesEdges.h"

/*Head insert of CitiesEdges*/
CitiesEdges* InsertIncidence(CitiesEdges *lst, int id, double peso){
   
    if (!lst || id < lst->id)
    {
        CitiesEdges* new = (CitiesEdges*)malloc(sizeof(CitiesEdges));
        new->id = id;
        new->peso = peso;
        new->next_edge = lst;
        lst = new;
    }
    else if(lst->id == id){
        if(lst->peso > peso){
            lst->peso = peso;
        }
    }
    else {
        lst->next_edge = InsertIncidence(lst->next_edge, id, peso);
    }
    return lst;
}


/*Head-Insert to create the path on the list*/
CitiesEdges* PathHeadInsert(CitiesEdges* path, int id){
    CitiesEdges* aux = (CitiesEdges*)malloc(sizeof(CitiesEdges));
    aux->id = id;
    aux->next_edge = path;
    return aux;
}