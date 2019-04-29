CC	:= gcc

RM	:= rm -rf

LDFLAGS	+= 

CFLAGS	+= -Iinclude

SRCS	:= $(shell find . -type f -name "*.c")

OBJS	:= $(SRCS:.c=.o)

NAME	:= rshell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
