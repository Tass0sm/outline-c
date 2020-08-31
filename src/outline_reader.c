#include "outline_reader.h"

/* File I/O */

// Open outline file.
outline_file * outline_open_file(char * fileName, char * perm) {
	outline_file * result = malloc(sizeof(outline_file));

	result->realFile = fopen(fileName, perm);
	result->previousChar = '\n';
	result->currentLevel = 0;

	if (result->realFile == NULL) {
		result = NULL;
	}

	return result;
}

// Free outline file.
void outline_free_file(outline_file * pFile) {
	fclose(pFile->realFile);
	free(pFile);
}

/* Metrics */

// Get the level of the most recently traversed heading. Initally 0.
int outline_level(outline_file * pFile) {
	return pFile->currentLevel;
}

/* Heading Seeking */

// Seek in the file to the next heading.
int outline_seek_next_heading(outline_file * pFile) {

	char currentLine[OUTLINE_MAX_LINE_LEN];
	bool done = false;
	int result = 1;

	// Read at least one line to move to the next heading.
	do {

		fgets(currentLine, OUTLINE_MAX_LINE_LEN, pFile->realFile);

		if (outline_is_heading(currentLine)) {
			printf("%s", currentLine);
			result = 0;
			done = true;
		}

	} while (!feof(pFile->realFile) && !done);

	return result;
}

// Seek in the file to the next heading with the given level.
int outline_seek_next_leveled_heading(outline_file * pFile, int level) {

	char currentLine[OUTLINE_MAX_LINE_LEN];
	bool done = false;
	int result = 1;

	// Read at least one line to move to the next heading.
	do {

		fgets(currentLine, OUTLINE_MAX_LINE_LEN, pFile->realFile);

		if (outline_is_leveled_heading(currentLine, level)) {
			printf("%s", currentLine);
			result = 0;
			done = true;
		}

	} while (!feof(pFile->realFile) && !done);

	return result;
}

// Seek in the file to the next heading with the given name.
int outline_seek_next_named_heading(outline_file * pFile, char * name) {

	char currentLine[OUTLINE_MAX_LINE_LEN];
	bool done = false;
	int result = 1;

	// Read at least one line to move to the next heading.
	do {

		fgets(currentLine, OUTLINE_MAX_LINE_LEN, pFile->realFile);

		if (outline_is_named_heading(currentLine, name)) {
			printf("%s", currentLine);
			result = 0;
			done = true;
		}

	} while (!feof(pFile->realFile) && !done);

	return result;
}

/* Printing Functions */

// Print the file contents to the next heading.
void outline_print_to_next_heading(outline_file * pFile) {

	char currentLine[OUTLINE_MAX_LINE_LEN];
	bool done = false;

	// Read at least one line to move to the next heading.
	do {

		fgets(currentLine, OUTLINE_MAX_LINE_LEN, pFile->realFile);
		if (!outline_is_heading(currentLine)) {
			printf("%s", currentLine);
		} else {
			done = true;
		}

	} while (!feof(pFile->realFile) && !done);
}

// Print the file contents to the next heading with the given level.
void outline_print_to_next_leveled_heading(outline_file * pFile, int level) {

	char currentLine[OUTLINE_MAX_LINE_LEN];
	bool done = false;

	// Read at least one line to move to the next heading.
	do {

		fgets(currentLine, OUTLINE_MAX_LINE_LEN, pFile->realFile);
		if (!outline_is_leveled_heading(currentLine, level)) {
			printf("%s", currentLine);
		} else {
			done = true;
		}

	} while (!feof(pFile->realFile) && !done);
}

// Print the file contents to the next heading with the given name.
void outline_print_to_next_named_heading(outline_file * pFile, char * name) {

	char currentLine[OUTLINE_MAX_LINE_LEN];
	bool done = false;

	// Read at least one line to move to the next heading.
	do {

		fgets(currentLine, OUTLINE_MAX_LINE_LEN, pFile->realFile);
		if (!outline_is_named_heading(currentLine, name)) {
			printf("%s", currentLine);
		} else {
			done = true;
		}

	} while (!feof(pFile->realFile) && !done);
}

/* Heading Tests */

// Does the line have a heading prefix of the given level.
bool outline_is_heading(char * line) {
	bool result = true;
	int i = 0;

	do {
		if (line[i] != '*') {
			result = false;
		}

		i++;
	} while (line[i] != ' ' && result);

	return result;
}

// Does the line have a heading prefix of the given level.
bool outline_is_leveled_heading(char * line, int level) {
	bool result = true;

	int i;
	for (i = 0; i < level && result; i++) {
		if (line[i] != '*') {
			result = false;
		}
	}

	if (line[i] != ' ' && result) {
		result = false;
	}

	return result;
}

// Does the line have a heading prefix with the given name.
bool outline_is_named_heading(char * line, char * name) {
	bool result = true;
	int i = 0;

	do {
		if (line[i] != '*') {
			result = false;
			// Yes, this goto is fine.
			goto end;
		}

		i++;
	} while (line[i] != ' ');

	i++;
	int j = 0;

	do {
		if (line[i] != name[j]) {
			result = false;
			goto end;
		}

		i++;
		j++;
	} while (line[i] > '\n' && line[j] > '\n');

 end:
	return result;
}
