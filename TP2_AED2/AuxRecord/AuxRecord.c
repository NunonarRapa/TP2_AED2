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

AuxRecord* PathHeadInsert(AuxRecord* path, int connection){
    AuxRecord* aux = (AuxRecord*)malloc(sizeof(AuxRecord));
    aux->id = connection;
    aux->cost = 0;
    aux->connection = 0;
    aux->next_rec = path;
    return aux;
}