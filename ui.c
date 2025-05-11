#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_screen() {
#ifdef _WIN32
    system("cls"); // Windows command
#else
    system("clear"); // Linux this time
#endif
}


void press_enter_to_continue() {
    printf("Press Enter to continue...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

int display_main_menu() {
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
            choice = -1;
        }
    } else {
        choice = -1;
    }
    return choice;
}
// Displays detailed information for all loaded characters.
void display_all_characters_detailed( Character all_chars[], int num_total_chars) {
    clear_screen();
    printf("--- All Available Characters ---\n");
    int count = 0;
    for (int i = 0; i < num_total_chars; ++i) {
        // Only display characters that have a name (i.e., are loaded)
        if (strlen(all_chars[i].name) > 0) {
            count++;
            printf("\n------------------------------\n");
            printf("Name: %s\n", all_chars[i].name);
            printf("MaxHP: %d, Attack: %d, Defense: %d, Agility: %d, Speed: %d\n",
                   all_chars[i].maxhp, all_chars[i].attack, all_chars[i].defense,
                   all_chars[i].agility, all_chars[i].speed);

            // Display Technique 1 details if it exists
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

            // Display Technique 2 details if it exists
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
    if (count == 0) {
        printf("No characters found or loaded.\n");
    }
    printf("\n------------------------------\n");
    press_enter_to_continue();
}

// Prints a text-based health bar.
void print_health_bar(int current_hp, int max_hp, int bar_width) {
    // Basic validation for HP values
    if (max_hp <= 0) max_hp = 1;
    if (current_hp < 0) current_hp = 0;
    if (current_hp > max_hp) current_hp = max_hp;

    // Calculate how many segments of the bar should be filled
    int filled_width = (int)(((float)current_hp / max_hp) * bar_width);
    if (filled_width < 0) filled_width = 0; // Ensure non-negative
    if (filled_width > bar_width) filled_width = bar_width; // Cap at bar_width

    printf("[");
    for (int i = 0; i < bar_width; ++i) {
        if (i < filled_width) {
            printf("#"); // Filled
        } else {
            printf(" "); // Empty
        }
    }
    printf("] %d/%d HP", current_hp, max_hp);
}

// Displays the current state of the combat, including both teams and the active character.
void display_combat_state(Team* team1, Team* team2, Character* current_combatant) {
    clear_screen();
    printf("=================================================================\n");
    printf("                        CY-FIGHTERS COMBAT                       \n");
    printf("=================================================================\n\n");

    printf("--- Player 1 (Team 1) ---\n");
    for (int i = 0; i < team1->current_size; ++i) {
        // Indicate the current combatant if they are from team1 and alive
        printf("%c %-15s ", (current_combatant == &team1->members[i] && team1->members[i].hp > 0) ? '>' : ' ', team1->members[i].name);
        print_health_bar(team1->members[i].hp, team1->members[i].maxhp, 20);
        if (current_combatant == &team1->members[i] && team1->members[i].hp > 0) {
            printf(" << CURRENT TURN");
        }
        printf("\n");
    }

    printf("\n-------------------------- VS --------------------------\n\n");

    printf("--- Player 2 (Team 2) ---\n");
    for (int i = 0; i < team2->current_size; ++i) {
        // Indicate the current combatant if they are from team2 and alive
        printf("%c %-15s ", (current_combatant == &team2->members[i] && team2->members[i].hp > 0) ? '>' : ' ', team2->members[i].name);
        print_health_bar(team2->members[i].hp, team2->members[i].maxhp, 20);
        if (current_combatant == &team2->members[i] && team2->members[i].hp > 0) {
            printf(" << CURRENT TURN");
        }
        printf("\n");
    }
    printf("=================================================================\n");

    // Display whose turn it is
    if (current_combatant && current_combatant->hp > 0) {
        const char* player_string = "";
        // Determine if the current combatant is Player 1 or Player 2 based on their team property
        if (comparestring(current_combatant->team, "red", 3)) { 
            player_string = "Player 1";
        } else if (comparestring(current_combatant->team, "blue", 4)) { 
            player_string = "Player 2";
        }
        printf("\nIt's %s's turn (%s).\n", current_combatant->name, player_string);
    }
}

// Displays the actions available to the current combatant.
void display_character_actions(const Character* combatant, const char* player_identifier_string) {
    if (!combatant ) return; // Do nothing if no combatant

    printf("\n--- %s's Turn (%s) ---\n", combatant->name, player_identifier_string);
    printf("HP: %d/%d\n", combatant->hp, combatant->maxhp);
    printf("Actions:\n");
    printf("1. Basic Attack\n");
    // Display Technique 1 if available
    if (strlen(combatant->technique1[0].name) > 0) {
        printf("2. %s (CD: %d)\n", combatant->technique1[0].name, combatant->technique1[0].oncooldown);
    } else {
        printf("2. (No Technique 1)\n");
    }
    // Display Technique 2 if available
    if (strlen(combatant->technique2[0].name) > 0) {
        printf("3. %s (CD: %d)\n", combatant->technique2[0].name, combatant->technique2[0].oncooldown);
    } else {
        printf("3. (No Technique 2)\n");
    }
    printf("5. Forfeit Turn / Do Nothing\n");
    printf("%s (%s), choose action: ", player_identifier_string, combatant->name);
}