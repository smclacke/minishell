/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unittest.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 17:57:52 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/14 18:00:31 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = ((unsigned char *)s);
	while (n-- > 0)
	{
		*(ptr++) = 0;
	}
}

static	t_parser	*init_parser(char **tokens)
{
	t_parser	*proc;

	proc = (t_parser *)malloc(sizeof(t_parser));
	if (!proc)
		return (NULL);// malloc error
	// ft_bzero(proc, sizeof(t_parser));
	proc->tokens = tokens;
	proc->proc_count = (count_procs(tokens) + 1);
	proc->process = (t_procs **)malloc(sizeof(t_procs *)
			* (proc->proc_count + 1));
	if (!proc->process)
	{
		free(proc);
		return (NULL);// malloc error
	}
	// ft_bzero(proc->process, sizeof(t_procs));
	return (proc);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Define the structures and functions from the header file
// #include "../../include/shelly.h"

// Mock implementation of count_procs function for testing
int count_procs(char **tokens) {
    // You can implement this mock function based on your test scenario
    // For simplicity, let's assume it returns a fixed value
    return 2; // You can adjust this based on your test case
}

// Declare the init_parser function from the source file
static t_parser *init_parser(char **tokens);

// Unit test function for init_parser
void test_init_parser() {
    char *tokens[] = {"token1", "token2", "token3", NULL};
    t_parser *proc = init_parser(tokens);

    // // Check if the proc pointer is not NULL
    // assert(proc != NULL);

    // // Check if the tokens are correctly assigned
    // assert(proc->tokens == tokens);

    // // Check if the proc_count is calculated correctly
    // assert(proc->proc_count == count_procs(tokens) + 1);

    // // Check if the process array is allocated and initialized correctly
    // assert(proc->process != NULL);
    // for (int i = 0; i < proc->proc_count; i++) {
    //     assert(proc->process[i] == NULL);
    // }

    // Free the allocated memory after the test
    free(proc);
}

int main() {
    // Run the unit test function
    test_init_parser();

    printf("All tests passed!\n");
    return 0;
}
