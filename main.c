#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>   
#include <string.h> 

#include "character.h"     
#include "team.h"          
#include "ui.h"            
#include "combat.h"

#define NAME_LENGTH 50 

void start_pvp_game_logic(Character all_available_characters[], int num_total_chars, Team* p1_team, Team* p2_team) {
    printf("Starting PvP Game...\n");
    
    if (num_total_chars < 1) {
        printf("Not enough characters loaded to start a game.\n");
        press_enter_to_continue();
        return;
    }

    int selection_size_p1 = MAX_TEAM_SIZE;
    if (num_total_chars < MAX_TEAM_SIZE) {
        selection_size_p1 = num_total_chars;
    }
    
    int selection_size_p2 = MAX_TEAM_SIZE;
    if (num_total_chars < MAX_TEAM_SIZE) {
        selection_size_p2 = num_total_chars;
    }

    printf("Player 1, create your team.\n");
    select_team_members(p1_team, all_available_characters, num_total_chars, "Player 1", selection_size_p1);
    display_team(p1_team, "Player 1's Team");

    printf("\nPlayer 2, create your team.\n");
    select_team_members(p2_team, all_available_characters, num_total_chars, "Player 2", selection_size_p2);
    display_team(p2_team, "Player 2's Team");
    
    if(p1_team->current_size > 0 && p2_team->current_size > 0) {
        int combat_size_per_team = p1_team->current_size;
        if (p2_team->current_size < combat_size_per_team) {
            combat_size_per_team = p2_team->current_size;
        }
        if (combat_size_per_team > MAX_TEAM_SIZE) {
             combat_size_per_team = MAX_TEAM_SIZE;
        }


        if(combat_size_per_team > 0) {
           combatInit(p1_team, p2_team, "PlayerVsPlayer"); 
        } else {
            printf("\nCannot start combat: teams are effectively empty for battle after selection.\n");
        }
    } else {
        printf("\nNot enough characters selected on one or both teams to start combat.\n");
    }
    press_enter_to_continue();
}


int main() {
    srand(time(NULL)); 

    Character all_available_characters[MAX_CHARACTERS]; 
    
    for(int i=0; i<MAX_CHARACTERS; i++) {
        clearchararray(all_available_characters[i].name, NAME_LENGTH); 
        all_available_characters[i].maxhp = 0; 
        all_available_characters[i].hp = 0;
        all_available_characters[i].attack = 0;
        all_available_characters[i].defense = 0;
        all_available_characters[i].agility = 0;
        all_available_characters[i].speed = 0;
        for(int j=0; j<EFFECTCOUNT; ++j) {
            clearchararray(all_available_characters[i].effects[j].name, NAME_LENGTH);
            all_available_characters[i].effects[j].value = 0;
            all_available_characters[i].effects[j].duration = 0;
        }
        memset(&all_available_characters[i].technique1[0], 0, sizeof(Technique)); 
        memset(&all_available_characters[i].technique2[0], 0, sizeof(Technique)); 
    }
    
    getcharacters(all_available_characters); 

    printf("Characters loaded.\n");
    int num_loaded_chars = 0;
    for(int i=0; i<MAX_CHARACTERS; ++i) {
        if(strlen(all_available_characters[i].name) > 0) {
            num_loaded_chars++;
        }
    }
    printf("%d characters are available.\n", num_loaded_chars);
    if (num_loaded_chars == 0) {
        printf("Warning: No characters were loaded from file.\n");
    }

    Team player1_team, player2_team; 

    int choice; 
    do {
        choice = display_main_menu();
        switch (choice) {
            case 1:
                memset(&player1_team, 0, sizeof(Team)); 
                memset(&player2_team, 0, sizeof(Team));
                start_pvp_game_logic(all_available_characters, num_loaded_chars, &player1_team, &player2_team);
                break;
            case 2:
                display_all_characters_detailed(all_available_characters, num_loaded_chars);
                break;
            case 3:
                printf("Exiting CY-Fighters. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please choose another number.\n");
                press_enter_to_continue();
                break;
        }
    } while (choice != 3);

    return 0;
}
