#ifndef CUSTOM_COMMANDS_H
#define CUSTOM_COMMANDS_H

/* Prompt to be printed */
#define PROMPT_MSG "$" /* Used as a shell prompt */

/* Unused attribute for variables */
#define UNUSED __attribute__((unused))

/* Buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/************* FORMATTED STRINGS FOR CUSTOM BUILT-IN COMMANDS **************/

#define CUSTOM_HELP_CD_MSG "cd=\n"\
"cd:\tcd [directory]\n\n"\
"	Change the current working directory.\n\n"\
"	If no directory argument is provided, the command will interpret it as 'cd $HOME'.\n"\
"	If the argument is '-', the command will interpret it as 'cd $OLDPWD'.\n\n"

#define CUSTOM_HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit the custom shell.\n\n"\
"	Exits the shell with an optional exit status 'STATUS'. If 'STATUS' is omitted,\n"\
"	the exit status will be that of the last executed command.\n\n"

#define CUSTOM_HELP_ENV_MSG "env=\n"\
"env:\tenv\n\n"\
"	Print the environment variables.\n\n"\
"	The 'env' command prints a complete list of environment variables.\n\n"

#define CUSTOM_HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	Initialize a new environment variable or modify an existing one.\n"\
"	Prints an error message when the correct number of arguments is not provided.\n\n"

#define CUSTOM_HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	Delete an environment variable.\n\n"\
"	The 'unsetenv' function deletes a specified variable from the environment.\n"\
"	Prints an error message when the correct number of arguments is not provided.\n\n"

#define CUSTOM_HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display information about custom built-in commands.\n\n"\
"	Displays brief summaries of custom built-in commands. If 'BUILTIN_NAME' is\n"\
"	specified, it provides detailed help for the specified command, otherwise,\n"\
"	it lists available custom built-in commands.\n\n"\
"	Available custom built-in commands:\n\n"\
"	cd\t[directory]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unsetenv\t[variable]\n"\
"	help\t[built_name]\n\n"

#endif

