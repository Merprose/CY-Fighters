#ifndef TEAM_H
#define TEAM_H

#include "character.h" 

#define MAX_TEAM_SIZE 3     
#define MAX_CHARACTERS 20   

typedef struct {
    char team_name[50]
    Character members[MAX_TEAM_SIZE];
    int current_size; 
} Team;


void display_available_characters(const Character all_chars[], int num_total_chars);
void select_team_members(Team *team, const Character all_chars[], int num_total_chars, const char* team_name);
void display_team(const Team *team, const char* team_name);

#endif // TEAM_H
