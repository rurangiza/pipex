/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/18 13:25:06 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child(t_data *data, int *pipe)
{
	int		infile;
	int		err_code;
	t_cmd	cmd;

	close(pipe[P_READ]);
	infile = open(data->arg_list[1], O_RDONLY);
	if (infile == -1)
		exit_nofile_msg(data->arg_list[1]);
	if (dup2(infile, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(infile);
	dup2(pipe[P_WRITE], STDOUT_FILENO);
	init_cmd(data->envp, data->arg_list[2], &cmd);
	if (cmd.path == NULL)
		exit_wrongcmd_msg(cmd.args[0], 0);
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg();
}

void	last_child(t_data *data)
{
	t_cmd	cmd;
	int		outfile;
	int		outfile_index;
	int		err_code;

	outfile_index = data->arg_count - 1;
	outfile = open(data->arg_list[outfile_index],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		exit_nofile_msg(data->arg_list[outfile_index]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	init_cmd(data->envp, data->arg_list[outfile_index - 1], &cmd);
	if (cmd.path == NULL)
		exit_wrongcmd_msg(cmd.args[0], 127);
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg();
}

void	parent_process(pid_t pid, int *pipe_ends, int index, int arg_count)
{
	int	status;

	close(pipe_ends[P_WRITE]);
	if (index <= arg_count - 2)
	{
		dup2(pipe_ends[P_READ], STDIN_FILENO);
		close(pipe_ends[P_READ]);
	}
	else
		close(pipe_ends[P_READ]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
			exit(WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGTERM)
			exit_msg();
		else if (WTERMSIG(status) == SIGKILL)
			exit_msg();
	}
}


// void	first_child(t_data *data, int *pipe_ends)
// {
// 	int		infile_fd;
// 	int		err_code;
// 	t_cmd	cmd;

// 	close(pipe_ends[P_READ]);
// 	infile_fd = open(data->arg_list[1], O_RDONLY);
// 	if (infile_fd == -1)
// 		exit_nofile_msg(data->arg_list[1]);
// 	if (dup2(infile_fd, STDIN_FILENO) < 0)
// 		exit_msg(0, "dup()");
// 	close(infile_fd);
// 	dup2(pipe_ends[P_WRITE], STDOUT_FILENO);
// 	init_cmd(data->envp, data->arg_list[2], &cmd);
// 	if (cmd.path == NULL)
// 		exit_wrongcmd_msg(cmd.args[0]);
// 	err_code = execve(cmd.path, cmd.args, NULL);
// 	if (err_code == -1)
// 		exit_msg(0, "execve");
// }

// void	second_child(t_data *data, int *pipe_ends)
// {
// 	int		outfile_fd;
// 	int		err_code;
// 	t_cmd	cmd;

// 	close(pipe_ends[P_WRITE]);
// 	dup2(pipe_ends[P_READ], STDIN_FILENO);
// 	outfile_fd = open(data->arg_list[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (outfile_fd == -1)
// 		exit_nofile_msg(data->arg_list[1]);
// 	dup2(outfile_fd, STDOUT_FILENO);
// 	close(outfile_fd);
// 	init_cmd(data->envp, data->arg_list[3], &cmd);
// 	if (cmd.path == NULL)
// 		exit_wrongcmd_msg(cmd.args[0]);
// 	err_code = execve(cmd.path, cmd.args, NULL);
// 	if (err_code == -1)
// 		exit_msg(0, "execve");
// }

// void	parent_process(int *pipe_ends, pid_t *pid)
// {
// 	int	status;
// 	int	i;

// 	close(pipe_ends[P_READ]);
// 	close(pipe_ends[P_WRITE]);
// 	i = 0;
// 	while (i < 2)
// 	{
// 		waitpid(pid[i], &status, 0);
// 		if (WIFEXITED(status))
// 		{
// 			if (WEXITSTATUS(status) != 0)
// 				exit_msg(WEXITSTATUS(status), "NORM");
// 		}
// 		if (WIFSIGNALED(status))
// 		{
// 			if (WTERMSIG(status) == SIGTERM)
// 				exit_msg(WTERMSIG(status), "SIGTERM");
// 			if (WTERMSIG(status) == SIGKILL)
// 				exit_msg(WTERMSIG(status), "SIGKILL");
// 		}
// 		i++;
// 	}
// }
