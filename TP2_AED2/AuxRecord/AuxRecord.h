#ifndef AUXRECORD_H_
#define AUXRECORD_H_

typedef struct auxRecord{ /*DijkstraAux*/
    int id;
    int connection;
    double cost;
    struct auxRecord* next_rec;
} AuxRecord;


AuxRecord *NewAuxRecord(int id);
AuxRecord* AuxRecSearchId(AuxRecord* lst, int id);
AuxRecord* AuxRecSortedInsert(AuxRecord* lst, AuxRecord* destinationRecord);
AuxRecord* PathHeadInsert(AuxRecord* path, int connection);

#endif