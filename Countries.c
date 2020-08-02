/*
 * Countries.c
 *
 *  Created on: Nov 14, 2018
 *      Author: ise
 */
#include "Countries.h"

/**************************************************************************************
 ******************************STRUCTS DEFENITIONS*************************************
 **************************************************************************************/

struct City {
	char* CityName;
	char* FamiliarFood;
	int PopulationNumber;
};

struct GeographicArea {
	int x1, y1;
	int x2, y2;
};

struct Country {
	char* CountryName;
	GeographicArea GeoArea;
	City* cities;
	int numOfCities;
};



/***************************************************************************************
 *******************************FUNCTIONS IMPLEMENTATION********************************
 **************************************************************************************/

/*add country by setting its name and geographic area and return pointer to new object*/
Country addCountry(char* countryName, int x1, int y1, int x2, int y2){

	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || countryName == NULL){
		return NULL;
	}

	Country countryToAdd = (Country)malloc(sizeof(struct Country));
	if (countryToAdd == NULL){
		return NULL;
	}

	countryToAdd->CountryName = (char*)malloc(sizeof(char)*(strlen(countryName) + 1));
	if (countryToAdd->CountryName == NULL){
		return NULL;
	}

	countryToAdd->GeoArea = (GeographicArea)malloc(sizeof(struct GeographicArea));
	if (countryToAdd->GeoArea == NULL){
		return NULL;

	}

	strcpy(countryToAdd->CountryName, countryName);
	countryToAdd->GeoArea->x1 = x1;
	countryToAdd->GeoArea->y1 = y1;
	countryToAdd->GeoArea->x2 = x2;
	countryToAdd->GeoArea->y2 = y2;
	countryToAdd->numOfCities = 0;
	countryToAdd->cities = NULL;
	return countryToAdd;
}


/*add city to given country and return true, if the operation didn't succeed return false*/
status addCity (Country CountryToAdd, char* CityName, char* FamiliarFood, int PopulationNum){

	if (CityName == NULL || FamiliarFood == NULL || PopulationNum < 0) {
		return failure;
	}

	int index = CountryToAdd->numOfCities;

	CountryToAdd->cities = (City*)realloc(CountryToAdd->cities, (CountryToAdd->numOfCities + 1)*sizeof(City));
	if (CountryToAdd->cities == NULL) //memory allocation failed
		return failure;

	CountryToAdd->cities[index] = (City)malloc(sizeof(struct City));
	if (CountryToAdd->cities[index] == NULL) //memory allocation failed
		return failure;

	CountryToAdd->cities[index]->CityName = (char*)malloc(sizeof(char)*(strlen(CityName) + 1));
	if (CountryToAdd->cities[index]->CityName == NULL) //memory allocation failed
		return failure;

	CountryToAdd->cities[index]->FamiliarFood = (char*)malloc(sizeof(char)*(strlen(FamiliarFood) + 1));
	if (CountryToAdd->cities[index]->FamiliarFood == NULL) //memory allocation failed
		return failure;


	strcpy(CountryToAdd->cities[index]->CityName, CityName);
	strcpy(CountryToAdd->cities[index]->FamiliarFood, FamiliarFood);
	CountryToAdd->cities[index]->PopulationNumber = PopulationNum;
	CountryToAdd->numOfCities++;
	return success;

}


/*remove given city from given country and return true, if the city wasn't found return false*/
status removeCity(Country CountryToRemoveCityFrom, char* CityToRemove){

	int index = CountryToRemoveCityFrom->numOfCities;
	for (int i = 0; i < index; i++){
		if (strcmp(CountryToRemoveCityFrom->cities[i]->CityName, CityToRemove) == 0){
			free(CountryToRemoveCityFrom->cities[i]->FamiliarFood);
			CountryToRemoveCityFrom->cities[i]->FamiliarFood = NULL;
			free(CountryToRemoveCityFrom->cities[i]->CityName);
			CountryToRemoveCityFrom->cities[i]->CityName = NULL;
			free(CountryToRemoveCityFrom->cities[i]);
			CountryToRemoveCityFrom->cities[i] = CountryToRemoveCityFrom->cities[index-1];
			CountryToRemoveCityFrom->cities[index-1] = NULL;
			CountryToRemoveCityFrom->numOfCities--;
			return success;
		}
	}
	return failure;
}


