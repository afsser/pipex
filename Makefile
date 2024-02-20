NAME		:= pipex
CC			:= gcc
FLAGS		:= -Wall -Wextra -Werror -g3
BIN			:= ./bin/
SRCS		:= $(addprefix ./src/mandatory/, main.c pipex.c utils.c error.c)
OBJS		:= $(patsubst ./src/mandatory/%.c,$(BIN)%.o,$(SRCS))
LIB			:= ./libft/libft.a
HEADERS		:= -I ./mandatory/pipex.h -I ./libft
#NAME_BONUS	:= pipex_bonus
#SRCS_BONUS	:= $(addprefix ./src/bonus/,)
#OBJS_BONUS	:= $(patsubst ./%.c,$(BIN_BONUS)%.o,$(SRCS_BONUS))
#BIN_BONUS	:= ./bin/
#HEADERS_BONUS:= -I ./bonus/pipex_bonus.h -I ./libft

# ifdef WITH_BONUS
# 	SRC = $(SRCS_BONUS)
# 	OBJS = $(OBJS_BONUS)
# 	BIN = $(BIN_BONUS)
# 	NAME = $(NAME_BONUS)
# 	HEADER = $(HEADERS_BONUS)
# endif

all: libft/libft.a $(BIN) $(NAME)

libft/libft.a:
	@make -sC ./libft 

$(BIN)%.o: ./src/mandatory/%.c
	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIB) $(HEADERS) -o $(NAME)

$(BIN):
	@mkdir -p $(BIN)

# $(BIN_BONUS)%.o: ./src/bonus/%.c
# 	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS_BONUS) && printf "Compiling: $(notdir $<)\n"

# bonus:
# 	@$(MAKE) WITH_BONUS=TRUE --no-print-directory

clean:
	rm -rf $(BIN)
	@make clean -sC ./libft 

fclean: clean
	rm -rf $(NAME) 
#	$(NAME_BONUS)
	rm -rf ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re