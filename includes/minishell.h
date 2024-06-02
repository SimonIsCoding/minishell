/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/29 16:04:57 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> // Open 
# include <string.h> //Macros
# include <dirent.h>
# include <sys/wait.h> // wait waitpid
# include <limits.h> // macros??
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# define QUOTE		39
# define DQUOTE		34
# define BACKSLASH	92

// STRUCTS

// Builtins

//s_env
typedef struct	s_builtin
{
	char				*key;
	char				*value;
	int					index;//this variable may be useless
	struct s_builtin	*next;
}				t_builtin;

// signals global variable

typedef struct	s_global_var
{
	int		inside_cmd;
	int		inside_hdoc;
	int		outside_hdoc; //stop
	int		error_code;
}				t_global_var;

t_global_var		g_global_var;

// 		Main struct

typedef struct s_mini
{
	char					*line;
	char					**original_env;
	char					*pwd;
	char					*old_pwd;
	t_builtin				*env;
	// hacer free solo al final exit
	char					**env_cpy;
	struct s_lexer			*lexer;
	int						pipes;
	int						count_infiles;
	int						flag_hdoc;
	int						*pid;
	int						error_code;
	struct s_cmd		*cmd;
	// meter tu estructura de builtins
	//t_builtin
}	t_mini;

//		Enum for builtins

enum	e_builtins
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NOT_HAVE,
};

//		Enum for code errors

enum	e_error_codes
{
	SINTAX_ERROR = 1,
	MALLOC_ERROR,		// allocation error
	IN_ERROR,			// infile error
	OUT_ERROR,			// outfile error
	PIPE_ERROR,
	FORK_ERROR,
	DUP2_ERROR,
	CMD_NOT_FOUND_ERROR,
	EXECVE_ERROR,
	EXIT_ERROR,
	CD_ERROR,
	UNLINK_ERROR,
};
//		Enum for operators

enum e_operator
{
	PIPE = 1, 		// |
	RED_IN,			// <
	RED_OUT,		// >
	HDOC,			// <<
	RED_OUT_APP,	// >>
};

//		Struct for the lexer/tokenizer

typedef struct s_lexer
{
	char				*str;
	enum e_operator		token;
	int					num_node;
	struct s_lexer		*next;
}	t_lexer;

//		Struct for parser

typedef struct s_parser
{
	t_lexer			*lexer;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_mini	*mini;
}	t_parser;


//typedef void (*builtin)(t_mini *mini, t_cmd *cmd);

typedef struct s_cmd
{
	char					**str;
	enum e_builtins			builtin;
	int						num_redirections;
	char					*hdoc_filename;
	t_lexer					*redirections;
	struct s_cmd		*next;
	struct s_cmd		*previous;
}	t_cmd;

// Test functions

void			ft_print(t_mini *mini);
void			ft_print_parser(t_mini *mini);
void			builtin_test(void);



// Minishell loop

int 			mini_live(t_mini *mini);
void			init_mini(t_mini *mini, char **env);
int				mini_reset(t_mini *mini);

// Init main struct
//t_builtin		*create_env(t_mini *mini, t_builtin *lst_env);
void			concat_lst_env(t_mini *mini);

// Lexer

int				lexer_tokenizer(t_mini *mini);
int				put_word(char *str, int i, t_lexer **lst);
int 			find_next_quote(char c, char *str, int i);
int				put_operator(char *str, int i, t_lexer **lst);
int				check_operator(int c);
void			clear_line(t_mini *mini);

// Parser

int				parser(t_mini *mini);
t_parser		init_struct(t_lexer *lexer, t_mini *mini);
t_cmd			*create_cmd(t_mini *mini, t_parser *parser);
void			redirections(t_mini *mini, t_parser *parser);
void			lst_clear_parser(t_cmd **lst);

// Parser utils

t_cmd			 *new_cmd(char **str, int num_redirects, t_lexer *redirections);
int				prepare_builtin(char *str);
void			count_pipes(t_mini *mini);
int				count_args(t_lexer *lst);
t_lexer			*move_to_next_cmd(t_lexer *lst);
void			ft_node_add_back_parser(t_cmd **lst, t_cmd *node);
int				check_line(t_mini *mini);

int				lst_size_cmd(t_mini *mini);
t_cmd			*clear_one_cmd(t_cmd **lst);
void			del_first_cmd(t_cmd **lst);
void			lst_clear_cmds(t_cmd **cmd);
void			free_cmd_line(char **str);

// Built-ins

int				builtin_pwd(t_mini *mini);
int				builtin_exit(t_mini *mini, t_cmd *cmd);
int				builtin_env(t_mini *mini);
int				builtin_export(t_mini *mini, t_cmd *cmd);
int				builtin_unset(t_mini *mini, t_builtin **head, t_cmd *cmd);
int				builtin_echo(t_mini *mini, t_cmd *cmd);
int				builtin_cd(t_mini *mini, t_cmd *cmd);
// cd

// Utils builtins

