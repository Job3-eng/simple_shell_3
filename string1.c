#include "shell.h"

/**
 * _strcpy - coping string
 * @dest: destinations
 * @src: source
 *
 * Return: ptr to destn
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - duplicating string
 * @str: string
 *
 * Return: ptr for  duplicat string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *rets;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	rets = malloc(sizeof(char) * (length + 1));
	if (!rets)
		return (NULL);
	for (length++; length--;)
		rets[length] = *--str;
	return (rets);
}

/**
 * _puts - printing input
 * @str: the str
 *
 * Return: void
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - writting characters
 * @c: char
 *
 * Return: success 1 .for failure -1
 */
int _putchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}
