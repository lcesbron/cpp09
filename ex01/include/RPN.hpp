#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

enum e_type
{
	NO_TYPE,
	VALUE,
	ADD,
	SUB,
	MULT,
	DIV,
};

typedef enum e_type		t_type;
typedef struct s_value	t_value;

struct s_value
{
	t_type	type;
	int		value;
};

class RPN
{
	private:
		RPN(void);

		std::stack<t_value> expression_;

		void	pushChar(int c);

		std::pair<t_value, t_value>	computeOperator(void);
		void							computeAdd(void);
	public:
		RPN(RPN const& toCopy);
		RPN(std::string const& expression);
		~RPN(void);

		RPN&	operator=(RPN const& toCopy);

		int		computeExpression(void);
};

#endif //RPN_HPP
