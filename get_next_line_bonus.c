/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:30:51 by hoakoumi          #+#    #+#             */
/*   Updated: 2022/12/13 15:12:46 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_fd(int fd,  char *s)
{
	char *buffer;
	int nbr;
	
	nbr = 1;
	buffer = malloc (sizeof (char) * (BUFFER_SIZE + 1));
	if(!buffer)
		return(NULL);
	while (!ft_strchr(s) && nbr != 0)
	{
		nbr = read (fd, buffer, BUFFER_SIZE);
		if (nbr == -1)
		{
			free (buffer);
			free (s);
			return (NULL);
		}
		buffer[nbr] = '\0';
		s = ft_strjoin (s, buffer);
	}
	free (buffer);
	return (s);
}

char	*check (char *s)
{
	int		i;
	int j;
	char	*str;
	
	i = 0;
	j = 0;
	if (!s[i])
		return(NULL);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	str = (char *)malloc (sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	while (s[j] != '\0' && s[j] != '\n') 
	{
		str[j] = s[j];
		j++;
	}
	if (s[j] == '\n')
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*next(char *s)
{
	int		i;
	char	*str;
	int		j;
	
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free (s);
		return (NULL);
	}
	str = (char *)malloc (sizeof(char) * (ft_strlen(s) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (s[i] != '\0') 
		str[j++]= s[i++];
	str[j] = '\0';
	free (s);
	return (str);
}

char	*get_next_line(int fd)
{
	static char *h[OPEN_MAX];
	char *line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	h[fd] = read_fd (fd, h[fd]);
	if (!h[fd])
		return (NULL);
	line = check (h[fd]);
	h[fd] = next (h[fd]);
	return (line);
}

