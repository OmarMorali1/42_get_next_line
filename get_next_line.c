/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommorali@student.42amman.com <ommorali>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 13:56:53 by ommorali          #+#    #+#             */
/*   Updated: 2026/10/19 10:50:26 by ommorali@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_and_store(int fd, t_list **lst)
{
	char	*buf;
	ssize_t	rd;

	while (!found_newline(*lst))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (0);
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
		{
			free(buf);
			free_all(lst);
			return (0);
		}
		if (!rd)
		{
			free(buf);
			break ;
		}
		buf[rd] = '\0';
		ft_lstadd_back(lst, buf);
	}
	return (1);
}

static char	*extract_line(t_list *lst)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!lst)
		return (NULL);
	line = malloc(sizeof(char) * (get_line_len(lst) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (lst)
	{
		j = 0;
		while (lst->content[j])
		{
			line[i++] = lst->content[j];
			if (lst->content[j++] == '\n')
				break ;
		}
		lst = lst->next;
	}
	line[i] = '\0';
	return (line);
}

static int	copy_clean_content(t_list *last, t_list *clean, ssize_t i)
{
	ssize_t	j;
	ssize_t	len;

	len = 0;
	while (last->content[i + len])
		len++;
	clean->content = malloc(sizeof(char) * (len + 1));
	if (!clean->content)
		return (0);
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	return (1);
}

static int	clean_lst(t_list **lst)
{
	t_list	*last;
	t_list	*node;
	ssize_t	i;

	if (!lst || !*lst)
		return (0);
	last = *lst;
	while (last->next)
		last = last->next;
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	if (!last->content[i] && free_all(lst))
		return (0);
	node = malloc(sizeof(t_list));
	if (node && copy_clean_content(last, node, i) && free_all(lst))
	{
		node->next = NULL;
		*lst = node;
		return (1);
	}
	free(node);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_file	*lst;
	t_file			*curr;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	curr = lst;
	while (curr && curr->fd != fd)
		curr = curr->next;
	if (!curr)
	{
		curr = malloc(sizeof(t_file));
		if (!curr)
			return (NULL);
		curr->fd = fd;
		curr->content = NULL;
		curr->next = lst;
		lst = curr;
	}
	if (!read_and_store(fd, &(curr->content)) || !curr->content)
		return (free_file(&lst, fd));
	res = extract_line(curr->content);
	if (!clean_lst(&curr->content))
		free_file(&lst, fd);
	return (res);
}
