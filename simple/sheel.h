#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h> /* for printf */
#include <unistd.h> /* for fork, execve */
#include <stdlib.h>
#include <string.h> /* for strtok */
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files */

/************* MACROS **************/
#ifndef CUSTOM_COMMANDS_H
#define CUSTOM_COMMANDS_H

/* Prompt to be printed */
#define PROMPT_MSG "$" /* Used as a shell prompt */

/* Unused attribute for variables */
#define UNUSED __attribute__((unused))

/* Buffer size for each read call in get */
#define BUFFER_SIZE 1024

/************* FORMATTED STRINGS FOR CUSTOM BUILT-IN COMMANDS **************/

#define CUSTOM_HELP_CD_MSG "cd=\n" \
"cd:\tcd [directory]\n\n" \
"	Change the current working directory.\n\n" \
"	If no directory argument is provided, the command will interpret it as 'cd $HOME'.\n" \
"	If the argument is '-', the command will interpret it as 'cd $OLDPWD'.\n\n"

#define CUSTOM_HELP_EXIT_MSG "exit=\n" \
"exit:\texit [STATUS]\n\n" \
"	Exit the custom shell.\n\n" \
"	Exits the shell with an optional exit status 'STATUS'. If 'STATUS' is omitted,\n" \
"	the exit status will be that of the last executed command.\n\n"

#define CUSTOM_HELP_ENV_MSG "env=\n" \
"env:\tenv\n\n" \
"	Print the environment variables.\n\n" \
"	The 'env' command prints a complete list of environment variables.\n\n"

#define CUSTOM_HELP_SETENV_MSG "setenv=\n" \
"setenv:\tsetenv VARIABLE VALUE\n\n" \
"	Change or add an environment variable.\n\n" \
"	Initialize a new environment variable or modify an existing one.\n" \
"	Prints an error message when the correct number of arguments is not provided.\n\n"

#define CUSTOM_HELP_UNSETENV_MSG "unsetenv=\n" \
"unsetenv:\tunsetenv VARIABLE\n\n" \
"	Delete an environment variable.\n\n" \
"	The 'unsetenv' function deletes a specified variable from the environment.\n" \
"	Prints an error message when the correct number of arguments is not provided.\n\n"

#define CUSTOM_HELP_MSG "help=\n" \
"help:\thelp [BUILTIN_NAME]\n\n" \
"	Display information about custom built-in commands.\n\n" \
"	Displays brief summaries of custom built-in commands. If 'BUILTIN_NAME' is\n" \
"	specified, it provides detailed help for the specified command, otherwise,\n" \
"	it lists available custom built-in commands.\n\n" \
"	Available custom built-in commands:\n\n" \
"	cd\t[directory]\n" \
"	exit\t[status]\n" \
"	env\n" \
"	setenv\t[variable value]\n" \
"	unsetenv\t[variable]\n" \
"	help\t[built_name]\n\n"

#endif

/************* STRUCTURES **************/

/**
 * struct ShellData - Structure to hold shell program data.
 * @program_name: The name of the shell executable.
 * @input_line: Pointer to the input read by _getline.
 * @command_name: Pointer to the first command typed by the user.
 * @exec_counter: Number of executed commands.
 * @file_descriptor: File descriptor for command input.
 * @tokens: Pointer to an array of tokenized input.
 * @env: Copy of the environment variables.
 * @alias_list: Array of pointers to aliases.
 */
typedef struct ShellData
{
    char *program_name;
    char *input_line;
    char *command_name;
    int exec_counter;
    int file_descriptor;
    char **tokens;
    char **env;
    char **alias_list;
} CustomShellData;

/**
 * struct ShellBuiltins - Structure for shell built-in commands.
 * @builtin: The name of the built-in command.
 * @function: Pointer to the associated function for the built-in.
 */
typedef struct ShellBuiltins
{
    char *builtin;
    int (*function)(CustomShellData *data);
} ShellBuiltins;

/************* MAIN FUNCTIONS *************/

/*========  custom_shell.c  ========*/

/* Initialize the CustomShellData structure with program information */
void initializeData(CustomShellData *data, int argc, char *argv[], char **env);

/* Main loop that displays the shell prompt */
void runShell(char *prompt, CustomShellData *data);

/* Print the prompt on a new line */
void handleCtrlC(int operation UNUSED);

