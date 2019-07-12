/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjohnsto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 09:30:46 by kjohnsto          #+#    #+#             */
/*   Updated: 2019/07/12 12:18:29 by kjohnsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	verifyline(char **stack, char **line)
{
	char	*tmp_stack;
	char	*strchr_stack;
	int		i;

	i = 0;
	strchr_stack = ft_strdup(*stack);
	tmp_stack = ft_strchr(strchr_stack, '\n');
	if (tmp_stack == NULL)
		return (0);
	*tmp_stack = '\0';
	*line = ft_strdup(strchr_stack);
	ft_strdel(stack);
	*stack = ft_strdup(tmp_stack + 1);
	ft_strdel(&strchr_stack);
	tmp_stack = NULL;
	return (1);
}

static int	readline(int fd, char *heap, char **stack, char **line)
{
	int		ret;
	char	*tmp_stack;
	char	*tmp;

	while ((ret = read(fd, heap, BUFF_SIZE)) > 0)
	{
		heap[ret] = '\0';
		tmp_stack = ft_strdup(*stack);
		ft_strdel(&(*stack));
		*stack = ft_strjoin(tmp_stack, heap);
		ft_strdel(&tmp_stack);
		if ((tmp = ft_strchr(*stack, '\n')) != NULL)
		{
			*tmp = '\0';
			*line = ft_strdup(*stack);
			tmp_stack = ft_strdup(tmp + 1);
			ft_strdel(stack);
			*stack = ft_strdup(tmp_stack);
			ft_strdel(&tmp_stack);
			break ;
		}
	}
	return (ret > 0 ? 1 : ret);
}

int			get_next_line(const int fd, char **line)
{
	static char	*stack[MAX_FD];
	char		heap[BUFF_SIZE + 1];
	int			ret;
	int			i;

	if (!line || fd < 0 || fd <= MAX_FD || (read(fd, stack[fd], 0) < 0))
		return (-1);
	i = 0;
	if (stack[fd] == NULL)
		ft_strnew(1);
	ret = readline(fd, heap, &stack[fd], line);
	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ret && *line)
			*line = NULL;
		ft_strdel(&stack[fd]);
		return (ret);
	}
	*line = stack[fd];
	ft_strdel(&stack[fd]);
	return (1);
}
