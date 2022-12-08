/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:16 by vsergio           #+#    #+#             */
/*   Updated: 2022/12/07 23:49:31 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
int	isbuiltin(char **splitted_cmd, t_list *env_lst)
{
	if (!ft_strncmp(splitted_cmd[0], "echo", 4))
		echo(splitted_cmd, 1);
	else if (!ft_strncmp(splitted_cmd[0], "cd", 2))
		cd(splitted_cmd);
	else if (!ft_strncmp(splitted_cmd[0], "pwd", 3))
		pwd(1);
	else if (!ft_strncmp(splitted_cmd[0], "export", 6))
		pwd(1);
	else if (!ft_strncmp(splitted_cmd[0], "unset", 5))
		pwd(1);
	else if (!ft_strncmp(splitted_cmd[0], "env", 3))
		env(env_lst, 1);
	else if (!ft_strncmp(splitted_cmd[0], "exit", 3))
		ft_exit(splitted_cmd);
	else
		return (0);
	free_matrix(splitted_cmd);
	return (1);
}
