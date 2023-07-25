#include "cs165_api.h"
#include <string.h>

// In this class, there will always be only one active database at a time
Db *current_db;

#define DEFAULT_TABLE_LENGTH 128

Column* create_column(Table *table, char *name, bool sorted, Status *ret_status) {
	(void) sorted;
	// TODO: hash table search for existing column
	if (table->col_capacity == table->col_count) {
		ret_status->code = ERROR;
		ret_status->error_message = "Table is full.";
		return NULL;
	}

	Column* next_column = table->columns + table->col_count;
	strcpy(next_column->name, name);
	// TODO: assuming all columns will hold ints
	next_column->data = malloc(table->table_length * sizeof(int));
	if (!next_column->data) {
		ret_status->code = NOMEM;
		return NULL;
	}

	ret_status->code = OK;
	return next_column;
}

/* 
 * Here you will create a table object. The Status object can be used to return
 * to the caller that there was an error in table creation
 */
Table* create_table(Db* db, const char* name, size_t num_columns, Status *ret_status) {
	// TODO: hash table search for existing table
	if (db->tables_capacity == db->tables_size) {
		// need to increase size of db
		Table* new_tables = malloc(2 * db->tables_capacity * sizeof(Table));
		if (!new_tables) {
			ret_status->code = NOMEM;
			return NULL;
		}

		memcpy(new_tables, db->tables, db->tables_capacity * sizeof(Table));
		// TODO: can memcpy fail?
		free(db->tables);
		db->tables = new_tables;
		db->tables_capacity *= 2;
	}

	// add table in next available slot
	Table* next_table = db->tables + db->tables_size;
	next_table->columns = malloc(num_columns * sizeof(Column));
	// TODO: potential memory leak, find place to free
	if (!next_table->columns) {
		ret_status->code = NOMEM;
		return NULL;
	}
	next_table->col_capacity = num_columns;
	next_table->col_count = 0;
	next_table->table_length = DEFAULT_TABLE_LENGTH;
	strcpy(next_table->name, name);
	db->tables_size++;

	ret_status->code = OK;
	return next_table;
}

/* 
 * Similarly, this method is meant to create a database.
 */
Status create_db(const char* db_name) {
	struct Status ret_status;
	ret_status.code = OK;

	if (current_db != NULL) {
		ret_status.code = ERROR;
	} else {
		current_db = malloc(sizeof(Db));
		// TODO: potential memory leak
		if (!current_db) {
			ret_status.code = NOMEM;
		} else {
			strcpy(current_db->name, db_name);
		}
	}

	return ret_status;
}
