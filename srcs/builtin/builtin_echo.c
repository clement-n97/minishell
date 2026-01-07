/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:33:02 by clnicola          #+#    #+#             */
/*   Updated: 2026/01/07 11:16:41 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_fd(t_data *data, int i)
{
	while (data->cmd->args[i])
	{
		ft_putstr_fd(data->cmd->args[i], STDOUT_FILENO);
		if (data->cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

void	builtin_echo(t_data *data)
{
	int	i;

	i = 1;
	if (!data->cmd->args)
		return ;
	if (data->cmd->args[1] && (!ft_strcmp(data->cmd->args[1], "-n")))
	{
		i = 2;
		ft_print_fd(data, i);
	}
	else
	{
		ft_print_fd(data, i);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}
