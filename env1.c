#include "shell.h"

/**
 * _myenv -This prints or displays the current [given] environment.
 * @info: This structure contains [particular] potential arguments. maintain
 *         a [given] constant function prototype.
 * Return: This will always return 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - This gets the value of a [particular] environment variable
 * @info: This is structure containing [given] potential arguments. maintain
 * @name:This is the [given] env variable name
 * Return: This is the returned value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - This initializes a [particular] new environment variable,
 *             or change, alter or modify an existing one
 * @info: This structure contains [a particular] potential arguments. maintain
 *       a [given] constant function prototype.
 *  Return: This always returns 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - This removes or deletes an environment variable
 * @info: This structure contains [particular] potential arguments. maintain
 *      a [given] constant function prototype.
 *  Return: This always  returns 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);
	return (0);
}

/**
 * populate_env_list - This populates a [given] environment linked list
 * @info: This is structure containing potential arguments. maintain
 *         a [given] constant function prototype.
 * Return: This always returns 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
