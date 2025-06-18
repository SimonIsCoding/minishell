# Minishell

A complete implementation of a Unix shell in C, featuring command execution, built-in commands, environment variable management, and advanced shell features like pipes, redirections, and here-documents.

## 📋 Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Core Components](#core-components)
- [Data Structures](#data-structures)
- [Execution Flow](#execution-flow)
- [Built-in Commands](#built-in-commands)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Error Handling](#error-handling)

## 🎯 Overview

Minishell is a comprehensive shell implementation that replicates the core functionality of bash, including:

- **Command parsing and execution**
- **Built-in commands** (echo, cd, pwd, export, unset, env, exit)
- **Environment variable management**
- **Variable expansion** ($VAR, $?)
- **Pipes and redirections** (|, >, <, >>, <<)
- **Here-documents** (<<)
- **Signal handling** (Ctrl+C, Ctrl+D)
- **Quote handling** (single and double quotes)
- **Word splitting and argument parsing**

## 📁 Project Structure

```
minishell/
├── includes/
│   ├── minishell.h      # Main header with all structures and function declarations
│   └── libft.h          # Library functions header
├── src/
│   ├── main.c           # Entry point and initialization
│   ├── lexer/           # Tokenization and lexical analysis
│   ├── parser/          # Command parsing and AST construction
│   ├── expander/        # Variable expansion and word splitting
│   ├── executor/        # Command execution and process management
│   ├── builtins/        # Built-in command implementations
│   ├── utils/           # Utility functions and signal handling
│   └── errors/          # Error handling and reporting
├── libft/               # Custom C library functions
├── readline-8.1/        # Readline library for command line editing
├── Makefile             # Build configuration
└── .gitignore           # Git ignore rules
```

## 🔧 Core Components

### 1. **The Lexer (Tokenizer)**
**Location**: `src/lexer/`

The lexer is the first crucial component that transforms raw input strings into structured tokens. It performs lexical analysis by breaking down the command line into meaningful units.

#### **What the Lexer Does:**
- **Tokenizes input**: Converts `"ls -la | grep .c"` into separate tokens
- **Identifies operators**: Recognizes pipes (|), redirections (>, <, >>, <<)
- **Handles quotes**: Processes single (') and double (") quotes as special tokens
- **Detects variables**: Identifies environment variable patterns ($VAR)
- **Preserves whitespace context**: Maintains information about spaces between tokens

#### **Token Types:**
```c
enum e_operator
{
    PIPE = 1,        // |
    RED_IN,          // <
    RED_OUT,         // >
    HDOC,            // <<
    RED_OUT_APP      // >>
};
```

#### **Lexer Structure:**
```c
typedef struct s_lexer
{
    char            *str;           // The actual token string
    enum e_operator token;          // Type of token (word, pipe, redirection)
    int             num_node;       // Position in the token list
    struct s_lexer  *next;          // Next token in the list
} t_lexer;
```

#### **Key Functions:**
- `lexer_tokenizer()`: **Main entry point** - orchestrates the entire tokenization process
- `put_word()`: **Extracts words** - handles commands, arguments, and filenames
- `put_operator()`: **Identifies operators** - processes pipes and redirections
- `find_next_quote()`: **Quote handling** - finds matching quotes and handles escaping

#### **Example Tokenization:**
```bash
Input: "ls -la | grep .c > output.txt"
Tokens: [ls] [-la] [|] [grep] [.c] [>] [output.txt]
Types:  [word] [word] [PIPE] [word] [word] [RED_OUT] [word]
```

### 2. **The Parser**
**Location**: `src/parser/`

The parser takes the tokenized input from the lexer and constructs an Abstract Syntax Tree (AST) that represents the command structure. It's responsible for understanding the command hierarchy and relationships.

#### **What the Parser Does:**
- **Builds command structure**: Creates nodes for each command separated by pipes
- **Processes redirections**: Associates redirections with their respective commands
- **Identifies built-ins**: Distinguishes between built-in and external commands
- **Validates syntax**: Checks for proper command structure and operator usage
- **Creates execution plan**: Prepares the command tree for execution

#### **Parser Structure:**
```c
typedef struct s_parser
{
    t_lexer         *lexer;         // Current position in token list
    t_lexer         *redirections;  // Redirections for current command
    int             num_redirections; // Count of redirections
    struct s_mini   *mini;          // Reference to main shell structure
} t_parser;
```

#### **Command Structure:**
```c
typedef struct s_cmd
{
    char            **str;          // Command and arguments array
    enum e_builtins builtin;        // Built-in command type (if applicable)
    int             num_redirections; // Number of redirections
    char            *hdoc_filename; // Here-document temporary filename
    t_lexer         *redirections;  // List of redirection tokens
    struct s_cmd    *next;          // Next command in pipeline
    struct s_cmd    *previous;      // Previous command in pipeline
} t_cmd;
```

#### **Key Functions:**
- `parser()`: **Main parsing function** - orchestrates the entire parsing process
- `redirections()`: **Processes redirections** - associates redirections with commands
- `new_cmd()`: **Creates command nodes** - allocates and initializes command structures
- `prepare_builtin()`: **Built-in detection** - identifies if command is a built-in

#### **Parsing Example:**
```bash
Input: "ls -la | grep .c > output.txt"
Parsed Structure:
┌─ Command 1 ──────────────┐    ┌─ Command 2 ──────────────┐
│ str: ["ls", "-la"]       │    │ str: ["grep", ".c"]      │
│ builtin: NOT_HAVE        │    │ builtin: NOT_HAVE        │
│ redirections: []         │    │ redirections: [>]        │
│ next: → Command 2        │    │ next: NULL               │
└──────────────────────────┘    └──────────────────────────┘
```

### 3. **The Expander**
**Location**: `src/expander/`

The expander handles variable substitution and word splitting. It's responsible for replacing environment variables with their actual values and preparing arguments for command execution.

#### **What the Expander Does:**
- **Variable expansion**: Replaces `$VAR` with actual environment variable values
- **Exit status expansion**: Expands `$?` with the last command's exit status
- **Word splitting**: Splits expanded variables on whitespace when appropriate
- **Quote removal**: Removes quotes after expansion while preserving meaning
- **Error handling**: Handles invalid variables and expansion errors

#### **Expansion Rules:**
- **Single quotes**: No expansion occurs inside single quotes
- **Double quotes**: Variables are expanded inside double quotes
- **Unquoted**: Variables are expanded and then word-split
- **Invalid variables**: Expand to empty string
- **Special variables**: `$?` expands to exit status, `$$` to process ID

#### **Key Functions:**
- `run_expander()`: **Main expansion function** - coordinates the entire expansion process
- `expand_the_line()`: **Variable expansion** - replaces variables with their values
- `word_splitting()`: **Word splitting** - splits expanded strings on whitespace
- `variable_existence()`: **Variable validation** - checks if environment variable exists
- `calculate_len_for_malloc()`: **Memory calculation** - determines required memory for expansion

#### **Expansion Example:**
```bash
Input: 'echo "Hello $USER, status: $?"'
Environment: USER=john, Last exit status=0
Expanded: 'echo "Hello john, status: 0"'
```

### 4. **The Executor**
**Location**: `src/executor/`

The executor is the heart of the shell that manages process creation, command execution, and process coordination. It handles both built-in commands and external programs.

#### **What the Executor Does:**
- **Process management**: Creates child processes using fork()
- **Command execution**: Uses execve() to run external commands
- **Pipe coordination**: Sets up pipes between commands in a pipeline
- **Redirection handling**: Manages file descriptors for input/output redirection
- **Built-in execution**: Directly executes built-in commands without forking
- **Process synchronization**: Waits for child processes to complete

#### **Execution Modes:**

##### **Single Command Execution:**
```c
void handle_single_cmd(t_mini *mini, t_cmd *cmd)
{
    // Check if it's a built-in command
    if (cmd->builtin != NOT_HAVE)
        do_builtin(mini, cmd);  // Execute directly
    else
        do_cmd(mini, cmd);      // Fork and exec
}
```

##### **Multiple Commands (Pipeline):**
```c
int executor(t_mini *mini)
{
    t_cmd *current = mini->cmd;
    int fds[2];
    int fd_in = STDIN_FILENO;
    
    while (current)
    {
        // Create pipe if there's a next command
        if (current->next)
            pipe(fds);
        
        // Fork and execute command
        ft_fork(mini, current, fds, fd_in);
        
        // Update file descriptors for next iteration
        if (current->next)
        {
            close(fds[1]);
            fd_in = fds[0];
        }
        current = current->next;
    }
    
    // Wait for all processes to complete
    wait_pipes(mini, mini->pid);
}
```

#### **Key Functions:**
- `executor()`: **Main execution function** - orchestrates command execution
- `ft_fork()`: **Process creation** - forks child processes and sets up execution
- `do_redirections()`: **Redirection setup** - configures file descriptors
- `handle_single_cmd()`: **Single command execution** - handles non-pipelined commands
- `wait_pipes()`: **Process synchronization** - waits for all child processes
- `ft_exec_cmd()`: **External command execution** - uses execve() to run programs

#### **Execution Flow Example:**
```bash
Command: "ls -la | grep .c | wc -l"
Execution:
1. Fork process 1: ls -la
2. Fork process 2: grep .c
3. Fork process 3: wc -l
4. Set up pipes: ls → grep → wc
5. Execute all processes
6. Wait for completion
7. Return exit status of last command
```

### 5. **Built-ins**
**Location**: `src/builtins/`

Built-in commands are implemented directly in the shell without creating separate processes. They have access to the shell's internal state and can modify environment variables and shell behavior.

#### **Built-in Command Types:**
```c
enum e_builtins
{
    ECHO = 1,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT,
    NOT_HAVE,  // Not a built-in command
};
```

#### **Implementation Details:**

##### **echo Command:**
```c
int builtin_echo(t_mini *mini, t_cmd *cmd)
{
    int i = 1;
    int newline = 1;
    
    // Check for -n flag
    if (cmd->str[1] && !ft_strcmp(cmd->str[1], "-n"))
    {
        newline = 0;
        i = 2;
    }
    
    // Print arguments
    while (cmd->str[i])
    {
        ft_putstr_fd(cmd->str[i], STDOUT_FILENO);
        if (cmd->str[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    
    // Add newline unless -n flag
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
    
    return (0);
}
```

##### **cd Command:**
```c
int builtin_cd(t_mini *mini, t_cmd *cmd)
{
    char *path;
    
    // Handle different cd scenarios
    if (!cmd->str[1] || !ft_strcmp(cmd->str[1], "~"))
        path = mini->home_env;  // Go to home directory
    else if (!ft_strcmp(cmd->str[1], "-"))
        path = mini->old_pwd;   // Go to previous directory
    else
        path = cmd->str[1];     // Go to specified directory
    
    return (do_cd(mini, path));
}
```

##### **export Command:**
```c
int builtin_export(t_mini *mini, t_cmd *cmd)
{
    int i = 1;
    
    // If no arguments, print all exported variables
    if (!cmd->str[1])
        return (print_env_export(mini, 1));
    
    // Process each argument
    while (cmd->str[i])
    {
        if (check_variable(cmd->str[i]))
            add_variable_to_env(mini, cmd->str[i]);
        else
            return (print_error(mini, EXPORT_ERROR));
        i++;
    }
    
    return (0);
}
```

#### **Key Functions:**
- `builtin_echo()`: **Echo implementation** - prints arguments with optional -n flag
- `builtin_cd()`: **Directory change** - changes current working directory
- `builtin_pwd()`: **Print working directory** - shows current directory path
- `builtin_export()`: **Environment export** - sets environment variables
- `builtin_unset()`: **Variable removal** - removes environment variables
- `builtin_env()`: **Environment display** - prints all environment variables
- `builtin_exit()`: **Shell exit** - exits shell with optional status code

### 6. **Here-documents (Heredoc)**
**Location**: `src/executor/hdoc.c`

Here-documents are a special form of input redirection that allows multi-line input to be passed to a command. They are processed before command execution.

#### **What Heredoc Does:**
- **Multi-line input**: Accepts multiple lines of input until a delimiter is found
- **Temporary file creation**: Stores input in a temporary file for later use
- **Variable expansion**: Expands variables within the here-document (unless quoted)
- **Quote handling**: Respects quotes in the delimiter and content
- **Memory management**: Creates and cleans up temporary files

#### **Heredoc Syntax:**
```bash
command << DELIMITER
line 1
line 2
line 3
DELIMITER
```

#### **Implementation Details:**
```c
int check_if_exists_hdoc(t_mini *mini, t_cmd *cmd)
{
    t_lexer *current = cmd->redirections;
    
    while (current)
    {
        if (current->token == HDOC)
        {
            // Generate unique filename for here-document
            cmd->hdoc_filename = generate_hdoc_filename();
            
            // Process here-document content
            if (!open_save_hdoc(mini, current, cmd->hdoc_filename, 
                               check_quotes_in_delimiter(current->str)))
                return (0);
        }
        current = current->next;
    }
    return (1);
}
```

#### **Key Functions:**
- `check_if_exists_hdoc()`: **Heredoc detection** - identifies here-documents in commands
- `open_save_hdoc()`: **Content processing** - reads and saves here-document content
- `check_eof()`: **Delimiter matching** - checks for end-of-file delimiter
- `remove_eof_quotes()`: **Quote removal** - removes quotes from delimiter for matching

#### **Heredoc Example:**
```bash
Input:
cat << EOF
Hello $USER
Current directory: $(pwd)
EOF

Processing:
1. Detect here-document with delimiter "EOF"
2. Read lines until "EOF" is found
3. Expand variables ($USER, $(pwd))
4. Save to temporary file
5. Redirect input from temporary file to cat command
```

### 7. **Single Command Execution**
**Location**: `src/executor/run_cmds.c`

Single command execution handles commands that don't involve pipes. It's the simplest execution mode where one command is executed directly.

#### **What Single Command Does:**
- **Built-in detection**: Checks if command is a built-in
- **Direct execution**: Executes built-ins without forking
- **Process creation**: Forks for external commands
- **Redirection handling**: Sets up input/output redirections
- **Error handling**: Manages execution errors and exit codes

#### **Implementation:**
```c
void handle_single_cmd(t_mini *mini, t_cmd *cmd)
{
    // Set up redirections first
    if (do_redirections(mini, cmd) == -1)
        return;
    
    // Check if it's a built-in command
    if (cmd->builtin != NOT_HAVE)
    {
        // Execute built-in directly (no fork needed)
        do_builtin(mini, cmd);
    }
    else
    {
        // Execute external command
        do_cmd(mini, cmd);
    }
}
```

#### **Execution Flow:**
1. **Redirection setup**: Configure file descriptors for input/output
2. **Built-in check**: Determine if command is built-in or external
3. **Execution**: Execute directly (built-in) or fork and exec (external)
4. **Cleanup**: Restore file descriptors and handle exit status

### 8. **Multiple Commands (Pipeline)**
**Location**: `src/executor/executor.c`

Pipeline execution handles multiple commands connected by pipes. It creates a chain of processes where the output of one command becomes the input of the next.

#### **What Multiple Commands Does:**
- **Process chain creation**: Creates multiple processes connected by pipes
- **Pipe coordination**: Sets up pipes between consecutive commands
- **File descriptor management**: Manages stdin/stdout redirection for each process
- **Process synchronization**: Waits for all processes to complete
- **Exit status handling**: Returns status of last command in pipeline

#### **Pipeline Implementation:**
```c
int executor(t_mini *mini)
{
    t_cmd *current = mini->cmd;
    int fds[2];
    int fd_in = STDIN_FILENO;
    int i = 0;
    
    // Allocate process ID array
    mini->pid = malloc(sizeof(int) * (mini->pipes + 1));
    
    while (current)
    {
        // Create pipe if there's a next command
        if (current->next && pipe(fds) == -1)
            return (print_error(mini, PIPE_ERROR));
        
        // Fork and execute command
        mini->pid[i] = ft_fork(mini, current, fds, fd_in);
        
        // Update file descriptors for next iteration
        if (current->next)
        {
            close(fds[1]);  // Close write end
            fd_in = fds[0]; // Next command reads from this pipe
        }
        
        current = current->next;
        i++;
    }
    
    // Wait for all processes to complete
    wait_pipes(mini, mini->pid);
    
    return (0);
}
```

#### **Pipeline Flow Example:**
```bash
Command: "ls -la | grep .c | wc -l"

Process Creation:
┌─────────────┐    ┌─────────────┐    ┌─────────────┐
│   ls -la    │───▶│  grep .c    │───▶│   wc -l     │
│   (PID 1)   │    │   (PID 2)   │    │   (PID 3)   │
└─────────────┘    └─────────────┘    └─────────────┘

File Descriptors:
ls: stdout → pipe1[1]
grep: stdin ← pipe1[0], stdout → pipe2[1]
wc: stdin ← pipe2[0]

Execution Steps:
1. Create pipe1 and pipe2
2. Fork ls process, redirect stdout to pipe1
3. Fork grep process, redirect stdin from pipe1, stdout to pipe2
4. Fork wc process, redirect stdin from pipe2
5. Execute all processes concurrently
6. Wait for all processes to complete
7. Return exit status of wc (last command)
```

#### **Key Functions:**
- `executor()`: **Main pipeline function** - orchestrates multi-command execution
- `ft_fork()`: **Process creation** - forks child processes and sets up execution
- `wait_pipes()`: **Process synchronization** - waits for all child processes
- `check_next_fd_in()`: **File descriptor management** - sets up input for next command

## 🏗️ Data Structures

### Main Shell Structure (`t_mini`)
```c
typedef struct s_mini
{
    char            *line;          // Current input line
    char            **original_env; // Original environment
    char            *pwd;           // Current working directory
    char            *old_pwd;       // Previous working directory
    char            *home_env;      // HOME environment variable
    t_env_lst       *env;           // Environment linked list
    char            **env_cpy;      // Environment array copy
    t_lexer         *lexer;         // Tokenized input
    int             pipes;          // Number of pipes
    int             count_infiles;  // Input file count
    int             flag_hdoc;      // Here-document flag
    int             flag_reset;     // Reset flag
    int             *pid;           // Process IDs array
    int             inside_cmd;     // Command execution flag
    int             inside_hdoc;    // Here-document flag
    int             outside_hdoc;   // Outside here-document flag
    int             error_code;     // Error status
    t_cmd           *cmd;           // Command linked list
} t_mini;
```

### Environment List (`t_env_lst`)
```c
typedef struct s_env_lst
{
    char            *key;           // Variable name
    char            *value;         // Variable value
    int             index;          // Position in list
    struct s_env_lst *next;         // Next node
} t_env_lst;
```

### Lexer Token (`t_lexer`)
```c
typedef struct s_lexer
{
    char            *str;           // Token string
    enum e_operator token;          // Token type
    int             num_node;       // Node index
    struct s_lexer  *next;          // Next token
} t_lexer;
```

### Command Structure (`t_cmd`)
```c
typedef struct s_cmd
{
    char            **str;          // Command arguments
    enum e_builtins builtin;        // Built-in type
    int             num_redirections; // Redirection count
    char            *hdoc_filename; // Here-document filename
    t_lexer         *redirections;  // Redirection tokens
    struct s_cmd    *next;          // Next command
    struct s_cmd    *previous;      // Previous command
} t_cmd;
```

## 🔄 Execution Flow

1. **Initialization**
   - Parse command line arguments
   - Initialize environment variables
   - Set up signal handlers
   - Save current working directory

2. **Main Loop** (`mini_live()`)
   - Display prompt using readline
   - Read user input
   - Handle Ctrl+D (EOF)
   - Process input line

3. **Lexical Analysis**
   - Tokenize input string
   - Identify operators and words
   - Handle quotes and escaping

4. **Parsing**
   - Build command structure
   - Separate commands by pipes
   - Process redirections
   - Identify built-in commands

5. **Expansion**
   - Expand environment variables
   - Handle exit status ($?)
   - Perform word splitting
   - Remove quotes

6. **Execution**
   - Execute built-in commands directly
   - Fork processes for external commands
   - Set up pipes and redirections
   - Wait for completion

7. **Cleanup**
   - Free allocated memory
   - Reset shell state
   - Return to main loop

## 🛠️ Built-in Commands

### echo
```bash
echo [-n] [string...]
```
- Prints arguments to stdout
- `-n` flag suppresses newline
- Handles escape sequences

### cd
```bash
cd [directory]
```
- Changes current directory
- Supports relative and absolute paths
- Handles `cd -` (previous directory)
- Updates PWD and OLDPWD variables

### pwd
```bash
pwd
```
- Prints current working directory
- Uses getcwd() system call

### export
```bash
export [name[=value]...]
```
- Sets environment variables
- Validates variable names
- Handles quoted values
- Prints all variables when no arguments

### unset
```bash
unset [name...]
```
- Removes environment variables
- Validates variable names
- Handles multiple variables

### env
```bash
env
```
- Prints all environment variables
- Format: `name=value`

### exit
```bash
exit [n]
```
- Exits shell with status code
- Validates numeric arguments
- Handles multiple arguments error

## ✨ Features

### Variable Expansion
- **Environment variables**: `$HOME`, `$PATH`
- **Exit status**: `$?`
- **Invalid variables**: Expand to empty string
- **Quoted variables**: Different behavior in quotes

### Redirections
- **Input redirection**: `< file`
- **Output redirection**: `> file`
- **Append redirection**: `>> file`
- **Here-document**: `<< EOF`

### Pipes
- **Multiple pipes**: `cmd1 | cmd2 | cmd3`
- **Process coordination**: Proper pipe setup
- **Error handling**: Pipe creation failures

### Signal Handling
- **SIGINT (Ctrl+C)**: Interrupts current command
- **SIGQUIT (Ctrl+\)**: Quit signal
- **Child processes**: Proper signal propagation

### Quote Handling
- **Single quotes**: Literal interpretation
- **Double quotes**: Variable expansion allowed
- **Nested quotes**: Proper parsing
- **Unclosed quotes**: Error handling

## 🚀 Installation

### Prerequisites
- GCC compiler
- Make utility
- Readline library (included in project)

### Build Instructions
```bash
# Clone the repository
git clone <repository-url>
cd minishell

# Build the project
make

# Run minishell
./minishell
```

### Build Options
```bash
make        # Build minishell
make clean  # Remove object files
make fclean # Remove all build files
make re     # Rebuild from scratch
```

## 💻 Usage

### Basic Commands
```bash
# Simple command execution
$ ls -la

# Environment variables
$ echo $HOME
$ export MY_VAR="hello world"
$ echo $MY_VAR

# Pipes
$ ls | grep .c | wc -l

# Redirections
$ echo "hello" > file.txt
$ cat < file.txt
$ ls >> output.log
```

### Advanced Features
```bash
# Here-documents
$ cat << EOF
> This is a here-document
> It ends with EOF
> EOF

# Multiple commands
$ ls -la && echo "success" || echo "failed"

# Variable expansion in quotes
$ echo "Current user: $USER"
$ echo 'Current user: $USER'  # No expansion
```

## ⚠️ Error Handling

The shell implements comprehensive error handling:

### Syntax Errors
- **Unclosed quotes**: Reports syntax error
- **Invalid operators**: Detects malformed redirections
- **Empty commands**: Handles empty input gracefully

### Execution Errors
- **Command not found**: Reports with appropriate message
- **Permission denied**: Handles file access errors
- **File not found**: Reports missing files/directories

### Memory Management
- **Malloc failures**: Graceful handling of memory allocation errors
- **Memory leaks**: Proper cleanup of allocated resources
- **Process cleanup**: Ensures child processes are properly terminated

### Error Codes
- **0**: Success
- **1**: General error
- **2**: Syntax error
- **126**: Command not executable
- **127**: Command not found
- **128+n**: Signal n

## 🔍 Testing

The shell can be tested with various scenarios:

```bash
# Test built-in commands
$ echo "test"
$ pwd
$ cd /tmp && pwd

# Test variable expansion
$ export TEST_VAR="hello"
$ echo $TEST_VAR
$ echo "$TEST_VAR"
$ echo '$TEST_VAR'

# Test pipes and redirections
$ ls | grep .c > files.txt
$ cat < files.txt | wc -l

# Test error handling
$ nonexistent_command
$ cd /nonexistent/directory
$ echo "unclosed quote
```

## 📝 Notes

- The shell follows POSIX standards for command behavior
- Signal handling is implemented for proper shell behavior
- Memory management is carefully handled to prevent leaks
- The project includes comprehensive error handling
- All built-in commands are implemented according to bash specifications

## 🤝 Contributing

This project was developed as part of the 42 school curriculum. The implementation follows strict coding standards and includes comprehensive error handling and memory management.

## 📚 References

### Official Documentation
- **[GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)** - The definitive reference for Bash shell behavior and features. This manual provides comprehensive documentation on shell syntax, built-in commands, expansions, redirections, and all other shell features that served as the specification for this minishell implementation.

### Related Projects
- **[minishell by maiadegraaf](https://github.com/maiadegraaf/minishell)** - Another implementation of the minishell project from 42 school. This repository provides additional insights and alternative approaches to implementing shell functionality, serving as a valuable reference for understanding different design patterns and implementation strategies.