/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hd_fd_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 21:54:56 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/01 21:59:31 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	close_hd_fd(t_parser *lst)
{
	int	i;
	int	count;

	i = 0;
	count = lst->proc_count;
	while (i < count)
	{
		close(lst->proc->hd_fd);
		if (lst->next != NULL)
			lst = lst->next;
		i++;
	}
}

void	unlink_heredoc(t_parser *lst)
{
	int		i;
	char	*number;
	char	*str;

	i = 0;
	while (i < lst->proc->hd_count)
	{
		number = ft_itoa(i);
		str = mini_strjoin("heredoc", number);
		unlink(str);
		free(str);
		free(number);
		i++;
	}
}
