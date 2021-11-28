#include "get_next_line.h"

char *read_buffer(int fd)
{
	char *buffer;
	int read_return;

	buffer  = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_return = read(fd, buffer, BUFFER_SIZE);
	buffer[read_return] = '\0';
	if (read_return == 0 || read_return == -1)
	{
		free(buffer);
		buffer = NULL;
	}
	return (buffer);
}

char *try_get_line(char *buffer)
{
	int i;
	char *line;

	i = 0;
	line = NULL;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			line = ft_substr(buffer, 0, ++i);
			break;
		}
		i++;
	}
	return (line);
}

char *get_rest_backup(char *buffer)
{
	char *res_backup;
	char *temp_str;

	res_backup = NULL;
	temp_str = NULL;
	if (!buffer)
		return (NULL);
	temp_str = ft_strchr(buffer , '\n');
	res_backup = ft_strdup(++temp_str);
	return (res_backup);
}

int check_nl(char *buffer)
{
	int i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}


void process_buffer(char **buffer, char **backup, char **line, char **rest, int fd)
{
	if (check_nl(*buffer) == 1)
	{
		if (!(*backup))
		*backup = ft_strdup("");
		*buffer = ft_strjoin(*backup, *buffer);
		*line = try_get_line(*buffer);
		*rest = get_rest_backup(*buffer);
		if (!rest)
		{
			free(*backup);
			*backup = NULL;
		}
		*backup = ft_strdup(*rest);
		free(*rest);
	}
	while (check_nl(*buffer) == 0 && *buffer)
	{
		if (!(*backup))
		*backup = ft_strdup("");
		*backup = ft_strjoin(*backup, *buffer);
		*buffer = read_buffer(fd);
	}
	if (!*line && *buffer && *backup)
	{
		*buffer = ft_strjoin(*backup, *buffer);
		*line = try_get_line(*buffer);
		*rest = get_rest_backup(*buffer);
		if (!rest)
		{
			free(*backup);
			*backup = NULL ;
		}
		*backup = ft_strdup(*rest);
		free(*rest);
	}
	 if (!*line && !(*buffer) && *backup)
	{
		*line = ft_strdup(*backup);
		free(*backup);
		*backup = NULL;
	}
}

char *get_next_line(int fd)
{
	char *buffer;
	char *rest;
	char *line ;
	static char *backup;

	line  = NULL ;
	buffer = read_buffer(fd);

	if (fd == -1 || (!buffer && !backup))
		return (NULL);

	 else if (!buffer && backup)
	{
		buffer = ft_strdup(backup);
		free(backup);
		backup = NULL ;
	}
	process_buffer(&buffer, &backup, &line, &rest, fd);
	return (line);
}

