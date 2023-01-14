/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:41:01 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/14 13:55:54 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NOTES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*//*

Output of ping goes to ping result


Zombie process :	a child process that has terminated but is still takes up
					ressources as a result of not having been waited on by its
					parent process

STDIN = a file that the system reads from
STDOUT = 
STDERR = 

dup() & dup2() 	:	functions that allow us to change those file descriptors 

pipe	:	a pipe is a buffer or block of data, with two file descriptors
			one for reading, and one for writing.
			a pipe is a form of redirection that is used to send the output
			of one program to another program

*//*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "includes/pipex.h"

int	main(void)
{
	printf("Process ID = %d\n", getpid());
	return (EXIT_SUCCESS);
}