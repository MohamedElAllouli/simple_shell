#include "main.h"
/**
 * get_file_history - gets the history file
 * @f: strucure of information
 * Return: string containg history file
 */
char *get_file_history(info_t *f)
{
	char *buf, *dir;

	dir = _envget(f, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
/**
 * history_write - file created or display  an existing file
 * @f: structure of information
 * Return: 1 on success
 */
int history_write(info_t *f)
{
	ssize_t fd;
	char *filename = get_file_history(f);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = f->history; node; node = node->next)
	{
		_puts_fd(node->str, fd);
		_put_fd('\n', fd);
	}
	_put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * history_read - get history from file
 * @f: structur of information
 * Return: hidtory count, 0 otherwise
 */
int history_read(info_t *f)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_file_history(f);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			history_build_list(f, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
	history_build_list(f, buf + last, linecount++);
	free(buf);
	f->histcount = linecount;
	while (f->histcount-- >= HIST_MAX)
		remove_node_at_index(&(f->history), 0);
	history_renumber(f);
	return (f->histcount);
}
/**
 * history_build_list - add entry to a history linked list
 * @f: Structure of information
 * @buffer: buffer
 * @r_count: history rowcount
 * Return: Always 0
 */
int history_build_list(info_t *f, char *buffer, int r_count)
{
	list_t *node = NULL;

	if (f->history)
		node = f->history;
	add_node_at_end(&node, buffer, r_count);

	if (!f->history)
		f->history = node;
	return (0);
}

/**
 *history_renumber - change numbers of  history linked list
 * @f: Structure of information
 * Return: new histcount
 */
int history_renumber(info_t *f)
{
	list_t *node = f->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (f->histcount = i);
}
