#include "shell.h"

/**
 * input_buf - This stores or  buffers [given] chained commands
 * @info:  this is the [given] parameter struct
 * @buf: This is the [particular] address of buffer or store
 * @len: This is the [particlar] address of length variable
 * Return: This is the [particular] bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* This takes place if nothing left in the buffer, fill it */
	{
		/*This is explained comment --- bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /*This deletes of removes trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}
/**
 * get_input -This receives or  gets a [given] line minus the newline
 * @info: This is a [particular] parameter struct
  * Return: This is bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer -- or store [ a comment] */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF - end of file*/
		return (-1);
	if (len)	/*This is when we have commands left in the chain buffer */
	{
		j = i; /* initialize the [givcen] new iterator to current buf position */
		p = buf + i; /*This receives or gets pointer for return */
		check_chain(info, buf, &j, i, len);
		while (j < len) /* This actually iterates to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1; /* This is the increment past nulled ';'' */
		if (i >= len) /* Has it reached end of buffer? */
		{
			i = len = 0; /* This changes or resets position and length */
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p; /*This is pointer to [particular] current command position */
		return (_strlen(p)); /* This returns length of a [given] current command */
	}
	*buf_p = buf; /*if not a chain, pass back buffer from _getline() */
	return (r); /* This returns the [given] length of buffer from _getline() */
}
/**
 * read_buf - This takes in or reads a buffer or store
 * @info: This is the parameter struct
 * @buf: This is the buffer or store
 * @i: This is the [given] size
 * Return: This returns r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - This gets the [particular] next line of input from STDIN
 * @info: This is a [given] parameter struct
 * @ptr: This is the [given] address of pointer to buffer, preallocated or NULL
 * @length: This is the [given] size of preallocated ptr buffer if not NULL
 * Return: This returns s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - This hinders copy or blocks ctrl-C
 * @sig_num:This is the [particular] signal number
 * Return:This doesn't return args. In other word, it returns  void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
