#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include "../../src/expressions.h"

namespace py = pybind11;

// PYBIND11_MAKE_OPAQUE(VectorXVariable);
PYBIND11_NUMPY_OBJECT_DTYPE(Variable);
PYBIND11_NUMPY_OBJECT_DTYPE(Expression);

typedef Eigen::Matrix<Expression, Eigen::Dynamic, 1> VectorXExpression;
// PYBIND11_MAKE_OPAQUE(VectorXExpression);


PYBIND11_PLUGIN(expressions) {

  py::module m("expressions", "pybind11 expressions");

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

  // py::class_<VectorXVariable>(m, "VectorXVariable")
  //   .def("__getitem__", [](const VectorXVariable &v, int i) {return v(i); }, py::return_value_policy::reference)
  //   .def("__len__", [](const VectorXVariable &v) {return v.size();});

  m.def("NewVariables", &NewVariables, "make some variables");
  return m.ptr();
}
