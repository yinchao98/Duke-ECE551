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
private:
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

class PlusExpression: public Expression{
private:
	Expression * lvalue;
	Expression * rvalue;
public:
	PlusExpression(Expression * lhs, Expression * rhs): lvalue(lhs), rvalue(rhs) {}
	virtual std::string toString() const {
		std::stringstream exp;
		exp << "(" << lvalue->toString() << "+" << rvalue->toString() << ")" << "\n";
		return exp.str();
	}
	virtual ~PlusExpression() {
		delete lvalue;
		delete rvalue;
	}
};
