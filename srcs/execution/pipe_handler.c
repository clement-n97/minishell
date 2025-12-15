/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 13:09:58 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_exit_status(int *status, t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(*status))
	{
		exit_code = *status >> 8;
		data->last_exit_status = exit_code;
	}
	else if (WIFSIGNALED(*status))
	{
		exit_code = 128 + (*status & 0x7F);
		data->last_exit_status = exit_code;
	}
	else
		data->last_exit_status = 1;
}

void	wait_for_last_pid(int last_pid, int *status, t_data *data)
{
	int	wpid;

	wpid = -1;
	if (last_pid != -1)
	{
		wpid = waitpid(last_pid, status, 0);
		while (wpid == -1 && errno == EINTR)
			wpid = waitpid(last_pid, status, 0);
		extract_exit_status(status, data);
	}
}

static void	close_pipe_fds(int prev_fd, int pipe_fd[2], t_command *cmd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
	}
}

void	pipeline_loop(t_command *cmd, char **env, t_data *data,
		t_fork_data *fork_data)
{
	int	pipe_fd[2];
	int	prev_fd;
	int	last_pid;
	int	status;

	prev_fd = -1;
	last_pid = -1;
	status = 0;
	fork_data->env = env;
	fork_data->data = data;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return ;
		last_pid = fork_and_execute(cmd, prev_fd, pipe_fd, (char **)fork_data);
		close_pipe_fds(prev_fd, pipe_fd, cmd);
		if (cmd->next)
			prev_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	wait_for_last_pid(last_pid, &status, data);
	while (wait(NULL) > 0)
		;
}

void	execute_pipeline(t_command *cmd, char **env, t_data *data)
{
	t_fork_data	fork_data;

	fork_data.env = NULL;
	fork_data.data = NULL;
	pipeline_loop(cmd, env, data, &fork_data);
}
