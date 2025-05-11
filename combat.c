#include "character.h"
#include "team.h"
#include "combat.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int getactualspeed(Character chara){
	int speed_mod = 0;
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(chara.effects[i].name,"speed",5)){
			speed_mod = chara.effects[i].value;
            break;
		}
	}
	if (chara.speed + speed_mod < 0){
		return 0;
	}
	return chara.speed + speed_mod;
}

int getactualagility(Character chara){
	int agility_mod = 0;
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(chara.effects[i].name,"agility",7)){
			agility_mod = chara.effects[i].value;
            break;
		}
	}
	if (chara.agility + agility_mod < 0){
		return 0;
	}
	return chara.agility + agility_mod;
}

int getactualattack(Character chara){
	int attack_mod = 0;
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(chara.effects[i].name,"attack",6)){
			attack_mod = chara.effects[i].value;
			break;
		}
	}
	if (chara.attack + attack_mod < 0){
		return 0;
	}
	return chara.attack + attack_mod;
}
int getactualdefense(Character chara){
	int defense_mod = 0;
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(chara.effects[i].name,"defense",7)){
			defense_mod = chara.effects[i].value;
            break;
		}
	}
	if (chara.defense + defense_mod < 0){
		return 0;
	}
	return chara.defense + defense_mod;
}

void typetargettostring(char type[],char target[],char newtype[],char newtarget[],Effects effect){
	clearchararray(newtype,50);
	clearchararray(newtarget,50);

	if (comparestring(type,"DAMAGE",6)){
		tabtotab("Damage",newtype);
	}
	else if (comparestring(type,"HEAL",5)){
		tabtotab("Heal",newtype);
	}
	else if (comparestring(type,"BUFF",5)){
		if (comparestring(effect.name,"ATTACKUP",9)){
			tabtotab("Attack Buff",newtype);
		}
		else if (comparestring(effect.name,"DEFENSEUP",10)){
			tabtotab("Defense Buff",newtype);
		}
		else if (comparestring(effect.name,"AGILITYUP",9)){
			tabtotab("Agility Buff",newtype);
		}
		else if (comparestring(effect.name,"SPEEDUP",8)){
			tabtotab("Speed Buff",newtype);
		}
		else {
            tabtotab("Unknown Buff", newtype);
		}
	}
	else if (comparestring(type,"DEBUFF",7)){
		if (comparestring(effect.name,"ATTACKLOWER",11)){
			tabtotab("Attack Debuff",newtype);
		}
        else if (comparestring(effect.name,"BLEED",5) || comparestring(effect.name,"BURN",4) || comparestring(effect.name,"POISON",6)){
            char temp_debuff_type[60];
            sprintf(temp_debuff_type, "%s Debuff", effect.name);
            tabtotab(temp_debuff_type, newtype);
        }
		else {
            tabtotab("Unknown Debuff", newtype);
		}
	}
    else {
        tabtotab("Unknown Type", newtype);
    }

	if (comparestring(target,"SELF",5)){
		tabtotab("Yourself",newtarget);
	}
	else if (comparestring(target,"SINGLE_ENEMY",14)){
		tabtotab("One Enemy",newtarget);
	}
	else if (comparestring(target,"ALL_ENEMIES",12)){
		tabtotab("All Enemies",newtarget);
	}
	else if (comparestring(target,"SINGLE_ALLY",13)){
		tabtotab("One Ally",newtarget);
	}
	else if (comparestring(target,"ALL_ALLIES",11)){
		tabtotab("All Allies",newtarget);
	}
    else {
        tabtotab("Unknown Target", newtarget);
    }

}

int teamalive(Character* team_members, int team_actual_size){
	if (!team_members || team_actual_size <= 0) return 0;
	for (int i = 0;i<team_actual_size;i++){
		if (team_members[i].hp > 0){
			return 1;
		}
	}
	return 0;
}

void getorder(Team* redteam_struct, Team* blueteam_struct, Character** sortorder, int* actual_total_combatants_ptr){
    if (!redteam_struct || !blueteam_struct || !sortorder || !actual_total_combatants_ptr) {
        if (actual_total_combatants_ptr) *actual_total_combatants_ptr = 0;
        return;
    }
    int k = 0;

    for (int i = 0; i < redteam_struct->current_size; i++){
        sortorder[k++] = &redteam_struct->members[i];
    }
    for (int i = 0; i < blueteam_struct->current_size; i++){
        sortorder[k++] = &blueteam_struct->members[i];
    }
    *actual_total_combatants_ptr = k;

	for (int i = 0; i < k - 1; i++){
		for(int j = 0; j < k - i - 1; j++){
            if (sortorder[j] && sortorder[j+1]) {
			    if (getactualspeed(*(sortorder[j])) < getactualspeed(*(sortorder[j+1]))){
				    Character* temp = sortorder[j];
				    sortorder[j] = sortorder[j+1];
				    sortorder[j+1] = temp;
			    }
            }
		}
	}
}

