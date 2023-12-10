/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_quotes.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/10 17:50:16 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/10 17:50:38 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	squote_bit(t_expand *str, char *input, int i)
{
	int		start;
	int		end;
	char	*tmp;
	char	*tmp_input;

	start = i;
	tmp = str->expanded;
	tmp_input = input;
	while (tmp_input[i])
	{
		if (ft_issquote(tmp_input[i]))
		{
			end = i - start;
			str->s_quote = ft_substr(tmp_input, start, end);
			if (add_to_expand(str, str->s_quote) == -1)
			{
				printf("errorrrrrrr\n");
				return (-1); // need proper error like
			}
			return (i + 1);
		}
		i++;
	}
	free(str);
	return (i);
}
