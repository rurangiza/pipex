/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/14 11:49:35 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// Executes the commands and pipes them together
void	ft_pipex(t_data *data)
{
    pid_t   pid[2];
    int     pipe_ends[2];

	if (pipe(pipe_ends) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid[0] = fork();
	if (data->pid[0] == -1)
    {
        perror("fork");
		exit(EXIT_FAILURE);
    }
	else if (pid[0] == 0)
		first_child(data, pipe_ends);
    pid[1] = fork();
	if (pid[1] == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid[1] == 0)
        second_child(data, pipe_ends);
    parent_process(pid, pipe_ends);
}

void    first_child(t_data *data, int *pipe_ends)
{
    int     infile_fd;
    int     err_code;
    t_cmd   cmd;

    close(pipe_ends[P_READ]);
    infile_fd = open(data->arg_list[1], O_RDONLY, 0777);
    if (infile_fd == -1)
        error_msg(1, "couldn't open <file1>");
    if (dup2(infile_fd, STDIN_FILENO) < 0)
        return ;
    close(infile_fd);
    dup2(pipe_ends[P_WRITE], STDOUT_FILENO);
    init_cmd(data->envp, data->arg_list[2], &cmd);
    err_code = execve(cmd.path, cmd.args, NULL);
    if (err_code == -1)
        error_msg(0, "couldn't find a program to execute");
}

void    second_child(t_data *data, int *pipe_ends)
{
    int     outfile_fd;
    int     err_code;
    t_cmd   cmd;

    close(pipe_ends[P_WRITE]);
    dup2(pipe_ends[P_READ], STDIN_FILENO);
    outfile_fd = open(data->arg_list[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (outfile_fd == -1)
        error_msg(2, "couldn't open <file2>");
    dup2(outfile_fd, STDOUT_FILENO);
    close(outfile_fd);
    init_cmd(data->envp, data->arg_list[3], &cmd);
    err_code = execve(cmd.path, cmd.args, NULL);
    if (err_code == -1)
        error_msg(0, "couldn't find a program to execute");
}

void    parent_process(int *pipe_ends, pid_t *pid)
{
    int status;

    close(pipe_ends[P_READ]);
    close(pipe_ends[P_WRITE]);
    waitpid(pid[0], &status, 0);
    waitpid(pid[1], &status, 0);
}
