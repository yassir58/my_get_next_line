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
	if (res_backup[0] == '\0')
	{
		free(res_backup);
		return (NULL);
	}
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

char* extract_line(char **buffer, char **backup,char **line_return)
{
	char *line;

	line = NULL;
	if (!(*backup))
		*backup = ft_strdup("");
	*buffer = ft_strjoin(*backup, *buffer);
	line = try_get_line(*buffer);
	*line_return = line;
	*backup = get_rest_backup(*buffer);
	return (line);
}

char *process_buffer(char **buffer, char **backup ,int fd)
{
	char *line_return;

	line_return = NULL;
	if (check_nl(*buffer) == 1)
		return (extract_line(buffer, backup, &line_return));
	while (check_nl(*buffer) == 0 && *buffer)
	{
		if (!(*backup))
		*backup = ft_strdup("");
		*backup = ft_strjoin(*backup, *buffer);
		*buffer = read_buffer(fd);
	}
	if (*buffer && *backup)
		return (extract_line(buffer, backup, &line_return));
	if (!line_return && !(*buffer) && *backup)
	{
		line_return = ft_strdup(*backup);
		free(*backup);
		*backup = NULL;
		return (line_return);
	}
	return (NULL);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *line ;
	static char *backup;

	line  = NULL ;
	if (backup && check_nl(backup) == 1)
	{
		buffer = ft_strdup(backup);
		free(backup);
		backup = NULL ;
	}
	else
	buffer = read_buffer(fd);
	
	if (fd == -1 || (!buffer && !backup))
		return (NULL);
	else if (!buffer && backup)
	{
		buffer = ft_strdup(backup);
		free(backup);
		backup = NULL ;
	}
	line = process_buffer(&buffer, &backup, fd);
	free(buffer);
	return (line);
}

