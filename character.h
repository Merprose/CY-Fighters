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
#define EFFECTCOUNT 10

#define FILENAME "character.txt"
#define ULTSFILE "technique.txt"
#define MAX_CHARACTERS 20  

typedef struct effects 
{
    char name[50];
    int value;
    int duration;
} Effects;

typedef struct technique
{   
    char name[50];
    char type[30];
    char target[30];
    int value;
    int duration;
    int cooldown;
    int oncooldown; 
    Effects effect;
    char description[200];
    
} Technique;

typedef struct character
{
    char name[50];
    int maxhp;
    int hp;
    int attack;
    int defense;
    int agility;
    int speed;
    Effects effects[EFFECTCOUNT];
    Technique technique1[1]; 
    Technique technique2[1]; 
    char team[5]; 
} Character;

int comparestring(const char a[], const char b[], int size);

void clearchararray(char array[],int size);

void tabtotab(char tab1[], char tab2[]);


int setattribute(char phrase[],Character* pchar);

void gogotechniques(Character* pchar);

void settechniques(char phrase[],Technique* technique);

void getcharacters(Character* endtab); 

#endif