/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:10:38 by clnicola          #+#    #+#             */
/*   Updated: 2026/01/05 11:03:23 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_builtin_with_redir(t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(data->cmd) == -1)
	{
		data->last_exit_status = 1;
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}
	builtin_commands(data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static void	execute_input(t_data *data, char **original_env)
{
	char	**env;

	(void)original_env;
	if (data->cmd && data->cmd->args && data->cmd->args[0])
	{
		if (is_builtin_cmd(data->cmd->args[0]) && !data->cmd->next)
			run_builtin_with_redir(data);
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
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_history(data->input);
		ft_parsing(data, data->input);
		execute_input(data, env);
		if (g_signal_received == SIGINT)
			data->last_exit_status = 130;
		g_signal_received = 0;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	set_signals_interactive();
	data = malloc(sizeof(t_data));
	data->env = ft_initialize_env();
	data->last_exit_status = 0;
	shell_loop(data, env);
	free(data);
	return (0);
}
