#include "shell.h"

/**
 * input_buf - buffs commands
 * @info: param structure
 * @buf: address
 * @len: length of  var
 *
 * Return: bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t length_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buf, &length_p, stdin);
#else
		a = _getline(info, buf, &length_p);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0';
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - getting line
 * @info: parameter structure
 *
 * Return: byte
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t m, n, lens;
	ssize_t a = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	a = input_buf(info, &buf, &lens);
	if (a == -1)
		return (-1);
	if (lens)
	{
		n = m;
		p = buf + m;

		check_chain(info, buf, &n, m, lens);
		while (n < lens)
		{
			if (is_chain(info, buf, &n))
				break;
			n++;
		}

		m = n + 1;
		if (m >= lens)
		{
			m = lens = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (a);
}

/**
 * read_buf - reading a  buff
 * @info: param structure
 * @buf: buffers
 * @i: the size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t  a = 0;

	if (*i)
		return (0);
	a = read(info->readfd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}

/**
 * _getline - getting inputs next line
 * @info: param structure
 * @ptr: ptr  address
 * @length: size
 *
 * Return: size
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, lens;
	size_t l;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == lens)
		a = lens = 0;

	r = read_buf(info, buf, &lens);
	if (r == -1 || (r == 0 && lens == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	l = c ? 1 + (unsigned int)(c - buf) : lens;
	new_p = _realloc(p, s, s ? s + l : l + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + a, l - a);
	else
		_strncpy(new_p, buf + a, l - a + 1);

	s += l - a;
	a = l;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocking handlers ctrl-C
 * @sig_num: signal no.
 *
 * Return: empty
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

