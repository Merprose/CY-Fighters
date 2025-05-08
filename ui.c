// ui.c
#include "ui.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

void clear_screen() {
    system("clear"); // To clear Windows when user enter prompt to start the game
}

void press_enter_to_continue() {
    printf("\nPress Enter to continue...");
    getchar(); // GetChar Check for input before Main Menu
}

int display_main_menu() { // The main Menu
    clear_screen();
    printf("=========================\n");
    printf("     CY-FIGHTERS RPG     \n");
    printf("=========================\n");
    printf("1. Start New Game (PvP)\n");
    printf("2. View All Characters\n");
    printf("3. Exit\n");
    printf("=========================\n");
    printf("Enter your choice: ");

    int choice = 0;
    char buffer[10];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%d", &choice) != 1) {
            choice = -1; // Invalid input
        }
    } else {
        choice = -1; // Error reading input
    }
    return choice;
}

void display_all_characters_detailed(const Character all_chars[], int num_total_chars) {
    clear_screen();
    printf("--- All Available Characters ---\n");
    for (int i = 0; i < num_total_chars; ++i) {
        if (strlen(all_chars[i].name) > 0) { // Check if character data is loaded
            printf("\n------------------------------\n");
            printf("Name: %s\n", all_chars[i].name);
            printf("MaxHP: %d, Attack: %d, Defense: %d, Agility: %d, Speed: %d\n",
                   all_chars[i].maxhp, all_chars[i].attack, all_chars[i].defense,
                   all_chars[i].agility, all_chars[i].speed);

            if (strlen(all_chars[i].technique1[0].name) > 0) {
                printf("Technique 1: %s\n", all_chars[i].technique1[0].name);
                printf("  Type: %s, Target: %s, Value: %d, Duration: %d, Cooldown: %d\n",
                       all_chars[i].technique1[0].type, all_chars[i].technique1[0].target,
                       all_chars[i].technique1[0].value, all_chars[i].technique1[0].duration,
                       all_chars[i].technique1[0].cooldown);
                printf("  Desc: %s\n", all_chars[i].technique1[0].description);
            } else {
                printf("Technique 1: None\n");
            }

            if (strlen(all_chars[i].technique2[0].name) > 0) {
                printf("Technique 2: %s\n", all_chars[i].technique2[0].name);
                printf("  Type: %s, Target: %s, Value: %d, Duration: %d, Cooldown: %d\n",
                       all_chars[i].technique2[0].type, all_chars[i].technique2[0].target,
                       all_chars[i].technique2[0].value, all_chars[i].technique2[0].duration,
                       all_chars[i].technique2[0].cooldown);
                printf("  Desc: %s\n", all_chars[i].technique2[0].description);
            } else {
                printf("Technique 2: None\n");
            }
        }
    }
    printf("\n------------------------------\n");
    press_enter_to_continue();
}

void print_health_bar(int current_hp, int max_hp, int bar_width) { //Unfinished
    if (max_hp <= 0) max_hp = 1; // Avoid division by zero
    if (current_hp < 0) current_hp = 0;
    printf("[");
    for (int i = 0; i < bar_width; ++i) {
        if (i < filled_width) {
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("] %d/%d HP", current_hp, max_hp);
}

void display_character_actions(const Character* combatant) { //Unfinished
    if (!combatant || combatant->is_ko) return;

    printf("\n--- %s's Turn (Player %s) ---\n", combatant->name, "?"); // Placeholder for player num
    printf("Actions:\n");
    printf("1. Basic Attack\n");
    printf("4. Switch Character (Not implemented yet)\n");
    printf("5. Forfeit Turn / Do Nothing\n");
    printf("Choose action: ");
}

// Missing: display_combat_state, display_character_actions, 