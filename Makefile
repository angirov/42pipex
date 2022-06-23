NAME = pipex

SRCS_DIR = srcs/
HEADERS = $(SRCS_DIR)pipex.h

# ========== mandatory ===========

SRCS_FILES = 	pipex_app.c \
				pipex_engine.c \
				pipex_child.c \
				pipex_destroy.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJ = ${SRCS:.c=.o}

# ==========   bonus   ===========

SRCS_FILES_BONUS = 	main_bonus.c \
				init_pipex.c \
				free_close.c \
				child.c

SRCS_BONUS = $(addprefix $(SRCS_DIR), $(SRCS_FILES_BONUS))

OBJ_BONUS = ${SRCS_BONUS:.c=.o}

# ========== libraries ==========
LIB_DIR = libs

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT_A = $(LIBFT_DIR)/libft.a

ALL_LIBS = $(LIBFT_A)

# ========== compilation ==========
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES_LOCAL = -I$(SRCS_DIR) -I$(LIBFT_DIR)

# ========== rules ==========
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(INCLUDES_LOCAL) $(ALL_LIBS) -o $(NAME)

bonus: $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(INCLUDES_LOCAL) $(ALL_LIBS) -o $(NAME)

%.o: %.c $(HEADERS) makelibs
	$(CC) $(CFLAGS) $(INCLUDES_LOCAL) -c $< -o $@ 

makelibs:
	make bonus -C $(LIBFT_DIR)

clean: cleanlibs
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: fcleanlibs clean
	rm $(NAME)

cleanlibs:
	make clean -C $(LIBFT_DIR)

fcleanlibs:
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re makelibs re