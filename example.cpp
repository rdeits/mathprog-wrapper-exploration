#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/eigen.h>
#include <Eigen/Core>

struct MyClass {
public:
  MyClass(): myname("dummy") {};
  MyClass(std::string _myname): myname(_myname) {};

  std::string getName() {
    return myname;
  }

  MyClass operator +(const MyClass &other) const {
    return MyClass(myname + other.myname);
  }

private:
  std::string myname;
};

Eigen::Matrix<MyClass, Eigen::Dynamic, 1> factory() {
  Eigen::Matrix<MyClass, Eigen::Dynamic, 1> result(2);
  result << MyClass("first"), MyClass("second");
  return result;
}

namespace py = pybind11;

typedef Eigen::Matrix<MyClass, Eigen::Dynamic, 1> VectorXMyClass;
// PYBIND11_MAKE_OPAQUE(MyClass);
PYBIND11_MAKE_OPAQUE(VectorXMyClass);

const MyClass& getitem(const VectorXMyClass & vec, int i) {
  return vec(i);
}

double mysum(const Eigen::Matrix<double, -1, -1> & vec) {
  return vec.sum();
}

PYBIND11_PLUGIN(example) {

  py::module m("example", "pybind11 example plugin");

  py::class_<MyClass>(m, "MyClass")
    .def(py::init<const std::string &>())
    .def("getName", &MyClass::getName)
    .def(py::self + py::self);

  py::class_<VectorXMyClass>(m, "VectorXMyClass")
    .def("__getitem__", &getitem, py::return_value_policy::reference)
    .def("__len__", [](const VectorXMyClass &v) {return v.size();});


  m.def("mysum", &mysum, "mysum's documentation");

  m.def("factory", &factory, "factory");
  return m.ptr();
}
