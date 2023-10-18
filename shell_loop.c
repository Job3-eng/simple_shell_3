#include "shell.h"

/**
 * hsh - the main entry for loop
 * @info: structure param
 * @av:  arg
 *
 * Return: 0 success, 1 otherwise.
 */
int hsh(info_t *info, char **av)
{
	ssize_t a = 0;
	int builtin_rets = 0;

	while (a != -1 && builtin_rets != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		a = get_input(info);
		if (a != -1)
		{
			set_info(info, av);
			builtin_rets = find_builtin(info);
			if (builtin_rets == -1)
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
	if (builtin_rets == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_rets);
}

/**
 * find_builtin - finding cmd
 * @info: structure param
 *
 * Return: -1 not,0 success,1 nota success,2 exit()
 */
int find_builtin(info_t *info)
{
	int a, built_in_rets = -1;
	builtin_table builtintbl[] = {
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL},
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			built_in_rets = builtintbl[a].func(info);
			break;
		}
	return (built_in_rets);
}

/**
 * find_cmd - finding cmd
 * @info: the parameter  structure
 *
 * Return: empty
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int a, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, l = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			l++;
	if (!l)
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
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forking cmd
 * @info: the parameter structure
 *
 * Return: empty
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

