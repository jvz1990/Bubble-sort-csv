/*
 * menu.h
 *
 *  Created on: 3Feb.,2017
 *      Author: j
 */

#include <commons.h>

#ifndef MENU_MENU_H_
#define MENU_MENU_H_
typedef enum 	{ONE, TWO, THREE,
				FOUR, FIVE, SIX,
				SEVEN, EIGHT, NINE, ERR} choices;

void dispOptions(void);
Bool process_input(choices * choice);
Bool err_check(char * input);


#endif /* MENU_MENU_H_ */
