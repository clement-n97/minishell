/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:10:38 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 15:19:55 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_input(t_data *data, char **original_env)
{
	char	**env;

	(void)original_env;
	if (data->cmd && data->cmd->args && data->cmd->args[0])
	{
		if (is_builtin_cmd(data->cmd->args[0]) && !data->cmd->next)
			builtin_commands(data);
		else
		{
			env = ft_env_to_array(&data->env);
			if (env)
			{
				execute_pipeline(data->cmd, env, data);
				ft_free_tabs(env);
			}
		}
	}
}

static void	shell_loop(t_data *data, char **env)
{
	while (1)
	{
		data->input = readline("User$ ");
		if (!data->input)
			break ;
		add_history(data->input);
		ft_parsing(data, data->input);
		execute_input(data, env);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	data->env = ft_initialize_env();
	data->last_exit_status = 0;
	shell_loop(data, env);
	free(data);
	return (0);
}
