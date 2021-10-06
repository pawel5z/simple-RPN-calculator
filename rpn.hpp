#ifndef RPN_HPP
#define RPN_HPP
#include <string>
#include <unordered_map>

namespace calc
{
	class Symbol
	{
	public:
		Symbol();
		virtual ~Symbol() = default;
		virtual std::string Tag() = 0;
		virtual double Calculate();
		virtual double Calculate(double arg1);
		virtual double Calculate(double arg1, double arg2);
	};

	class Operand : public Symbol
	{
	public:
		std::string Tag() override;
	};

	class Func : public Symbol
	{
	};

	class Number : public Operand
	{
	private:
		double val;

	public:
		Number(double val);
		double Calculate() override;
	};

	class Variable : public Operand
	{
	private:
		std::string name;

	public:
		static std::unordered_map<std::string, double> assoc;
		Variable(std::string name);
		double Calculate() override;
		static void Clear();
	};

	class Constant : public Operand
	{
	private:
		std::string name;
		double val;

	public:
		Constant(std::string name, double val);
		double Calculate() override;
	};

	class Arg1F : public Func
	{
	public:
		virtual std::string Tag() override;
	};

	class Arg2F : public Func
	{
	public:
		virtual std::string Tag() override;
	};

	class Add : public Arg2F
	{
	public:
		Add();
		double Calculate(double arg1, double arg2) override;
	};

	class Sub : public Arg2F
	{
	public:
		Sub();
		double Calculate(double arg1, double arg2) override;
	};

	class Mult : public Arg2F
	{
	public:
		Mult();
		double Calculate(double arg1, double arg2) override;
	};

	class Div : public Arg2F
	{
	public:
		Div();
		double Calculate(double arg1, double arg2) override;
	};

	class Modulo : public Arg2F
	{
	public:
		Modulo();
		double Calculate(double arg1, double arg2) override;
	};

	class Min : public Arg2F
	{
	public:
		Min();
		double Calculate(double arg1, double arg2) override;
	};

	class Max : public Arg2F
	{
	public:
		Max();
		double Calculate(double arg1, double arg2) override;
	};

	class Log : public Arg2F
	{
	public:
		Log();
		double Calculate(double arg1, double arg2) override;
	};

	class Pow : public Arg2F
	{
	public:
		Pow();
		double Calculate(double arg1, double arg2) override;
	};

	//1 arg
	class Abs : public Arg1F
	{
	public:
		Abs();
		double Calculate(double arg1) override;
	};

	class Sgn : public Arg1F
	{
	public:
		Sgn();
		double Calculate(double arg1) override;
	};

	class Floor : public Arg1F
	{
	public:
		Floor();
		double Calculate(double arg1) override;
	};

	class Ceil : public Arg1F
	{
	public:
		Ceil();
		double Calculate(double arg1) override;
	};

	class Frac : public Arg1F
	{
	public:
		Frac();
		double Calculate(double arg1) override;
	};

	class Sin : public Arg1F
	{
	public:
		Sin();
		double Calculate(double arg1) override;
	};

	class Cos : public Arg1F
	{
	public:
		Cos();
		double Calculate(double arg1) override;
	};

	class Atan : public Arg1F
	{
	public:
		Atan();
		double Calculate(double arg1) override;
	};

	class Acot : public Arg1F
	{
	public:
		Acot();
		double Calculate(double arg1) override;
	};

	class Ln : public Arg1F
	{
	public:
		Ln();
		double Calculate(double arg1) override;
	};

	class Exp : public Arg1F
	{
	public:
		Exp();
		double Calculate(double arg1) override;
	};
}

#endif // RPN_HPP
