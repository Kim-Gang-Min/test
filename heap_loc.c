#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void show_menu();
char* rand_lotto(int success);
void del_lotto();
void show_lotto();
void cheat_mode();
void cmp_lotto();
void read_file();

int num=0;
char* lotto_list[1000];
char flag[100];

int main(){
	int cho=0;
	char* success_num;
	
	read_file();
	srand((unsigned int)time(NULL));	
	
	success_num = rand_lotto(-1);

	while(1){
		show_menu();
		scanf("%d", &cho);
		
		switch(cho){
			case 1:
				lotto_list[num++] = rand_lotto(1);
				break;
			case 2:
				del_lotto();
				break;
			case 3:
				show_lotto();
				break;
			case 4:
				printf("****** Today Lotto ******\n");
				printf("%s\n", success_num);
				printf("******* Good Luck *******\n");
				break;
			case 5:
				cmp_lotto(success_num);
				break;
			case -1:
				cheat_mode();
				break;
			case 0:
				printf("Good bye :)\n");
				return 0;
		}
	}
	return 0;
}

void read_file(){
	FILE* f = fopen("/home/flag.txt", "r");
	fread(flag, sizeof(char), 100, f);
}	


void show_menu(){
	printf("------MENU------\n");
	printf("1. Get Lotto\n");
	printf("2. Delete Lotto\n");
	printf("3. Show Lotto\n");
	printf("4. Show winning lotto number\n");
	printf("5. Compare my lotto number\n");
	printf("0. Exit\n");
	printf("----------------\n");
	printf("Enter: ");
}

char* rand_lotto(int success){
	char* tmp;
	int money = rand()%5 + 1;	
	if (success == -1)
		money = 4;
	else
		printf("You invested %d won!\n", money*100);

	tmp = (char*)malloc(sizeof(char)*money*100);
	
	for(int i=0; i<10; i++){
		char tmp_chr[2];
		if (i!=0)
			strcat(tmp, ", ");
		sprintf(tmp_chr, "%d", rand()%45 + 1);
		strcat(tmp, tmp_chr);
	}
	return tmp;
}

void show_lotto(){
	int cho;
	
	if (num == 0){
		printf("You don't have any lotto.\n");
		printf("Please buy some lotto :).\n");
		return;
	}
	
	printf("Enter a number you want to see\n");
	printf("Now you can see 0 - %d\n", num-1);
	printf("Input: ");
	
	scanf("%d", &cho);
	
	if(cho < 0 || num <= cho){
		printf("Out of bounds :(\n");
		printf("Please input a number 0 - %d\n", num-1);
		return;
	}

	printf("%s\n", lotto_list[cho]);
}

void cheat_mode(char* success_lotto){
	printf("You used a cheat!\n");
	printf("You can input 10 lotto numbers!\n");
	printf("But lotto's number remains the same.\n");
	
	char* cheat_lotto = (char*)malloc(sizeof(char)*400);
	memset(cheat_lotto, 0, 400);

	for(int i=0; i<10; i++){
		char tmp_chr[2];
		if (i!=0)
			strcat(cheat_lotto, ", ");
		int tmp_num;
		scanf("%d", &tmp_num);
		if (tmp_num < 1 || 45 < tmp_num){
			printf("Out of bounds :(\n");
			printf("Please input a number 1 - 45\n");
			return;
		}	
		sprintf(tmp_chr, "%d", tmp_num);
		strcat(cheat_lotto, tmp_chr);
	}

	return;
}

void del_lotto(){
	int cho;

	if (num == 0){
		printf("You don't have any lotto.\n");
		printf("Please buy some lotto :).\n");
		return;
	}
		
	printf("Enter a number you want to see\n");
	printf("Now you can see 0 - %d\n", num-1);
	printf("Input: ");
	
	scanf("%d", &cho);

	if(cho < 0 || num <= cho){
		printf("Out of bounds :(\n");
		printf("Please input a number 0 - %d\n", num-1);
		return;
	}

	if (strcmp(lotto_list[cho], "Empty lotto.") == 0){
		printf("It's already delete\n");
		return;
	}
	
	free(lotto_list[cho]);
	memset(lotto_list[cho], 0, sizeof(lotto_list[cho]));
	strcat(lotto_list[cho],"Empty lotto.");
	
	printf("Now %d lotto is gone\n", cho);

	return;
}

void cmp_lotto(char* success_num){
	//char flag[10] = "tmp flag";
	for (int i=0; i<num; i++)
		if(strcmp(lotto_list[i], success_num) == 0){
			printf("Congraturation! :)\n");
			printf("You get a flag: %s\n", flag);
			exit(0);
		}
	
	printf("There are no lottoes that you won :(\n");
}