/*========  custom_getline.c  ========*/

/* Read one line from standard input */
int custom_getline(CustomShellData *data);

/* Split each line based on logical operators if they exist */
int check_logical_operators(char *array_commands[], int i, char array_operators[]);

/*======== custom_expansions.c ========*/

/* Expand variables in the input */
void expandVariables(CustomShellData *data);

/* Expand aliases in the input */
void expandAliases(CustomShellData *data);

/* Append a string to the end of the buffer */
int bufferAdd(char *buffer, char *str_to_add);

/*======== custom_strtok.c ========*/

/* Separate the input string into tokens using a specified delimiter */
void customTokenizer(CustomShellData *data);

/* Create a pointer to a part of a string */
char *customStrtok(char *line, char *delimiter);

/*======== custom_execute.c ========*/

/* Execute a command with its full path */
int executeCommand(CustomShellData *data);

/*======== custom_builtins_list.c ========*/

/* Check if a command is a built-in and execute it */
int executeBuiltin(CustomShellData *data);

/*======== custom_find_in_path.c ========*/

/* Create an array of path directories */
char **tokenizePath(CustomShellData *data);

/* Search for a program in the PATH */
int findProgramInPath(CustomShellData *data);

/************** MEMORY MANAGEMENT HELPERS **************/

/*======== custom_memory_free.c ========*/

/* Free memory for arrays of pointers */
void free_pointer_array(char **array);

/* Free fields that need to be cleared for each loop iteration */
void free_recurring_data(CustomShellData *data);

/* Free all data fields */
void free_all_shell_data(CustomShellData *data);

/************** SHELL BUILT-IN FUNCTIONS **************/

/*======== custom_builtins_more.c ========*/

/* Terminate the shell */
int exitShell(CustomShellData *data);

/* Change the current directory */
int changeDirectory(CustomShellData *data);

/* Set the working directory */
int setWorkingDirectory(CustomShellData *data, char *new_dir);

/* Display help information */
int displayHelp(CustomShellData *data);

/* Set, unset, and display aliases */
int manageAliases(CustomShellData *data);

/*======== enviromt.c ========*/

/* Display the environment where the shell runs */
int showEnvironment(CustomShellData *data);

/* Create or update an environment variable */
int setEnvironmentVariable(CustomShellData *data);

/* Delete an environment variable */
int unsetEnvironmentVariable(CustomShellData *data);

/************** ENVIRONMENT VARIABLE MANAGEMENT HELPERS **************/

/*======== custom_env_management.c ========*/

/* Get the value of an environment variable */
char *getEnvironmentVariable(char *name, CustomShellData *data);

/* Set the value of an environment variable */
int setenvironmentVariable(char *key, char *value, CustomShellData *data);

/* Remove an environment variable */
int removeEnvironmentVariable(char *key, CustomShellData *data);

/* Print the current environment variables */
void printEnvironment(CustomShellData *data);

/************** PRINTING HELPERS **************/

/*======== custom_print_helpers.c ========*/

/* Print a string to standard output */
int printToStdout(char *string);

/* Print a string to standard error */
int printToStderr(char *string);

/* Print an error message with a specific error code */
int printErrorMessage(int error_code, CustomShellData *data);

/************** STRING MANAGEMENT HELPERS **************/

/*======== custom_string_helpers.c ========*/

/* Get the length of a string */
int strLength(char *string);

/* Duplicate a string */
char *strDuplicate(char *string);

/* Compare two strings */
int strCompare(char *string1, char *string2, int num);

/* Concatenate two strings */
char *strConcat(char *string1, char *string2);

/* Reverse a string */
void strReverse(char *string);

/*======== custom_number_helpers.c ========*/

/* Convert a long integer to a string */
void convertLongToString(long number, char *string, int base);

/* Convert a string to an integer */
int parseInt(char *s);

/* Count occurrences of a character in a string */
int countCharacterOccurrences(char *string, char *character);

/*======== custom_alias_management.c ========*/

/* Print the list of aliases */
int showAliases(CustomShellData *data, char *alias);

/* Get the alias name */
char *getAliasValue(CustomShellData *data, char *alias);

/* Set an alias */
int setAlias(char *alias_string, CustomShellData *data);

#endif /* _SHEEL_H */

