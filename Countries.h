/*
 * Countries.h
 *
 *  Created on: Nov 14, 2018
 *      Author: ise
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef COUNTRIES_H_
#define COUNTRIES_H_

/*************************************************************************************
 ********************************STRUCTS DEFENITIONS**********************************
 *************************************************************************************/
typedef struct Country* Country;

typedef struct City* City;

typedef struct GeographicArea* GeographicArea;

typedef enum e_bool{
	true,false
}bool ;

typedef enum e_status{
	success, failure
}status ;


/**************************************************************************************
 ********************************FUNCTIONS DECLARATIONS********************************
 **************************************************************************************/

Country addCountry(char*, int, int, int, int);
status addCity (Country, char*, char*, int);
status removeCity(Country, char*);
bool isCoordinateInCountry (Country, int, int);
void freeAllocatedMemoryOfCountry(Country);
Country deepCopyOfCountryObject(Country);
status printCountry (Country);
bool searchCity(Country, char*);
void freeAllocatedMemoryOfCountryList(Country*, int);
char* getCountryName(Country);
char* getCityName(City);
#endif /* COUNTRIES_H_ */
