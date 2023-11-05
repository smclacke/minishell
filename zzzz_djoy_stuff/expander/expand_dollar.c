/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:05:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/05 19:21:47 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/shelly.h"

// /**
//  * @param node node from parser linked list
//  * @param exp expander struct
//  * @param i index
//  * @param j index at next $ sign
//  * @brief gets the string to compare the environment key to
// */
// static int	get_var_str(char *str, t_expand *exp, int i, int j)
// {
// 	while (ft_isquote(str[i]) && str[i] != '\0')
// 		i++;
// 	j = i;
// 	while (!ft_isquote(str[j]) && str[j] != '\0')
// 		j++;
// 	exp->var = ft_substr(str, i, j - i);
// 	return (j);
// }

// // helaas werkt dit gewoooonnn niet, met mijn twee problemen EN norm, 
// // we hebben gewoon nieuwe logical nodig, balen
// // werkt wel echt bijna maar godver en met veel te veel funcs
// static char	*exp_dollar(char *str, t_env **env, t_expand *exp, int len)
// {
// 	int			i;
// 	int			j;

// 	i = 0;
// 	printf("str = %s\n", str);
// 	while (str[i])
// 	{
// 		if (((str[i] == '$') || (ft_isquote(str[i]))) && (i + 1) != len)
// 		{
// 			get_before_dollar(str, exp, i);
// 			if (ft_isquote(str[i]) && (i + 1) != len)
// 			{
// 				i = get_var_str(str, exp, i, j);
// 				exp->var = remove_quotes(exp->var);
// 				reassing_before_dollar_with_var(exp);
// 			}
// 			else
// 			{		
// 				i++;
// 				j = i;
// 				if (i == len)
// 				{
// 					str = return_exp(str, exp);
// 					return (str);
// 				}
// 				get_compare_str(str, exp, i, j);
// 				get_check_value(exp, env);
// 				save_expanded(exp);
// 			}
// 		}
// 		i++;
// 	}
// 	printf("str before ret = %s\n", str);
// 	str = return_exp(str, exp);
// 	printf("str ret = %s\n", str);
// 	return (str);
// }

