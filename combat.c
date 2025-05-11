
#include "character.h"
#include "combat.h"
#define CHARCOUNT 8

int getactualspeed(Character chara){
	int speed = 1;
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(chara.effects[i].name,"speed",5)){
			speed = chara.effects[i].value;
		}
	}
	if (chara.speed + speed < 0){
		return 0;
	}
	return chara.speed + speed;
}

int getactualagility(Character chara){
	int agility = 0;
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(chara.effects[i].name,"agility",7)){
			agility = chara.effects[i].value;
		}
	}
	if (chara.agility + agility < 0){
		return 0;
	}
	return chara.agility + agility;
}

int getactualattack(Character chara){
	int attack = 0;
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(chara.effects[i].name,"attack",6)){
			attack = chara.effects[i].value;
			break;
		}
	}
	if (chara.attack + attack < 0){
		return 0;
	}
	return chara.attack + attack;
}
int getactualdefense(Character chara){
	int defense = 0;
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(chara.effects[i].name,"defense",7)){
			defense = chara.effects[i].value;
		}
	}
	if (chara.defense + defense < 0){
		return 0;
	}
	return chara.defense + defense;
}

void typetargettostring(char type[],char target[],char newtype[],char newtarget[],Effects effect){
	char name[50];
	clearchararray(newtype,50);
	clearchararray(newtarget,50);
	clearchararray(name,50);
	if (comparestring(type,"DAMAGE",6)){
		tabtotab("Damage",newtype);
	}
	else if (comparestring(type,"HEAL",5)){
		tabtotab("Heal",newtype);
	}
	else if (comparestring(type,"BUFF",5)){
		if (comparestring(effect.name,"ATTACKUP",9)){
			tabtotab("attack buff",newtype);
		}
		else if (comparestring(effect.name,"DEFENSEUP",10)){
			tabtotab("defense buff",newtype);
		}
		else if (comparestring(effect.name,"AGILITYUP",9)){
			tabtotab("agility buff",newtype);
		}
		else if (comparestring(effect.name,"SPEEDUP",8)){
			tabtotab("speed buff",newtype);
		}
		else {
			printf("Effect not found");
			exit(42);
		}
	}
	else if (comparestring(type,"DEBUFF",7)){
		if (comparestring(effect.name,"ATTACKDOWN",11)){
			tabtotab("attack debuff",newtype);
		}
		else if (comparestring(effect.name,"DEFENSEDOWN",12)){
			tabtotab("defense debuff",newtype);
		}
		else if (comparestring(effect.name,"AGILITYDOWN",11)){
			tabtotab("agility debuff",newtype);
		}
		else if (comparestring(effect.name,"SPEEDDOWN",12)){
			tabtotab("speed debuff",newtype);
		}
		else {
			printf("Effect not found");
			exit(42);
		}
	}
	if (comparestring(target,"SELF",5)){
		tabtotab("yourself",newtarget);
	}
	else if (comparestring(target,"SINGLE_ENEMY",14)){
		tabtotab("one enemy",newtarget);
	}
	else if (comparestring(target,"ALL_ENEMIES",12)){
		tabtotab("all enemies",newtarget);
	}
	else if (comparestring(target,"SINGLE_ALLY",13)){
		tabtotab("one ally",newtarget);
	}
	else if (comparestring(target,"ALL_ALLIES",11)){
		tabtotab("all allies",newtarget);
	}
	
}

int teamalive(Character* team, int size){
	int total = 0;
	for (int i = 0;i<size;i++){
		if (team[i].hp <= 0){
			total++;
		}
	}
	if (total == size){
		return 0;
	}
	return 1;
}
void getorder(Character* redteam, Character* blueteam,int size,Character** sortorder){
	int count = 0;
	Character* pmaxspeed;
	Character* temp;
	int pos = 0;
	if (sortorder == NULL){
		printf("Not enough memory");
		exit(42);
	}
	for (int i = 0; i<size;i++){
		if (i<size/2){
			sortorder[i] = &redteam[i];
		}
		else {
			sortorder[i] = &blueteam[i-(size/2)];
		}
	}

	for (int i = 0; i<size;i++){
		pmaxspeed = sortorder[count];
		for(int j = count;j<size;j++){
			if (getactualspeed(*pmaxspeed) <= getactualspeed(*sortorder[j])){
				pmaxspeed = sortorder[j];
				pos = j;
			}
		}
		temp = sortorder[count];
		sortorder[count] = pmaxspeed;
		sortorder[pos] = temp;
		count++;
	}
}

