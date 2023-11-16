#include "shell.h"

/**
 * is_cmd - This function determines if a file is an executable command
 * @info: This is the info struct
 * @path: This is the path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * double_charts - This function duplicates characters
 * @pathstr: This is the PATH string
 * @start: This is the starting index
 * @stop: This is the stopping index
 *
 * Return: pointer to new buffer
 */
char *double_charts(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[b++] = pathstr[a];
	buf[b] = 0;
	return (buf);
}

/**
 * find_path - This function finds this cmd in the PATH string
 * @info: This is the info struct
 * @pathstr: This is the PATH string
 * @cmd: This is the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && started_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = double_charts(pathstr, curr_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
