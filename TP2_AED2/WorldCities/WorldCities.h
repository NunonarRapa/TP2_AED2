#ifndef WCITYEDGES_H_
#define WCITYEDGES_H_

typedef struct WorldCities /*Lista das cidades do mundo*/
{
    char* city;
    char* country;
    int population;
    int id;
    struct WorldCities* next;
}WorldCities;

WorldCities* HeadInsert(WorldCities *lst, int id, char* city, char* country, int population);
char* CheckCountryWithID(WorldCities *lst, int id);
char* CheckCityWithID(WorldCities *lst, int id);
int CheckPopulationWithID(WorldCities *lst, int id);
extern char* strdup(const char*);

#endif