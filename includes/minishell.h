/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:25:06 by clnicola          #+#    #+#             */
/*   Updated: 2025/12/15 15:25:46 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum s_token_type
{
	WORD,
	VAR,
	PIPE,
	HEREDOC,
	APPEND,
	INPUT,
	TRUNC,
	END,
	VOID,
}						t_token_type;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				*token;
	t_token_type		type;
	struct s_token		*previous;
	struct s_token		*next;
}						t_token;

typedef struct s_redir
{
	int					type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char				*input;
	pid_t				pid;
	int					type;
	t_command			*cmd;
	t_token				*token;
	t_env				*env;
	int					last_exit_status;
}						t_data;

typedef struct s_quote_data
{
	char				*str;
	int					*i;
	char				*result;
	int					*j;
	t_data				*data;
}						t_quote_data;

typedef struct s_fork_data
{
	char				**env;
	t_data				*data;
}						t_fork_data;

typedef struct s_env_set_args
{
	t_env				*curr;
	t_env				*prev;
	char				*name;
	char				*value;
}						t_env_set_args;

typedef struct s_expand_data
{
	char				*str;
	int					*i;
	char				*res;
	int					*j;
	int					len;
	t_data				*data;
}						t_expand_data;

/*------PARSING------*/
t_token					*ft_word_to_token(char *input, t_data *data);
void					ft_parsing(t_data *data, char *input);
char					*extract_operator(char *str, int *i);
t_token					*ft_new_token(char *value, t_token_type type);
void					ft_add_back_token(t_token **head, t_token *new);
t_token					*ft_make_token(char *input, int *i, t_data *data);
void					ft_assign_token_type(t_data *data);
char					*extract_word(char *str, int *i, t_data *data);
char					*build_unquoted_token(char *str, int *i, int len,
							t_data *data);
void					copy_quoted(t_quote_data *qd);
char					*expand_variable(char *str, int *i, t_data *data);
char					*build_expanded_token(char *str, int *i, int len,
							t_data *data);
t_command				*parse_tokens(t_token *tok);
t_command				*new_cmd(void);
t_command				*ft_new_command(int arg_count);
void					add_arg(t_command *cmd, char *arg);
void					add_redir(t_command *cmd, int type, char *file);
t_command				*ft_tokens_to_commands(t_token *token_list);
void					ft_add_back_command(t_command **head, t_command *new);
int						ft_count_args(t_token *token_list);
char					**ft_build_args(t_token *token_list, int arg_count);
t_token					*ft_skip_to_next_pipe(t_token *token_list);
void					ft_display_commands(t_command *cmd);
char					*get_var_value(char *str, int *i, t_data *data);

/*------UTILS------*/
void					ft_free_tabs(char **args);
char					*ft_get_path(char **env);
char					*ft_get_cmd(char **env, char *cmd);
void					ft_handle_cmd_errors(char **args, char *path);
char					*ft_prompt_name(void);
int						ft_strisnum(char *str);
int						ft_is_space(char c);
int						ft_is_operator(char c);

/*------EXECUTION------*/
void					execute_pipeline(t_command *cmd, char **env,
							t_data *data);
int						fork_and_execute(t_command *cmd, int prev_fd,
							int pipe_fd[2], char **env_and_data);

/*------BUILTIN------*/
int						is_builtin_cmd(char *cmd);
void					builtin_commands(t_data *data);
void					builtin_echo(t_data *data);
int						builtin_echo_status(t_data *data);
int						builtin_cd_status(t_data *data);
int						builtin_pwd_status(t_data *data);
int						builtin_export_status(t_data *data);
int						builtin_unset_status(t_data *data);
int						builtin_env_status(t_data *data);
int						builtin_exit_status(t_data *data);
char					*ft_export_noargs(t_env **env);
void					ft_export(char **args, t_env **env);
char					*ft_env(t_env **env);
void					ft_unset(char **args, t_env **env);
char					*ft_pwd(void);
int						ft_cd(char *path, t_env **env);
void					builtin_exit(t_data *data);

/*---COMMANDS_UTILS---*/
int						ft_set_env(char *name, char *value, t_env **env);
char					*ft_get_env_value(char *name, t_env **env);
int						ft_rm_env(char *name, t_env **env);
t_env					*ft_initialize_env(void);
t_env					*ft_new_env_var(char *name, char *value, t_env *next);
t_env					**ft_copy_env(t_env **env);
void					ft_swap_env(t_env **env, t_env *to_swap);
void					ft_free_env(t_env **env);
char					**ft_env_to_array(t_env **env);
int						ft_count_env_vars(t_env **env);
char					*ft_build_env_string(char *name, char *value);
void					ft_fill_env_array(char **result, t_env **env);
#endif
