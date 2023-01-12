/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:41:31 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/12 13:15:36 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_cmd_path(char **envp, char *cmd)
{
	char	**paths_list;
	int		index;

	index = 0;
	while (envp[index] != NULL)
	{
		if (ft_strnstr(envp[index], "PATH", 4))
		{
			paths_list = ft_split_sep(envp[index] + 4, ':', '/');
			if (paths_list == NULL)
				return (NULL);
			return (validated_path(paths_list, cmd));
		}
		index++;
	}
	return (NULL);
}

char	*validated_path(char **paths_list, char *cmd)
{
	char	*cmd_path;
	int		index;

	index = 0;
	while (paths_list[index] != NULL)
	{
		cmd_path = ft_strjoin(paths_list[index], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			ft_free_matrix(paths_list);
			return (cmd_path);
		}
		free(cmd_path);
		index++;
	}
	ft_free_matrix(paths_list);
	return (NULL);
}
