#ifndef TEAM_H
#define TEAM_H

#include "character.h" 

#define MAX_TEAM_SIZE 5
#define MAX_CHARACTERS 20   


typedef struct {
    char team_name[50];
    int current_size; 
    Character members[MAX_TEAM_SIZE];
} Team;


void display_available_characters( Character all_chars[], int num_total_chars);
void select_team_members(Team *team,  Character all_chars[], int num_total_chars,  char* team_name,int team_size);
void display_team( Team *team,  char* team_name);
void auto_select_team_members(Team *team, Character all_chars[], int num_total_chars, char* team_name_prompt,int team_size);

#endif // TEAM_H
