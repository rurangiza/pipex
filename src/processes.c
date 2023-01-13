/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/13 10:42:23 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    child_routine(void)
{
    char *args[] = {"cat", NULL};

    // Open infile for reading
    int file_fd = open("infile", O_RDONLY);
    // Redirect its output to stdin
    dup2(file_fd, 0);
    // execute cat command on stdin
    execve("/bin/cat", args, NULL);
}

void    parent_routine(void)
{
    //char    *args[] = {"grep", "illness", NULL};
    
}
