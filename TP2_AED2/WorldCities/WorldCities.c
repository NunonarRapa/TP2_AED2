#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WorldCities.h"

WorldCities* HeadInsert(WorldCities *lst, int id, char* city, char* country, int population){
    WorldCities* aux = (WorldCities*)malloc(sizeof(WorldCities));
    aux->city = strdup(city);
    aux->country = strdup(country);
    aux->population = population;
    aux->id = id;
    
    aux->next = lst;
    return aux;
}

char* CheckCountryWithID(WorldCities *lst, int id){
    WorldCities* aux = lst;
    while (aux)
    {
        if (aux->id == id)
        {
            return lst->country;
        }
        aux = aux->next;
    }
    return NULL;
}

char* CheckCityWithID(WorldCities *lst, int id){
    WorldCities* aux = lst;
    while (aux)
    {
        if (aux->id == id)
        {
            return aux->city;
        }
        aux = aux->next;
    }
    return "City not found in worldcities.csv file";
}

int CheckPopulationWithID(WorldCities *lst, int id){
    WorldCities* aux = lst;
    while (aux)
    {
        if (aux->id == id)
        {
            return aux->population;
        }
        aux = aux->next;
    }
    return 0;
}