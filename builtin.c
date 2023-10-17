#include "shell.h"

/**
 * _myexit - exiting shell
 * @info: Structure with the  arguments.
 * Return: success
 */
int _myexit(info_t *info)
{
	int exitchecking;

	if (info->argv[1])
	{
		exitchecking = _erratoi(info->argv[1]);
		if (exitchecking == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
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
 * _mycd - changing the directory
 * @info: Structure with the arg.
 * Return: 0 success
 */
int _mycd(info_t *info)
{
	char *t, *dirs, buffer[1024];
	int chdir_rets;

	t = getcwd(buffer, 1024);
	if (!t)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirs = _getenv(info, "HOME=");
		if (!dirs)
			chdir_rets =
				chdir((dirs = _getenv(info, "PWD=")) ? dirs : "/");
		else
			chdir_rets = chdir(dirs);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(t);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_rets =
			chdir((dirs = _getenv(info, "OLDPWD=")) ? dirs : "/");
	}
	else
		chdir_rets = chdir(info->argv[1]);
	if (chdir_rets == -1)
	{
		print_error(info, "can't cd to ");
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
 * _myhelp - changing the  directory
 * @info: Structurewith the args.
 * Return: 0 success
 */
int _myhelp(info_t *info)
{
	char **args_arrays;

	args_arrays = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args_arrays);
	return (0);
}
