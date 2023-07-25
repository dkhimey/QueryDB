#include "client_context.h"
#include <string.h>
/* This is an example of a function you will need to
 * implement in your catalogue. It takes in a string (char *)
 * and outputs a pointer to a table object. Similar methods
 * will be needed for columns and databases. How you choose
 * to implement the method is up to you.
 * 
 */
Table* lookup_table(char *name) {
	// TODO: hash table to search for tables
	for (size_t i = 0; i < current_db->tables_size; i++) {
		if (strcmp(current_db->tables[i].name, name) == 0) {
			return current_db->tables + i;
		}
	}
	return NULL;
}

/**
*  Getting started hint:
* 		What other entities are context related (and contextual with respect to what scope in your design)?
* 		What else will you define in this file?
**/
