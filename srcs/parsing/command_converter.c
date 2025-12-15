/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:26:35 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 13:04:27 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection_type(int t)
{
	return (t == INPUT || t == TRUNC || t == APPEND || t == HEREDOC);
}

static int	handle_word(t_command *cmd, t_token **tok_ptr, int idx)
{
	cmd->args[idx++] = (*tok_ptr)->token;
	*tok_ptr = (*tok_ptr)->next;
	return (idx);
}

static void	handle_redirection_token(t_command *cmd, t_token **tok_ptr)
{
	t_token	*tok;

	tok = *tok_ptr;
	if (tok->next && (tok->next->type == WORD || tok->next->type == VAR))
	{
		add_redir(cmd, tok->type, tok->next->token);
		*tok_ptr = tok->next->next;
	}
	else
		*tok_ptr = tok->next;
}

static void	populate_command(t_command *cmd, t_token **tok_ptr)
{
	int		i;
	t_token	*tok;

	i = 0;
	tok = *tok_ptr;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == WORD || tok->type == VAR)
			i = handle_word(cmd, &tok, i);
		else if (is_redirection_type(tok->type))
			handle_redirection_token(cmd, &tok);
		else
			tok = tok->next;
	}
	cmd->args[i] = NULL;
	*tok_ptr = tok;
}

t_command	*ft_tokens_to_commands(t_token *token_list)
{
	t_command	*head;
	t_command	*new_cmd;
	int			arg_count;

	head = NULL;
	while (token_list)
	{
		arg_count = ft_count_args(token_list);
		new_cmd = ft_new_command(arg_count);
		if (!new_cmd)
			return (NULL);
		populate_command(new_cmd, &token_list);
		ft_add_back_command(&head, new_cmd);
		if (token_list && token_list->type == PIPE)
			token_list = token_list->next;
	}
	return (head);
}
