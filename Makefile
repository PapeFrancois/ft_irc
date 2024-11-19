
###### SOURCES ######################################


SRCS =	Server.cpp \
		Client.cpp \
		socket.cpp \
		main.cpp


###### VARIABLES ####################################


CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -Iinclude

VPATH = src/

BIN = bin

OBJS = $(addprefix $(BIN)/, $(notdir $(SRCS:.cpp=.o)))

DEPS = $(OBJS:.o=.d)

NAME = ircserv


###### RULES #######################################


all: $(BIN) $(NAME)

$(BIN):
	mkdir $(BIN)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BIN)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re