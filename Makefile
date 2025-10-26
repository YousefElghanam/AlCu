# =========================
# Project
# =========================
NAME        = alcu
#NAME_BONUS  = alcu_bonus
NAME_DEBUG  = alcu_debug

# =========================
# Compiler & Flags
# =========================
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I. -Ilibft
LIBFT       = libft/libft.a
#LDFLAGS_BONUS = -lncurses

# =========================
# Sources
# =========================
SRC_DIR     = src
SOURCES     = main.c parsing.c utils.c algo.c
#SOURCES_BONUS = $(SOURCES) visual.c

# =========================
# Mode / Objects
# =========================
MODE        ?= normal
OBJ_DIR_BASE = obj
OBJ_DIR     = $(OBJ_DIR_BASE)/$(MODE)
OBJECTS     = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))
#OBJECTS_BONUS = $(addprefix $(OBJ_DIR)/,$(SOURCES_BONUS:.c=.o))

# Standard-Binärziel (wird in Wrapper-Targets überschrieben)
BIN         ?= $(NAME)

# =========================
# User-facing Targets (Wrapper)
# =========================
.PHONY: all debug bonus re clean fclean build do_build

all:
	@$(MAKE) MODE=normal BIN=$(NAME) build

debug:
	@$(MAKE) MODE=debug CFLAGS="$(CFLAGS) -DVERBOSE=1" BIN=$(NAME_DEBUG) build

#bonus:
#	@$(MAKE) MODE=bonus BIN=$(NAME_BONUS) LDFLAGS_BONUS="$(LDFLAGS_BONUS)" build_bonus

# =========================
# Core build (gemeinsam genutzt)
# =========================
build: do_build

do_build: $(LIBFT) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) -o $(BIN)

# =========================
# Object Compilation
# =========================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# =========================
# Libft
# =========================
$(LIBFT):
	$(MAKE) -C libft

# =========================
# Cleaning
# =========================
clean:
	rm -rf $(OBJ_DIR_BASE)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG) $(NAME_BONUS)
	$(MAKE) -C libft fclean

re: fclean all
