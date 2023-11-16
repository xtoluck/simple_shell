#include "shell.h"

/**
 * clear_info - This instantiates or initializes info_t struct
 * @info: This is the [given] struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - This instantiates or initializes info_t struct
 * @info: This is the [given] struct address
 * @av: This is the [particular] argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - This clears or frees the [given]  info_t struct fields
 * @info: This is the [given] struct address
 * @all: This is true if freeing or clearing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			frees_lists(&(info->env));
		if (info->history)
			frees_lists(&(info->history));
		if (info->alias)
			frees_lists(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
