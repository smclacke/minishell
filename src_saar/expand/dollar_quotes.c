/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/05 19:54:32 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * "$USER"
 * smclacke
 * 
 * '$USER'
 * $USER
 * 
 * $"USER"
 * USER
 * 
 * abd$"USER"
 * abd$USER
 * 
 * echo asdf'$USER'
 * asdf$USER
*/
