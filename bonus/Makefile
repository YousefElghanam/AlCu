NAME = alcu1

CC = cc

OBJ_DIR = objects/

CFLAGS = -Wall -Wextra -Werror -Ilibft

SOURCES = main.c parsing.c algo.c utils.c

OBJECTS = $(SOURCES:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

debug: CFLAGS = -Wall -Wextra -Werror -lncurses -g -DVERBOSE=1
debug:
	make re

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) -lncurses -o $(NAME)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	mkdir -p $@

# bonus: $(NAME_BONUS)

# $(NAME_BONUS): $(LIBFT) $(OBJECTS_BONUS)
# 	$(CC) $(OBJECTS_BONUS) $(LIBFT) -o $(NAME_BONUS)

# $(OBJ_DIR_BONUS)%.o: $(SOURCES_DIR_BONUS)%.c | $(OBJ_DIR_BONUS)
# 	$(CC) $(CFLAGS) -o $@ -c $<

# $(OBJ_DIR_BONUS):
# 	mkdir -p $@

$(LIBFT):
	make -C libft

clean:
	rm -rf *.o
	make clean -C libft

fclean:
	rm -rf *.o $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all bonus clean fclean re