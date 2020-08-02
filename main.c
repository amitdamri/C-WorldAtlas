/*
 * main.c
 *
 *  Created on: Nov 15, 2018
 *      Author: ise
 */
/***********************************************************************************
************************************************************************************
********** Authors: Amit Damri ID 312199698 & Dvir Simhon ID 205520141 *************
************************************************************************************
***********************************************************************************/

#include "Countries.h"

Country searchCountry(Country[], int, char*);
Country isCoordinateInCountryList(Country[], int, int, int);
status ReadCountriesFile(FILE*, Country*, int);

int main( int argc, char* argv[] ){

	/******Read file******/
	FILE* Countries = fopen(argv[2], "r");
	int numOfCountries;
	sscanf(argv[1], "%d", &numOfCountries);
	Country CountriesArr[numOfCountries];

	if ( ReadCountriesFile(Countries, CountriesArr, numOfCountries) == failure ){
		printf("no memory available\n");
		return 1;
	}

	int choose = 1;
	char countryName[300];
	char cityName[300];
	Country CountryToCheck;


	/*******************MENU*******************/
	while (choose != 6){
		printf("please choose one of the following numbers:\n");
		printf("1 : print countries\n");
		printf("2 : add city to country\n");
		printf("3 : remove city from country\n");
		printf("4 : find country in area\n");
		printf("5 : print country by name\n");
		printf("6 : exit\n");
		scanf("%d", &choose);
		switch ( choose )
		{
			case 1: /* Print the countries */
				for (int i = 0; i < numOfCountries; i++){
					if ( printCountry(CountriesArr[i]) == failure )
					{
						freeAllocatedMemoryOfCountryList(CountriesArr, numOfCountries);
						return 1;
					}
				}
				break;

			case 2: /* Adds city to given country */
				printf("please enter a country name\n");
				scanf("%s", countryName);
				//search whether country exists
				CountryToCheck =  searchCountry(CountriesArr, numOfCountries, countryName);
				if (CountryToCheck == NULL) {
					printf("country name not exist\n");
				}
				else {
					printf("please enter a city name\n");
					scanf("%s", cityName);
					if (searchCity(CountryToCheck, cityName) == false){
						printf("please enter the city favorite food\n");
						char favoriteFood[300];
						scanf("%s", favoriteFood);
						printf("please enter number of residents in city\n");
						int resNum;
						scanf("%d", &resNum);
						if(addCity(CountryToCheck, cityName, favoriteFood, resNum) == failure){
							freeAllocatedMemoryOfCountryList(CountriesArr, numOfCountries);
							printf("no memory available\n");
							return 1;
						}
					}

					else {
						printf("this city already exist in this country.\n");
					}
				}
				break;

			case 3: /* Removes city from given country */
				printf("please enter a country name\n");
				scanf("%s", countryName);
				CountryToCheck = searchCountry(CountriesArr, numOfCountries, countryName);
				if (CountryToCheck == NULL) {
					printf("country name not exist.\n");
				}
				else {
					printf("please enter a city name\n");
					scanf("%s", cityName);
						if (searchCity(CountryToCheck, cityName) == true){
							if (removeCity(CountryToCheck, cityName) == failure) {
								freeAllocatedMemoryOfCountryList(CountriesArr, numOfCountries);
								return 1;
							}
						}
						else {
							printf("the city not exist in this country\n");
						}
					}
				break;


			case 4: /* Finds a country in area of given coordinations */
				printf("please enter x and y coordinations:x,y\n");
				int x, y;
				char comma;
				scanf("%d %c %d", &x, &comma, &y);
				CountryToCheck = isCoordinateInCountryList(CountriesArr, numOfCountries, x, y);
				if (CountryToCheck != NULL){
					printf("found in: %s\n", getCountryName(CountryToCheck));
				}
				else {
					printf("there is no country in the area\n");
				}
				break;


			case 5: /* Prints all details about the country by giving its name */
				printf("please enter a country name\n");
				scanf("%s", countryName);
				CountryToCheck = searchCountry(CountriesArr, numOfCountries, countryName);
				if (CountryToCheck != NULL){
					if ( printCountry(CountryToCheck) == failure ) {
						freeAllocatedMemoryOfCountryList(CountriesArr, numOfCountries);
						return 1;
					}
				}
				else {
					printf("country name not exist.\n");
				}
				break;


			case 6: /* Exits from program */
				freeAllocatedMemoryOfCountryList(CountriesArr, numOfCountries);
				printf("all the memory cleaned and the program is safely closed");
				return 0;

			default: printf("please choose a valid number\n");
		}
	}
	return 1;
}



