/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:43:36 by olachgue          #+#    #+#             */
/*   Updated: 2024/11/30 18:55:04 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_from_file(int fd, char *leftover)
{
	char	*buffer;
	char	*tmp;
	int		bytes;

	bytes = 1;
	buffer = (char *)malloc((size_t)BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (free(leftover), leftover = NULL, NULL);
	while (bytes > 0 && (!leftover || !ft_strchr(leftover, '\n')))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buffer), free(leftover), NULL);
		buffer[bytes] = '\0';
		tmp = ft_strjoin(leftover, buffer);
		if (!tmp)
			return (free(buffer), NULL);
		leftover = tmp;
	}
	free(buffer);
	return (leftover);
}

char	*get_till_newline(char *leftover)
{
	size_t	len;
	char	*line;

	len = 0;
	while (leftover[len] != '\n' && leftover[len] != '\0')
		len++;
	if (leftover[len] == '\n')
		len++;
	if (len == 0 && leftover[len] == '\0')
		return (NULL);
	line = (char *)malloc(len + 1 * sizeof(char));
	if (!line)
		return (NULL);
	ft_strncpy(line, leftover, len);
	return (line);
}

char	*update_leftover(char *leftover)
{
	char	*new_leftover;
	int		j;
	int		i;
	size_t	left_len;

	j = 0;
	i = 0;
	left_len = ft_strlen(leftover);
	while (leftover[j] != '\n' && leftover[j] != '\0')
		j++;
	if (!leftover[j])
		return (free(leftover), leftover = NULL, NULL);
	j++;
	new_leftover = (char *)malloc((left_len - j + 1) * sizeof(char));
	if (!new_leftover)
		return (free(leftover), leftover = NULL, NULL);
	while (leftover[j])
		new_leftover[i++] = leftover[j++];
	new_leftover[i] = '\0';
	free(leftover);
	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	leftover = read_from_file(fd, leftover);
	if (!leftover)
		return (NULL);
	line = get_till_newline(leftover);
	if (!line)
		return (free(leftover), leftover = NULL, NULL);
	tmp = update_leftover(leftover);
	leftover = tmp;
	return (line);
}
