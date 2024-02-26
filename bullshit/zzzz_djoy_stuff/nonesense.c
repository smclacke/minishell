/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nonesense.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 14:49:26 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/26 14:09:31 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/shelly.h"

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_list(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s=%s\n", env->key, env->value);
// 		env = env->next;
// 	}
// }

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_list_key(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->key);
// 		env = env->next;
// 	}
// }

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_list_value(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->value);
// 		env = env->next;
// 	}
// }

// /**
//  * @param data execute struct
//  * @brief frees content of execute struct plus struct
// */
// void	free_data(t_execute *data)
// {
// 	ft_free_arr(data->env_array);
// 	free(data->path);
// 	free (data);
// }

// /**
//  * @param lst parser linked list
//  * @brief returns list size
// */
// int	list_iter(t_parser *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		i++;
// 		lst = lst->next;
// 	}
// 	return (i);
// }
