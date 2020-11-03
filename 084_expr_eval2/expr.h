#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>

class Expression {
public:
	Expression() {}
	virtual std::string toString() const = 0;
	virtual ~Expression() {}
};

class NumExpression: public Expression {
	long number;
public:
	NumExpression(long n): number(n) {} 
	virtual std::string toString() const {
		std::stringstream outputNum;
		outputNum << number;
		return outputNum.str();
	}
	virtual ~NumExpression() {}
};

class operatorExpression: public Expression {
protected:
	Expression * lvalue;
	Expression * rvalue;
public:
	operatorExpression(Expression * lhs, Expression * rhs): lvalue(lhs), rvalue(rhs) {}
	virtual std::string toString() const = 0;
	virtual ~operatorExpression() {
		delete lvalue;
		delete rvalue;
	}
};

class PlusExpression: public operatorExpression{
public:
	PlusExpression(Expression * lhs, Expression * rhs): operatorExpression(lhs, rhs) {}
	virtual std::string toString() const {
		std::stringstream exp;
		exp << "(" << lvalue->toString() << " + " << rvalue->toString() << ")";
		return exp.str();
	}
	virtual ~PlusExpression() {}
};

class MinusExpression: public operatorExpression{
public:
	MinusExpression(Expression * lhs, Expression * rhs): operatorExpression(lhs, rhs) {}
	virtual std::string toString() const {
		std::stringstream exp;
		exp << "(" << lvalue->toString() << " - " << rvalue->toString() << ")";
		return exp.str();
	}
	virtual ~MinusExpression() {}
};

class TimesExpression: public operatorExpression{
public:
	TimesExpression(Expression * lhs, Expression * rhs): operatorExpression(lhs, rhs) {}
	virtual std::string toString() const {
		std::stringstream exp;
		exp << "(" << lvalue->toString() << " * " << rvalue->toString() << ")";
		return exp.str();
	}
	virtual ~TimesExpression() {}
};

class DivExpression: public operatorExpression{
public:
	DivExpression(Expression * lhs, Expression * rhs): operatorExpression(lhs, rhs) {}
	virtual std::string toString() const {
		std::stringstream exp;
		exp << "(" << lvalue->toString() << " / " << rvalue->toString() << ")";
		return exp.str();
	}
	virtual ~DivExpression() {}
};

