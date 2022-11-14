# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 16:26:20 by ralves-g          #+#    #+#              #
#    Updated: 2022/11/08 16:18:15 by ralves-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -fsanitize=address

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f

NAME		=	minishell

INCLUDE		=	-I ./ -I ~/brew/opt/readline/include -lreadline 

SRCS_		=	\
				minishell.c \
				env.c \
				errors_and_frees.c \
				errors_and_frees2.c \
				path.c \
				signal_handle.c \
				\
				executor/executor.c \
				executor/executor_prep.c \
				executor/executor_prep2.c \
				executor/executor_prep3.c \
				executor/run_builtins.c \
				\
				builtins/exit/exit.c \
				builtins/env/env.c \
				builtins/pwd/pwd.c \
				builtins/echo/echo.c \
				builtins/export/export.c \
				builtins/export/export_utils.c \
				builtins/unset/unset.c \
				builtins/cd/cd.c \
				\
				libs/lib.c \
				libs/lib2.c \
				libs/lib3.c \
				libs/split_join.c \
				\
				parser/parse_pipes.c \
				parser/parser_utils.c \
				parser/parser.c \
				parser/quotes.c \
				parser/treat_dollar.c \
				parser/treat_dollar2.c \
				parser/treat_dollar3.c \
				parser/treat_tilde.c \
				parser/tree_creation.c \
				parser/tree_creation_utils.c \
				parser/backslash.c \
				\
				redirections/redirections.c \
				redirections/heredoc.c \
				redirections/heredoc2.c \
				redirections/redir_builtins.c

SRCS		=	$(addprefix $(_SRC), $(SRCS_))

_OBJ		=
_SRC		=	./src/

OBJS		=	$(patsubst %.c, %.o, $(SRCS))
all:		$(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

#bonus:		$(SRCS_B) $(OBJS_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -o $(NAME_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -c

$(_OBJ):
	mkdir $@

clean:
	$(RM) -r $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re