#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>

/* rdwri buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* system getline() */
#define USE_GETLINE     0
#define USE_STRTOK      0
#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: number field
 * @str: a string
 * @next: point to next node
 */

typedef struct liststr
{
	char *str;
	int num;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @path: a string path for the current command
 * @line_count: the error count
 * @histcount: the history line number count
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @history: the history node
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @alias: the alias node
 * @status: the return status of the last exec'd command
 * @env_changed: on if environ was changed
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @argv:an array of strings generated from arg
 * @argc: the argument count
 */
typedef struct passinfo
{
	char *path;
	char **argv;
	char *arg;
	char *fname;
	char **environ;
	int env_changed;
	int status;
	int argc;
	int err_num;
	int histcount;
	int linecount_flag;
	int readfd;
	unsigned int line_count;
	list_t *alias;
	list_t *env;
	list_t *history;
	int cmd_buf_type; /* for CMD_types */
	char **cmd_buf; /* cmd ; chain buffer, for memory mangement pointers */
} info_t;

#define INFO_INIT \
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}
/**
 * struct builtin - contains builtin string and its related function
 * @func: the function
 * @type: the builtin command flag
 */

typedef struct builtin
{
	int (*func)(info_t *);
	char *type;
} builtin_table;

/* kshlloop.c */
int ksh(info_t *, char **);
int find_builtin(info_t *);
void fork_cmd(info_t *);
void find_cmd(info_t *);

/* parser.c */
int ks_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loopksh.c */
int loopksh(char **);

/* errors_0.c */
int _putfd(char c, int fd);
int _eputchar(char);
int _putsfd(char *str, int fd);
void _eputs(char *);

/* errors_1.c */
int _erratoi(char *);
int print_z(int, int);
char *convert_number(long int, int, int);
void print_error(info_t *, char *);
void remove_comments(char *);

/* string_0.c */
int _strcmp(char *, char *);
int _strlen(char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_1.c */
int _putchar(char);
char *_strdup(const char *);
char *_strcpy(char *, char *);
void _puts(char *);

/* end.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);

/* tokn.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);

/* memory.c */
int btfree(void **);

/* atoi.c */
int _atoi(char *);
int _ksalpha(int);
int ks_delim(char, char *);
int interactive(info_t *);

/* builtin_0.c */
int _kshhelp(info_t *);
int _kshcd(info_t *);
int _kshexit(info_t *);

/* builtin_1.c */
int _kshhistory(info_t *);
int _kshalias(info_t *);

/* getline.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

/* getinfo.c */
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);

/* environ.c */
int _kshenv(info_t *);
char *_getenv(info_t *, const char *);
int _kshunsetenv(info_t *);
int _kshsetenv(info_t *);
int populate_env_list(info_t *);

/* getenv.c */
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

/* history.c */
int build_history_list(info_t *info, char *buf, int linecount);
int read_history(info_t *info);
int write_history(info_t *info);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);

/* lists_0.c */
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
void free_list(list_t **);

/* lists_1.c */
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
list_t *node_starts_with(list_t *, char *, char);

/* vars.c */
int replace_alias(info_t *);
int ks_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

#endif
