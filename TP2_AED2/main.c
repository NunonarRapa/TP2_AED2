#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CitiesGraph/CitiesGraph.h"
#include "WorldCities/WorldCities.h"
#define HASH_SIZE 50000

/*Ler o ficheiro cidades e coloca-lo na hash*/
void readcidades(FILE* fh, Cities** hash){
    char buf[200];
	fgets(buf, 200, fh);

	while (fgets(buf, 200, fh) != NULL) {
        char *line = buf, *field = NULL;
        int index = 0, id, idDestino;
        double peso;
        while ((field = strsep(&line, ",")) != NULL) {
            /*note the trailing field will contain newline*/
            if(index == 0) id = atoi(field);
            if(index == 2) idDestino = atoi(field);
            if(index == 4) peso = atof(field);
            index++;
        }
        HashInsertEdge(hash, id, idDestino, peso);
    }
}

/*Ler o ficheiro WorldCities e coloca-lo na lista*/
WorldCities* read(FILE* fh, WorldCities* worldCities){
    char buf[200];
	fgets(buf, 200, fh);
	while (fgets(buf, 200, fh) != NULL) {
        char *line = buf, *field, *city, *country;
        int index = 0, population, id;
        while ((field = strsep(&line, ",")) != NULL) {
            /*note the trailing field will contain newline*/
            if(index == 1) city = field;
            if(index == 4) country = field;
            if(index == 9) population = atoi(field);
            if(index == 10) id = atoi(field);
            index++;
        }
        worldCities = HeadInsert(worldCities, id, city, country, population);
    }
   return worldCities;
}

/*Verifica quantas cidades têm o mesmo nome*/
void CheckMultipleCities(WorldCities* worldCities, char* city){

    WorldCities* aux = worldCities;
    char answer[100] = "\0", answerAux[30] = "\0";
    int i = 0;
    printf("\nChecking for cities with the same name...\n");
    strcpy(answer, "Cities IDs: ");
    while (aux)
    {
        if (strcmp(aux->city, city) == 0)
        {
            sprintf(answerAux, "%d | ", aux->id);
            strcat(answer, answerAux);
            i++;
        }
        aux = aux->next;
    }
    if (i == 0)
    {
        printf("No cities with the same name found!\n");
    }
    if (i == 1)
    {
        printf("There is %d city with the same name!\n", i);
        printf("%s", answer);
    }
    else
    {
        printf("There are %d cities with the same name!\n", i);
        printf("%s", answer);
    }
}

/*Verifica os destinos de uma cidade*/
void WhereCanIGo(Cities** hash, WorldCities* worldCities, int id){
    Cities* cityy;
    CitiesEdges* edge;
    int i = 0;
    cityy = HashSearch(hash, id);
    printf("Checking for all destinations possible from city: %s...\n", CheckCityWithID(worldCities, cityy->id));
    for (edge = cityy->edges; edge; edge = edge->next_edge) {
        Cities* c = HashSearch(hash, edge->id);
        if (c != NULL)
        {
            printf("\t%s\n", CheckCityWithID(worldCities, edge->id));
            i++;
        }
    }
    if (i == 0)
    {
        printf("There were no destinations possible!\n");
    }
    else if (i == 1)
    {
        printf("There is %d destination possible!\n", i);
    }
    else
    {
        printf("There are %d destinations possible!\n", i);
    }
}

/*Lista as viagens de cidades com mais de 50k population para cidades com menos de 30k population*/
void AllCities50kto30k(Cities** hash, WorldCities* worldCities){

    CitiesEdges* neighbours;
    int i = 0, check = 0;
    printf("Checking for all trips possible...\n\t");

    for(i = 0; i < HASH_SIZE; i++) {
        if(hash[i] != NULL) {
            if (CheckPopulationWithID(worldCities, hash[i]->id) > 50000)
            {
                neighbours = hash[i]->edges;
                while (neighbours)
                {
                    if (CheckPopulationWithID(worldCities, neighbours->id) < 30000)
                    {
                        printf("%s-%s\n      \t", CheckCityWithID(worldCities, hash[i]->id), CheckCityWithID(worldCities, neighbours->id));
                        check++;
                    }
                    neighbours = neighbours->next_edge;
                }
            }
        }
    }
    if (check == 0)
    {
        printf("There were no trips avaiable");
    }
    else
    {
        printf("There is %d trips from cities with at least 50k population to cities under 30k population\t", check);
    }
    
    
}

