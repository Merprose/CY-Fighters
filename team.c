#include "team.h"
#include <stdio.h>
#include <string.h>


// function to read a line of input safely and remove newline
int read_line_safe(char *buffer, int size) {
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0'; 
        return 0; 
    }
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
    return 1;
}

void display_available_characters( Character all_chars[], int num_total_chars) {
    printf("\n--- Available Characters (Case-Sensitive Names) ---\n");
    int displayed_count = 0;
    for (int i = 0; i < num_total_chars; ++i) {
        if (strlen(all_chars[i].name) > 0) {
            printf("%d. %s (MaxHP:%d, Attack:%d,Defense:%d,Agility:%d,Speed:%d)\n",displayed_count + 1,
                   all_chars[i].name,
                   all_chars[i].maxhp,
                   all_chars[i].attack,
                   all_chars[i].defense,
                   all_chars[i].agility,
                   all_chars[i].speed);
                   displayed_count++;
        }
    }
    if (displayed_count == 0) {
        printf("No characters available for selection.\n");
    }
    printf("-------------------------------------------------\n");
    }

        

void select_team_members(Team *team, Character all_chars[], int num_total_chars, char* team_name_prompt) {
    team->current_size = 0;
    char input_name[50]; 
    printf("\n--- %s: Select %d Characters ---\n", team_name_prompt, MAX_TEAM_SIZE);
    printf("Note: Character names are case-sensitive.\n");
    display_available_characters(all_chars, num_total_chars);
    for (int i = 0; i < MAX_TEAM_SIZE; ++i) {
                int selected_successfully = 0;
                do {
                        printf("%s, pick character %d of %d (enter name exactly as listed): ", team_name_prompt, team->current_size + 1, MAX_TEAM_SIZE);

                        if (!read_line_safe(input_name, sizeof(input_name))) {
                                printf("Error reading input. Aborting team selection for %s.\n", team_name_prompt);
                                return; // Exit if input fails
                        }

                        if (strlen(input_name) == 0) {
                                printf("No name entered. Please try again.\n");
                                continue;
                        }

                        int found_index = -1;
                        for (int j = 0; j < num_total_chars; ++j) {
                                if (strlen(all_chars[j].name) > 0 && strcmp(all_chars[j].name, input_name) == 0) {
                                found_index = j;
                                break;
                        }
                        }    

                        if (found_index != -1) {
                        // Check if character is already in this team
                                int already_in_team = 0;
                                for (int k = 0; k < team->current_size; ++k) {
                                if (strcmp(team->members[k].name, all_chars[found_index].name) == 0) {
                                       already_in_team = 1;
                                 break;
                                }
                        }

                        if (already_in_team) {
                                printf("'%s' is already in your team. Please pick a different character.\n", all_chars[found_index].name);
                        } else {
                                team->members[team->current_size] = all_chars[found_index]; // Struct copy
                                team->current_size++;
                                printf("'%s' added to %s.\n", all_chars[found_index].name, team_name_prompt);
                                selected_successfully = 1;
                        }
                        } else {
                                printf("Character '%s' not found. Please ensure the name is entered exactly as listed (case-sensitive) and try again.\n", input_name);
                                printf("Available characters are listed above.\n");
                        }
                } while (!selected_successfully && team->current_size < MAX_TEAM_SIZE); 
                if (!selected_successfully && team->current_size < MAX_TEAM_SIZE) {
                        printf("Failed to select a character. Continuing selection if slots remain.\n");
                }
        }
        printf("\n%s formation complete!\n", team_name_prompt);
}

void display_team( Team *team, char* team_name_prompt) {
        if (!team) {
                fprintf(stderr, "Error: Team structure is NULL for display.\n");
                return;
        }
        printf("\n--- %s ---\n", team_name_prompt);
        if (team->current_size == 0) {
                printf("Team is empty.\n");
        } else {
                for (int i = 0; i < team->current_size; ++i) {
                        printf("%d. %s (MaxHP: %d, Attack: %d, Defense: %d, Agility: %d, Speed: %d)\n",
                         i + 1,
                        team->members[i].name,
                        team->members[i].maxhp,    
                        team->members[i].attack,   
                        team->members[i].defense,  
                        team->members[i].agility,  
                        team->members[i].speed     
                );
                if (strlen(team->members[i].technique1[0].name) > 0) {
                        printf("    Technique 1: %s\n", team->members[i].technique1[0].name);
                }
                if (strlen(team->members[i].technique2[0].name) > 0) {
                        printf("    Technique 2: %s\n", team->members[i].technique2[0].name);
                }
                }
        }
        printf("-------------------\n");
}
