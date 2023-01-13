/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/13 15:59:48 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    child_process(t_data *data, char *infile)
{
    int infile_fd;
    
    close(data->pipe_ends[READ_END]);
    infile_fd = open(infile, O_RDONLY | O_CREAT, 0777); // open infile for reading
    if (infile_fd == -1)
        error_msg(1, "couldn't open <file1>");
    dup2(infile_fd, STDIN_FILENO); // replace STDIN with infile
    close(infile_fd);
    dup2(data->pipe_ends[WRITE_END], STDOUT_FILENO); // replace STDOUT with WRITE_END of pipe
    execve(data->cmd_1.path, data->cmd_1.args, NULL); // execute cmd1 on stdin
}

void    parent_process(t_data *data, char *outfile)
{
    int status;
    int outfile_fd;

    close(data->pipe_ends[WRITE_END]);
    outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777); // open outfile for writing
    if (outfile_fd == -1)
        error_msg(2, "couldn't open <file2>");
    dup2(outfile_fd, STDOUT_FILENO); // replace stdout with outfile
    close(outfile_fd);
    dup2(data->pipe_ends[READ_END], STDIN_FILENO); // replace stdin with READ_END of pipe
    execve(data->cmd_2.path, data->cmd_2.args, NULL);
    waitpid(data->pid, &status, 0);
}