void doeffect(Character* target){
    if (!target) return;
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(target->effects[i].name,"NONE",4) == 0){
			target->effects[i].duration--;

			if (comparestring(target->effects[i].name,"BLEED",6) ||
                comparestring(target->effects[i].name,"BURN",5) ||
			    comparestring(target->effects[i].name,"POISON",6)){

                printf("%s takes %d damage from %s.\n", target->name, target->effects[i].value, target->effects[i].name);
                target->hp -= target->effects[i].value;
				if (target->hp <= 0){
					target->hp = 0;
                    printf("%s has been KO'd by %s!\n", target->name, target->effects[i].name);
				}
			}

            if (target->effects[i].duration <= 0){
                printf("%s's %s effect wore off.\n", target->name, target->effects[i].name);
				tabtotab("NONE",target->effects[i].name);
				target->effects[i].value = 0;
			}
		}
	}
}

void usetechnique(Character* user, Character* target, Technique* tech){
    if(!user || !target || !tech) return;

	int damage = 0;
	char effect_application_name[50];
	int found_existing_effect = 0;
	clearchararray(effect_application_name,50);

    printf("%s uses %s!\n", user->name, tech->name);


	if (comparestring(tech->type,"DAMAGE",6)){
		damage = (tech->value + getactualattack(*user)) - getactualdefense(*target);
		if (damage < 0){
			damage = 0;
		}
		target->hp -= damage;
        printf("%s takes %d damage from %s. HP: %d/%d", target->name, damage, tech->name, (target->hp > 0 ? target->hp : 0), target->maxhp);
        if (target->hp <= 0){
			target->hp = 0;
            printf(". %s is KO'd!\n", target->name);
		} else {
            printf("\n");
        }

        if(comparestring(tech->effect.name, "NONE", 4) == 0) {
            if (comparestring(tech->effect.name,"BLEED",5) ||
                comparestring(tech->effect.name,"BURN",4) ||
                comparestring(tech->effect.name,"POISON",6)) {

                tabtotab(tech->effect.name, effect_application_name);

                found_existing_effect = 0;
                for (int i = 0; i < EFFECTCOUNT; i++) {
                    if (comparestring(target->effects[i].name, effect_application_name, strlen(effect_application_name)+1)) {
                        target->effects[i].value = tech->effect.value;
                        target->effects[i].duration = tech->effect.duration;
                        printf("%s is now %s for %d turns, taking %d damage per turn.\n", target->name, effect_application_name, tech->effect.duration, tech->effect.value);
                        found_existing_effect = 1;
                        break;
                    }
                }
                if (!found_existing_effect) {
                    for (int i = 0; i < EFFECTCOUNT; i++) {
                        if (comparestring(target->effects[i].name, "NONE", 4)) {
                            tabtotab(effect_application_name, target->effects[i].name);
                            target->effects[i].value = tech->effect.value;
                            target->effects[i].duration = tech->effect.duration;
                            printf("%s is now %s for %d turns, taking %d damage per turn.\n", target->name, effect_application_name, tech->effect.duration, tech->effect.value);
                            break;
                        }
                    }
                }
            }
        }
	}
	else if (comparestring(tech->type,"HEAL",5)){
		int heal_amount = tech->value;
        target->hp += heal_amount;
		if (target->hp > target->maxhp){
			target->hp = target->maxhp;
		}
		printf("%s healed %s for %d HP. %s is now at %d/%d HP.\n",user->name, target->name, heal_amount, target->name, target->hp, target->maxhp);
	}
	else if (comparestring(tech->type,"BUFF",5) || comparestring(tech->type,"DEBUFF",7)){
        if (comparestring(tech->effect.name,"ATTACKUP",9) || comparestring(tech->effect.name,"ATTACKLOWER",11)){
            tabtotab("attack", effect_application_name);
        } else if (comparestring(tech->effect.name,"DEFENSEUP",10)  ){
            tabtotab("defense", effect_application_name);
        } else if (comparestring(tech->effect.name,"AGILITYUP",9) ){
            tabtotab("agility", effect_application_name);
        } else if (comparestring(tech->effect.name,"SPEEDUP",8) ){
            tabtotab("speed", effect_application_name);
        } else {
            tabtotab(tech->effect.name, effect_application_name);
        }

        if(strlen(effect_application_name) > 0 && comparestring(effect_application_name, "NONE", 4) == 0) {
            found_existing_effect = 0;
            for (int i = 0;i<EFFECTCOUNT;i++){
                if (comparestring(target->effects[i].name,effect_application_name, strlen(effect_application_name)+1)){
                    target->effects[i].value = tech->effect.value;
                    target->effects[i].duration = tech->effect.duration;
                    printf("%s's %s changed by %d for %d turns.\n", target->name, effect_application_name, tech->effect.value, tech->effect.duration);
                    found_existing_effect = 1;
                    break;
                }
            }
            if (!found_existing_effect){
                for (int i = 0;i<EFFECTCOUNT;i++){
                    if (comparestring(target->effects[i].name,"NONE",4)){
                        tabtotab(effect_application_name,target->effects[i].name);
                        target->effects[i].value = tech->effect.value;
                        target->effects[i].duration = tech->effect.duration;
                        printf("%s's %s changed by %d for %d turns.\n", target->name, effect_application_name, tech->effect.value, tech->effect.duration);
                        break;
                    }
                }
            }
        } else {
            printf("Technique %s (type %s) has an unhandled effect '%s'.\n", tech->name, tech->type, tech->effect.name);
        }
	}
	else {
		printf("Technique type '%s' not recognized for %s.\n", tech->type, tech->name);
	}
}

