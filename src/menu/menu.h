/*
 * menu.h
 *
 *  Created on: 3Feb.,2017
 *      Author: j
 */

#include <commons.h>

#ifndef MENU_MENU_H_
#define MENU_MENU_H_

void dispOptions(void);
Bool process_input(choices * choice);
Bool err_check(char * input, int * no);
Bool get_file_path(char ** filepath);
Bool check_YN(Bool yn);


#endif /* MENU_MENU_H_ */
