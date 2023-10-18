#include "shell.h"

/**
 * _erratoi - converting string to integers
 * @s: string being converted.
 * Return: 0 for no strings -1 if error
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			result *= 10;
			result += (s[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - printing message for error
 * @info: parameter
 * @estr: string with the errors type
 * Return: 0 success  -1 errors
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d -  printing decimal
 * @input: input
 * @fd: filedescriptor
 *
 * Return:  chars printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, counts = 0;
	unsigned int _abs_, currents;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counts++;
	}
	else
		_abs_ = input;
	currents = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + currents / a);
			counts++;
		}
		currents %= a;
	}
	__putchar('0' + currents);
	counts++;

	return (counts);
}

/**
 * convert_number - clon function
 * @num: no
 * @base: base 10
 * @flags: arg flags
 *
 * Return: string for success.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char signs = 0;
	char *ptr;
	unsigned long a = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		a = -num;
		signs = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[a % base];
		a /= base;
	} while (a != 0);

	if (signs)
		*--ptr = signs;
	return (ptr);
}

/**
 * remove_comments - replacing 1st instances
 * @buf: string address.
 *
 * Return: 0 for success
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
