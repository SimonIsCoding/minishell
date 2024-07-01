/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/25 16:15:04 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define QUOTE			39
# define DQUOTE			34
# define BACKSLASH		92
//# define LONG_LONG_MAX	9223372036854775807
//# define LONG_LONG_MIN 	-9223372036854775808

// STRUCTS

extern int	g_status;

// 		Main struct

typedef struct s_mini
{
	char					*line;
	char					**original_env;
	char					*pwd;
	char					*old_pwd;
	char					*home_env;
	struct s_env_lst		*env;
	char					**env_cpy;
	struct s_lexer			*lexer;
	int						pipes;
	int						count_infiles;
	int						flag_hdoc;
	int						flag_reset;
	int						*pid;
	int						inside_cmd;
	int						inside_hdoc;
	int						outside_hdoc;
	int						error_code;
	struct s_cmd			*cmd;
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

enum	e_error_codes
{
	SINTAX_ERROR = 1,
	MALLOC_ERROR,
	IN_ERROR,
	OUT_ERROR,
	PIPE_ERROR,
	FORK_ERROR,
	DUP2_ERROR,
	CMD_NOT_FOUND_ERROR,
	EXECVE_ERROR,
	EXIT_ERROR,
	CD_ERROR,
	UNLINK_ERROR,
	MAX_HDOC,
	UNSET_HOME,
	EXPORT_ERROR,
	RANDOM,
};

enum e_operator
{
	PIPE = 1,
	RED_IN,
	RED_OUT,
	HDOC,
	RED_OUT_APP
};

// ------------------------------------------------------------------------ //

//     Struct for the environment variable parser.

// env list => A structure containing the environment
			// formatted as a linked list.

typedef struct s_env_lst
{
	char				*key;
	char				*value;
	int					index;
	struct s_env_lst	*next;
}				t_env_lst;

// ------------------------------------------------------------------------ //

//		Struct for the lexer/tokenizer

typedef struct s_lexer
{
	char				*str;
	enum e_operator		token;
	int					num_node;
	struct s_lexer		*next;
}	t_lexer;

// for example if we have:
// ls -l > outfile
// this structure has to classify the word of the line we received
												//   Example:
// letters separated by space.                       'ls' '-l' '>' 'outfile'
// the number that corresponds to the operator list.  0    0    3     0
// the index of the node in the list				  0    1    2     3

// ------------------------------------------------------------------------ //

//		Struct for parser

typedef struct s_parser
{
	t_lexer			*lexer;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_mini	*mini;
}	t_parser;

// Acts as a connector/intermediary between the lexer list and cmd list.
//ls -l > outfile
// lexer ==> Constantly updated lexer list, 
		//   removes pipe-to-pipe nodes as it creates cmd nodes.
// redirects ==> Contains the identified redirections for each cmd node.
// num_redirects ==> Simple redirection counter for later control.

//typedef void (*builtin)(t_mini *mini, t_cmd *cmd);

// ------------------------------------------------------------------------ //

//      Struct for CMDS

typedef struct s_cmd
{
	char					**str;
	enum e_builtins			builtin;
	int						num_redirections;
	char					*hdoc_filename;
	t_lexer					*redirections;
	struct s_cmd			*next;
	struct s_cmd			*previous;
}	t_cmd;

//this is the structre that contains all the commands of the line received
//our command node this structure. 1 node represents 1 command.
//1 command means everything before encountering a pipe or the end of line
//for example : ls -l | echo a > outfile

// str = command line between pipes. [[ls][-l]] || [[echo][a]]
// builtin = Identifies if it is a builtin or not for later control.
// num_redirects = Simple redirection counter for later control.
// hdoc_filename = If we identify a here-document (hdoc), we generate
				// a filename and place it there, differentiating the
				// filename from the redirection to a here-document.
// redirections = List containing redirection tokens and filenames.
			//    Or in the case of hdoc, it contains the EOF.

// ------------------------------------------------------------------------ //

// Test functions

void			ft_print(t_mini *mini);
void			ft_print_parser(t_mini *mini);

// Minishell loop

int				mini_live(t_mini *mini);
void			init_mini(t_mini *mini, char **env);
int				mini_reset(t_mini *mini);

// Init main struct

void			concat_lst_env(t_mini *mini);

// Lexer

int				lexer_tokenizer(t_mini *mini);
int				put_word(char *str, int i, t_lexer **lst);
int				find_next_quote(char c, char *str, int i);
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

t_cmd			*new_cmd(char **str, int num_redirects, t_lexer *redirections);
int				prepare_builtin(char *str);
void			count_pipes(t_mini *mini);
int				count_args(t_lexer *lst);
void			ft_node_add_back_parser(t_cmd **lst, t_cmd *node);
int				check_line(t_mini *mini);
int				lst_size_cmd(t_mini *mini);
t_cmd			*clear_one_cmd(t_cmd **lst);
void			lst_clear_cmds(t_cmd **cmd);
void			free_cmd_line(char **str);

// Built-ins

int				builtin_pwd(t_mini *mini);
int				builtin_exit(t_mini *mini, t_cmd *cmd);
int				builtin_env(t_mini *mini);
int				builtin_export(t_mini *mini, t_cmd *cmd);
int				builtin_unset(t_mini *mini, t_env_lst **head, t_cmd *cmd);
int				builtin_echo(t_mini *mini, t_cmd *cmd);
int				builtin_cd(t_mini *mini, t_cmd *cmd);

// Utils builtins

int				get_pwd(t_mini *mini);
void			create_builtin_lst(t_mini *mini,
					t_env_lst **lst_env, char **env);
t_env_lst		*ft_lstnew_builtin(t_mini *mini, char *str);
void			ft_lstadd_back_builtin(t_env_lst **lst, t_env_lst *new);
void			ft_lstclear_builtin(t_env_lst **lst);
int				ft_lstsize_builtin(t_env_lst *lst);
char			*get_key_from_env(t_mini *mini, char *str);
char			*get_value_from_env(t_mini *mini, char *str);
void			remove_special_node(t_env_lst **head);
int				check_variable(char *str);
char			*clean_value(t_mini *mini, char *str);
char			*value_to_export(t_mini *mini, const char *str,
					const char quote_to_del);
char			*value_with_quotes(t_mini *mini, char *str);
char			*modify_line(t_mini *mini, char *str);
char			*modify_line_aux(char **env, char *tmp);
char			*return_value(t_mini *mini, char *str);
t_env_lst		*sort_ascii(t_env_lst *lst_export, t_env_lst *sorted);
void			print_env_export(t_mini *mini, int flag);
int				lines_counter(char **array);
int				check_zero(char *str);
int				ft_isdigit_and_signs(char *str);
int				numeric_argument_required(char *str);
int				check_exit_many_arguments(char *str);
int				check_exit_number(char *str_user, char *positive_lim,
					char *negative_lim);
int				exit_with_one_argument(t_mini *mini, char *str1, char *str2);
void			free_elements(char *str1, char *str2);
void			free_mini(t_mini *mini);
t_env_lst		*clear_one_node_env(t_env_lst **lst);
void			del_first_node_env(t_env_lst **lst);
void			delone_node_env(int num_del, t_env_lst **lst);
void			cd_dash(t_mini *mini, int *error);
int				do_cd(t_mini *mini, char *path);

// Expander

void			run_expander(t_mini *mini, t_cmd *cmd);
char			*expand_str_line(t_mini *mini, char *str);
char			**expand_cmd_line(t_mini *mini, char **str);
char			*search_and_replace_variable(t_env_lst *env_variable,
					char *expand_name);
char			*catch_expansion_key(t_mini *mini, char *str, int *i);
int				variable_existence(t_mini *mini, char *line, int i);
void			forget_the_variable(char *str, int *i);
int				expand_error_code(t_mini *mini, int *i, char *result);
char			*expand_the_line(t_mini *mini, char *str);
char			*expand_the_line_lead_zero(t_mini *mini, char *str);
char			*final_expansion(t_mini *mini, char *str);

// Utils expander

int				update_the_situation(char c, int lead);
int				invalid_characters(const char *str);
int				is_dollar(char *str);
int				is_equal(char *str);
void			create_space_for_error_code(t_mini *mini, int *i, int *counter);
void			iterate_classic_characters(char *str, int *i, int *counter);
int				check_cd_home(t_mini *mini, t_cmd *cmd);
int				calculate_len_for_malloc(t_mini *mini, char *str);

// Executor

int				pre_executor(t_mini *mini);
void			handle_single_cmd(t_mini *mini, t_cmd *cmd);
int				executor(t_mini *mini);
int				ft_fork(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in);
void			ft_dup(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in);
void			ft_exec_cmd(t_mini *mini, t_cmd *cmd);
t_env_lst		*find_node_path(t_env_lst *lst_env);
int				do_cmd(t_mini *mini, t_cmd *cmd_lst);
int				do_builtin(t_mini *mini, t_cmd *cmd);
void			handle_single_cmd(t_mini *mini, t_cmd *cmd);
void			wait_pipes(t_mini *mini, int *pid);
int				check_next_fd_in(t_mini *mini, t_cmd *cmd, int fds[2]);
void			ft_free_paths(char **str);
int				not_found(char *str);

// Redirections

int				do_redirections(t_mini *mini, t_cmd *cmd);
int				put_infile(t_mini *mini, char *filename);
int				put_outfile(t_mini *mini, t_lexer *lex, char *filename);

// Hdoc

void			set_up_signals_hdoc(void);
int				check_if_exists_hdoc(t_mini *mini, t_cmd *cmd);
char			*generate_filename(void);
int				check_eof(t_mini *mini, t_lexer	*redir, char *hdoc_filename);
int				open_save_hdoc(t_mini *mini, t_lexer *redir,
					char *hdoc_filename, bool quotes);
void			remove_eof_quotes(t_lexer *node);
void			check_max_hdoc(t_mini *mini, t_lexer *redirects);

// Utils nodes

t_lexer			*ft_new_node(char *str, int token);
void			ft_node_add_back(t_lexer **lst, t_lexer *node);
int				list_add_node(t_lexer **lst, enum e_operator token, char *str);
void			clear_one_node(t_lexer **lst);
void			del_first_node(t_lexer **lst);
void			delone_node(int num_del, t_lexer **lst);
int				lst_size_lexer(t_mini *mini);
void			lexer_clear(t_lexer **list);

// Signals

void			init_signals(void);
void			sigint_handler(int signal);
void			sigquit_handler(int signal);

// Random utils

int				check_quotes_is_married(char *line);
char			*get_home_value(t_mini *mini);
int				save_pwd(t_mini *mini, char **env);

// Errors

int				print_error(t_mini *mini, int keycode);
int				token_error(t_mini *mini, int token);

#endif
