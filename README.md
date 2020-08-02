# C-WorldAtlas
Create world atlas that contains countries, cities and information about them. 
The script gets two parameters - number of countries (the number of countries it should read from the countries file), and configuration file path (contains countries and cities that should be in the system).

## Explanation about the entities in the system:

### Country:
Every country has name, geographical area, number of cities that it contains and list of those cities.

### City:
Every city has name, number of residents and popular food.

### Geographical Area:
Two coordinates - the first coordinate (x1,y1) represents the upper left point, and the second coordinate represents the lower right point.

## Functionalities:
```
please choose one of the following numbers:
1 : print countries
2 : add city to country
3 : remove city from country
4 : find country in area
5 : print country by name
6 : exit
```

print country by name example:
```
Country Israel coordinates: <1,5> , <8,2>
HodHasharon includes 56700 residents and their favorite food is
frozenYogurt.
Berrsheba includes 202495 residents and their favorite food is
hummus.
```
