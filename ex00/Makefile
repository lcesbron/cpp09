NAME	=			btc

#		UTILS

CXX			=		c++
CXXFLAGS	=		-Wall -Wextra -Wshadow -Werror -std=c++98 -g3
CPPFLAGS	=		$(addprefix -I, $(INCLUDE_DIR)) -MD -MP -MF

RM			=		rm -rf

#		FILES

BUILD_DIR	=		.build/
SRC_DIR		=		src/
INCLUDE_DIR	=		include/
OBJ_DIR		=		$(addprefix $(BUILD_DIR), obj/)
DEP_DIR		=		$(addprefix $(BUILD_DIR), dep/)

#		SRC

BASENAME	=		main BitcoinExchange

SRC			=		$(addprefix $(SRC_DIR), $(addsuffix .cpp, $(BASENAME)))
OBJ			=		$(addprefix $(OBJ_DIR), $(addsuffix .o, $(BASENAME)))
DEP			=		$(addprefix $(DEP_DIR), $(addsuffix .d, $(BASENAME)))

#		RULES

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	@mkdir -p $(DEP_DIR)
	$(CXX) $(CPPFLAGS) $(DEP_DIR)$(notdir $(basename $@).d) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

-include $(DEP)
