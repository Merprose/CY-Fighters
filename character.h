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


int setattribute(char phrase[],int size,Character actualchar){
    char start[3];
    int doublepoint = 0;
    char after[50];
    for(int i =0;i<size;i++){
        printf("%d",i);
      // printf("%c",phrase[i]);
        if (i<3){
            
            start[i] = phrase[i];
        }
        if (phrase[i] == ':'){
            doublepoint = i;
        }
        if (doublepoint != 0){
            after[i-doublepoint] = phrase[i];
        }
    }
    printf("m");
   printf("%s",start);
    if (comparestring("Nom",phrase,3)){
        for (int i = 0; i<50;i++){
            actualchar.name[i] = after[i];
        }
    }
    else if (comparestring("Max",phrase,3)){
        actualchar.maxhp = atoi(after);
    }
    else if (comparestring("Atk",phrase,3)){
        actualchar.attack = atoi(after);
    }
    else if (comparestring("Def",phrase,3)){
        actualchar.defense = atoi(after);
    }
    else if (comparestring("Agl",phrase,3)){
        actualchar.agility = atoi(after);
    }
    else if (comparestring("Spd",phrase,3)){
        actualchar.speed = atoi(after);
    }
    else if (comparestring("Tec",phrase,3)){
        for (int i = 0; i<50;i++){
            actualchar.technique1[i] = after[i];
        }
    }
    else if (comparestring("tec",phrase,3)){
        for (int i = 0; i<50;i++){
            actualchar.technique2[i] = after[i];
        }
    }
     else if (comparestring("End",phrase,3)){
        return 55;}
    printf("hm");
}

void getcharacters(Character* endtab){ 
    FILE* file = NULL;
    file = fopen(FILENAME,"r");
    int a = fgetc(file);
    int actualpos = 0;
    int result = 0;
    int size = 3;
    while (a != EOF){
        Character actualchar;
        char phrase[200];
        while (result != 55){
            int count = 0;
            while (a != 10)
            {
                phrase[count] = a; 
                count++;
                printf("%c",a);
                a = fgetc(file);
            }
            a = fgetc(file);
            result = setattribute(phrase,size,actualchar);
            endtab[actualpos] = actualchar;
            printf("%s",phrase);
            for (int j = 0;j<200;j++){
                phrase[j] = '\0';
            }
        }
    }
}
