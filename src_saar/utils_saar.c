/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_saar.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 01:18:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/06/27 14:07:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

// is whitespace
// is quote
// quote is open
// is token (?)

// Meta characters: SPACE, TAB, NEWLINE, ;, (, ), <, >, |, &.
// Types of tokens: words, keywords, In / Out redirectors, and semicolons.

// Delimiters ";", "|", "&".
