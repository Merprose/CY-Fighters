#ifndef TEAM_H
#define TEAM_H

#include "character.h"

#define MAX_TEAM_SIZE 5 // Maximum number of characters a team can hold.

// Structure representing a team of characters in the game.
typedef struct {
    char team_name[50];         // Name of the team.
    int current_size;           // Current number of members in the team.
    Character members[MAX_TEAM_SIZE]; // Array of characters forming the team.
} Team;


// Displays characters available for selection.
void display_available_characters( Character all_chars[], int num_total_chars);
// Handles the process of a player selecting their team members.
void select_team_members(Team *team,  Character all_chars[], int num_total_chars,  char* team_name,int team_size);
// Prints the details of a team to the console.
void display_team( Team *team,  char* team_name);
// Automatically populates a team with characters.
void auto_select_team_members(Team *team, Character all_chars[], int num_total_chars, char* team_name_prompt,int team_size);

#endif