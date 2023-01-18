/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/18 10:58:46 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child(t_data *data, int *pipe_ends)
{
	int		infile_fd;
	int		err_code;
	t_cmd	cmd;

	close(pipe_ends[P_READ]);
	infile_fd = open(data->arg_list[1], O_RDONLY);
	if (infile_fd == -1)
		exit_msg(EXIT_FAILURE, "infile");
	if (dup2(infile_fd, STDIN_FILENO) < 0)
		exit_msg(0, "dup()");
	close(infile_fd);
	dup2(pipe_ends[P_WRITE], STDOUT_FILENO);
	init_cmd(data->envp, data->arg_list[2], &cmd);
	if (cmd.path == NULL)
		exit_msg(0, "shell cmd");
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg(0, "execve");
}

void	second_child(t_data *data, int *pipe_ends)
{
	int		outfile_fd;
	int		err_code;
	t_cmd	cmd;

	close(pipe_ends[P_WRITE]);
	dup2(pipe_ends[P_READ], STDIN_FILENO);
	outfile_fd = open(data->arg_list[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		exit_msg(1, "outfile");
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	init_cmd(data->envp, data->arg_list[3], &cmd);
	if (cmd.path == NULL)
		exit_msg(1, "shell cmd2");
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg(0, "execve");
}

void	parent_process(int *pipe_ends, pid_t *pid)
{
	int	status;
	int	i;

	close(pipe_ends[P_READ]);
	close(pipe_ends[P_WRITE]);
	i = 0;
	while (i < 2)
	{
		waitpid(pid[i], &status, 0);	
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				exit_msg(WEXITSTATUS(status), "NORM");
			else
				exit(EXIT_SUCCESS);
		}
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGTERM)
				exit_msg(WTERMSIG(status), "SIGTERM");
			if (WTERMSIG(status) == SIGKILL)
				exit_msg(WTERMSIG(status), "SIGKILL");
		}
		i++;
	}
}
