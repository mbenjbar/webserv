NAME = Request
CXX_FLAGS = -Wall -Wextra -Werror -std=c++98
CXX = c++
SRC = main.cpp Request.cpp First_line.cpp Key_Value.cpp Setter.cpp Getter.cpp utils.cpp 
OBJ =$(SRC:.cpp=.o) 

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all