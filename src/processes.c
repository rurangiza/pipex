/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/12 17:08:23 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    child_routine(int *pipe_fd)
{
    char *args[] = {"cat", "infile", NULL};

    close(pipe_fd[READ_END]);
    // read content of a file
    dup2(pipe_fd[WRITE_END], 1);
    // execute cat command on the received content
    execve("/bin/cat", args, NULL);
}

void    parent_routine(pid_t pid, int *pipe_fd)
{
    int     status;
    char    *args[] = {"grep", "wolves", NULL};
    int     outfile;
    
    int pid2 = fork();
    if (pid2 == 0)
    {
        close(pipe_fd[WRITE_END]);
        dup2(pipe_fd[READ_END], 0); // redirect stdin to the read end of the pipe
        outfile = open("outfile", O_WRONLY | O_CREAT, 0777); // open my output file
        dup2(outfile, 1); // redirect strout to my output file
        execve("/usr/bin/grep", args, NULL); // Execute the command
    }
    // Print result
    close(pipe_fd[WRITE_END]);
    waitpid(pid, &status, 0);
    waitpid(pid2, &status, 0);
}
