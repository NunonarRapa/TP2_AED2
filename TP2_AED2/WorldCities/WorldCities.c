#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WorldCities.h"

/*Faz um Head-Insert dos dados na lista*/
WorldCities* HeadInsert(WorldCities *lst, int id, char* city, char* country, int population){
    WorldCities* aux = (WorldCities*)malloc(sizeof(WorldCities));
    aux->city = strdup(city);
    aux->country = strdup(country);
    aux->population = population;
    aux->id = id;
    
    aux->next = lst;
    return aux;
}

/*Retorna o nome do país se tiver o mesmo ID*/
char* CheckCountryWithID(WorldCities *lst, int id){
    WorldCities* aux = lst;
    while (aux)
    {
        if (aux->id == id)
        {
            return aux->country;
        }
        aux = aux->next;
    }
    return "Country not found in worldcities.csv file";
}

/*Retorna o nome da cidade se tiver o mesmo ID*/
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

/*Retorna a populaçao se tiver o mesmo ID*/
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