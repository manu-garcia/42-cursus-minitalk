# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manu <manu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 20:21:02 by manu              #+#    #+#              #
#    Updated: 2022/06/05 23:01:26 by manu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	client
NAME_SERVER			=	server
NAME_BONUS			=	client_bonus
NAME_BONUS_SERVER	=	server_bonus

SRC_DIR				=	src
INCLUDES_DIR		= 	includes

CLIENT_SRC			= 	$(SRC_DIR)/client.c
SERVER_SRC			= 	$(SRC_DIR)/server.c
CLIENT_BONUS_SRC	= 	$(SRC_DIR)/client_bonus.c $(SRC_DIR)/process.c $(SRC_DIR)/signals.c $(SRC_DIR)/message.c $(SRC_DIR)/bit.c
SERVER_BONUS_SRC	= 	$(SRC_DIR)/server_bonus.c $(SRC_DIR)/process.c $(SRC_DIR)/signals.c $(SRC_DIR)/message.c $(SRC_DIR)/state.c $(SRC_DIR)/state_message.c $(SRC_DIR)/state_char.c $(SRC_DIR)/error.c $(SRC_DIR)/bit.c

CLIENT_OBJ			= 	$(CLIENT_SRC:.c=.o)
SERVER_OBJ			= 	$(SERVER_SRC:.c=.o)
CLIENT_BONUS_OBJ	= 	$(CLIENT_BONUS_SRC:.c=.o)
SERVER_BONUS_OBJ	= 	$(SERVER_BONUS_SRC:.c=.o)

LIB_FT_PRINTF		=	ft_printf
CFLAGS 				= 	-Wall -Wextra -Werror
CC 					= 	gcc

all: $(NAME) $(NAME_SERVER)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -I ${INCLUDES_DIR} -o $@ $^

$(NAME): $(CLIENT_OBJ)
	@make -C $(LIB_FT_PRINTF)
	@cp $(LIB_FT_PRINTF)/libftprintf.a .
	@$(CC) $(CFLAGS) -I ${INCLUDES_DIR} $(CLIENT_OBJ) libftprintf.a -o $(NAME)

$(NAME_SERVER): $(SERVER_OBJ)
	@make -C $(LIB_FT_PRINTF)
	@cp $(LIB_FT_PRINTF)/libftprintf.a .
	@$(CC) $(CFLAGS) -I ${INCLUDES_DIR} $(SERVER_OBJ) libftprintf.a  -o $(NAME_SERVER)

$(NAME_BONUS): $(CLIENT_BONUS_SRC)
	@make -C $(LIB_FT_PRINTF)
	@cp $(LIB_FT_PRINTF)/libftprintf.a .
	@$(CC) $(CFLAGS) -I ${INCLUDES_DIR} $(CLIENT_BONUS_SRC) libftprintf.a  -o $(NAME_BONUS)

$(NAME_BONUS_SERVER): $(SERVER_BONUS_OBJ)
	@make -C $(LIB_FT_PRINTF)
	@cp $(LIB_FT_PRINTF)/libftprintf.a .
	@$(CC) $(CFLAGS) -I ${INCLUDES_DIR} $(SERVER_BONUS_OBJ) libftprintf.a  -o $(NAME_BONUS_SERVER)

bonus: $(NAME_BONUS) $(NAME_BONUS_SERVER)

re: fclean all

clean:
	rm -f $(CLIENT_OBJ)
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_BONUS_OBJ)
	rm -f $(SERVER_BONUS_OBJ)
	rm ./libftprintf.a
	@make fclean -C $(LIB_FT_PRINTF)


fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_SERVER)
	rm -f $(NAME_BONUS)
	rm -f $(NAME_BONUS_SERVER)

norminette:
	norminette -R CheckForbiddenSourceHeader | grep Error

.PHONY: all clean fclean re
