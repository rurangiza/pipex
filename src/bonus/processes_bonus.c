/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:32:06 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/15 19:06:27 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

void	first_child(t_data *data, int *outfile)
{
	int		infile;
	int		err_code;
	t_cmd	cmd;

	close(outfile[P_READ]);
	
	infile = open(data->arg_list[1], O_RDONLY);
	if (infile == -1)
		exit_msg();
	if (dup2(infile, STDIN_FILENO) < 0)
		exit(EXIT_FAILURE);
	close(infile);
	
	dup2(outfile[P_WRITE], STDOUT_FILENO);

	init_cmd(data->envp, data->arg_list[2], &cmd);
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg();
}

void	middle_child(t_data *data, int *outfile, int arg_number)
{
	int		err_code;
	t_cmd	cmd;

	close(outfile[P_READ]);
	dup2(outfile[P_WRITE], STDOUT_FILENO);
	
	init_cmd(data->envp, data->arg_list[arg_number], &cmd);
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg();
}

void	last_child(t_data *data)
{
	int		outfile;
	int		err_code;
	t_cmd	cmd;
	int		outfile_index;
	outfile_index = data->arg_count - 1;
	outfile = open(data->arg_list[outfile_index], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		exit_msg();
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	
	init_cmd(data->envp, data->arg_list[outfile_index - 1], &cmd);
	err_code = execve(cmd.path, cmd.args, NULL);
	if (err_code == -1)
		exit_msg();
}

void	parent_process(int *pipe_ends, pid_t pid)
{
	int	status;


	close(pipe_ends[P_WRITE]);
	close(pipe_ends[P_READ]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		success_msg(0, "Parent: Child %d terminated normally", pid);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGTERM)
			error_msg(0, "Parent: Child [%d] got SIGTERM", pid);
		if (WTERMSIG(status) == SIGKILL)
			error_msg(0, "Parent: child [%d] got SIGKILL", pid);
	}
}