void doeffect(Character* target){
	for (int i = 0;i<EFFECTCOUNT;i++){
		if (comparestring(target->effects[i].name,"NONE",4) == 0){
			target->effects[i].duration--;
			if (target->effects[i].duration <= 0){
				tabtotab("NONE",target->effects[i].name);
				target->effects[i].value = 0;
				target->effects[i].duration = 0;
			}
			if (comparestring(target->effects[i].name,"BLEED",6) || comparestring(target->effects[i].name,"BURN",4)
			|| comparestring(target->effects[i].name,"POISON",6)){
				target->hp -= target->effects[i].value;
				if (target->hp <= 0){
					target->hp = 0;
				}
			}
		}
	}
}

void usetechnique(Character user, Character* target, Technique tech){
	int damage = 0;
	char name[50];
	int found = 0;
	clearchararray(name,50);
	if (comparestring(tech.type,"DAMAGE",6)){
		damage = (tech.value+getactualattack(user)+user.attack) - getactualdefense(*target);
		if (damage < 0){
			damage = 0;
		}
		if ((*target).hp - damage <= 0){
			(*target).hp = 0;
		}
		else {
			(*target).hp -= damage;
		}
		printf("%s dealt %d damage to %s\n",user.name,damage,(*target).name);
		printf("%s has %d hp left\n",(*target).name,(*target).hp);
	}
	else if (comparestring(tech.type,"HEAL",5)){
		(*target).hp += tech.value;
		if ((*target).hp > (*target).maxhp){
			(*target).hp = (*target).maxhp;
		}
		printf("%s healed %d hp to %s\n",user.name,tech.value,(*target).name);
	}
	else if (comparestring(tech.type,"BUFF",5)){
		if (comparestring(tech.effect.name,"ATTACKUP",9)||comparestring(tech.effect.name,"DEFENSEUP",10)
		||comparestring(tech.effect.name,"AGILITYUP",9)||comparestring(tech.effect.name,"SPEEDUP",8)){
			if (comparestring(tech.effect.name,"SPEEDUP",8)){
				tabtotab("speed",name);
			}
			else if (comparestring(tech.effect.name,"AGILITYUP",9)){
				tabtotab("agility",name);
			}
			else if (comparestring(tech.effect.name,"DEFENSEUP",10)){
				tabtotab("defense",name);
			}
			else if (comparestring(tech.effect.name,"ATTACKUP",9)){
				tabtotab("attack",name);
			}
			tabtotab(tech.effect.name,name);
			for (int i = 0;i<EFFECTCOUNT;i++){
				if (comparestring((*target).effects[i].name,name,10)){
					if ((*target).effects[i].value <= tech.effect.value){
						(*target).effects[i].value = tech.effect.value;
						(*target).effects[i].duration = tech.effect.duration;
					}
					found = 1;
					break;
				}
			}
			if (found == 0){
				for (int i = 0;i<EFFECTCOUNT;i++){
					if (comparestring((*target).effects[i].name,"NONE",4)){
						tabtotab(name,(*target).effects[i].name);
						(*target).effects[i].value = tech.effect.value;
						(*target).effects[i].duration = tech.effect.duration;
						break;
					}
				}
			}
		}
	}
	else if (comparestring(tech.type,"DEBUFF",7)){
			tabtotab(tech.effect.name,name);
			if (comparestring(tech.effect.name,"SPEEDDOWN",12)){
				tabtotab("speed",name);
			}
			else if (comparestring(tech.effect.name,"AGILITYDOWN",11)){
				tabtotab("agility",name);
			}
			else if (comparestring(tech.effect.name,"DEFENSEDOWN",12)){
				tabtotab("defense",name);
			}
			else if (comparestring(tech.effect.name,"ATTACKDOWN",11)){
				tabtotab("attack",name);
			}
			for (int i = 0;i<50;i++){
				if (comparestring((*target).effects[i].name,name,10)){
					if ((*target).effects[i].value <= tech.effect.value){
						(*target).effects[i].value = tech.effect.value;
						(*target).effects[i].duration = tech.effect.duration;
					}
					found = 1;
					break;
				}
			}
			if (found == 0){
				for (int i = 0;i<50;i++){
					if (comparestring((*target).effects[i].name,"NONE",4)){
						tabtotab(name,(*target).effects[i].name);
						(*target).effects[i].value = tech.effect.value;
						(*target).effects[i].duration = tech.effect.duration;
						break;
					}
				}
			}
	}
	else {
		printf("Type not found");
		exit(42);
	}
}

