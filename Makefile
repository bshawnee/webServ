CC = clang++
NAME = HttpServer
SRC =	srcs/Socket.cpp \
		srcs/main.cpp \
		srcs/Buffer.cpp \
		srcs/utils.cpp \
		srcs/HttpRequest.cpp \
		srcs/Acceptor.cpp
HEADERS =	includes/Socket.hpp \
			includes/Buffer.hpp \
			includes/Acceptor.hpp
OBJ = $(SRC:.cpp=.o)
LDFLAGS =
FLAGS = -c -Wall -Wextra -Werror -std=c++98 -g

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