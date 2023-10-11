#include "shell.h"

/**
 * _strlen - returning the  string length
 * @s: string
 *
 * Return: int len
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmp - performing comparisons of  strangs.
 * @s1: 1st strang
 * @s2: 2nd strang
 *
 * Return: 1 for -ve,>2 for +ve
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checking start for haystack.
 * @haystack: string
 * @needle: found str.
 *
 * Return: next character address.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenating strings
 * @dest: destina buf
 * @src: source
 *
 * Return: dstn pointer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