Character* chosetarget(Character* team,int size){
	int choice = -1;
	char input[10];
	for (int i = 0; i<size;i++){
		printf("%d. %s\n",i+1,team[i].name);
	}
	do {
		printf("Choose your target: \n");
	   if (fgets(input, sizeof(input), stdin) != NULL) {
			if (sscanf(input, "%d", &choice) != 1) {
				printf("Invalid input. Please enter a number between 1 and %d.\n",size);
				choice = -1; 
			}
			else if (team[choice-1].hp <= 0){
				printf("%s is dead, please choose another target\n",team[choice-1].name);{
				choice = -1; 
				}	
			}
		}
	}while (choice < 1 || choice > size);
	return &team[choice-1];
}

void dotechnique(Character* redteam,Character* blueteam,Character chara, Technique tech,int size){
	Character* target;
	Character** pteam;
	Character** eteam;
	if (comparestring(chara.team,"red",3)){
		pteam = &redteam;
		eteam = &blueteam;
	}
	else if (comparestring(chara.team,"blue",4)){
		pteam = &blueteam;
		eteam = &redteam;
	}
	else {
		printf("Team not found");
		exit(42);
	}
	if (comparestring(tech.target,"SELF",5)){
		usetechnique(chara,&chara,tech);
	}
	else if (comparestring(tech.target,"SINGLE_ENEMY",14)){
		Character* target = chosetarget(*eteam,size/2);
		usetechnique(chara,target,tech);
	}
	else if (comparestring(tech.target,"ALL_ENEMIES",12)){
		for (int i = 0; i<size/2;i++){
			if ((*eteam)[i].hp > 0){
				usetechnique(chara,&(*eteam)[i],tech);
			}
		}
	}
	else if (comparestring(tech.target,"SINGLE_ALLY",13)){
		Character* target = chosetarget(*pteam,size/2);
		usetechnique(chara,target,tech);
	}
	else if (comparestring(tech.target,"ALL_ALLIES",11)){
		for (int i = 0; i<size/2;i++){
			if ((*pteam)[i].hp > 0){
				usetechnique(chara,&(*pteam)[i],tech);
			}
		}
	}
	else {
		printf("Target not found");
		exit(42);
	}
}

void playerturn(Character* redteam,Character* blueteam,Character chara,int size){
	int t1cooldown = chara.technique1[0].oncooldown;
	int t2cooldown = chara.technique2[0].oncooldown;
	int choice = -1;
	char input[10];
	char type1[100];
	char type2[100];
	char target1[30];
	char target2[30];
	clearchararray(type1,100);
	clearchararray(type2,100);
	clearchararray(target1,30);
	clearchararray(target2,30);
	typetargettostring(chara.technique1[0].type,chara.technique1[0].target,type1,target1,chara.technique1->effect);
	typetargettostring(chara.technique2[0].type,chara.technique2[0].target,type2,target2,chara.technique2->effect);
	printf("You can chose between the following actions:\n");
	printf("1. Attack\n");
	printf("2. %s%s \n",chara.technique1[0].name,chara.technique1[0].description);
	printf("Targets %s dealing %d %s, with a cooldown of %d\n turn",target1,chara.technique1->value,type1,chara.technique1->cooldown);
	if (chara.technique1->cooldown > 1){
		printf("s");
	}
	printf("\n");
	printf("Actual cooldown: %d\n\n",chara.technique1[0].oncooldown);
	printf("3. %s%s \n",chara.technique2[0].name,chara.technique2[0].description);
	printf("Targets %s dealing %d %s, with a cooldown of %d turn",target2,chara.technique2->value,type2,chara.technique2->cooldown);
	if (chara.technique2->cooldown > 1){
		printf("s");
	}
	printf("\n");
	printf("Actual cooldown: %d\n\n",chara.technique2[0].oncooldown);
	do {
		printf("Choose your action: \n");
       if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &choice) != 1) {
                printf("Invalid input. Please enter a number between 1 and 3.\n");
                choice = -1; 
            }
			else if (choice == 2 && chara.technique1->oncooldown != 0){ 
                printf("Technique on cooldown, try another.\n");
                choice = -1; 
            }
			else if (choice == 3 && chara.technique2->oncooldown != 0){ 
                printf("Technique on cooldown, try another.\n");
                choice = -1; 
            }
		}
	}while (choice < 1 || choice > 3);
	 if (choice == 1){
		printf("You chose to attack\n");
	 }
	 else if (choice == 2){
		dotechnique(redteam,blueteam,chara,chara.technique1[0],size);
	 }
	 else if (choice == 3){
		dotechnique(redteam,blueteam,chara,chara.technique2[0],size);
	 }
	 else {
		printf("Error, please restart the game\n");
		exit(42);
	 }
}