int				get_pwd(t_mini *mini);
//t_builtin		*create_env(t_mini *mini, t_builtin *lst_env);
t_builtin		*create_builtin_lst(t_mini *mini, t_builtin *lst_env, char **env);
//t_builtin		*create_builtin_lst(t_mini *mini, char **env);
t_builtin		*ft_lstnew_builtin(t_mini *mini, char *str);
void			ft_lstadd_back_builtin(t_builtin **lst, t_builtin *new);
void			ft_lstclear_builtin(t_builtin **lst);
int				ft_lstsize_builtin(t_builtin *lst);
void			print_list(t_builtin **lst_env);//do you really use it ?
char			*get_key_from_env(t_mini *mini, char *str);
char			*get_value_from_env(t_mini *mini, char *str);
t_builtin		*init_builtin_node(char **env);
void			remove_special_node(t_builtin **head);
t_builtin		*sort_ascii(t_builtin *lst_export, t_builtin *sorted);
int				check_variable(char *str);
char			*clean_value(char *str);//YOU MIGHT HAVE A LEAK

void			print_env_export(t_mini *mini, int flag);
char			**delete_variable(char **old_env, char *str);
char			**create_new_env(char **old_env, char **new_env, char *variable);
int				detect_unset_error(t_cmd *cmd);

t_builtin		*clear_one_node_env(t_builtin **lst);
void			del_first_node_env(t_builtin **lst);
void			delone_node_env(int num_del, t_builtin **lst);

// Expander

void			run_expander(t_mini *mini, t_cmd *cmd);
char   			*expand_str_line(t_mini *mini, char *str);
char			**expand_cmd_line(t_mini *mini, char **str);
int				calculate_malloc_size(char *str);
char			*search_and_replace_variable(t_builtin *env_variable, char *expand_name);
//char			*search_and_replace_variable(t_mini *mini, t_builtin *env_variable, char *expand_name);
char			*get_expansion_key(t_mini *mini, char *str);
char			*catch_expansion_key(t_mini *mini, char *str, int *i);
char			*expanded_string(t_mini *mini, char *str);
int				count_env_variable(t_mini *mini, char *line);
int				variable_existence(t_mini *mini, char *line, int i);
//void			send_line(t_mini *mini, char *str);
void			forget_the_variable(char *str, int *i);
int				calculate_len_for_malloc(t_mini *mini, char *str);
char			*expand_the_line(t_mini *mini, char *str);
char			*expand_the_line_lead_zero(t_mini *mini, char *str);
//int				about_quotes(t_mini *mini, char *str);
char			*quit_single_quotes(t_mini *mini, char *str);
int				update_the_situation(char c, int lead);
//void			check_the_situation(char *str);
char			*final_expansion(t_mini *mini, char *str);
int				possible_env(char *str, int i);


// Utils expander

int 			is_dollar(char *str);
int 			is_equal(char *str);

// Executor

int				pre_executor(t_mini *mini);
void			handle_single_cmd(t_mini *mini, t_cmd *cmd);

int				executor(t_mini *mini);
int				ft_fork(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in);
void			ft_dup(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in);
void			ft_exec_cmd(t_mini *mini, t_cmd *cmd);
//char			*find_check_path(t_mini *mini, char *cmd, char **env);
t_builtin		*find_node_path(t_builtin *lst_env);
//char			*check_path(char *cmd, t_builtin *lst_env);
int				do_cmd(t_mini *mini, t_cmd *cmd_lst);
int				do_builtin(t_mini *mini, t_cmd *cmd);
void			handle_single_cmd(t_mini *mini, t_cmd *cmd);
void			wait_pipes(t_mini *mini, int *pid, int pipes);
int				check_next_fd_in(t_mini *mini, t_cmd *cmd, int fds[2]);


// Redirections

int				do_redirections(t_mini *mini, t_cmd *cmd);
int				put_infile(t_mini *mini, char *filename);
int				put_outfile(t_mini *mini, t_lexer *lex, char *filename);



// Hdoc

int				check_if_exists_hdoc(t_mini *mini, t_cmd *cmd);
char			*generate_filename(void);
int				check_eof(t_mini *mini, t_lexer	*redir, char *hdoc_filename);
int				open_save_hdoc(t_lexer *redir, char *hdoc_filename, bool quotes);
void			remove_eof_quotes(t_lexer *node);

// Utils nodes

t_lexer			*ft_new_node(char *str, int token);
void			ft_node_add_back(t_lexer **lst, t_lexer *node);
int				list_add_node(t_lexer **lst, enum e_operator token, char *str);
void			clear_one_node(t_lexer **lst);
void			del_first_node(t_lexer **lst);
void			delone_node(int num_del, t_lexer **lst);
int				lst_size_lexer(t_mini *mini);
void			lst_clear_lexer(t_lexer **lst);
void			lexer_clear(t_lexer **list);

// Signals

void    init_signals(void);
void    sigquit_handler(int signal);
void    sigint_handler(int signal);



// Random utils

//void			check_quotes(char *line);
int				 check_quotes_is_married(char *line);


// Errors

int				print_error(t_mini *mini, int keycode);
int				token_error(t_mini *mini, int token);

#endif
