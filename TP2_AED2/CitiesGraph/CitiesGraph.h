#ifndef CITYGRAPH_H_
#define CITYGRAPH_H_
#include "../CitiesEdges/CitiesEdges.h"


typedef struct CitiesGraph{ /*ID das cidades*/
    int id;
    CitiesEdges *edges;
    struct CitiesGraph *next_city;
} Cities;


int HashInt(int id);
Cities* HashSearchCl(Cities *lst, int id);
Cities* HashSearch(Cities** hash, int id);
Cities** HashNew();
Cities* HashInsertEdgeCl(Cities* lst, int id, int idDestino, double peso);
void HashInsertEdge(Cities** hash, int id, int idDestino, double peso);
AuxRecord *PathFind(Cities **hash, int origin, int destination);
extern char* strdup(const char*);


#endif