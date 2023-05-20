#include "shell.h"

/**
 * ksh - main shell loop
 * @info: the parameter and return info struct
 * @av: the argument vector from the main()
 * Return: 0 on success, 1 on error, or error code
 */
int ksh(info_t *info, char **av)
{
	ssize_t b = 0;
	int builtin_ret = 0;

	while (b != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		b = get_input(info);
		if (b != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds  builtin commands
 * @info: the parameter the return info struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int a, built_in_ret = -1;
	builtin_table builtintbl[] = {
	{"exit", _kshexit},
	{"env", _kshenv},
	{"help", _kshhelp},
	{"history", _kshhistory},
	{"setenv", _kshsetenv},
	{"unsetenv", _kshunsetenv},
	{"cd", _kshcd},
	{"alias", _kshalias},
	{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[a].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - find a command in PATH
 * @info: the parameter and returns info struct
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!ks_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && ks_cmd(info, info->argv[0]))
				fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an exec thread to run cmd
 * @info: the parameter and return info struct
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;
	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
