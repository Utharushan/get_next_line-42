/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuthayak <tuthayak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 09:18:42 by tuthayak          #+#    #+#             */
/*   Updated: 2024/12/24 11:36:12 by tuthayak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	contains_newline(char *str)
{
	int	index;

	if (!str)
		return (-1);
	index = 0;
	while (str[index])
	{
		if (str[index] == '\n')
			return (1);
		index++;
	}
	return (-1);
}

char	*extract_line(char **stash, int bytes_read)
{
	char	*line;

	if (bytes_read < BUFFER_SIZE && contains_newline(*stash) == -1)
	{
		line = ft_substr(*stash, 0, ft_strlen(*stash));
		if (!line)
			return (NULL);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	if (contains_newline(*stash) == 1)
	{
		line = ft_substr(*stash, 0, ft_strchr(*stash, '\n') - *stash + 1);
		if (!line)
			return (NULL);
		*stash = cut_after_newline(*stash);
		return (line);
	}
	return (NULL);
}

char	*initialize_stash(char *stash, int fd, char *buffer)
{
	int	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0 && stash == NULL)
		return (free(buffer), NULL);
	buffer[bytes_read] = '\0';
	if (!stash)
		stash = ft_substr(buffer, 0, ft_strlen(buffer));
	else
		stash = ft_strjoin(stash, buffer);
	free(buffer);
	if (stash && stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (stash);
}

char	*append_to_stash(int fd, char *stash, int *bytes_read)
{
	char	*buffer;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		free(buffer);
		free(stash);
		return (NULL);
	}
	buffer[*bytes_read] = '\0';
	temp = stash;
	stash = ft_strjoin(temp, buffer);
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			bytes_read;

	stash = initialize_stash(stash, fd, NULL);
	if (!stash)
		return (NULL);
	while (stash)
	{
		stash = append_to_stash(fd, stash, &bytes_read);
		if (!stash)
			return (NULL);
		line = extract_line(&stash, bytes_read);
		if (line)
			return (line);
	}
	return (NULL);
}
