/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_expand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/31 15:43:36 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* sarah parses the word i need to check if the word requires an action:
"user" = user (word), "$user" = djoyke (action), '$user' = $user (word) */
//>>
//>
// removing files int unlink(const char *pathname);
