#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif
#ifndef STDLIB
    #define STDLIB
    #include <stdlib.h>
#endif

#define FILENAME "character.txt"

typedef struct character
{
    char name[50];
    int maxhp;
    int attack;
    int defense;
    int agility;
    int speed;
    char technique1[50];
    char technique2[50];
} Character;

int comparestring(char a[], char b[], int size){
    for (int l = 0; l<size;l++){
        if (a[l] != b[l] ){
            return 0;
        }
    }
    return 1;
}

void clearchararray(char array[],int size){
    for (int i=0;i<size;i++){
        array[i] = '\0';
    }
}


int setattribute(char phrase[],int size,Character* pchar){
    char start[4];
    Character actualchar = *(pchar);
    int doublepoint = 0;
    char after[50];
    clearchararray(start,4);
    clearchararray(after,50);
    int count = 0;
    for (int i = 0; i<3;i++){
        start[i] = phrase[i];
    }
    
    while (phrase[count] != '\0' && phrase[count] != '\n'){
        if (phrase[count] == ':'){
            doublepoint = count+1;
        }
        if (doublepoint != 0){
            after[count-doublepoint] = phrase[count];
        }
        count++;
        //printf("%c", phrase[count]);
    }
    start[3] = '\0';
    if (comparestring("Nom",start,3)){
        int pos = 0;
        while(after[pos] != '\0' && after[pos] != '\n'){
            (*pchar).name[pos] = after[pos];
            pos++;
        }
    }
    else if (comparestring("Max",start,3)){
        (*pchar).maxhp = atoi(after);
    }
    else if (comparestring("Atk",start,3)){
        (*pchar).attack = atoi(after);
    }
    else if (comparestring("Def",start,3)){
        (*pchar).defense = atoi(after);
    }
    else if (comparestring("Agl",start,3)){
        (*pchar).agility = atoi(after);
    }
    else if (comparestring("Spd",start,3)){
        (*pchar).speed = atoi(after);
    }
    else if (comparestring("Tec",start,3)){
        for (int i = 0; i<50;i++){
            (*pchar).technique1[i] = after[i];
        }
    }
    else if (comparestring("tec",start,3)){
        for (int i = 0; i<50;i++){
            (*pchar).technique2[i] = after[i];
        }
    }
     else if (comparestring("End",start,3)){
        clearchararray(start,4);
        clearchararray(after,50);
        return 55;}
    //printf("str: %s\n",start);
    clearchararray(phrase,50);
}

void getcharacters(Character* endtab){ 
    FILE* file = NULL;
    file = fopen(FILENAME,"r");
    int actualpos = 0;
    int result = 0;
    int size = 90;
    char phrase[100];
    int restart = 1;
    Character actualchar;
    Character* pchar = &actualchar;
    fgets(phrase,100,file);
    while (comparestring("EOF",phrase,3) != 1){
        //printf("phrase: %s",phrase);
        result = setattribute(phrase, size, pchar);
        if (result == 55){
            endtab[actualpos] = actualchar;
            restart = 1;
            actualpos++;
            clearchararray((*pchar).name,50);
            clearchararray((*pchar).technique1,50);
            clearchararray((*pchar).technique2,50);

            //printf("%s\n",actualchar.name);
            //printf("%d\n",actualchar.maxhp);
        }
        clearchararray(phrase,100);
        printf("%s",phrase);
        fgets(phrase,100,file);
    }
}
