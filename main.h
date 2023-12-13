#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - linked list
 * @num: number field
 * @str: string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - pseudo-arguements to pass into a fallowin
 *		 uniform prototype for function pointer struct
 *@arg: string generated from getline containing arguements
 *@argv: array of strings generated from arg
 *@path: string path for the current command
 *@argc: argument count
 *@line_count: error count
 *@err_num: error code for exit
 *@linecount_flag: if on count this line of input
 *@fname: program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: history node
 *@alias: alias node
 *@env_changed: on if environ was changed
 *@status: return status of the last exec command
 *@cmd_buf: address of pointer to cmd_buf
 *@cmd_buf_type: CMD_type
 *@readfd: fd from which to read line input
 *@histcount: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
/**
 *struct builtin - builtin string and function
 *@type: builtin command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int builtin_find(info_t *);
void find_cmd(info_t *);
void cmd_forck(info_t *);
/* path.c */
int _iscmd(info_t *, char *);
char *chars_dup(char *, int, int);
char *path_find(info_t *, char *, char *);
/* loophsh.c */
int hsh_loop(char **);
/* err_string_functions.c */
void e_puts(char *);
int e_putchar(char);
int _put_fd(char c, int fd);
int _puts_fd(char *str, int fd);
/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
/* string_functions2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
/* string_functions3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
/* string_functions4.c */
char **str_tow1(char *, char *);
char **str_tow2(char *, char);
/* memory_functions */
char *_memoryset(char *, char, unsigned int);
void f_free(char **);
void *_realloc(void *, unsigned int, unsigned int);
/* memory_functions2.c */
int bfree(void **);
/* more_functions.c */
int is_interactive(info_t *);
int is_de_lim(char, char *);
int _isalpha(int);
int _atoi(char *);
/* more_functions2.c */
int _err_atoi(char *);
void error_print(info_t *, char *);
int d_print(int, int);
char *number_toconvert(long int, int, int);
void delete_comments(char *);
/* builtin_emulators.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);
/* builtin_emulators2.c */
int _my_history(info_t *);
int _my_alias(info_t *);
/* getline.c module */
ssize_t get_input(info_t *);
int get_line(info_t *, char **, size_t *);
void sig_int_Handler(int);
/* info.c module */
void info_clear(info_t *);
void info_set(info_t *, char **);
void info_free(info_t *, int);
/* env.c module */
char *_envget(info_t *, const char *);
int _my_env(info_t *);
int _my_set_env(info_t *);
int _my_unset_env(info_t *);
int populate_list_env(info_t *);
/* env2.c module */
char **environ_get(info_t *);
int _unset_env(info_t *, char *);
int _set_env(info_t *, char *, char *);
/* file_io_functions.c */
char *get_file_history(info_t *info);
int history_write(info_t *info);
int history_read(info_t *info);
int history_build_list(info_t *info, char *buf, int linecount);
int history_renumber(info_t *info);
/* liststr.c module */
list_t *node_add(list_t **, const char *, int);
list_t *add_node_at_end(list_t **, const char *, int);
size_t list_print_str(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void list_free(list_t **);
/* liststr2.c module */
size_t len_list(const list_t *);
char **to_strings_list(list_t *);
size_t list_print(const list_t *);
list_t *node_begin_with(list_t *, char *, char);
ssize_t get_index_node(list_t *, list_t *);
/* chain.c */
int is_chain(info_t *, char *, size_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);
int alias_replace(info_t *);
int vars_replace(info_t *);
int string_replace(char **, char *);

#endif
