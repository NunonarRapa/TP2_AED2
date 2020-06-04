#ifndef CITYEDGES_H_
#define CITYEDGES_H_
#include "../AuxRecord/AuxRecord.h"

typedef struct CitiesEdges{ /*Edges*/
    int id;
    double peso;
    struct CitiesEdges *next_edge;
} CitiesEdges;

CitiesEdges* InsertIncidence(CitiesEdges *lst, int id, double peso);
extern char* strdup(const char*);

#endif