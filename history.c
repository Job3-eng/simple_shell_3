#include "shell.h"

/**
 * get_history_file - getting file history
 * @info: param structure
 *
 * Return: allocatting  string for file history
 */

char *get_history_file(info_t *info)
{
	char *bufs, *dirs;

	dirs = _getenv(info, "HOME=");
	if (!dirs)
		return (NULL);
	bufs = malloc(sizeof(char) * (_strlen(dirs) + _strlen(HIST_FILE) + 2));
	if (!bufs)
		return (NULL);
	bufs[0] = 0;
	_strcpy(bufs, dirs);
	_strcat(bufs, "/");
	_strcat(bufs, HIST_FILE);
	return (bufs);
}

/**
 * write_history - creating a file
 * @info: param structure
 *
 * Return: 1 success,  -1 otherwise
 */
int write_history(info_t *info)
{
	ssize_t fds;
	char *filenames = get_history_file(info);
	list_t *node = NULL;

	if (!filenames)
		return (-1);

	fds = open(filenames, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenames);
	if (fds == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fds);
		_putfd('\n', fds);
	}
	_putfd(BUF_FLUSH, fds);
	close(fds);
	return (1);
}

/**
 * read_history - readimg file  history
 * @info: param structures
 *
 * Return:counting for  success, 0 failure.
 */
int read_history(info_t *info)
{
	int a, lasts = 0, linecounts = 0;
	ssize_t fds, rd_len, f_size = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fds = open(filename, O_RDONLY);
	free(filename);
	if (fds == -1)
		return (0);
	if (!fstat(fds, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (f_size + 1));
	if (!buf)
		return (0);
	rd_len = read(fds, buf, f_size);
	buf[f_size] = 0;
	if (rd_len <= 0)
		return (free(buf), 0);
	close(fds);
	for (a = 0; a < f_size; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history_list(info, buf + lasts, linecounts++);
			lasts = a + 1;
		}
	if (lasts != a)
		build_history_list(info, buf + lasts, linecounts++);
	free(buf);
	info->histcount = linecounts;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adding entry
 * @info: Structure with the args
 * @buf: buffer
 * @linecount: histcount
 *
 * Return: 0 success
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbering lists
 * @info: Structure with the args
 *
 * Return: historycount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