Character* chosetarget(Character* team_members, int team_actual_size, const char* prompt_message){
	int choice = -1;
	char input[10];

    if(team_actual_size <=0) return NULL;

    printf("%s\n", prompt_message);
	for (int i = 0; i<team_actual_size;i++){
        if(team_members[i].hp > 0) {
		    printf("%d. %s (HP: %d/%d)\n",i+1,team_members[i].name, team_members[i].hp, team_members[i].maxhp);
        } else {
            printf("%d. %s (KO'd)\n",i+1,team_members[i].name);
        }
	}
	do {
		printf("Choose your target (1-%d): ", team_actual_size);
	   if (fgets(input, sizeof(input), stdin) != NULL) {
			if (sscanf(input, "%d", &choice) != 1) {
				printf("Invalid input. Please enter a number.\n");
				choice = -1;
			}
            else if (choice < 1 || choice > team_actual_size) {
                printf("Choice out of range. Please enter a number between 1 and %d.\n", team_actual_size);
                choice = -1;
            }
			else if (team_members[choice-1].hp <= 0){
				printf("%s is already KO'd. Please choose an alive target.\n",team_members[choice-1].name);
				choice = -1;
			}
		} else {
            return NULL;
        }
	} while (choice == -1);
	return &team_members[choice-1];
}

void dotechnique(Character* user_char, Team* friendly_team, Team* enemy_team, Technique* tech_to_use){
    if(!user_char || !friendly_team || !enemy_team || !tech_to_use) return;

    Character* target_char = NULL;

	if (comparestring(tech_to_use->target,"SELF",5)){
		usetechnique(user_char, user_char, tech_to_use);
	}
	else if (comparestring(tech_to_use->target,"SINGLE_ENEMY",14)){
		target_char = chosetarget(enemy_team->members, enemy_team->current_size, "Choose an enemy target:");
        if(target_char) usetechnique(user_char, target_char, tech_to_use);
        else printf("No valid enemy target selected or available.\n");
	}
	else if (comparestring(tech_to_use->target,"ALL_ENEMIES",12)){
        printf("%s uses %s on all enemies!\n", user_char->name, tech_to_use->name);
		for (int i = 0; i < enemy_team->current_size; i++){
			if (enemy_team->members[i].hp > 0){
				usetechnique(user_char, &enemy_team->members[i], tech_to_use);
			}
		}
	}
	else if (comparestring(tech_to_use->target,"SINGLE_ALLY",13)){
		target_char = chosetarget(friendly_team->members, friendly_team->current_size, "Choose an allied target:");
        if(target_char) usetechnique(user_char, target_char, tech_to_use);
        else printf("No valid allied target selected or available.\n");
	}
	else if (comparestring(tech_to_use->target,"ALL_ALLIES",11)){
        printf("%s uses %s on all allies!\n", user_char->name, tech_to_use->name);
		for (int i = 0; i < friendly_team->current_size; i++){
			if (friendly_team->members[i].hp > 0){
				usetechnique(user_char, &friendly_team->members[i], tech_to_use);
			}
		}
	}
	else {
		printf("Target type '%s' for technique '%s' not recognized.\n", tech_to_use->target, tech_to_use->name);
	}
}


