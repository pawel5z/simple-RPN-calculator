#include "onp.hpp"
#include <unordered_map>
#include <cmath>
#include <string>

namespace calc
{
	//Symbol
	Symbol::Symbol()
	{}

	double Symbol::Calculate()
	{ return 0.0; }

	double Symbol::Calculate(double arg1)
	{ return arg1; }

	double Symbol::Calculate(double arg1, double arg2)
	{ return arg1 + arg2; }

	//Operand
	std::string Operand::Tag()
	{ return "operand"; }

	//Number
	Number::Number(double val) : val(val)
	{}

	double Number::Calculate()
	{ return val; }

	//Variable
	std::unordered_map<std::string, double> Variable::assoc;

	Variable::Variable(std::string name) : name(name)
	{}

	double Variable::Calculate()
	{
		if (Variable::assoc.find(name) == Variable::assoc.end())
			throw std::invalid_argument(std::string("Environment does not contain variable named \'" + name + "\'"));
		return assoc[name];
	}

	void Variable::Clear()
	{ assoc.clear(); }

	//Constant
	Constant::Constant(std::string name, double val) : name(name), val(val)
	{}

	double Constant::Calculate()
	{ return val; }

	//Arg1F
	std::string Arg1F::Tag()
	{ return "1arg-function"; }

	//Arg2F
	std::string Arg2F::Tag()
	{ return "2arg-function"; }

	//Add
	Add::Add()
	{}

	double Add::Calculate(double arg1, double arg2)
	{ return arg1 + arg2; }

	//Sub
	Sub::Sub()
	{}

	double Sub::Calculate(double arg1, double arg2)
	{ return arg1 - arg2; }

	//Mult
	Mult::Mult()
	{}

	double Mult::Calculate(double arg1, double arg2)
	{ return arg1 * arg2; }

	//Div
	Div::Div()
	{}

	double Div::Calculate(double arg1, double arg2)
	{ return arg1 / arg2; }

	//Modulo
	Modulo::Modulo()
	{}

	double Modulo::Calculate(double arg1, double arg2)
	{ return (int)arg1 % (int)arg2; }

	//Min
	Min::Min()
	{}

	double Min::Calculate(double arg1, double arg2)
	{ return std::min(arg1, arg2); }

	//Max
	Max::Max()
	{}

	double Max::Calculate(double arg1, double arg2)
	{ return std::max(arg1, arg2); }

	//Log
	Log::Log()
	{}

	double Log::Calculate(double arg1, double arg2)
	{ return std::log(arg2) / std::log(arg1); }

	//Pow
	Pow::Pow()
	{}

	double Pow::Calculate(double arg1, double arg2)
	{ return std::pow(arg1, arg2); }

	//Abs
	Abs::Abs()
	{}

	double Abs::Calculate(double arg1)
	{ return std::abs(arg1); }

	//Sgn
	Sgn::Sgn()
	{}

	double Sgn::Calculate(double arg1)
	{
		if (arg1 > 0)
			return 1;
		else if (arg1 < 0)
			return -1;
		else
			return 0;
	}

	//Floor
	Floor::Floor()
	{}

	double Floor::Calculate(double arg1)
	{ return std::floor(arg1); }

	//Ceil
	Ceil::Ceil()
	{}

	double Ceil::Calculate(double arg1)
	{ return std::ceil(arg1); }

	//Frac
	Frac::Frac()
	{}

	double Frac::Calculate(double arg1)
	{ return arg1 - std::floor(arg1); }

	//Sin
	Sin::Sin()
	{}

	double Sin::Calculate(double arg1)
	{ return std::sin(arg1); }

	//Cos
	Cos::Cos()
	{}

	double Cos::Calculate(double arg1)
	{ return std::cos(arg1); }

	//Atan
	Atan::Atan()
	{}

	double Atan::Calculate(double arg1)
	{ return std::atan(arg1); }

	//Acot
	Acot::Acot()
	{}

	double Acot::Calculate(double arg1)
	{ return M_PI / 2 - std::atan(arg1); }

	//Ln
	Ln::Ln()
	{}

	double Ln::Calculate(double arg1)
	{ return std::log(arg1); }

	//Exp
	Exp::Exp()
	{}

	double Exp::Calculate(double arg1)
	{ return std::exp(arg1); }

}		
