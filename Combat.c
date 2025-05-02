
#include "character.h"
#define CHARCOUNT 8

int main(){
    Character chars[CHARCOUNT];
    getcharacters(chars);
    for(int i=0;i<CHARCOUNT;i++){
        if (chars[i].name != NULL){
            printf("Nom: %s \n",chars[i].name);
            printf("Special 1: %s \n",chars[i].technique1);
            printf("Special 2: %s \n",chars[i].technique2);
            printf("Hp: %d \n",chars[i].maxhp);
            printf("Attack: %d \n",chars[i].attack);
            printf("Defense: %d \n",chars[i].defense);
            printf("Speed: %d \n",chars[i].speed);
            printf("Agility: %d \n",chars[i].agility);
        }
    }
    return 0;
}
