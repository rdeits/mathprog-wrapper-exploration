#include <Eigen/Core>

class Variable;

class Expression {
private:
  std::string value;

public:
  Expression(const std::string &_val): value(_val) {}

  std::string getValue() const { return value; }

  Expression operator +(const Expression &other) const {
    return Expression(value + " + " + other.value);
  }

  Expression operator +(const Variable &other) const;

  Expression operator +(int other) const {
    std::stringstream ss;
    ss << other;
    return Expression(value + " + " + ss.str());
  }
};

class Variable {
private:
  std::string name;

public:
  Variable(const std::string &_name): name(_name) {}
  Variable(): name("") {}

  std::string getName() const { return name; }

  Expression operator +(const Variable &other) const {
    return Expression(name + " + " + other.name);
  }

  Expression operator +(int other) const {
    std::stringstream ss;
    ss << other;
    return Expression(name + " + " + ss.str());
  }
};

Expression Expression::operator +(const Variable &other) const {
  return Expression(value + " + " + other.getName());
}

template<int rows, int cols>
using MatrixVariable = Eigen::Matrix<Variable, rows, cols>;

template<int rows>
using VectorVariable = MatrixVariable<rows, 1>;

using VectorXVariable = VectorVariable<Eigen::Dynamic>;

VectorXVariable NewVariables() {
  VectorXVariable result(2);
  result << Variable("x"), Variable("y");
  return result;
}

int NumVariables(const VectorXVariable& v) {
  return v.size();
}

Eigen::Matrix<Variable, 2, 1> TwoVariables() {
  Eigen::Matrix<Variable, 2, 1> result(Variable("x"), Variable("y"));
  return result;
}

Expression SumTwoVariables(const Eigen::Matrix<Variable, 2, 1>& v) {
  return v(0) + v(1);
}
