/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjohnsto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 09:30:46 by kjohnsto          #+#    #+#             */
/*   Updated: 2019/07/15 09:49:25 by kjohnsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdupdel(char **str)
{
	char	*tmp;

	tmp = ft_strdup(*str);
	ft_strdel(str);
	return (tmp);
}

void	ft_readline(char **stack, int fd)
{
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	while (ft_strchr(*stack, '\n') == NULL)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) == 0)
			break ;
		buff[ret] = '\0';
		tmp = ft_strjoin(*stack, buff);
		ft_strdel(stack);
		*stack = ft_strdupdel(&tmp);
	}
}

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static char		*stack[MAX_FD];
	char			*ptr;
	char			*tmp;

	if (fd < 0 || read(fd, buff, 0) < 0 || !line)
		return (-1);
	if (stack[fd] == NULL)
		stack[fd] = ft_strnew(0);
	ft_readline(&stack[fd], fd);
	if ((ptr = ft_strchr(stack[fd], '\n')) != NULL)
	{
		*ptr = '\0';
		tmp = ft_strdup(ptr + 1);
		*line = ft_strdupdel(&stack[fd]);
		ft_strdel(&stack[fd]);
		if (tmp != NULL)
			stack[fd] = ft_strdupdel(&tmp);
		return (1);
	}
	if (ft_strlen(stack[fd]) == 0)
		return (0);
	if (ft_strlen(stack[fd]) != 0)
		*line = ft_strdupdel(&stack[fd]);
	return (1);
}
