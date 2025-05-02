#include "character.h"

int main(){
    Character chars[100];
    getcharacters(chars);
    for(int i=0;i<100;i++){
        if (chars[i].name != NULL){
            printf("%s\n",chars[i].name);
        }
    }
    return 0;
}
