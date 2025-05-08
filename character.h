#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif
#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif
#ifndef CHARACTER_H 
#define CHARACTER_H

#define FILENAME "character.txt"
#define ULTSFILE "technique.txt"
typedef struct technique
{   
    char name[50];
    char type[30];
    char target[30];
    int value;
    int duration;
    int cooldown;
    char description[200];
    
} Technique;


typedef struct character
{
    char name[50];
    int maxhp;
    int attack;
    int defense;
    int agility;
    int speed;
    Technique technique1[50];
    Technique technique2[50];
} Character;

int comparestring(char a[], char b[], int size);

void clearchararray(char array[],int size);

void tabtotab(char tab1[], char tab2[]);

void assignstats(char tab1[],char tab2[]);

int setattribute(char phrase[],Character* pchar);

void gogotechniques(Character* pchar);

void settechniques(char phrase[],Technique* technique);

void getcharacters(Character* endtab);

#endif
