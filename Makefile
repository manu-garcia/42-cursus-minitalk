# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 20:21:02 by manu              #+#    #+#              #
#    Updated: 2022/06/04 18:53:18 by manugarc         ###   ########.fr        #
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
CLIENT_BONUS_SRC	= 	$(SRC_DIR)/client_bonus.c $(SRC_DIR)/process.c $(SRC_DIR)/bit.c $(SRC_DIR)/message.c
SERVER_BONUS_SRC	= 	$(SRC_DIR)/server_bonus.c $(SRC_DIR)/process.c $(SRC_DIR)/signals.c $(SRC_DIR)/state.c $(SRC_DIR)/error.c $(SRC_DIR)/bit.c

CLIENT_OBJ			= 	$(CLIENT_SRC:.c=.o)
SERVER_OBJ			= 	$(SERVER_SRC:.c=.o)
CLIENT_BONUS_OBJ	= 	$(CLIENT_BONUS_SRC:.c=.o)
SERVER_BONUS_OBJ	= 	$(SERVER_BONUS_SRC:.c=.o)

CFLAGS 				= 	-Wall -Wextra -Werror
CC 					= 	gcc

all: $(NAME) $(NAME_SERVER)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -I ${INCLUDES_DIR} -o $@ $^

$(NAME): $(CLIENT_OBJ)
	@$(CC) $(CFLAGS) -I ${INCLUDES_DIR} $(CLIENT_OBJ) -o $(NAME)

$(NAME_SERVER): $(SERVER_OBJ)
	@$(CC) $(CFLAGS) -I ${INCLUDES_DIR} $(SERVER_OBJ) -o $(NAME_SERVER)

$(NAME_BONUS): $(CLIENT_BONUS_SRC)
	@$(CC) $(CFLAGS) -I ${INCLUDES_DIR} $(CLIENT_BONUS_SRC) -o $(NAME_BONUS)

$(NAME_BONUS_SERVER): $(SERVER_BONUS_OBJ)
	@$(CC) $(CFLAGS) -I ${INCLUDES_DIR} $(SERVER_BONUS_OBJ) -o $(NAME_BONUS_SERVER)

bonus: $(NAME_BONUS) $(NAME_BONUS_SERVER)

re: fclean all

clean:
	rm -f $(CLIENT_OBJ)
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_BONUS_OBJ)
	rm -f $(SERVER_BONUS_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_SERVER)
	rm -f $(NAME_BONUS)
	rm -f $(NAME_BONUS_SERVER)

norminette:
	norminette -R CheckForbiddenSourceHeader | grep Error

.PHONY: all clean fclean re
