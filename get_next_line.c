/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:13:17 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/30 12:17:07 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(int fd)
{
	char	*buffer;
	int		read_return;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_return = read(fd, buffer, BUFFER_SIZE);
	if (read_return == 0 || read_return == -1)
	{
		free(buffer);
		buffer = NULL;
	}
	else
		buffer[read_return] = '\0';
	return (buffer);
}

char	*try_get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			line = ft_strndup(buffer, ++i);
			break ;
		}
		i++;
	}
	return (line);
}

char	*get_rest_backup(char *buffer)
{
	char	*res_backup;
	char	*temp_str;

	res_backup = NULL;
	temp_str = NULL;
	if (!buffer)
		return (NULL);
	temp_str = ft_strchr(buffer, '\n') + 1;
	res_backup = ft_strndup(temp_str, ft_strlen(temp_str));
	if (res_backup[0] == '\0')
	{
		free(res_backup);
		return (NULL);
	}
	return (res_backup);
}

char	*process_buffer(char **buffer, char **backup, int fd)
{
	char	*line_return;

	line_return = NULL;
	if (ft_strchr(*buffer, '\n'))
		return (extract_line(buffer, backup, &line_return));
	while (!(ft_strchr(*buffer, '\n')) && *buffer)
	{
		if (!(*backup))
			*backup = ft_strndup("", 0);
		*backup = ft_strjoin(*backup, *buffer);
		*buffer = read_buffer(fd);
	}
	if (*buffer && *backup)
		return (extract_line(buffer, backup, &line_return));
	if (!line_return && !(*buffer) && *backup)
	{
		line_return = ft_strndup(*backup, ft_strlen(*backup));
		free(*backup);
		*backup = NULL;
		return (line_return);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*line ;
	static char		*backup;

	line = NULL;
	if (backup && ft_strchr(backup, '\n'))
	{
		buffer = ft_strndup(backup, ft_strlen(backup));
		free(backup);
		backup = NULL ;
	}
	else
		buffer = read_buffer(fd);
	if (fd == -1 || (!buffer && !backup))
		return (NULL);
	else if (!buffer && backup)
	{
		buffer = ft_strndup(backup, ft_strlen(backup));
		free(backup);
		backup = NULL ;
	}
	line = process_buffer(&buffer, &backup, fd);
	free(buffer);
	return (line);
}
