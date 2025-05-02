#include "character.h"
#define CHARCOUNT 8

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

void assignstats(char tab1[],char tab2[]){ // cette fonction utilise les virgules pour
//trouver quel est la proprieté actuelle
    int count = 0;
    int canfound = 0;
    int found;
    char sec[200]
   while(tab1[count] != '\n'){
       while(found <= canfound){
           if (found == canfound){
            sec[count] = tab1[count]   
           }
           if (tab1[count] == ','){
               found++;
           }
       }
       switch (found){
           int j=0;
           case 1:
            while(sec[j])
            break;
       }
       canfound++;
       count++;
   } 
}

int setattribute(char phrase[],Character* pchar){
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
            (*pchar->technique1).name[i] = after[i];
        }
    }
    else if (comparestring("tec",start,3)){
        for (int i = 0; i<50;i++){
            (*pchar->technique2).name[i] = after[i];
        }
    }
     else if (comparestring("End",start,3)){
        clearchararray(start,4);
        clearchararray(after,50);
        return 55;}
    //printf("str: %s\n",start);
    clearchararray(phrase,50);
}

void gogotechniques(Character* pchar){
    char name1[50]; 
    char name2[50];
    char start[30];
    char phrase[200];
    char sec[200];
    int onefound = 0;
    int twofound = 0;
    int i = 0;
    int stat = 1;
    fgets(phrase,200,ULTSFILE);
    while(comparestring(phrase,"End",3) == 0){
        while(phrase[i] != '\0' && phrase[i] != ','&& phrase[i] != '\n'){
            sec[i] = phrase[i];
            i++;
        }
        if (onefound == 0 && comparestring(phrase,*pchar->technique1).name) == 1){
            
        }
        else if (twofound == 0 && comparestring(phrase,*pchar->technique2).name) == 1){
        
        }
        fgets(phrase,200,ULTSFILE);
    }
    
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
        result = setattribute(phrase, pchar);
        if (result == 55){
            endtab[actualpos] = actualchar;
            restart = 1;
            actualpos++;
            clearchararray((*pchar).name,50);
            clearchararray((*pchar->technique1).name,50);
            clearchararray((*pchar->technique1).name,50);

            //printf("%s\n",actualchar.name);
            //printf("%d\n",actualchar.maxhp);
        }
        clearchararray(phrase,100);
        printf("%s",phrase);
        fgets(phrase,100,file);
    }
}

int main() {
	Character chars[CHARCOUNT];
	getcharacters(chars);
	for(int i=0; i<CHARCOUNT; i++) {
		if (chars[i].name != NULL) {
			printf("Nom: %s \n",chars[i].name);
			printf("Special 1: %s \n",(*chars->technique1).name);
			printf("Special 1: %s \n",(*chars->technique1).name);
			printf("Special 2: %s \n",(*chars->technique2).name);
			printf("Hp: %d \n",chars[i].maxhp);
			printf("Attack: %d \n",chars[i].attack);
			printf("Defense: %d \n",chars[i].defense);
			printf("Speed: %d \n",chars[i].speed);
			printf("Agility: %d \n",chars[i].agility);
		}
	}
	return 0;
}
