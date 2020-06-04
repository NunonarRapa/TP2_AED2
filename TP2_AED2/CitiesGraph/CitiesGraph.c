#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CitiesGraph.h"

#define HASH_SIZE 50000

int HashInt(int id){
    return id % HASH_SIZE;
}

Cities* HashSearchCl(Cities *lst, int id) {
    if (lst && lst->id == id) return lst;
    if (lst) return HashSearchCl(lst->next_city, id);
    return NULL;
}

Cities* HashSearch(Cities** hash, int id) {
    int pos = HashInt(id);
    return HashSearchCl(hash[pos], id);
}

Cities** HashNew() {
    return (Cities**) calloc(HASH_SIZE, sizeof(Cities*));
}

Cities* HashInsertEdgeCl(Cities* lst, int id, int idDestino, double peso){
    if (lst && lst->id == id) {
        /* Nodo ja existente, adicionar nova incidencia*/
        lst->edges = InsertIncidence(lst->edges, idDestino, peso);
    } else if (lst && lst->id < id) {
        /* Insercao Ordenada*/
        lst->next_city = HashInsertEdgeCl(lst->next_city, id, idDestino, peso);
    } else {
        /* Insercao de novo nodo*/
        Cities* new = (Cities*) malloc(sizeof(Cities));
        new->id = id;
        new->next_city = lst;
        new->edges = InsertIncidence(NULL, idDestino, peso);
        lst = new;
    }
    return lst;
}

void HashInsertEdge(Cities** hash, int id, int idDestino, double peso){
    int pos = HashInt(id);
    hash[pos] = HashInsertEdgeCl(hash[pos], id, idDestino, peso);
}

AuxRecord* PathFind(Cities **hash, int origin, int target) {
    AuxRecord *current = NULL;

    /* open is sorted by cost */
    AuxRecord *open = NewAuxRecord(origin);
    AuxRecord *closed = NULL;
    AuxRecord* path = NULL;
    CitiesEdges *neighbours;
    double costSoFar = 0;
    while (open) {
        current = open;   /* get element */
        open = open->next_rec;   /* remove from list */
        current->next_rec = NULL;   /* remove list from current */
        printf("currid %d\n", current->id);
        if (current->id == target) break;
        printf("target %d\n", target);
        neighbours = HashSearch(hash, current->id)->edges;
        
        for ( ; neighbours ; neighbours = neighbours->next_edge) {
            printf("neigID %d\n", neighbours->id);
            int destination = neighbours->id;
            AuxRecord *destinationRecord = NULL;
            costSoFar = current->cost + neighbours->peso;

            /* se ja visitamos, skip */
            if (AuxRecSearchId(closed, destination) != NULL) continue;

            destinationRecord = AuxRecSearchId(open, destination);
            if (destinationRecord) {
                /* nodo ja tinha sido marcado para visita */
                if (costSoFar >= destinationRecord->cost) continue;
            } 
            else {
                /* nodo novo! */
                destinationRecord = NewAuxRecord(destination);
                open = AuxRecSortedInsert(open, destinationRecord);
            }
            destinationRecord->cost = costSoFar;
            destinationRecord->connection = current->id;
            printf("destR_connec %d\n", destinationRecord->connection);
            closed = AuxRecSortedInsert(closed, current);
        }
    }
    if(current->id != target) return NULL;
    printf("curr_id target %d %d\n", current->id, target);

    path->id = current->id; /*ERROR HERE SEGMENTATION FAULT CORE DUMPED*/
    printf("pathid %d\n", path->id);
    while(current->id != origin) {
        PathHeadInsert(path, current->connection);

        current = AuxRecSearchId(closed, current->connection);
    }
    printf("pathid %d", path->id);
    return path;
}