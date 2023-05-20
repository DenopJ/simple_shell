#include "shell.h"

/**
 * _kshexit - exit the shell
 * @info: Structure containing potential arguments used to maintain
 * constant function prototype.
 * Return: exit with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _kshexit(info_t *info)
{
	int checkexit;

	if (info->argv[1])
	{
		checkexit = _erratoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			print_error(info, "unaccepted number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _kshcd - change the current directory of the process
 * @info: Structure containing potential arguments used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _kshcd(info_t *info)
{
	char *g, *dir, buffer[1024];
	int chngdir_ret;

	g = getcwd(buffer, 1024);
	if (!g)
	_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chngdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chngdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(g);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chngdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chngdir_ret = chdir(info->argv[1]);
	if (chngdir_ret == -1)
	{
		print_error(info, "can't cd into ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _kshhelp - change the current directory of the process
 * @info: Structure containing potential arguments used to maintain
 * the constant function prototype.
 * Return: Always 0
 */
int _kshhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
