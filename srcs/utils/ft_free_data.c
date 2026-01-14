/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:44:22 by rlefort           #+#    #+#             */
/*   Updated: 2026/01/14 18:41:04 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_dataenv(t_env *env)
{
	t_env	*curr;
	t_env	*n;

	if (!env)
		return ;
	curr = env;
	while (curr->next)
	{
		n = curr->next;
		if (curr->name)
			free(curr->name);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = n;
	}
	if (curr->name)
		free(curr->name);
	if (curr->value)
		free(curr->value);
	free(curr);
}

static void	ft_free_redirs(t_redir *red)
{
	t_redir	*curr;
	t_redir	*n;

	if (!red)
	{
		return ;
	}
	curr = red;
	while (curr->next)
	{
		n = curr->next;
		if (curr->file)
			free(curr->file);
		free(curr);
		curr = n;
	}
	if (curr->file)
		free(curr->file);
	free(curr);
}

void	ft_free_datacmd(t_command *cmd)
{
	t_command	*curr;
	t_command	*n;

	if (!cmd)
		return ;
	curr = cmd;
	while (curr->next)
	{
		n = curr->next;
		if (curr->args)
			free(curr->args);
		ft_free_redirs(curr->redirs);
		free(curr);
		curr = n;
	}
	if (curr->args)
		free(curr->args);
	ft_free_redirs(curr->redirs);
	free(curr);
}

void	ft_free_datatoken(t_token *tok)
{
	t_token	*curr;
	t_token	*n;

	if (!tok)
		return ;
	curr = tok;
	while (curr->next)
	{
		n = curr->next;
		free(curr->token);
		free(curr);
		curr = NULL;
		curr = n;
	}
	free(curr->token);
	free(curr);
	curr = NULL;
}

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->env)
		ft_free_dataenv(data->env);
	if (data->cmd)
		ft_free_datacmd(data->cmd);
	if (data->token)
		ft_free_datatoken(data->token);
	free(data);
}