/*****************************************************************************************
 ****************************** MAIN FUNCTIONS *******************************************
 *****************************************************************************************/

/* search whether country exists */
Country searchCountry(Country* CountriesArr, int CountriesNumber, char* countryName) {
	for (int i = 0; i < CountriesNumber; i++){
		if (strcmp(getCountryName(CountriesArr[i]), countryName) == 0)
			return CountriesArr[i];
	}
	return NULL;
}


/* search coordinate in country list */
Country isCoordinateInCountryList(Country* CountriesArr, int CountriesNumber, int x, int y) {
	for (int i = 0; i < CountriesNumber; i++){
		if (isCoordinateInCountry(CountriesArr[i], x, y) == true){
			return CountriesArr[i];
		}
	}
	return NULL;
}

/* read Atlas file and import data to array of countries */
status ReadCountriesFile(FILE* Countries, Country* CountriesArr, int numOfCountries) {
int nextCountry = -1;
	int index = 0;
	char line[1000];
	while (fgets(line, 1000, Countries) != NULL){
		if (line[0] != '\t'){
			//it's a country
			nextCountry++;
			index = 0;
			char countryName[300];
			while (line[index] != ',') {
				countryName[index] = line[index];
				index++;
			}
			countryName[index] = '\0';
			index++;

			int X1, X2, Y1, Y2;

			int i = 0;
			char x1[10];
			while (line[index] != ',') {
				x1[i] = line[index];
				i++;
				index++;
			}
			x1[i] = '\0';
			sscanf(x1, "%d", &X1);
			index++;

			i = 0;
			char y1[10];
			while (line[index] != ',') {
				y1[i] = line[index];
				i++;
				index++;
			}
			y1[i] = '\0';
			sscanf(y1, "%d", &Y1);
			index++;

			i = 0;
			char x2[10];
			while (line[index] != ',') {
				x2[i] = line[index];
				i++;
				index++;
			}
			x2[i] = '\0';
			sscanf(x2, "%d", &X2);
			index++;

			i = 0;
			char y2[10];
			while (line[index] != '\n') {
				y2[i] = line[index];
				i++;
				index++;
			}
			y2[i] = '\0';
			sscanf(y2, "%d", &Y2);

			CountriesArr[nextCountry] = addCountry(countryName, X1, Y1, X2, Y2);

			if (CountriesArr[nextCountry] == NULL){
				freeAllocatedMemoryOfCountryList(CountriesArr, numOfCountries);
				return failure;
			}
		}
		else {
			//it's a city
			index = 1; //first char is tab
			int i = 0;
			char cityName[300];
			while (line[index] != ','){
				cityName[i] = line[index];
				index++;
				i++;
			}
			cityName[i] = '\0';
			index++;

			char favoriteFood[300];
			i = 0;
			while (line[index] != ','){
				favoriteFood[i] = line[index];
				index++;
				i++;
			}
			favoriteFood[i] = '\0';

			index++;

			char numOfRes[300];
			i = 0;
			while (line[index] >= '0' && line[index] <= '9'){
				numOfRes[i] = line[index];
				index++;
				i++;
			}
			numOfRes[i] = '\0';
			int PopNum;
			sscanf(numOfRes, "%d", &PopNum);

			if (addCity(CountriesArr[nextCountry], cityName, favoriteFood, PopNum) == failure) {
				freeAllocatedMemoryOfCountryList(CountriesArr, numOfCountries);
				return failure;
			}
		}

	}
	fclose(Countries);
	return success;
}
