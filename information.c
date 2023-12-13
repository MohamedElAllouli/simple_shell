#include "main.h"
/**
 * info_clear - initializes information structur
 * @f: structur
 */
void info_clear(info_t *f)
{
	f->arg = NULL;
	f->argv = NULL;
	f->path = NULL;
	f->argc = 0;
}
/**
 * info_set - initializes information structur
 * @f: structur
 * @va: vector argument
 */
void info_set(info_t *f, char **va)
{
	int i = 0;

	f->fname = va[0];
	if (f->arg)
	{
		f->argv = str_tow1(f->arg, " \t");
		if (!f->argv)
		{

			f->argv = malloc(sizeof(char *) * 2);
			if (f->argv)
			{
				f->argv[0] = _strdup(f->arg);
				f->argv[1] = NULL;
			}
		}
		for (i = 0; f->argv && f->argv[i]; i++)
			;
		f->argc = i;

		alias_replace(f);
		vars_replace(f);
	}
}
/**
 * info_free - free fields of iformation structur
 * @f: structur
 * @a: boolean
 */
void info_free(info_t *f, int a)
{
	f_free(f->argv);
	f->argv = NULL;
	f->path = NULL;
	if (a)
	{
		if (!f->cmd_buf)
			free(f->arg);
		if (f->env)
			list_free(&(f->env));
		if (f->history)
			list_free(&(f->history));
		if (f->alias)
			list_free(&(f->alias));
		f_free(f->environ);
			f->environ = NULL;
		bfree((void **)f->cmd_buf);
		if (f->readfd > 2)
			close(f->readfd);
		_putchar(BUF_FLUSH);
	}
}
