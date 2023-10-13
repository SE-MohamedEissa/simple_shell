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
#define BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convert_number() */
#define CONV_LOWERCASE       1
#define CONV_UNSIGNED        2

/* 1 if using system getline() */
#define GETLINE_USE 0
#define STRTOK_USE 0
#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096
extern char **environ;

/**
 * struct lists - singly linked list
 * @num: number
 * @str: string
 * @next: pointer
 */
typedef struct lists
{
	int num;
	char *str;
	struct lists *next;
} list_type;

/**
 * struct informations - contains pseudo-arguements.
 * @arg: string
 * @argv:an array of strings
 * @path: a string path
 * @argc: the argument count
 * @line_count: error count
 * @err_num: error code
 * @linecount_flag: input
 * @finame: filename
 * @env: linked list
 * @environ: custom modified
 * @history: his node
 * @alias: alias node
 * @env_changed: changed
 * @status: the status
 * @cmd_buf: address of pointer
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: input
 * @histcount: his line number count
 */

typedef struct informations
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *finame;
	list_type *env;
	list_type *history;
	list_type *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} inf_type;
#define INF_INIT {NULL, NULL, NULL, 0, 0, \
	0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct builtin - contains a builtin str.
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(inf_type *);
} builtin_type;

/*  loop_shell.c */
int hash(inf_type *, char **);
int f_builtin(inf_type *);
void fnd_cmd(inf_type *);
void frk_cmd(inf_type *);

/* parser.c */
int is_cmd(inf_type *, char *);
char *dup_ch(char *, int, int);
char *fnd_path(inf_type *, char *, char *);

/* err.c */
void _erputs(char *);
int _eputchar(char);
int _eputfd(char v, int fd);
int _eputsfd(char *str, int fd);


/* stringfunc.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *sta_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);

/* stringfunc2.c */
char *_strsdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strscpy(char *, char *, int);
char *_strscat(char *, char *, int);

/* stringfunc3.c */
char *_strnchr(char *, char);
char **strstow(char *, char *);
char **strstowar(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffre(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfre(void **);

/* atoi.c */
int interactives(inf_type *);
int is_delimet(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);

/* err2.c */
void pr_error(inf_type *info, char *message);
int pr_d(int, int);
char *conv_number(long int, int, int);
void rmov_comments(char *);

/* built.c */
int _mineexit(inf_type *);
int _minecd(inf_type *);
int _minehelp(inf_type *);

/* built2.c */
int _minehistory(inf_type *);
int _minealias(inf_type *);

/*getline.c */
ssize_t gets_input(inf_type *);
int _getsline(inf_type *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void cls_inf(inf_type *);
void sets_inf(inf_type *, char **);
void fre_inf(inf_type *, int);
char *_getsenv(inf_type *, const char *);

/* environ.c */
int _myineenv(inf_type *);
int _mineenv(inf_type *);
int _minesetenv(inf_type *);
int _mineunsetenv(inf_type *);
int pop_env_list(inf_type *);

/* getenv.c */
char **gets_environ(inf_type *);
int _unsetsenv(inf_type *, char *);
int _setsenv(inf_type *, char *, char *);

/* history.c */
char *get_his_fl(inf_type *info);
int write_his(inf_type *info);
int red_his(inf_type *info);
int buld_his_lst(inf_type *info, char *buf, int linecount);
int renum_history(inf_type *info);

/* list.c */
list_type *add_node(list_type **, const char *, int);
list_type *add_node_end(list_type **, const char *, int);
size_t pr_lst_str(const list_type *);
int del_node_at_ndex(list_type **, unsigned int);
void fre_lst(list_type **);

/* list2.c */
size_t lst_len(const list_type *);
char **lst_tostrs(list_type *);
size_t pr_lst(const list_type *);
list_type *node_sta_with(list_type *, char *, char);
ssize_t get_node_ndex(list_type *, list_type *);

/* vars.c */
int is_chain(inf_type *, char *, size_t *);
void ch_chain(inf_type *, char *, size_t *, size_t, size_t);
int repl_alias(inf_type *);
int repl_var(inf_type *);
int repl_str(char **, char *);

#endif
