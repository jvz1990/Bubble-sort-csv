/*
 * menu.c
 *
 *  Created on: 3Feb.,2017
 *      Author: j
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	puts(" [3] Sort by amount of Dollars.");
	puts(" [4] Sort by CC number.");
	puts(" [5] Sort by first name.");
	puts(" [6] Sort by last name.");
	puts(" [7] Print list.");
	puts(" [9] Save list.");
	puts(" [10] Exit.\n");
	puts("*******************************\n");
}

Bool err_check(char * input) {
	int no = atoi(input);
	if(no < min_input || no > max_input) return false;
	return true;
}

Bool process_input(choices * choice) {

	char * input = NULL;
	dispOptions();
	input = getline();
	if(err_check(input) == false) {
		*choice = ERR;
		return true;
	}



	printf("\n the input string: [%s] \n", input);
	getchar();

	return false;
}
