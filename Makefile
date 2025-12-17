NAME = minishell

CC = cc
C_FLAGS = -Wall -Wextra -Werror -no-pie

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

LIBFT_PATH = ./includes/Libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC = main.c\
builtin/main_builtin.c\
builtin/builtin_status.c\
builtin/builtin_status_env.c\
builtin/ft_cd.c\
builtin/ft_env.c\
builtin/ft_exit.c\
builtin/ft_export.c\
builtin/ft_pwd.c\
builtin/ft_unset.c\
builtin/builtin_echo.c\
builtin/env_utils.c\
builtin/env_utils_2.c\
builtin/env_utils_3.c\
parsing/main_parsing.c\
parsing/parsing_helpers.c\
parsing/lexer_utils.c\
parsing/word_extraction.c\
parsing/word_expansion.c\
parsing/quote_handler.c\
parsing/command_parser.c\
parsing/command_builder.c\
parsing/command_converter.c\
parsing/command_converter_utils.c\
parsing/command_converter_args.c\
parsing/tokenizer.c\
execution/pipe_handler.c\
execution/pipe_executor.c\
utils/utils.c\
utils/utils1.c\
utils/utils_path.c\
signal/signals.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(SRCS:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)
INC = -I $(INC_PATH) -I $(LIBFT_PATH)

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)builtin
	mkdir -p $(OBJ_PATH)parsing
	mkdir -p $(OBJ_PATH)execution
	mkdir -p $(OBJ_PATH)utils
	mkdir -p $(OBJ_PATH)signal

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) -o $@ $(INC) -L$(LIBFT_PATH) -lft -lreadline -lhistory

$(LIBFT):
	make -C $(LIBFT_PATH)

clean: 
	rm -rf $(OBJ_PATH)
	@echo "Object files removed"

fclean: clean
	rm -rf $(NAME)
	@echo "Objects and binary removed"

re: fclean all

.PHONY: all clean fclean re