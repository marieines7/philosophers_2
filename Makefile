SRCS    =parsing.c \
	   main.c\
       parsing.c \
       philo_life.c \
       utils.c \
       init_philo.c \


OBJS = ${SRCS:.c=.o}

NAME = philo

HEADER = philo.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra #-pthread -g #-fsanitize=address
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