#ifndef STDIO
    #define STDIO
    #include <stdio.h>
#endif

#ifndef TEAM_H
#define TEAM_H_DUMMY_FOR_COMBAT_H
#include "team.h"
#undef TEAM_H_DUMMY_FOR_COMBAT_H
#endif


#ifndef COMBAT_H
    #define COMBAT_H
    #include "ui.h" // Added for display_combat_state and display_character_actions

    int getactualspeed(Character chara);
    void getorder(Team* redteam_struct, Team* blueteam_struct, Character** sortorder, int* actual_total_combatants);
    void combatInit(Team* red_team_ptr, Team* blue_team_ptr, const char* ia_mode); 
    void playerturn(Character* current_player_char, Team* friendly_team, Team* enemy_team); 
#endif