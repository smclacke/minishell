/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/05 23:35:06 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// $USER
// zsh: command not found: smclacke
// this was still expanded

/**
 * "$USER"				// remove quotes, expand
 * smclacke
 * 
 * '$USER'				// echo what is literally in the quotes
 * $USER
 * 
 * $"USER"				// echo what is literally in the quotes, ignore the dollar
 * USER
 * 
 * abd$"USER"			// echo what is literally in the quotes, ignore the dollar
 * abdUSER
 * 
 * echo asdf'$USER'		// echo what is literally in the quotes
 * asdf$USER
 * 
 * $U"SER"				 // echo what is literally in the quotes, ignore the dollar
 * SER
 * 
 * $U'SER'				// echo what is literally in the quotes
 * SER
 * 
 * echo asdf$U"SER"		// echo what is literally in the quotes, ignore the dollar
 * asdfSER

*/

/**
 * double quotes = 
 * 		remove and expand when whole is quoted
 * 		echo what is literally in the quotes
 * 		ignore the dollar and anything after dollar outside quotes
 * 		if something before dollar, that is also echoed with the rest
 * 
 * single qoutes = 
 * 		take what is inside the quotes literally
 * 		ignore dollar and anything after dollar outside quotes
*/
