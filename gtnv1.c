#include "shell.h"

/**
 * get_environ - This returns [given] string array copy of our environment var
 * @info: This is the sStructure containing a [given] potential arguments.
 * It is used to maintain a [particular] constant function prototype.
 * Return: This returns always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = lists_to_string(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - This deletes or removes a [given] environment variable
 * @info: This is structure containing [given] potential arguments. maintain
 *        [particular] constant function prototype.
 *  Return:This returns value 1 on delete, and then 0 otherwise.
 * @var: This is the [given] string environment variable property.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = started_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = deletes_nodes_at_indexes(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - This initializes a [particular] new environment variable,
 *             or modify a [particular] existing one
 * @info: This is structure containing [given] potential arguments. maintain
 *      [particular] constant function prototype.
 * @var: Thhis is the [given] string environment variable property.
 * @value: This is the string environment variable value
 *  Return: This always returns 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = started_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	adds_nodes_ended(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
