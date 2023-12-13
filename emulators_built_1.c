#include "main.h"
/**
 * my_exit - shell exit
 * @f: Structure of arguments.
 * Return: 0 if success.
 */
int my_exit(info_t *f)
{
	int check_exit;

	if (f->argv[1])
	{
		check_exit = _err_atoi(f->argv[1]);
		if (check_exit == -1)
		{
			f->status = 2;
			error_print(f, "Illegal number: ");
			e_puts(f->argv[1]);
			e_putchar('\n');
			return (1);
		}
		f->err_num = _err_atoi(f->argv[1]);
		return (-2);
	}
	f->err_num = -1;
	return (-2);
}
/**
 * my_cd - change  current directory
 * @f: Structure of arguments. Used to maintain
 *  Return: Always 0
 */
int my_cd(info_t *f)
{
	char *s, *d, buffer[1024];
	int ret_chdir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!f->argv[1])
	{
		d = _envget(f, "HOME=");
		if (!d)
			ret_chdir = chdir((d = _envget(f, "PWD=")) ? d : "/");
		else
			ret_chdir = chdir(d);
	}
	else if (_strcmp(f->argv[1], "-") == 0)
	{
		if (!_envget(f, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_envget(f, "OLDPWD=")), _putchar('\n');
		ret_chdir = chdir((d = _envget(f, "OLDPWD=")) ? d : "/");
	}
	else
		ret_chdir = chdir(f->argv[1]);
	if (ret_chdir == -1)
	{
		error_print(f, "can't cd to ");
		e_puts(f->argv[1]), e_putchar('\n');
	}
	else
	{
		_set_env(f, "OLDPWD", _envget(f, "PWD="));
		_set_env(f, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * my_help - changes current directory
 * @f: Structure of arguments
 *  Return:  0 if success
 */
int my_help(info_t *f)
{
	char **a_array;

	a_array = f->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*a_array);
	return (0);
}
