/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuthayak <tuthayak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:07:26 by tuthayak          #+#    #+#             */
/*   Updated: 2024/12/22 22:43:24 by tuthayak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *buffer);
static char	*update_buffer(char *buffer);
static char	*read_and_store(int fd, char *buffer);
static char	*join_and_free(char *buffer, char *read_buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_and_store(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}

static char	*read_and_store(int fd, char *buffer)
{
	char	*read_buffer;
	ssize_t	bytes_read;

	read_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(read_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		buffer = join_and_free(buffer, read_buffer);
		if (!buffer)
			break ;
	}
	free(read_buffer);
	return (buffer);
}

static char	*join_and_free(char *buffer, char *read_buffer)
{
	char	*temp;

	temp = buffer;
	buffer = ft_strjoin(temp, read_buffer);
	free(temp);
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_substr(buffer, 0, i + 1);
	else
		line = ft_substr(buffer, 0, i);
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	size_t	i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(buffer + i + 1);
	free(buffer);
	return (new_buffer);
}
