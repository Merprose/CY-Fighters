#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif
#ifndef COMBAT_H
    #define COMBAT_H
    int getactualspeed(Character chara);
    void getorder(Character* redteam, Character* blueteam, int size,Character** sortorder );
    void combatInit(Character* redteam, Character* blueteam,char ia[],int size);
#endif
