#include "shell.h"

/**
 * _getline - gets input line from STDIN
 * @info: first parameter
 * @ptr: second parameter
 * @length: third parameter
 *
 * Return: Always 0
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t y;
	ssize_t r = 0, s = 0;
	char *p = NULL, *next = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (x == len)
		x = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + x, '\n');
	y = c ? 1 + (unsigned int)(c - buf) : len;
	next = _realloc(p, s, s ? s + y : y + 1);

	if (!next)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(next, buf + x, y - x);
	else
		_strncpy(next, buf + x, y - x + 1);

	s = s + y - x;
	x = y;
	p = next;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * input_buf - chain commands
 * @info: first parameter
 * @buf: second parameter
 * @len: third parametr
 *
 * Return: bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		r = getline(buf, &len_p, stdin);
		r = _getline(info, buf, &len_p);

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
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
 * get_input - gets a line, excludes newline
 * @info: parameter
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t x, y, len;
	ssize_t r = 0;
	char **buffer = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);

	if (r == -1)
		return (-1);
	if (len)
	{
		y = x;
		p = buf + x;

		check_chain(info, buf, &y, x, len);
		while (y < len)
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer = p;
		return (_strlen(p));
	}

	*buffer = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @info: first parameter
 * @buf: second parameter
 * @i: third parameter
 *
 * Return: x
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * sigintHandler - function blocks ctrl-C
 * @sig_num: parameter
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
