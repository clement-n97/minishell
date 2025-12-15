/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:45:09 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 12:05:44 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	builtin_commands(t_data *data)
{
	char	*cmd;
	int		status;

	status = 0;
	if (!data || !data->cmd || !data->cmd->args)
		return ;
	cmd = data->cmd->args[0];
	if (!ft_strcmp(cmd, "echo"))
		status = builtin_echo_status(data);
	else if (!ft_strcmp(cmd, "cd"))
		status = builtin_cd_status(data);
	else if (!ft_strcmp(cmd, "pwd"))
		status = builtin_pwd_status(data);
	else if (!ft_strcmp(cmd, "export"))
		status = builtin_export_status(data);
	else if (!ft_strcmp(cmd, "unset"))
		status = builtin_unset_status(data);
	else if (!ft_strcmp(cmd, "env"))
		status = builtin_env_status(data);
	else if (!ft_strcmp(cmd, "exit"))
		status = builtin_exit_status(data);
	data->last_exit_status = status;
}
