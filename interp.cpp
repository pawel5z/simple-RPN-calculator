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

std::deque<calc::Symbol *> Parse(std::string &input)
{
	using namespace calc;
	std::stringstream ss;
	std::deque<Symbol *> symbols;
	ss << input;

	double number = 0.0;
	while (!ss.eof() && ss.peek() != '\n')
	{
		ss >> input;
		try
		{
			number = std::stod(input);
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

		if (input == "e")
			symbols.push_back(new Constant("e", 2.718281828459));
		else if (input == "pi")
			symbols.push_back(new Constant("pi", 3.141592653589));
		else if (input == "fi")
			symbols.push_back(new Constant("fi", 1.618033988750));
		else if (input == "+")
			symbols.push_back(new Add());
		else if (input == "-")
			symbols.push_back(new Sub());
		else if (input == "*")
			symbols.push_back(new Mult());
		else if (input == "/")
			symbols.push_back(new Div());
		else if (input == "modulo")
			symbols.push_back(new Modulo());
		else if (input == "min")
			symbols.push_back(new Min());
		else if (input == "max")
			symbols.push_back(new Max());
		else if (input == "log")
			symbols.push_back(new Log());
		else if (input == "pow")
			symbols.push_back(new Pow());
		else if (input == "abs")
			symbols.push_back(new Abs());
		else if (input == "sgn")
			symbols.push_back(new Sgn());
		else if (input == "floor")
			symbols.push_back(new Floor());
		else if (input == "ceil")
			symbols.push_back(new Ceil());
		else if (input == "frac")
			symbols.push_back(new Frac());
		else if (input == "sin")
			symbols.push_back(new Sin());
		else if (input == "cos")
			symbols.push_back(new Cos());
		else if (input == "atan")
			symbols.push_back(new Atan());
		else if (input == "acot")
			symbols.push_back(new Acot());
		else if (input == "ln")
			symbols.push_back(new Ln());
		else if (input == "exp")
			symbols.push_back(new Exp());
		else
			symbols.push_back(new Variable(input));
	}

	return symbols;
}

double Eval(const std::deque<calc::Symbol *> &symbols)
{
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

int main()
{
	using namespace calc;
	std::string command = "";
	std::deque<Symbol *> symbols;
	std::string toParse;
	std::set<std::string> forbiddenVarNames{"e", "phi", "pi", "print", "assign", "to", "clear", "exit", "+", "-", "*", "/", "modulo", "min", "max", "log", "pow", "abs", "sgn", "floor", "ceil", "frac", "sin", "cos", "atan", "acot", "ln", "exp"};

	do
	{
		symbols.clear();
		command = "";
		std::cout << "> ";
		std::cin >> command;
		if (command == "print")
		{
			std::getline(std::cin, toParse);
			try
			{
				symbols = Parse(toParse);
			}
			catch (std::out_of_range &e)
			{
				std::clog << e.what() << std::endl
						  << "Given number is too big" << std::endl;
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
			std::getline(std::cin, toParse);
			std::stringstream ss;
			std::string aux, varName;
			ss << toParse;
			toParse = "";
			while (!ss.eof())
			{
				ss >> aux;
				if (aux == "to")
				{
					ss >> varName;
					break;
				}
				toParse += aux + " ";
			}
			toParse.pop_back();
			if (forbiddenVarNames.count(varName) > 0)
			{
				std::clog << "Invalid variable name: \'" + varName + "\'" << std::endl;
				continue;
			}
			else if (varName.size() > 7)
			{
				std::clog << "Variable name must consist of at most 7 characters" << std::endl;
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
			std::cout << "Assigned " << varName << " = " << result << std::endl;
		}
		else if (command == "clear")
		{
			Variable::Clear();
			std::cout << "Environment clear" << std::endl;
		}
		else if (command != "exit")
		{
			std::clog << "Unknown command: \'" << command << "\'" << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (command != "exit");
	return 0;
}
