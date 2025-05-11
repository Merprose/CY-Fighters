#ifndef UI_H
#define UI_H

#include "character.h"
#include "team.h"

void clear_screen();
void press_enter_to_continue();
int display_main_menu();
// void display_combat_state( Team* team1,  Team* team2, int p1_active_idx, int p2_active_idx, int current_player_turn); //Old
void display_combat_state(Team* team1, Team* team2, Character* current_combatant); // New
void display_character_actions(const Character* combatant, const char* player_identifier_string);
void print_health_bar(int current_hp, int max_hp, int bar_width);
void display_all_characters_detailed(Character all_characters[], int num_chars);

#endif