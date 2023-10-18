#include "shell.h"

/**
 * interactive - returning true for  shell in interactive mode system.
 * @info:address  structure
 *
 * Return: 1 interactive, 0 if not
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checking for a delimeter
 * @c: character to be  checked
 * @delim: delimeter
 * Return: 1 for  true and  0 for false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checking alphabetic characters
 * @c: char input
 * Return: 1  alphabet, 0 false
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converting strings integers
 * @s: string
 * Return: 0 true,  otherwise
 */

int _atoi(char *s)
{
	int a, signs = 1, flags = 0, outputs;
	unsigned int results = 0;

	for (a = 0; s[a] != '\0' && flags != 2; a++)
	{
		if (s[a] == '-')
			signs *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flags = 1;
			results *= 10;
			results += (s[a] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (signs == -1)
		outputs = -results;
	else
		outputs = results;

	return (outputs);
}
