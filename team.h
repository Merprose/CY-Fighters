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


void display_available_characters( Character all_chars[], int num_total_chars);
void select_team_members(Team *team,  Character all_chars[], int num_total_chars,  char* team_name);
void display_team( Team *team,  char* team_name);

#endif // TEAM_H
