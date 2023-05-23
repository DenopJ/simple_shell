#include "shell.h"

/**
 * _kshenv - print the current environment
 * @info: Structure containing the potential arguments used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _kshenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - get the value of an environ variable
 * @info: Structure containing potential arguments which is used to maintain
 * @name: env var name
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _kshsetenv - Initializes a new environment variable,
 * or modify an existing environment
 * @info: Structure containing the potential argument which is used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _kshsetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _kshunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments which is used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _kshunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_kshenv_list - populates an env linked list
 * @info: Structure containing potential arguments which is used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int populate_kshenv_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

