#include "main.h"
/**
 * _iscmd - if a file is an executable command
 * @f: struct
 * @p: path of  the file
 * Return: 1 if success, 0 otherwise
 */
int _iscmd(info_t *f, char *p)
{
	struct stat st;

	(void)f;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * chars_dup - double characters
 * @pstr: the  string path
 * @start: star index
 * @stop: stop index
 * Return: new buffer
 */
char *chars_dup(char *pstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (pstr[i] != ':')
			buf[j++] = pstr[i];
	buf[j] = 0;
	return (buf);
}

/**
 * path_find - finds this cmd in the string string
 * @f: the struct
 * @pstr: the string path
 * @cmd: the cmd to find
 * Return: the path of cmd
 */
char *path_find(info_t *f, char *pstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *p;

	if (!pstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (_iscmd(f, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pstr[i] || pstr[i] == ':')
		{
			p = chars_dup(pstr, curr_pos, i);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (_iscmd(f, p))
				return (p);
			if (!pstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
