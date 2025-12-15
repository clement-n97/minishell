/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:25:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 13:13:39 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *str, int *i, t_data *data)
{
	int		start;
	int		len;
	char	*var_name;
	char	*value;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start, len);
	value = ft_get_env_value(var_name, &data->env);
	free(var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*build_unquoted_token(char *str, int *i, int len, t_data *data)
{
	char	*res;
	int		j;

	(void)data;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (str[*i] && j < len)
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			res[j] = '\0';
			return (res);
		}
		if (ft_is_space(str[*i]) || ft_is_operator(str[*i]))
			break ;
		res[j++] = str[(*i)++];
	}
	res[j] = '\0';
	return (res);
}

static void	process_expanded_char(t_expand_data *ed)
{
	char			*exp;
	int				k;
	t_quote_data	qd;

	if (ed->str[*ed->i] == '\'' || ed->str[*ed->i] == '"')
	{
		qd.str = ed->str;
		qd.i = ed->i;
		qd.result = ed->res;
		qd.j = ed->j;
		qd.data = ed->data;
		copy_quoted(&qd);
	}
	else if (ed->str[*ed->i] == '$')
	{
		exp = expand_variable(ed->str, ed->i, ed->data);
		k = 0;
		while (exp && exp[k] && *ed->j < ed->len)
			ed->res[(*ed->j)++] = exp[k++];
		free(exp);
	}
	else
		ed->res[(*ed->j)++] = ed->str[(*ed->i)++];
}

static void	expand_token_loop(t_expand_data *ed)
{
	while (ed->str[*ed->i] && *ed->j < ed->len)
	{
		if (ed->str[*ed->i] == '\'' || ed->str[*ed->i] == '"'
			|| ed->str[*ed->i] == '$')
			process_expanded_char(ed);
		else if (ft_is_space(ed->str[*ed->i])
			|| ft_is_operator(ed->str[*ed->i]))
			break ;
		else
			ed->res[(*ed->j)++] = ed->str[(*ed->i)++];
	}
}

char	*build_expanded_token(char *str, int *i, int len, t_data *data)
{
	char			*res;
	int				j;
	int				capacity;
	t_expand_data	ed;

	capacity = len * 4 + 256;
	res = malloc(capacity);
	if (!res)
		return (NULL);
	j = 0;
	ed.str = str;
	ed.i = i;
	ed.res = res;
	ed.j = &j;
	ed.len = capacity - 1;
	ed.data = data;
	expand_token_loop(&ed);
	res[j] = '\0';
	return (res);
}
