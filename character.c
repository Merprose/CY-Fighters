#include "character.h"
#include <string.h> 
#include <stdlib.h> 
#include <stdio.h>  

#define TEAM_H_DUMMY_FOR_MAX_CHARACTERS 
#include "team.h" 
#undef TEAM_H_DUMMY_FOR_MAX_CHARACTERS


int comparestring(const char a[], const char b[], int size){
    for (int l = 0; l<size;l++){
    	if (a[l] == b[l] &&  a[l] == '\0'){
        	return 1;
        }
        if((a[l]=='\0' && b[l]=='\n') || (b[l]=='\0' && a[l]=='\n')){
        	return 1;
        }
        if (a[l] != b[l] ){
            return 0;
        }
    }
    return 1;
}

void clearchararray(char array[],int size){
    if (size > 0){
        for (int i=0;i<size;i++){
            array[i] = '\0';
            }
    }
    else {
        int i = 0;
        while (array[i] != '\0' && array[i] != '\n'){ 
            array[i] = '\0';
            i++; 
        }
    }
}

void tabtotab(char tab1[], char tab2[]){
    int i = 0;
    clearchararray(tab2,0); 
    while (tab1[i] != '\0' && tab1[i] != '\n'){
        tab2[i] = tab1[i];
        i++;
    }
    tab2[i] = '\0'; 
}



int setattribute(char phrase[],Character* pchar){
    char start[4];
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
            doublepoint = count;
        }
        if (doublepoint != 0 && (count - doublepoint < 49)){ 
           after[count-doublepoint] = phrase[count+1];  
        }
        count++;
    }
    
    after[count-doublepoint]='\0';
    start[3] = '\0';
  if (comparestring("Nom",start,3)){
        int pos = 0;
        while(after[pos] != '\0' && after[pos] != '\n' && pos < 49){ 
            (*pchar).name[pos] = after[pos];
            pos++;
        }
        (*pchar).name[pos] = '\0'; 
    }
    else if (comparestring("Max",start,3)){
        (*pchar).maxhp = atoi(after);
        (*pchar).hp = atoi(after);
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
        clearchararray((*pchar).technique1[0].name,50); 
        for (int i = 0; i < 49 && after[i] != '\0' && after[i] != '\n'; i++){
            (*pchar).technique1[0].name[i] = after[i];
        }
        (*pchar).technique1[0].name[49] = '\0'; 
    }
    else if (comparestring("tec",start,3)){ 
        clearchararray((*pchar).technique2[0].name,50); 
        for (int i = 0; i < 49 && after[i] != '\0' && after[i] != '\n'; i++){
            (*pchar).technique2[0].name[i] = after[i];
        }
         (*pchar).technique2[0].name[49] = '\0'; 
    }
    else if (comparestring("End",start,3)){
        clearchararray(start,4);
        clearchararray(after,50);
        return 55;
    }

    clearchararray(phrase,50); 
    return 0; 
}

void settechniques(char phrase[],Technique* technique){
    int canfound = 0, found = 0,i = 0,count = 0;
    char sec[200]; 
    clearchararray(sec,200);

    while (phrase[i] != '\n' && phrase[i] != '\0' ){
        if (found == canfound){ 
            count = 0; 
            while(phrase[i] != ',' && phrase[i] != '\n' && phrase[i] != '\0'){
                if(count < 199) { 
                    sec[count] = phrase[i];
                    count++;
                }
                i++;
            }
            sec[count] = '\0'; 

            switch(found){
                case 0: 
                    clearchararray((*technique).name,50);
                    tabtotab(sec,(*technique).name);
                    break;
                case 1:
                    clearchararray((*technique).type,30);
                    tabtotab(sec,(*technique).type);
                    break;
                case 2:
                    clearchararray((*technique).target,30);
                    tabtotab(sec,(*technique).target);
                    break;
                case 3:
                    clearchararray((*technique).effect.name,50); 
                    tabtotab(sec,(*technique).effect.name);
                    break;
                case 4:
                    (*technique).value = atoi(sec);
                    if (comparestring((*technique).effect.name,"NONE",4) == 0 ){ 
                        (*technique).effect.value = atoi(sec); 
                    }
                    else { 
                        (*technique).effect.value = 0;
                    }
                    break;
                case 5:
                    (*technique).duration = atoi(sec);
                    if (comparestring((*technique).effect.name,"NONE",4) == 0 ){ 
                        (*technique).effect.duration = atoi(sec); 
                    }
                    else { 
                         (*technique).effect.duration = 0;
                    }
                    break;
                case 6:
                    (*technique).cooldown = atoi(sec);
                    break;
                case 7:
                    clearchararray((*technique).description,200);
                    tabtotab(sec,(*technique).description);
                    break;
            }
            canfound++;
        }
        if (phrase[i] == ','){
            found++;
        }
        if(phrase[i] != '\0') { 
            i++;
        }
    }
}

