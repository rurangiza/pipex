/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/13 18:27:59 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_pipex(t_data *data, char **arg_list)
{
    int status;

	// Create and handle processes
	data->pid[0] = fork();
	if (data->pid[0] == -1)
    {
        perror("fork");
		exit(EXIT_FAILURE);
    }
	else if (data->pid[0] == 0)
		first_child(data, arg_list[1]);
    data->pid[1] = fork();
	if (data->pid[1] == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (data->pid[1] == 0)
        second_child(data, arg_list[4]);
    close(data->pipe_ends[READ_END]);
    close(data->pipe_ends[WRITE_END]);
    waitpid(data->pid[0], &status, 0);
    waitpid(data->pid[1], &status, 0);
}

void    first_child(t_data *data, char *infile)
{
    int infile_fd;
    int err_code;
    
    close(data->pipe_ends[READ_END]);
    infile_fd = open(infile, O_RDONLY, 0777); // open infile for reading
    if (infile_fd == -1)
        error_msg(1, "couldn't open <file1>");
    if (dup2(infile_fd, STDIN_FILENO) < 0) // replace STDIN with infile
        return ;
    close(infile_fd);
    dup2(data->pipe_ends[WRITE_END], STDOUT_FILENO); // replace STDOUT with WRITE_END of pipe
    err_code = execve(data->cmd_1.path, data->cmd_1.args, NULL); // execute cmd1 on stdin
    if (err_code == -1)
        error_msg(0, "couldn't find a program to execute");
}

void    second_child(t_data *data, char *outfile)
{
    int outfile_fd;
    int err_code;

    close(data->pipe_ends[WRITE_END]);
    outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777); // open outfile for writing
    if (outfile_fd == -1)
        error_msg(2, "couldn't open <file2>");
    dup2(outfile_fd, STDOUT_FILENO); // replace stdout with outfile
    close(outfile_fd);
    dup2(data->pipe_ends[READ_END], STDIN_FILENO); // replace stdin with READ_END of pipe
    err_code = execve(data->cmd_2.path, data->cmd_2.args, NULL);
    if (err_code == -1)
        error_msg(0, "couldn't find a program to execute");
}
