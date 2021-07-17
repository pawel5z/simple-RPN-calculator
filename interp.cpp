#include "onp.hpp"
#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include <stack>
#include <sstream>
#include <set>
#include <deque>
#include <limits>
#include <readline/readline.h>
#include <readline/history.h>
#include <regex>

std::deque<calc::Symbol *> Parse(std::stringstream &ss)
{
	using namespace calc;
	std::deque<Symbol *> symbols;

	double number;
	std::string token;
	while (!ss.eof())
	{
		ss >> token;

		/* try converting token to number */
		try
		{
			number = std::stod(token);
			symbols.push_back(new Number(number));
			continue;
		}
		catch (std::out_of_range &e)
		{
			throw e;
		}
		catch (std::invalid_argument &e)
		{
		}

		if (token == "e")
			symbols.push_back(new Constant("e", 2.718281828459));
		else if (token == "pi")
			symbols.push_back(new Constant("pi", 3.141592653589));
		else if (token == "fi")
			symbols.push_back(new Constant("fi", 1.618033988750));
		else if (token == "+")
			symbols.push_back(new Add());
		else if (token == "-")
			symbols.push_back(new Sub());
		else if (token == "*")
			symbols.push_back(new Mult());
		else if (token == "/")
			symbols.push_back(new Div());
		else if (token == "modulo")
			symbols.push_back(new Modulo());
		else if (token == "min")
			symbols.push_back(new Min());
		else if (token == "max")
			symbols.push_back(new Max());
		else if (token == "log")
			symbols.push_back(new Log());
		else if (token == "pow")
			symbols.push_back(new Pow());
		else if (token == "abs")
			symbols.push_back(new Abs());
		else if (token == "sgn")
			symbols.push_back(new Sgn());
		else if (token == "floor")
			symbols.push_back(new Floor());
		else if (token == "ceil")
			symbols.push_back(new Ceil());
		else if (token == "frac")
			symbols.push_back(new Frac());
		else if (token == "sin")
			symbols.push_back(new Sin());
		else if (token == "cos")
			symbols.push_back(new Cos());
		else if (token == "atan")
			symbols.push_back(new Atan());
		else if (token == "acot")
			symbols.push_back(new Acot());
		else if (token == "ln")
			symbols.push_back(new Ln());
		else if (token == "exp")
			symbols.push_back(new Exp());
		else
			symbols.push_back(new Variable(token));
	}

	return symbols;
}

double Eval(const std::deque<calc::Symbol *> &symbols)
{
	if (symbols.empty())
		throw std::invalid_argument("symbols queue is empty");

	using namespace calc;
	std::stack<double> evalStack;
	double arg1, arg2;
	for (auto it = symbols.begin(); it != symbols.end(); it++)
	{
		Symbol *aux = *it;
		if (aux->Tag() == "operand")
			evalStack.push(aux->Calculate());
		else if (aux->Tag() == "1arg-function")
		{
			arg1 = evalStack.top();
			evalStack.pop();
			evalStack.push(aux->Calculate(arg1));
		}
		else if (aux->Tag() == "2arg-function")
		{
			arg2 = evalStack.top();
			evalStack.pop();
			arg1 = evalStack.top();
			evalStack.pop();
			evalStack.push(aux->Calculate(arg1, arg2));
		}
	}
	if (evalStack.size() > 1)
		throw std::invalid_argument("Bad number of arguments");
	return evalStack.top();
}

static const char *const prompt = "> ";

int main()
{
	using namespace calc;
	std::deque<Symbol *> symbols;
	std::set<std::string> forbiddenVarNames{"", "e", "phi", "pi", "print", "assign", "to", "clear", "exit", "+", "-", "*", "/", "modulo", "min", "max", "log", "pow", "abs", "sgn", "floor", "ceil", "frac", "sin", "cos", "atan", "acot", "ln", "exp"};

	bool quit = false;
	char *line = nullptr;
	while (!quit)
	{
		for (auto *var : symbols)
			delete var;
		symbols.clear();

		if (line)
			free(line);
		line = readline(prompt);

		if (!line)
		{
			quit = true;
			continue;
		}

		std::stringstream ss(line);
		std::string command;

		ss >> command;
		if (command == "print")
		{
			try
			{
				symbols = Parse(ss);
			}
			catch (std::out_of_range &e)
			{
				std::clog << e.what() << std::endl
						  << "Too large number detected" << std::endl;
				continue;
			}

			try
			{
				std::cout << Eval(symbols) << std::endl;
			}
			catch (std::invalid_argument &e)
			{
				std::clog << e.what() << std::endl;
			}
		}
		else if (command == "assign")
		{
			std::string aux, varName;
			std::stringstream toParse;
			while (!ss.eof())
			{
				ss >> aux;
				if (aux == "to")
				{
					ss >> varName;
					break;
				}
				toParse << aux;
			}
			if (forbiddenVarNames.count(varName) > 0)
			{
				std::clog << "Invalid variable name: \"" + varName + "\"" << std::endl;
				continue;
			}
			else if (varName.size() > 7)
			{
				std::clog << "Variable identifier must be at most 7 characters long" << std::endl;
				continue;
			}

			double result = 0.0;
			symbols = Parse(toParse);
			try
			{
				result = Eval(symbols);
			}
			catch (std::invalid_argument &e)
			{
				std::clog << e.what() << std::endl;
				continue;
			}
			Variable::assoc[varName] = result;
			std::cout << "\"" << varName << "\""
					  << " = " << result << std::endl;
		}
		else if (command == "clear")
		{
			Variable::Clear();
			std::cout << "Environment clear" << std::endl;
		}
		else if (command == "exit")
		{
			quit = true;
		}
		else
		{
			auto const re = std::regex(R"(\s*)");
			if (std::regex_match(command, re))
				continue;
			std::clog << "Unknown command: \'" << command << "\'" << std::endl;
			add_history(line);
		}
	}

	return 0;
}
