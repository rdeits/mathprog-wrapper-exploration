#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/eigen.h>
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


Eigen::Matrix<Variable, Eigen::Dynamic, 1> NewVariables() {
  Eigen::Matrix<Variable, Eigen::Dynamic, 1> result(2);
  result << Variable("x"), Variable("y");
  return result;
}

namespace py = pybind11;

typedef Eigen::Matrix<Variable, Eigen::Dynamic, 1> VectorXVariable;
PYBIND11_MAKE_OPAQUE(VectorXVariable);

typedef Eigen::Matrix<Expression, Eigen::Dynamic, 1> VectorXExpression;
PYBIND11_MAKE_OPAQUE(VectorXExpression);


PYBIND11_PLUGIN(example) {

  py::module m("example", "pybind11 example plugin");

  py::class_<Variable>(m, "Variable")
    .def(py::init<const std::string &>())
    .def("getName", &Variable::getName)
    .def(py::self + py::self)
    .def(py::self + int());

  py::class_<Expression>(m, "Expression")
    .def(py::init<const std::string &>())
    .def("getValue", &Expression::getValue)
    .def(py::self + py::self)
    .def(py::self + int())
    .def(py::self + Variable());

  py::class_<VectorXVariable>(m, "VectorXVariable")
    .def("__getitem__", [](const VectorXVariable &v, int i) {return v(i); }, py::return_value_policy::reference)
    .def("__len__", [](const VectorXVariable &v) {return v.size();});

  m.def("NewVariables", &NewVariables, "make some variables");
  return m.ptr();
}
