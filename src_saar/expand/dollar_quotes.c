/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/05 20:14:09 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// $USER
// zsh: command not found: smclacke
// this was still expanded

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
 * 
 * $U"SER"
 * SER
 * 
 * $U'SER'
 * SER
 * 
 * echo asdf$U"SER"
 * asdfSER

*/
