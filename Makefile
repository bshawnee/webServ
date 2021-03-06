CC = clang++
NAME = HttpServer
SERV_PREF = srcs/server/
HAND_PREF = srcs/handlers/
CGI_PREF = srcs/cgi/
SRC =	$(SERV_PREF)Socket.cpp \
		$(SERV_PREF)IOService.cpp \
		$(SERV_PREF)Server.cpp \
		srcs/main.cpp \
		$(SERV_PREF)Buffer.cpp \
		srcs/utils.cpp \
		$(HAND_PREF)HttpRequest.cpp \
		$(HAND_PREF)AResponse.cpp \
		$(HAND_PREF)Get.cpp \
		$(HAND_PREF)Post.cpp \
		$(HAND_PREF)ResponseHeader.cpp \
		$(HAND_PREF)ResponseFactory.cpp \
		$(SERV_PREF)Acceptor.cpp \
		$(CGI_PREF)Cgi.cpp
HEADERS =	includes/server/Socket.hpp \
			includes/handlers/ResponseHeader.hpp \
			includes/server/Buffer.hpp \
			includes/server/Server.hpp \
			includes/handlers/HttpRequest.hpp \
			includes/utils.h \
			includes/server/IOService.hpp \
			includes/server/Acceptor.hpp \
			includes/handlers/Post.hpp \
			includes/cgi/Cgi.hpp
OBJ = $(SRC:.cpp=.o)
LDFLAGS =
FLAGS = -c -Wall -Wextra  -std=c++98 -g

all: $(SRC) $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.cpp.o:
	$(CC) $(FLAGS) $< -o $@