void doturn(Character* redteam,Character* blueteam,int size,char ia[]){
	Character* order[size*2];
	getorder(redteam,blueteam,size,order);
	for (int i = 0; i<size;i++){
		if (order[i]->hp > 0){
			printf("Turn of %s in the %s team\n",order[i]->name,order[i]->team);
			if (comparestring(order[i]->team,"red",3)){
				if (comparestring(ia,"No",2)){
					playerturn(redteam,blueteam,*order[i],size);
				//printf("IA\n");
				}
				else {
					//player
					//printf("Player\n");
				}
			}
			else {
				playerturn(redteam,blueteam,*order[i],size);
				//printf("Player\n");
			}
		}
	}
}

void combatInit(Character* redteam, Character* blueteam,char ia[],int size){
	int turn = 1;
    if (redteam == NULL || blueteam == NULL){
		printf("Not enough memory");
		exit(42);
	}
	while (teamalive(redteam,size/2) && teamalive(blueteam,size/2)){
		printf("=============Turn %d=============\n",turn);
		doturn(redteam,blueteam,size,ia);
		for (int i = 0;i<size/2;i++){
			if (redteam[i].hp > 0){
				doeffect(&redteam[i]);
			}
			if (blueteam[i].hp > 0){
				doeffect(&blueteam[i]);
			}
		}
	}
	
}

int main() {
	Character chars[CHARCOUNT];
	Character redteam[3];
	Character blueteam[3];
	Character* order[6];
	getcharacters(chars);
	for(int i=0; i<CHARCOUNT; i++) {
		if (chars[i].name[0] != '\0') {
			printf("hm");
			/*printf("Nom: %s \n",chars[i].name);
			printf("Special 1: %s \n",chars[i].technique1->name);
			printf("Special 1 type: %s \n",chars[i].technique1->type);
			printf("Special 1 desc: %s \n",chars[i].technique1->description);
			printf("Damage: %d \n",chars[i].technique1->value);
			printf("Special 2: %s \n",chars[i].technique2->name);
			printf("Special 2 desc: %s \n",chars[i].technique2->description);
			printf("Special 2 type: %s \n",chars[i].technique2->type);
			printf("Damage: %d \n",chars[i].technique2->value);
			printf("Hp: %d \n",chars[i].maxhp);
			printf("Attack: %d \n",chars[i].attack);
			printf("Defense: %d \n",chars[i].defense);
			printf("Speed: %d \n",chars[i].speed);
			printf("Agility: %d \n",chars[i].agility);
			printf("\n"); */
			if (i<3){
				redteam[i] = chars[i];
				tabtotab("red",redteam[i].team);
			}
			else if (i<6){
				blueteam[i-3] = chars[i];
				tabtotab("blue",blueteam[i-3].team);
			}
		}
	}
	getorder(redteam,blueteam,6,order);
	/*for (int i = 0; i<6;i++){
		printf("Character %d: %s\n",i+1,order[i]->name);
		printf("Speed: %d\n",getactualspeed(*order[i]));
	}*/
	combatInit(redteam,blueteam,"No",6);
	return 0;
}
