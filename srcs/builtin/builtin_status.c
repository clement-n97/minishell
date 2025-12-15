/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:00:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 12:05:44 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo_status(t_data *data)
{
	builtin_echo(data);
	return (0);
}

int	builtin_cd_status(t_data *data)
{
	int	ret;

	ret = 0;
	if (data->cmd->args[1])
		ret = ft_cd(data->cmd->args[1], &data->env);
	else
		ret = ft_cd(ft_get_env_value("HOME", &data->env), &data->env);
	return (ret);
}

int	builtin_pwd_status(t_data *data)
{
	char	*pwd;

	(void)data;
	pwd = ft_pwd();
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
	}
	return (0);
}

int	builtin_exit_status(t_data *data)
{
	builtin_exit(data);
	return (data->last_exit_status);
}
