/*
 * cc_holder.c
 *
 *  Created on: 27Jan.,2017
 *      Author: j
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <commons.h>
#include <cc_holder.h>
#include <util.h>

#define _file2 "C:\\Users\\j\\workspace\\CCcsvParser\\convertcsv_sorted.csv"

Bool init_list(cc_holder_t ** head, char ** filepath) {

	if (*head != NULL) {
		puts("\n\n!!=== ERROR - EXISTING LIST DETECTED ===!!\n\n");
		return false;
	}

	cc_holder_t * tmp_node;

	FILE* input_file = fopen(*filepath, "r");

	char record[1024];
	fields field = last;
	char *tmp, *tok;

	while (fgets(record, 1024, input_file)) {
		tmp = strdup(record);
		field = last;

		if ((tmp_node = malloc(sizeof(cc_holder_t))) == NULL)
			return false;

		for (tok = strtok(tmp, ","); tok && *tok; tok = strtok(NULL, ",\n")) {

			switch (field) {
			case (last):
				tmp_node->last_name = tok;
				break;
			case (first):
				tmp_node->first_name = tok;
				break;
			case (cc_no):
				tmp_node->cc = tok;
				break;
			case (money):
				remove_chars(tok);
				tmp_node->cents = (unsigned int) (atoi(tok));
				break;
			default:
				break;
			}

			field++;
		}

		if (*head == NULL) {
			if ((*head = malloc(sizeof(cc_holder_t))) == NULL)
				return false;
			tmp_node->previous = *head;
			tmp_node->next = *head;
			(*head)->next = tmp_node;
			(*head)->previous = tmp_node;
		} else {
			tmp_node->previous = (*head)->previous;
			tmp_node->next = *head;

			(*head)->previous->next = tmp_node;
			(*head)->previous = tmp_node;
		}

	}

	if (fclose(input_file) == 0)
		return true;
	else
		return false;
}

void destroy_cc_list(cc_holder_t ** head) {

	if (*head == NULL) {
		//puts("\n!!--NO LIST FOUND. PLEASE INITIALIZE!--!!\n");
		return;
	}

	cc_holder_t * temp;
	temp = (*head)->next;
	while (temp != *head) {
		temp = temp->next;
		free(temp->previous);
	}
	free(*head); // destroying head
	*head = NULL; // setting NULL
	temp = NULL;
}

void destroy_list(cc_list_t ** head) {

	if (*head == NULL) {
		//puts("\n!!--NO LIST FOUND. PLEASE INITIALIZE!--!!\n");
		return;
	}

	cc_list_t * temp;
	temp = (*head)->next;
	while (temp != *head) {
		temp = temp->next;
		free(temp->previous);
	}
	free(*head); // destroying head
	*head = NULL; // setting NULL
	temp = NULL;
}

void print_cc_list(cc_holder_t * head) {

	if (head == NULL) {
		puts("\n!!--NO LIST FOUND. PLEASE INITIALIZE!--!!\n");
		return;
	}

	int i = 0;
	cc_holder_t * current = head->next;
	int c = 0;

	while (current != head) {
		c = current->cents % 100;
		printf("Object no. [%i] with person [%s %s] has cc no [%s] and has [$%d%s%d]\n",
				i++, current->first_name,
				current->last_name,
				current->cc,
				(unsigned int) (current->cents / 100),
				(c < 10) ? ".0" : ".",
				c);
		current = current->next;

	}
}

void print_list(cc_list_t * head) {
	if(head == NULL) {
		if (head == NULL) {
			puts("\n!!--NO LIST FOUND. PLEASE INITIALIZE!--!!\n");
			return;
		}
	}

	int i = 0;
	cc_list_t * current = head->next;
	int c = 0;

	while (current != head) {
		c = current->obj->cents % 100;
		printf("Object no. [%i] with person [%s %s] has cc no [%s] and has [$%d%s%d]\n",
				i++, current->obj->first_name,
				current->obj->last_name,
				current->obj->cc,
				(unsigned int) (current->obj->cents / 100),
				(c < 10) ? ".0" : ".",
				c);
		current = current->next;

	}
}

void remove_chars(char *str) {
	char *read = str, *write = str;
	while (*read) {
		//write same position as read
		*write = *read++;
		//write does not include characters below
		write += ((*write != ',') && (*write != '$') && (*write != '.'));
	}
	*write = '\0';
	str = write;
}

void bubbleSort(cc_holder_t * head, choices * choice) {

	/*
	 * Essentially start from the head and find an item to 'bubble up'
	 * until there are items to 'bubble up'.
	 * TODO optimize algorithm to exclude highest values -> need counter and chain size counter
	 */
	int i = 0;
	if(head == NULL) {
		puts("\nPlease load a csv file first.\n");
		return;
	}
	while (1) {
		if (bubbleSortInner(head, choice) == false)
			break;
		i++;
	}

	printf("Number of outer iterations [%i]\n", i);

}

