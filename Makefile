# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 12:49:42 by miwasa            #+#    #+#              #
#    Updated: 2024/12/02 11:06:01 by miwasa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex

FT_DIR		:= ./libft
LIBFT		:= $(FT_DIR)/libft.a
INCS_DIR	:= ./includes
SRCS_DIR	:= ./srcs
OBJS_DIR	:= ./objs

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -I$(INCS_DIR) -I$(FT_DIR)

SRCS		:= \
	main.c \
	is_valid_args.c \
	display_help.c \
	get_shell_proc.c \
	init_args.c \
	create_pipe.c \
	proc_cmd1.c \
	proc_cmd2.c \
	error_exit.c \
	execute_command.c \
	get_command_path.c

OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

.PHONY: all clean fclean re bonus test

all: $(LIBFT) $(NAME)

bonus: all

$(LIBFT):
	$(MAKE) -C $(FT_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)
	$(MAKE) clean -C $(FT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(FT_DIR)

re: fclean all

test: all
	valgrind --leak-check=full --track-fds=yes --trace-children=yes \
	./pipex files/in "ls -l" "wc -l" files/out
