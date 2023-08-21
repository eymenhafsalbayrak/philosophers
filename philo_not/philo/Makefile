CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

NAME = philo
SRCS = init.c main.c utils.c philo.c routine.c die_control.c utils2.c

${NAME}:
	${CC} ${CFLAGS} ${SRCS} -o ${NAME}

all: ${NAME}

clean:

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re