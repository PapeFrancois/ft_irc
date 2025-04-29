
###### SOURCES ######################################


SRCS =	Server.cpp \
		Client.cpp \
		Channel.cpp \
		\
		socket.cpp \
		data.cpp \
		\
		cap.cpp \
		pass.cpp \
		nick.cpp \
		user.cpp \
		pong.cpp \
		quit.cpp \
		privmsg.cpp \
		join.cpp \
		\
		main.cpp


###### VARIABLES ####################################


CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -Iinclude

VPATH = src/:src/commands/

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