void gogotechniques(Character* pchar){
    char phrase[200];
    char sec[200]; 
    int onefound = 0;
    int twofound = 0;
    clearchararray(sec,200);

    FILE* file = fopen(ULTSFILE,"r");
    if (file == NULL){
        printf("Error: Cannot open techniques file: %s\n", ULTSFILE);
        exit(1); 
    }

    fgets(phrase,sizeof(phrase),file); 
    clearchararray(phrase,sizeof(phrase)); 

    while(fgets(phrase,sizeof(phrase),file) != NULL){ 
        if (comparestring(phrase,"End",3) == 1) { 
            break;
        }

        int i = 0;
        int k = 0;
        clearchararray(sec,200);
        while(phrase[i] != '\0' && phrase[i] != ','&& phrase[i] != '\n'){
            if (k < 199) { 
                sec[k] = phrase[i];
                k++;
            }
            i++;
        }
        sec[k] = '\0'; 
     
        if (onefound == 0 && (comparestring(sec,(*pchar).technique1[0].name, strlen(sec)+1))){ 
            onefound = 1;
            settechniques(phrase, &((*pchar).technique1[0])); 
        }
        else if (twofound == 0 && comparestring(sec,(*pchar).technique2[0].name, strlen(sec)+1)){
            twofound = 1;
            settechniques(phrase, &((*pchar).technique2[0])); 
        }
        
        if (onefound && twofound) break; 
        clearchararray(phrase,200); 
    }
    fclose(file);
}

void getcharacters(Character* endtab){ 
    FILE* file = NULL;
    file = fopen(FILENAME,"r");
    if (file == NULL){
        printf("Error: Cannot open characters file: %s\n", FILENAME);
        exit(1); 
    }
    int actualpos = 0;
    int result = 0;
    char phrase[100];
    
    Character actualchar;
    memset(&actualchar, 0, sizeof(Character)); 
    for (int k = 0; k<EFFECTCOUNT; k++){ 
      tabtotab("NONE",actualchar.effects[k].name);
      actualchar.effects[k].value = 0;
      actualchar.effects[k].duration = 0;
    }

    Character* pchar = &actualchar;

    while (fgets(phrase,sizeof(phrase),file) != NULL){
        if (comparestring("EOF",phrase,3) == 1){
            break; 
        }
        result = setattribute(phrase, pchar);
        if (result == 55){ 
            gogotechniques(pchar);
            if(actualpos < MAX_CHARACTERS) { 
                endtab[actualpos] = actualchar; 
                actualpos++;
            } else {
                printf("Warning: Exceeded MAX_CHARACTERS while loading. Some characters may not be loaded.\n");
                break; 
            }
            memset(&actualchar, 0, sizeof(Character));
            for (int k = 0; k<EFFECTCOUNT; k++){
                tabtotab("NONE",actualchar.effects[k].name);
                actualchar.effects[k].value = 0;
                actualchar.effects[k].duration = 0;
            }
        }
        clearchararray(phrase,100); 
   }
   fclose(file);
}