Bool swap(cc_holder_t * cur, choices * choice) {

	switch (*choice) {
		 case THREE:
			 if(cur->cents > cur->next->cents) return true;
			 break;
		 case FOUR:
			 if(strcmp(cur->first_name, cur->next->first_name) > 0) return true;
			 break;
		 case FIVE:
			 //printf("1: [%s], 2: [%s]\n",cur->last_name, cur->next->last_name);
			 if(strcmp(cur->last_name, cur->next->last_name) > 0) return true;
			 break;
		 case SIX:
			 if(strcmp(cur->cc, cur->next->cc) > 0) return true;
			 break;
		 default:
			 puts("\n Programmer Error\n");
			 break;
	}

	return false;
}

Bool bubbleSortInner(cc_holder_t * head, choices * choice) {

	// Update. Can look confusing but pointer swap is do able.
	/*
	 * Have to consider 4 elements, previous (1), current (2), next(3) & next->next (4)
	 * So swap positions 2 & 3. 1 & 4 have to be corrected as well (prev/next ptr)
	 *
	 * 4.previous = 2 //outer 2
	 * 1.next = 3
	 *
	 * 2.next = 4
	 * 2.previous = 1
	 *
	 * 3.previous = 1
	 * 3.next = 2
	 *	 */

	Bool swapped = false;
	cc_holder_t *first = NULL,
				//*second = NULL,
				*third = NULL,
				*fourth = NULL,
				*node = head->next;
	//UInt i = 0;

	while (node->next != head) {
		if (swap(node, choice) == true) {

			first = node->previous;
			//second = node;
			third = node->next;
			fourth = node->next->next;

			//outers
			fourth->previous = node; //4 to 2
			first->next = third; //1 to 3

			third->previous = first; // 3 to 1
			third->next = node; // 3 to 2

			node->next = fourth; //2 to 4
			node->previous = third; //2 to 3

			swapped = true;
		} else {
			node = node->next;
		}
		//i++;
	}
	//printf("number of inner iterations [%d]\n", i);
	return swapped;
}

Bool writeToFile(cc_holder_t * head, char * filepath) {

	int len = strlen(filepath) + 6;

	char * newfile = NULL;
	newfile = malloc(len);
	strncpy(newfile, filepath, len - 10);
	strcat(newfile, "(copy).csv");

	FILE* output_file = fopen(newfile, "w");
	int c = 0;
	cc_holder_t * node = head->next;

	while (node != head) {
		c = node->cents % 100;
		fprintf(output_file,
				"%s,%s,%s,$%d%s%d\n",
				node->last_name,
				node->first_name,
				node->cc, (unsigned int) (node->cents / 100),
				(c < 10) ? ".0" : ".", c);

		node = node->next;
	}

	if (fclose(output_file) == 0) {
		printf("\nSuccessfully written list to file:\n%s\n", newfile);
		return true;
	}
	else
		return false;
}

void searchPerson(cc_holder_t * head) {
	cc_holder_t * node = head->next;
	cc_list_t * node_list = NULL, * node_list_head = NULL;

	puts("Please enter search string:\n");

	char * entry = getline();
	puts("Searching...\n");

	while(node != head) {

		if(strstr(node->first_name, entry) != NULL || strstr(node->last_name, entry) != NULL) {

			if(node_list_head == NULL) {
				node_list_head = malloc(sizeof(cc_list_t));
				node_list = malloc(sizeof(cc_list_t));

				node_list->previous = node_list_head;
				node_list->next = node_list_head;

				node_list_head->next = node_list;
				node_list_head->previous = node_list;

				node_list->obj = node;

			} else {

				node_list->next = malloc(sizeof(cc_list_t));
				node_list->next->previous = node_list;
				node_list->next->next = node_list_head;
				node_list_head->previous = node_list->next;

				node_list = node_list->next;
				node_list->obj = node;

			}
		}
		node = node->next;
	}

	free(entry);
	entry = NULL;

	puts("Results found:\n");
	print_list(node_list_head);

	destroy_list(&node_list_head);

}
