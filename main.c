#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>   // For srand
#include <string.h> // For memset, strlen

#include "character.h"     
#include "team.h"          
#include "ui.h"            
#include "combat.h"

#define NAME_LENGTH 50 // Max length for character/team names, consistent with struct definitions

// Helper function to get team size choice from the user.
int get_team_size_choice() {
    int chosen_size = 0;
    char buffer[10];
    int parsed_choice;

    do {
        printf("\nChoose team size for this match:\n");
        printf("1. Single character (1 vs 1)\n");
        printf("2. Two characters (2 vs 2)\n");
        printf("3. Five characters (5 vs 5 - full team)\n");
        printf("Enter your selection (1, 2, or 3): ");

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &parsed_choice) == 1) {
                switch (parsed_choice) {
                    case 1:
                        chosen_size = 1;
                        break;
                    case 2:
                        chosen_size = 2;
                        break;
                    case 3:
                        chosen_size = 5;
                        break;
                    default:
                        printf("Invalid selection. Please enter 1, 2, or 3.\n");
                        break;
                }
            } else {
                printf("Invalid input. Please enter a number.\n");
            }
        } else {
            // Handle fgets error, perhaps default or re-prompt
            printf("Error reading input. Please try again.\n");
        }
    } while (chosen_size == 0); // Loop until a valid size (1, 2, or 5) is chosen

    return chosen_size;
}

// Manages the game logic for a Player vs Player game.
void start_pvp_game_logic(Character all_available_characters[], int num_total_chars, Team* p1_team, Team* p2_team) {
    printf("Starting PvP Game...\n");
    
    // Check if there are enough characters loaded to play
    if (num_total_chars < 1) {
        printf("Not enough characters loaded to start a game.\n");
        press_enter_to_continue();
        return;
    }

    // Get desired team size from user for the match
    int desired_team_size = get_team_size_choice();
    printf("Team size for this match will be %d character(s) per team.\n", desired_team_size);

    // Determine actual team size, capped by available characters and MAX_TEAM_SIZE
    int actual_selection_size = desired_team_size;
    if (actual_selection_size > num_total_chars) {
        actual_selection_size = num_total_chars;
        printf("Note: Team size capped at %d due to the number of available characters.\n", actual_selection_size);
    }

    if (actual_selection_size < 1 && num_total_chars > 0) { // Should not happen if num_total_chars >=1 and desired_team_size >=1
        printf("Warning: Effective team size is less than 1, defaulting to 1 if characters are available.\n");
        actual_selection_size = 1; // Ensure at least 1 if possible
    }
    if (actual_selection_size > num_total_chars) actual_selection_size = num_total_chars; // Final safety cap


    // Player 1 team selection
    printf("\nPlayer 1, create your team.\n");
    select_team_members(p1_team, all_available_characters, num_total_chars, "Player 1", actual_selection_size);
    display_team(p1_team, "Player 1's Team");

    // Player 2 team selection
    printf("\nPlayer 2, create your team.\n");
    select_team_members(p2_team, all_available_characters, num_total_chars, "Player 2", actual_selection_size);
    display_team(p2_team, "Player 2's Team");
    
    // Start combat if both teams have at least one member (current_size is set by select_team_members)
    if(p1_team->current_size > 0 && p2_team->current_size > 0) {
        combatInit(p1_team, p2_team, "PlayerVsPlayer"); 
    } else {
        printf("\nNot enough characters selected on one or both teams (or no characters available for the chosen size) to start combat.\n");
    }
    press_enter_to_continue();
}


int main() {
    srand(time(NULL)); // Seed the random number generator (used for auto-select, could be for other mechanics)

    Character all_available_characters[MAX_CHARACTERS]; // Array to store all loadable characters
    
    // Initialize the character array to a known state (empty/zeroed)
    for(int i=0; i<MAX_CHARACTERS; i++) {
        clearchararray(all_available_characters[i].name, NAME_LENGTH); 
        all_available_characters[i].maxhp = 0; 
        all_available_characters[i].hp = 0;
        all_available_characters[i].attack = 0;
        all_available_characters[i].defense = 0;
        all_available_characters[i].agility = 0;
        all_available_characters[i].speed = 0;
        for(int j=0; j<EFFECTCOUNT; ++j) { // Initialize effects array
            clearchararray(all_available_characters[i].effects[j].name, NAME_LENGTH); // Assuming NAME_LENGTH for effect names
            all_available_characters[i].effects[j].value = 0;
            all_available_characters[i].effects[j].duration = 0;
        }
        // Zero out technique structures
        memset(&all_available_characters[i].technique1[0], 0, sizeof(Technique)); 
        memset(&all_available_characters[i].technique2[0], 0, sizeof(Technique)); 
    }
    
    getcharacters(all_available_characters); // Load character data from file

    printf("Characters loaded.\n");
    // Count how many characters were actually loaded
    int num_loaded_chars = 0;
    for(int i=0; i<MAX_CHARACTERS; ++i) {
        if(strlen(all_available_characters[i].name) > 0) {
            num_loaded_chars++;
        }
    }
    printf("%d characters are available.\n", num_loaded_chars);
    if (num_loaded_chars == 0) {
        printf("Warning: No characters were loaded from file. The game might not function correctly.\n");
    }

    Team player1_team, player2_team; // Declare team structures

    int choice; 
    // Main game loop
    do {
        choice = display_main_menu(); // Show menu and get user choice
        switch (choice) {
            case 1: // Start New Game (PvP)
                memset(&player1_team, 0, sizeof(Team)); // Clear P1 team for new game
                memset(&player2_team, 0, sizeof(Team)); // Clear P2 team for new game
                start_pvp_game_logic(all_available_characters, num_loaded_chars, &player1_team, &player2_team);
                break;
            case 2: // View All Characters
                display_all_characters_detailed(all_available_characters, num_loaded_chars);
                break;
            case 3: // Exit
                printf("Exiting CY-Fighters. Goodbye!\n");
                break;
            default: // Invalid choice
                printf("Invalid choice. Please choose another number.\n");
                press_enter_to_continue();
                break;
        }
    } while (choice != 3); // Loop until user chooses to exit

    return 0;
}