/*check if given coordinate is in given country geographic area and return true or false accordingly*/
bool isCoordinateInCountry (Country CountryToSearchIn, int x, int y){

	if (CountryToSearchIn == NULL || x < 0 || y < 0) {
		return false;
	}

	if (x >= CountryToSearchIn->GeoArea->x1 &&
		x <= CountryToSearchIn->GeoArea->x2 &&
		y <= CountryToSearchIn->GeoArea->y1 &&
		y >= CountryToSearchIn->GeoArea->y2)
			return true;

	return false;
}


/*free memory of given country*/
void freeAllocatedMemoryOfCountry(Country CountryToRelease){
	for (int i = 0; i < CountryToRelease->numOfCities; i++) {
		free(CountryToRelease->cities[i]->FamiliarFood);
		CountryToRelease->cities[i]->FamiliarFood = NULL;
		free(CountryToRelease->cities[i]->CityName);
		CountryToRelease->cities[i]->CityName = NULL;
		free(CountryToRelease->cities[i]);
		CountryToRelease->cities[i] = NULL;
	}
	free (CountryToRelease->cities);
	CountryToRelease->cities = NULL;
	free(CountryToRelease->GeoArea);
	CountryToRelease->GeoArea = NULL;
	free(CountryToRelease->CountryName);
	CountryToRelease->CountryName = NULL;
}


/*deep copy of country object*/
Country deepCopyOfCountryObject(Country countryToCpy){

	Country cpy = (Country)addCountry(countryToCpy->CountryName, countryToCpy->GeoArea->x1,
			countryToCpy->GeoArea->y1, countryToCpy->GeoArea->x2, countryToCpy->GeoArea->y2);

	if (cpy == NULL){
		return NULL;
	}

	for (int i = 0; i < countryToCpy->numOfCities; i++) {
		cpy->cities[i] = (City)addCity(countryToCpy, countryToCpy->cities[i]->CityName, countryToCpy->cities[i]->FamiliarFood, countryToCpy->cities[i]->PopulationNumber);
		if (cpy->cities[i] == NULL) {
			return NULL;
		}
	}

	return cpy;
}


/*print country details*/
status printCountry (Country countryToPrint){
	int status = printf("Country %s coordinates:<%d,%d> , <%d,%d> \n",
			countryToPrint->CountryName,
			countryToPrint->GeoArea->x1, countryToPrint->GeoArea->y1,
			countryToPrint->GeoArea->x2, countryToPrint->GeoArea->y2);
	if (status < 0)
		return failure;

	if (countryToPrint->cities != NULL){
		City* cityPrint = countryToPrint->cities;
		int index = countryToPrint->numOfCities;
		for (int i = 0; i < index; i++){
			status = printf("\t%s includes %d residents and their favorite food is %s\n", cityPrint[i]->CityName,
					cityPrint[i]->PopulationNumber, cityPrint[i]->FamiliarFood);
			if (status < 0)
				return failure;
		}
	}
	return success;
}

/*check whether city is in given country*/
bool searchCity(Country CountryToSearchIn, char* cityName){
	City* CityToAdd = CountryToSearchIn->cities;
	int CitiesNum = CountryToSearchIn->numOfCities;
	for (int j = 0; j < CitiesNum; j++){
		if (strcmp(getCityName(CityToAdd[j]), cityName) == 0){
			return true;
		}
	}
	return false;
}

/* free memory of countries list */
void freeAllocatedMemoryOfCountryList(Country* countryList, int numOfCountriesToFree) {
	for (int i = 0; i < numOfCountriesToFree; i++){
		freeAllocatedMemoryOfCountry(countryList[i]);
		free(countryList[i]);
		countryList[i] = NULL;
	}
}

/******************GETTERS******************/
char* getCountryName(Country countryToGetName){
	return countryToGetName->CountryName;
}
char* getCityName(City cityToGetName){
	return cityToGetName->CityName;
}