/*Verifica a cidade com mais destinos*/
void FromWhereCanIGoToMoreCities(Cities** hash, WorldCities* worldCities){
    int i = 0, f = 0, check = 0, arrayIDs[20];
    printf("Checking for the city with more trips possible...\n");
    for (i = 0; i <= 20; i++) arrayIDs[i] = 0;
    for (i = 0; i < HASH_SIZE; i++) {
        if(hash[i] != NULL) {
            while(hash[i]->edges){
                hash[i]->edgeCounter++;
                hash[i]->edges = hash[i]->edges->next_edge;               
            }     
        }
    }
    for (i = 0; i < HASH_SIZE; i++)
    {
        if (hash[i] != NULL)
        {
            if (hash[i]->edgeCounter >= check)
            {
                for (f = 0; f <= 20; f++)
                {
                    if (arrayIDs[f] == 0)
                    {
                        arrayIDs[f] = hash[i]->id;
                        check = hash[i]->edgeCounter;
                        break;
                    }
                    
                }
            }            
        }        
    }
    for (i = 0; i <= 20; i++)
    {
        if (arrayIDs[i] != 0)
        {
            printf("%d %s\n", arrayIDs[i], CheckCityWithID(worldCities, arrayIDs[i]));
        }
    }
    printf("is(are) the city(ies) with more destinations");
}

/*Escreve os ID's da lista passada como argumento ao contrário*/
void ReverseListValues(AuxRecord* lst, WorldCities* worldCities){
    AuxRecord* aux = lst;
    if (aux != NULL)
    {
        ReverseListValues(aux->next_rec, worldCities);
        printf("-> %d - %s", aux->id, CheckCityWithID(worldCities, aux->id));
    }    
}

/*Soma os costs da lista toda*/
double PathCost(AuxRecord* lst){
    AuxRecord* aux = lst;
    double cost = 0;
    while (aux)
    {
        cost += aux->cost;
        aux = aux->next_rec;
    }
    return cost;
}

int main()
{
    Cities** hash = HashNew(); /*Create hash, initializes the variables*/
    WorldCities* worldCities = NULL; 
    int origin, target, condition = -1, idChoose;
    double cost;
    char cityChoose[50];
    AuxRecord* path;

    while (condition != 0)
    {
        FILE *fh  = fopen("cidadesPT.txt", "r"); /*Open for read only*/
        if (!fh) { printf("Can't open file!\n"); exit(1); } 
        readcidades(fh, hash);
        fclose(fh);

        fh  = fopen("worldcities.csv", "r"); /*Open for read only*/
        if (!fh) { printf("Can't open file!\n"); exit(1); } 
        worldCities = read(fh, worldCities);
        fclose(fh);

        printf("\n\nEscreva '1' para verificar se existem cidades com o mesmo nome\n");
        printf("Escreva '2' para verificar os destinos de uma cidade\n");
        printf("Escreva '3' para ver todas as viagens de cidades com mais de 50k de populacao para cidades com menos de 30k\n");
        printf("Escreva '4' para ver a cidade com mais destinos\n");
        printf("Escreva '5' para verificar o menor caminho entre duas cidades\n");
        printf("Escreva '0' para sair do programa\n");
        scanf("%d", &condition);
        
        switch (condition)
        {
        case 1:
            printf("\nCity: ");
            scanf("%s", cityChoose);
            CheckMultipleCities(worldCities, cityChoose);
            break;
        case 2:
            printf("\nCity ID: ");
            scanf("%d", &idChoose);
            WhereCanIGo(hash, worldCities, idChoose);
            break;
        case 3:
            AllCities50kto30k(hash, worldCities);
            break;
        case 4:
            FromWhereCanIGoToMoreCities(hash, worldCities);
            break;
        case 5:
            printf("\nOrigin CityID: ");
            scanf("%d", &origin);
            printf("\nDestination CityID: ");
            scanf("%d", &target);

            path = PathFind(hash, origin, target);
            puts("");
            cost = PathCost(path);
            ReverseListValues(path, worldCities);
            printf("\nDistancia/Custo da viagem: %.2lf\n", cost);
            break;
        default:
            break;
        }
    }
    return 0;
}