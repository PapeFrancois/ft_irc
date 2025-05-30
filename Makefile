
###### SOURCES ######################################


SRCS =	Server.cpp \
		Client.cpp \
		Channel.cpp \
		\
		initOper.cpp \
		socket.cpp \
		data.cpp \
		\
		pass.cpp \
		nick.cpp \
		user.cpp \
		pong.cpp \
		quit.cpp \
		privmsg.cpp \
		join.cpp \
		part.cpp \
		mode.cpp \
		kick.cpp \
		invite.cpp \
		topic.cpp \
		oper.cpp \
		kill.cpp \
		\
		main.cpp


# BOT
SRCS_BOT = bot.cpp


###### VARIABLES ####################################


CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -Iinclude

VPATH = src/:src/commands/:bot/

BIN = bin

OBJS = $(addprefix $(BIN)/, $(notdir $(SRCS:.cpp=.o)))

DEPS = $(OBJS:.o=.d)

NAME = ircserv


# BOT
OBJS_BOT = $(addprefix $(BIN)/, $(notdir $(SRCS_BOT:.cpp=.o)))

DEPS_BOT = $(OBJS_BOT:.o=.d)

NAME_BOT = britneyboT


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


# BOT
bot: $(BIN) $(OBJS_BOT)
	$(CC) $(OBJS_BOT) -o $(NAME_BOT)



-include $(DEPS) $(DEPS_BOT)

.PHONY: all clean fclean re