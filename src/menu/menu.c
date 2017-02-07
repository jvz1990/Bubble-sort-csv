/*
 * menu.c
 *
 *  Created on: 3Feb.,2017
 *      Author: j
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include <menu.h>
#include <util.h>
#include <commons.h>


#define min_input  1
#define max_input 10

void dispOptions(void) {
	puts("\n******* CC Parser Demo *******\n");
	puts("Menu:\n");
	puts(" [1] Select csv file.");
	puts(" [2] Load csv file.");
	puts(" \n Account Sorting Options:\n");
	puts(" [3] Sort by amount of dollars.");
	puts(" [4] Sort by first name.");
	puts(" [5] Sort by last name.");
	puts(" [6] Sort by CC number.");
	puts(" [7] Display list.");
	puts(" [8] Search for persons.");
	puts(" [9] Save list.");
	puts(" [10] Exit.\n");
	puts("*******************************\n");
}

Bool err_check(char * input, int * no) {
	*no = atoi(input);
	if(*no < min_input || *no > max_input || *no == 0) return false;
	return true;
}

Bool process_input(choices * choice) {

	char * input = NULL;
	int no;
	dispOptions();
	input = getline();

	if(err_check(input, &no) == false) {
		*choice = ERR;
		return true;
	}

	switch(no) {
		case(1):
			*choice = ONE;
			break;
		case(2):
			*choice = TWO;
			break;
		case(3):
			*choice = THREE;
			break;
		case(4):
			*choice = FOUR;
			break;
		case(5):
			*choice = FIVE;
			break;
		case(6):
			*choice = SIX;
			break;
		case(7):
			*choice = SEVEN;
			break;
		case(8):
			*choice = EIGHT;
			break;
		case(9):
			*choice = NINE;
			break;
		case(10):
			return false;
			break;
	}

	return true;
}

Bool get_file_path(char ** filepath) {
	puts(" *Please copy and paste exact file location:\n");
	*filepath = getline();
	if(access(*filepath, F_OK) != -1) return true;
	else return false;

	return false;
}

Bool check_YN(Bool yn) {

	char * input_str = NULL;
	char ans;

	do {

		puts((yn == true) ? "[Y]/n" : "y/[N]");
		input_str = getline();
		ans = toupper(*input_str);

	} while(ans != 'Y' && ans != 'N');

	return (ans == 'Y') ? true : false;
}
