#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>   

#include "character.h"     // For Character struct definition
#include "team.h"          // For Team struct definition 
#include "ui.h"            // For UI functions 
#include "game.h"     

void clear_screen();
void press_enter_to_continue();
int display_main_menu();

int main() {
    srand(time(NULL)); // random number generator

    Character all_available_characters[ACTUAL_CHARCOUNT];
    // Initialize all characters to empty state for memory to not use wrong data that was previously stored in those memory locations
    for(int i=0; i<ACTUAL_CHARCOUNT; i++) {
        clearchararray(all_available_characters[i].name, MAX_NAME_LENGTH);
        all_available_characters[i].maxhp = 0; // etc.
    }
    printf("Characters loaded.\n");

    int choice; //so thats all the different choice input the user do in the main menu
    do {
        choice = display_main_menu();
        switch (choice) {
            case 1:
                start_pvp_game();
                break;
            case 2:
                break;
            case 3:
                printf("Exiting CY-Fighters. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please choose another number.\n");
                press_enter_to_continue();
                break;
        }
