SRCS    = main.c\
		parsing.c \
       end_simulation.c \
       utils.c \
       init.c \


OBJS = ${SRCS:.c=.o}

NAME = philo

HEADER = philo.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread -g3 -fsanitize=address
RM = rm -f

.c.o:
	${CC} -c ${CFLAGS} -o $@ $< 

$(NAME):    ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:	${NAME}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:	 fclean all

.PHONY: all clean fclean re
