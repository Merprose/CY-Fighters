// ui.h
#ifndef UI_H
#define UI_H

#include "character.h"
#include "team.h"

void clear_screen();
void press_enter_to_continue();
int display_main_menu();
void display_combat_state(const Team* team1, const Team* team2, int p1_active_idx, int p2_active_idx, int current_player_turn); //Subject to change
void display_character_actions(); //Working On...
void print_health_bar(int current_hp, int max_hp, int bar_width); 

#endif