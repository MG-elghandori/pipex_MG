NAME = pipex

SRC =  ft_split.c functions.c tools.c pipex.c
SRCSB = pipex_bonus.c tools_bonus.c tools2_bonus.c ft_split.c functions.c tools.c

CC = cc

OBJ = $(SRC:.c=.o)
OBJSB = $(SRCSB:.c=.o)

%.o : %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -Wall -Wextra -Werror $(OBJ) -o pipex

bonus: $(OBJSB)
	$(CC) -Wall -Wextra -Werror $(OBJSB) -o pipex_bonus

clean:
	rm -rf $(OBJ) $(OBJSB)

fclean: clean
	rm -rf $(NAME)

re: fclean all
