/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:37:09 by rlefort           #+#    #+#             */
/*   Updated: 2025/12/18 15:50:44 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exit_code(t_data *data, int arg_count)
{
	if (arg_count > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (arg_count == 1)
	{
		if (ft_strisnum(data->cmd->args[1])) 
			return (ft_atoi(data->cmd->args[1]) % 256);
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	return (data->last_exit_status);
}

void	builtin_exit(t_data *data)
{
	int	exit_code;
	int	arg_count;

	arg_count = 0;
	if (data && data->cmd && data->cmd->args)
	{
		while (data->cmd->args[arg_count])
			arg_count++;
		arg_count--;
	}
	exit_code = get_exit_code(data, arg_count);
	exit(exit_code);
}
