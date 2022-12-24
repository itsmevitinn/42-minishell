/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <Vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:08:25 by gcorreia          #+#    #+#             */
/*   Updated: 2022/12/24 00:27:28 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void print_error(char *cmd, int fd);
static void print_vars(t_var_lst *env_lst, int fd);
static void export_var(t_var_lst *env_lst, char *cmd);
static int name_is_invalid(char *cmd);

void export(t_cmd_lst *cmd, t_cmd_info *data, t_var_lst *env_lst)
{
	char **args;

	args = cmd->args;
	if (data->qty != 1)
	{
		data->pids[cmd->id] = fork();
		if (!data->pids[cmd->id])
		{
			args++;
			if (!*args)
				print_vars(env_lst, cmd->output);
			while (*args && data->qty == 1)
			{
				if (name_is_invalid(*args))
				{
					print_error(*args, cmd->output);
					exit(1);
				}
				else
					export_var(env_lst, *args);
				args++;
			}
			exit(0);
		}
	}
	else
	{
		args++;
		if (!*args)
			print_vars(env_lst, cmd->output);
		while (*args)
		{
			if (name_is_invalid(*args))
			{
				print_error(*args, cmd->output);
				g_exit_status = 1;
			}
			else
				export_var(env_lst, *args);
			args++;
		}
		g_exit_status = 0;
	}
}

static void print_vars(t_var_lst *env_lst, int fd)
{
	int should_print;
	while (env_lst)
	{
		should_print = ft_strncmp("_", env_lst->name, 2);
		if (should_print)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(env_lst->name, fd);
		}
		if (should_print && env_lst->content)
		{
			write(fd, "=\"", 2);
			ft_putstr_fd(env_lst->content, fd);
			write(fd, "\"", 1);
		}
		if (should_print)
			write(fd, "\n", 1);
		env_lst = env_lst->next;
	}
}

static int name_is_invalid(char *cmd) // CHECK VALID CHARACTERS DIFFERENT FOR 1ST CHARACTER
{
	if (*cmd == '=')
		return (1);
	while (*cmd && *cmd != '=')
	{
		if (!ft_isalpha(*cmd) && *cmd != '_')
			return (1);
		cmd++;
	}
	return (0);
}

static void print_error(char *cmd, int fd)
{
	ft_putstr_fd("export: `", fd);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
}

static void export_var(t_var_lst *env_lst, char *cmd)
{
	char *content;
	char *name;
	char *aux;

	content = ft_strchr(cmd, '=');
	if (content)
	{
		name = malloc(content - cmd + 1);
		aux = name;
		while (cmd != content)
			*aux++ = *cmd++;
		*aux = '\0';
		content = ft_strdup(content + 1);
	}
	else
		name = ft_strdup(cmd);
	if (get_env(name, env_lst))
		change_content(name, content, env_lst);
	else
		ft_varadd_back(&env_lst, ft_var_new(name, content));
}
