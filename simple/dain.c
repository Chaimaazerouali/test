#include "shell.h"

/**
 * shellMain - Entry point of the shell program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * @env: Array of environment variables.
 * Return: Always returns 0 on successful execution.
 */
int shellMain(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *shell_prompt = "";

	initializeData(data, argc, argv, env);

	signal(SIGINT, handleCtrlC);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		shell_prompt = PROMPT_MSG;
	}
	errno = 0;
	runShell(shell_prompt, data);
	return (0);
}

/**
 * handleCtrlC - Handles the SIGINT signal (Ctrl+C).
 * @signal: Signal number (unused parameter).
 */
void handleCtrlC(int signal UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initializeData - Initializes the data structure with program information.
 * @data: Pointer to the data_of_program structure.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * @env: Array of environment variables.
 */
void initializeData(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = strDuplicate(env[i]);
		}
	}
	data->env[i] = NULL;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * runShell - Main loop of the shell program.
 * @prompt: The shell prompt string.
 * @data: Pointer to the data_of_program structure.
 */
void runShell(char *prompt, data_of_program *data)
{
	int errorCode = 0, lineLength = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		errorCode = lineLength = _getline(data);

		if (errorCode == EOF)
		{
			freeAllData(data);
			exit(errno);
		}
		if (lineLength >= 1)
		{
			expandAliases(data);
			expandVariables(data);
			tokenize(data);
			if (data->tokens[0])
			{
				errorCode = execute(data);
				if (errorCode != 0)
					_printError(errorCode, data);
			}
			freeRecurrentData(data);
		}
	}
}