void playerturn(Character* current_player_char, Team* friendly_team, Team* enemy_team){
    if (!current_player_char || current_player_char->hp <= 0) return; // Skip turn if 

	int choice = -1;
	char input_buffer[10];

    Technique* tech1 = &current_player_char->technique1[0];
    Technique* tech2 = &current_player_char->technique2[0];

    // Loop for action selection until a valid action is chosen
	do {
		if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
            if (sscanf(input_buffer, "%d", &choice) != 1) { // Validate numeric input
                printf("Invalid input. Please enter a number (1-4): "); // Max choice is 4 now
                choice = -1;
            } else {
                // Validate choice range and technique availability/cooldown
                if (choice < 1 || choice > 4) { // Max choice is 4 
                    printf("Invalid choice. Please enter a number between 1 and 4: "); // Max choice is 4 now
                    choice = -1;
                }
                else if (choice == 2 && (strlen(tech1->name) == 0 || tech1->oncooldown > 0)) {
                    printf("Technique 1 (%s) is not available or on cooldown. Choose another action: ", strlen(tech1->name) > 0 ? tech1->name : "N/A");
                    choice = -1;
                }
                else if (choice == 3 && (strlen(tech2->name) == 0 || tech2->oncooldown > 0)) {
                    printf("Technique 2 (%s) is not available or on cooldown. Choose another action: ", strlen(tech2->name) > 0 ? tech2->name : "N/A");
                    choice = -1;
                }
                // No choice == 4 for switch anymore, choice 4 is now forfeit
            }
        } else { // fgets failed
            printf("Error reading input. Forfeiting turn.\n");
            choice = 4; // Default to forfeit turn (now option 4) on input error
        }
	}while (choice == -1);

    // Execute chosen action
	 if (choice == 1){ // Basic Attack
        Character* target = chosetarget(enemy_team->members, enemy_team->current_size, "Choose an enemy to attack:");
        if (target) {
            printf("%s attacks %s!\n", current_player_char->name, target->name);
            int damage_dealt = getactualattack(*current_player_char) - getactualdefense(*target);
            if (damage_dealt < 0) damage_dealt = 0; // No negative damage
            target->hp -= damage_dealt;
            printf("%s takes %d damage. HP: %d/%d", target->name, damage_dealt, (target->hp > 0 ? target->hp : 0), target->maxhp);
            if(target->hp <= 0) {
                target->hp = 0;
                printf(". %s has been KO'd!\n", target->name);
            } else {
                printf("\n");
            }
        } else {
            printf("No valid target selected or available. %s forfeits the turn.\n", current_player_char->name);
        }
	 }
	 else if (choice == 2){ // Use Technique 1
		dotechnique(current_player_char, friendly_team, enemy_team, tech1);
        if(tech1->cooldown > 0) tech1->oncooldown = tech1->cooldown; // Set cooldown
	 }
	 else if (choice == 3){ // Use Technique 2
		dotechnique(current_player_char, friendly_team, enemy_team, tech2);
        if(tech2->cooldown > 0) tech2->oncooldown = tech2->cooldown; // Set cooldown
	 }
     else if (choice == 4) { // Forfeit turn (was choice 5)
         printf("%s forfeits the turn.\n", current_player_char->name);
     }
	 else { // fallback
		printf("Action %d not recognized or invalid under current conditions. %s forfeits the turn.\n", choice, current_player_char->name);
	 }
}

void reduce_cooldowns(Character* character) {
    if (!character) return;
    if (character->technique1[0].oncooldown > 0) character->technique1[0].oncooldown--;
    if (character->technique2[0].oncooldown > 0) character->technique2[0].oncooldown--;
}


