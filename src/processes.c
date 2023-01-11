/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/11 20:39:15 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    child_process(pid_t pid)
{
    success_msg(0, "I'm child process, ID %d", pid);
    exit(0);
}

void    parent_process(pid_t pid)
{
    int status;

    info_msg(0, "Parent: I'm the parent. PID received from fork = %d", pid);
    info_msg(0, "Parent: Waiting for my child with PID [%d]", pid);
    waitpid(pid, &status, 0);
    info_msg(0, "Parent: My child exited with status %d", pid);
}