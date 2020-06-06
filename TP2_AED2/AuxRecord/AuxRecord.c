#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AuxRecord.h"

AuxRecord* NewAuxRecord(int id){
    AuxRecord *new = (AuxRecord*) malloc(sizeof(AuxRecord));
    new->id = id;
    new->connection = 0;
    new->cost = 0;
    new->next_rec = NULL;
    return new;
}

/*Searches an ID on the list and returns the respective node or NULL, if it doesnt find*/
AuxRecord* AuxRecSearchId(AuxRecord* lst, int id){
    AuxRecord* aux = lst;
    if (!lst) return NULL;
    while (aux)
    {
        if (aux->id == id)
        {
            return aux;
        }
        aux = aux->next_rec;
    }
    return NULL;
}

/*Inserts a AuxRecord on the list, sorted be cost*/
AuxRecord* AuxRecSortedInsert(AuxRecord* lst, AuxRecord* destinationRecord){
    if (!lst || lst->cost > destinationRecord->cost) 
    {
        AuxRecord *new = (AuxRecord*)malloc(sizeof(AuxRecord));    
        new->id = destinationRecord->id;  
        new->connection = destinationRecord->connection; 
        new->cost = destinationRecord->cost;        
        new->next_rec = lst;                       
        return new;                              
    }
    else 
    {
        lst->next_rec = AuxRecSortedInsert(lst->next_rec, destinationRecord);   
    }
    return lst;
}

AuxRecord* Find(AuxRecord* lst, int connection){
    AuxRecord* aux = lst;
    while (aux)
    {
        if (aux->id == connection) return aux;
        aux = aux->next_rec;        
    }
    return NULL;
}