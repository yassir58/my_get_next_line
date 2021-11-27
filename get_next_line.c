#include "get_next_line.h"

char *read_buffer(int fd)
{
	char *buffer;
	int i;
	int read_return;

	i = 0;
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
			line = ft_substr(buffer, 0, ++i);
		i++;
	}
	return (line);
}

char *get_rest_backup(char *buffer)
{
	int i;
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
		//printf("line found");
		if (!(*backup))
		*backup = ft_strdup("");
		//printf("backup : %s \n", *backup);
		//printf("buffer : %s \n", *buffer);
		*buffer = ft_strjoin(*backup, *buffer);
		//printf("buffer after join: %s \n", *buffer);
		*line = try_get_line(*buffer);
		//printf("getting line .. \n");
		*rest = get_rest_backup(*buffer);
		//printf("processed element : \n");
		//printf("buffer : %s \n", *buffer);
		//printf("line : %s \n", *line);
		//printf("rest : %s \n", *rest);
		if (!rest)
		{
			free(*backup);
			*backup = NULL;
		}
		*backup = ft_strdup(*rest);
		//printf("rest backup : %s \n", *backup);
	}
	// this part is good
	while (check_nl(*buffer) == 0 && *buffer)
	{
		if (!(*backup))
		*backup = ft_strdup("");
		*backup = ft_strjoin(*backup, *buffer);
		*buffer = read_buffer(fd);
		//printf("backup in loop : %s \n", *backup);
	}
	//printf("backup coolected : %s \n", *backup);
	if (!*line && *buffer && *backup)
	{
		*buffer = ft_strjoin(*backup, *buffer);
		*line = try_get_line(*buffer);
		*rest = get_rest_backup(*buffer);
		if (!rest)
		{
			free(*backup);
			*backup = NULL;
		}
		*backup = ft_strdup(*rest);
		//printf("process buffer again .... \n");
		//printf("backup extracted ... %s \n", *backup);
		//printf("buffer : %s \n", *buffer);
		//process_buffer (buffer, backup, line , rest, fd);
	}
	 if (!*line && !(*buffer) && (*backup))
	{
		*line = ft_strdup(*backup);
		//printf("line returned : %s \n", *line);
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

	//backup = "";
	line  = NULL ;
	buffer = read_buffer(fd);
	//printf("buffer read : %s \n", buffer);
	//printf("** backup saved : %s **\n", backup);
	if (fd == -1 || (!buffer && !backup))
		return (NULL);

	else if (!buffer && backup)
	{
		//printf("condition satisfied !\n");
		buffer = ft_strdup(backup);
		free(backup);
		backup = NULL;
	}
	process_buffer(&buffer, &backup, &line, &rest, fd);
	return (line);
}

