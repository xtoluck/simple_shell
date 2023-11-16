#ifndef _SHELL_H_
#define _SHELL_H_

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

/* This function is for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* This function is for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* This function is for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* In this function 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - This function is singly linked list
 * @num: This represents the number field
 * @str: This represents a string
 * @next: Yhis represents points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - It contains pseudo-arguements to pass into a function,
 *allowing uniform prototype for function pointer struct
 *@arg: This is a string generated from getline containing arguements
 *@argv: This is an array of strings generated from arg
 *@path: This is a string path for the current command
 *@argc: This is the argument count
 *@line_count: This is the error count
 *@err_num: This is the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: For the program filename
 *@env: It is linked list local copy of environ
 *@environ: This is custom modified copy of environ from LL env
 *@history: This is the history node
 *@alias: This is the alias node
 *@env_changed: This is on if environ was changed
 *@status: It is the return status of the last exec'd command
 *@cmd_buf: This is address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: The CMD_type ||, &&, ;
 *@readfd: This is the fd from which to read line input
 *@histcount: This is the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - This contains a builtin string and related function
 *@type: It is the builtin command flag
 *@func: It is the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c function */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c function*/
int is_cmd(info_t *, char *);
char *double_charts(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c function*/
int loophsh(char **);

/* toem_errors.c function*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_strng.c function*/
int _strlen(char *);
int _strcmp(char *, char *);
char *started_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_strng1.c function*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c function*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizr.c function*/
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realoc.c function*/
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memry.c function*/
int bfree(void **);

/* toem_atoi.c function*/
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c function*/
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c function*/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c function*/
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c function*/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c function*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c function*/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c function*/
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_histry.c function*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lsts.c function*/
list_t *adds_nodes(list_t **, const char *, int);
list_t *adds_nodes_ended(list_t **, const char *, int);
size_t prints_lists_string(const list_t *);
int deletes_nodes_at_indexes(list_t **, unsigned int);
void frees_lists(list_t **);

/* toem_lsts1.c function*/
size_t lists_lens(const list_t *);
char **lists_to_string(list_t *);
size_t prints_lists(const list_t *);
list_t *nodes_start_with(list_t *, char *, char);
ssize_t gets_nodes_indexes(list_t *, list_t *);

/* toem_vars.c function*/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
