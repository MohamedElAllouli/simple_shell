#include "main.h"
/**
 * hsh - shell loop
 * @f: the parameter & return info struct
 * @av: the argument vector from mai
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *f, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		info_clear(f);
		if (is_interactive(f))
			_puts("$ ");
		e_putchar(BUF_FLUSH);
		r = get_input(f);
		if (r != -1)
		{
			info_set(f, av);
			builtin_ret = builtin_find(f);
			if (builtin_ret == -1)
				find_cmd(f);
		}
		else if (is_interactive(f))
			_putchar('\n');
		info_free(f, 0);
	}
	history_write(f);
	info_free(f, 1);
	if (!is_interactive(f) && f->status)
		exit(f->status);
	if (builtin_ret == -2)
	{
		if (f->err_num == -1)
			exit(f->status);
		exit(f->err_num);
	}
	return (builtin_ret);
}
/**
 * builtin_find - finds a builtin command
 * @f: the parameter & return info struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int builtin_find(info_t *f)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", _my_env},
		{"help", my_help},
		{"history", _my_history},
		{"setenv", _my_set_env},
		{"unsetenv", _my_unset_env},
		{"cd", my_cd},
		{"alias", _my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(f->argv[0], builtintbl[i].type) == 0)
		{
			f->line_count++;
			built_in_ret = builtintbl[i].func(f);
			break;
		}
	return (built_in_ret);
}
/**
 * find_cmd - finds  in PATH
 * @f: the parameter & return info struct
 */
void find_cmd(info_t *f)
{
	char *path = NULL;
	int i, k;

	f->path = f->argv[0];
	if (f->linecount_flag == 1)
	{
		f->line_count++;
		f->linecount_flag = 0;
	}
	for (i = 0, k = 0; f->arg[i]; i++)
		if (!is_de_lim(f->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = path_find(f, _envget(f, "PATH="), f->argv[0]);
	if (path)
	{
		f->path = path;
		cmd_forck(f);
	}
	else
	{
		if ((is_interactive(f) || _envget(f, "PATH=")
			|| f->argv[0][0] == '/') && _iscmd(f, f->argv[0]))
			cmd_forck(f);
		else if (*(f->arg) != '\n')
		{
			f->status = 127;
			error_print(f, "not found\n");
		}
	}
}
/**
 * cmd_forck - exec thread to run cmd
 * @f: parameter and return info struct
 *
 */
void cmd_forck(info_t *f)
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
		if (execve(f->path, f->argv, environ_get(f)) == -1)
		{
			info_free(f, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(f->status));
		if (WIFEXITED(f->status))
		{
			f->status = WEXITSTATUS(f->status);
			if (f->status == 126)
				error_print(f, "Permission denied\n");
		}
	}
}