void combatInit(Team* red_team_ptr, Team* blue_team_ptr, const char* ia_mode){
	int turn_counter = 1;
	Character* turn_order_list[MAX_TEAM_SIZE * 2];
    int actual_combatants_in_round = 0;

    if (!red_team_ptr || !blue_team_ptr ) {
		printf("Error: Invalid teams for combat initialization.\n");
		return;
	}
    if (red_team_ptr->current_size == 0 || blue_team_ptr->current_size == 0) {
        printf("One or both teams have no members. Combat cannot start.\n");
        return;
    }


    for(int i=0; i < red_team_ptr->current_size; ++i) tabtotab("red", red_team_ptr->members[i].team);
    for(int i=0; i < blue_team_ptr->current_size; ++i) tabtotab("blue", blue_team_ptr->members[i].team);


	while (teamalive(red_team_ptr->members, red_team_ptr->current_size) &&
           teamalive(blue_team_ptr->members, blue_team_ptr->current_size)){

        getorder(red_team_ptr, blue_team_ptr, turn_order_list, &actual_combatants_in_round);

        if (actual_combatants_in_round == 0) {
            printf("No combatants available to take turns. Ending combat.\n");
            break;
        }

        for (int i = 0; i < actual_combatants_in_round; i++){
            Character* active_char = turn_order_list[i];

            if (!teamalive(red_team_ptr->members, red_team_ptr->current_size) ||
                !teamalive(blue_team_ptr->members, blue_team_ptr->current_size)){
                break;
            }

            display_combat_state(red_team_ptr, blue_team_ptr, active_char);

            if (active_char->hp > 0) {
                Team* friendly_tm = (comparestring(active_char->team, "red", 3)) ? red_team_ptr : blue_team_ptr;
                Team* enemy_tm = (comparestring(active_char->team, "red", 3)) ? blue_team_ptr : red_team_ptr;

                doeffect(active_char);
                if(active_char->hp <= 0) {
                    printf("%s was KO'd by an effect before their turn!\n", active_char->name);
                    press_enter_to_continue();
                    continue;
                }
                reduce_cooldowns(active_char);

                int is_player_controlled_turn = 0;
                const char* player_identifier_string = "";

                if (comparestring(active_char->team, "red", 3)) {
                    player_identifier_string = "Player 1";
                    if (comparestring(ia_mode, "PlayerVsPlayer", 15) || comparestring(ia_mode, "PlayerVsAI", 11)) {
                        is_player_controlled_turn = 1;
                    }
                } else if (comparestring(active_char->team, "blue", 4)) {
                    player_identifier_string = "Player 2";
                    if (comparestring(ia_mode, "PlayerVsPlayer", 15)) {
                        is_player_controlled_turn = 1;
                    }
                }


                if (is_player_controlled_turn) {
                    display_character_actions(active_char, player_identifier_string);
                    playerturn(active_char, friendly_tm, enemy_tm);
                } else {
                    printf("[AI TURN] %s (%s Team) takes its turn (Basic AI).\n", active_char->name, active_char->team);
                    Character* ai_target = NULL;
                    for(int k=0; k < enemy_tm->current_size; ++k) {
                        if(enemy_tm->members[k].hp > 0) {
                            ai_target = &enemy_tm->members[k];
                            break;
                        }
                    }
                    if (ai_target) {
                        printf("%s attacks %s!\n", active_char->name, ai_target->name);
                        int damage_dealt = getactualattack(*active_char) - getactualdefense(*ai_target);
                        if (damage_dealt < 0) damage_dealt = 0;
                        ai_target->hp -= damage_dealt;
                        printf("%s takes %d damage. HP: %d/%d", ai_target->name, damage_dealt, (ai_target->hp > 0 ? ai_target->hp : 0), ai_target->maxhp);
                        if(ai_target->hp <= 0) {
                            ai_target->hp = 0;
                            printf(". %s has been KO'd!\n", ai_target->name);
                        } else {
                             printf("\n");
                        }
                    } else {
                        printf("[AI] %s has no targets to attack. Turn forfeited.\n", active_char->name);
                    }
                }
            } else {
                 printf("%s is KO'd and skips their turn.\n", active_char->name);
            }
            if (teamalive(red_team_ptr->members, red_team_ptr->current_size) &&
                teamalive(blue_team_ptr->members, blue_team_ptr->current_size)){
                press_enter_to_continue();
            }
        }
		turn_counter++;
	}

    display_combat_state(red_team_ptr, blue_team_ptr, NULL);
    if (teamalive(red_team_ptr->members, red_team_ptr->current_size)) {
        printf("\nPlayer 1 (Red Team) Wins!\n");
    } else if (teamalive(blue_team_ptr->members, blue_team_ptr->current_size)) {
        printf("\nPlayer 2 (Blue Team) Wins!\n");
    } else {
        printf("\nIt's a Draw!\n");
    }
    press_enter_to_continue();
}
