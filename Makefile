NAME = pipex

SRCS_DIR = srcs/
SRCS_FILES = 	main.c \
				init_pipex.c \
				free_close.c \
				child.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJ = ${SRCS:.c=.o}

HEADERS = $(SRCS_DIR)pipex.h

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

%.o: %.c $(HEADERS) makelibs
	$(CC) $(CFLAGS) $(INCLUDES_LOCAL) -c $< -o $@ 

makelibs:
	make bonus -C $(LIBFT_DIR)

clean: cleanlibs
	rm $(OBJ)

fclean: fcleanlibs
	rm $(OBJ) $(NAME)

cleanlibs:
	make clean -C $(LIBFT_DIR)

fcleanlibs:
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re makelibs re