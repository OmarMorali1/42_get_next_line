/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommorali@student.42amman.com <ommorali>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:44:24 by ommorali          #+#    #+#             */
/*   Updated: 2026/10/12 09:19:20 by ommorali@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_file
{
	int				fd;
	t_list			*content;
	struct s_file	*next;
}	t_file;

char	*get_next_line(int fd);
int		found_newline(t_list *lst);
void	ft_lstadd_back(t_list **lst, char *buffer);
void	free_all(t_list **lst);
char	*free_file(t_file **lst, int fd);
size_t	get_line_len(t_list *lst);

#endif
