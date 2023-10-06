/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 19:50:33 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/06 17:55:54 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// $USER
// zsh: command not found: smclacke
// this was still expanded

/**
 * echo "$USER"				// remove quotes, expand
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
 * all in doubles check env for var
 * 
 * if single, take literally 
 * 
 * save everything from start without quotes up to quote, then separate after/inside quotes
 * 
 * find dollar, if quote before, find matching, create separate strings
 * if dollar and quote after, ignore dollar
 * 
 * 
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

char	*handle_dollar_qs(char *str)
{
	// if something before dollar and not quote, skip and save it
	// if quote before dollar, single or double, closed? where?
	// 
	printf("handle_quotes for dollar strings\n");
	return (str);
}
