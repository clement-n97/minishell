/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:30:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 12:34:40 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_single_quote(t_quote_data *qd)
{
	(*qd->i)++;
	while (qd->str[*qd->i] && qd->str[*qd->i] != '\'')
		qd->result[(*qd->j)++] = qd->str[(*qd->i)++];
}

static void	handle_double_quote(t_quote_data *qd)
{
	char	*exp;
	int		k;

	(*qd->i)++;
	while (qd->str[*qd->i] && qd->str[*qd->i] != '"')
	{
		if (qd->str[*qd->i] == '$')
		{
			exp = expand_variable(qd->str, qd->i, qd->data);
			k = 0;
			while (exp && exp[k])
				qd->result[(*qd->j)++] = exp[k++];
			free(exp);
		}
		else
			qd->result[(*qd->j)++] = qd->str[(*qd->i)++];
	}
}

void	copy_quoted(t_quote_data *qd)
{
	char	quote;

	quote = qd->str[*qd->i];
	if (quote == '\'')
		handle_single_quote(qd);
	else if (quote == '"')
		handle_double_quote(qd);
	if (qd->str[*qd->i] == quote)
		(*qd->i)++;
}
