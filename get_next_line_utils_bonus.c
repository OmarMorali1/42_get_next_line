/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommorali@student.42amman.com <ommorali>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 12:19:10 by ommorali@st       #+#    #+#             */
/*   Updated: 2026/10/12 12:19:33 by ommorali@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	found_newline(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n' || !lst->content[i])
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_lstadd_back(t_list **lst, char *buffer)
{
	t_list	*node;
	t_list	*last;

	node = malloc(sizeof(t_list));
	if (!node)
	{
		free(buffer);
		return ;
	}
	node->content = buffer;
	node->next = NULL;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = node;
}

void	free_all(t_list **lst)
{
	t_list	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

size_t	get_line_len(t_list *lst)
{
	size_t	len;
	int		i;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			len++;
			if (lst->content[i] == '\n')
				return (len);
			i++;
		}
		lst = lst->next;
	}
	return (len);
}

char	*free_file(t_file **lst, int fd)
{
	t_file	*curr;
	t_file	*prev;

	if (!lst || !*lst)
		return (NULL);
	curr = *lst;
	prev = NULL;
	while (curr && curr->fd != fd)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return (NULL);
	if (prev)
		prev->next = curr->next;
	else
		*lst = curr->next;
	free_all(&(curr->content));
	free(curr);
	return (NULL);
}
