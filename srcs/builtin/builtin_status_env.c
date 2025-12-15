/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_status_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:00:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 15:20:10 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export_status(t_data *data)
{
	char	*output;
	int		ret;

	ret = 0;
	if (data->cmd->args[1])
		ft_export(data->cmd->args + 1, &data->env);
	else
	{
		output = ft_export_noargs(&data->env);
		if (output)
		{
			ft_putstr_fd(output, STDOUT_FILENO);
			free(output);
		}
	}
	return (ret);
}

int	builtin_unset_status(t_data *data)
{
	int	ret;

	ret = 0;
	if (data->cmd->args[1])
		ft_unset(data->cmd->args + 1, &data->env);
	return (ret);
}

int	builtin_env_status(t_data *data)
{
	int	ret;

	ret = 0;
	ft_putstr_fd(ft_env(&data->env), STDOUT_FILENO);
	return (ret);
}
