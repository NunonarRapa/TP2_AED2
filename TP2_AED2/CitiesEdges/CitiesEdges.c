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