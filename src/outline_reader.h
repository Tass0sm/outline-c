#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <regex.h>

// This is taken from the org-outline-regexp variable.
// It describes any length string of asterisks with a final space.
#define OUTLINE_REGEXP "\\*+ "
#define OUTLINE_LEVELED_REGEXP "\\*{1,1} "

// The max line length in a valid input file.
#define OUTLINE_MAX_LINE_LEN 100

/* Global Variables */
typedef struct {
	FILE * realFile;
	char previousChar;
	int currentLevel;
} outline_file;

/* File Functions */

// Open outline file.
outline_file * outline_open_file(char * fileName, char * perm);

// Free outline file.
void outline_free_file(outline_file * pFile);

/* Info Functions */

// Get the level of the most recently traversed heading. Initally 0.
int outline_level(outline_file * pFile);

/* Movement Functions */

// Seek in the file to the next heading.
int outline_seek_next_heading(outline_file * pFile);

// Seek in the file to the next heading with the given level.
int outline_seek_next_leveled_heading(outline_file * pFile, int level);

// Seek in the file to the next heading with the given name.
int outline_seek_next_named_heading(outline_file * pFile, char * name);

/* Printing Functions */

// Print the file contents to the next heading.
void outline_print_to_next_heading(outline_file * pFile);

// Print the file contents to the next heading with the given level.
void outline_print_to_next_leveled_heading(outline_file * pFile, int level);

// Print the file contents to the next heading with the given name.
void outline_print_to_next_named_heading(outline_file * pFile, char * name);

/* Heading Tests */

// Does the line have a heading prefix.
bool outline_is_heading(char * line);

// Does the line have a heading prefix of the given level.
bool outline_is_leveled_heading(char * line, int level);

// Does the line have a heading prefix with the given name.
bool outline_is_named_heading(char * line, char * name);
