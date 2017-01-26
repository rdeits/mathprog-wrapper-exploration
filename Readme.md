Explorations of wrapping types which are superficially similar to the Variables and Expressions used in Drake. 

There are two parallel implementations here, contained in the `pybind` and `swig` folders. 

# Requirements

The `pybind` project should have no requirements (it will download Eigen as needed). It should also "just work" with python2 and python3. 

The `swig` project is hard-coded to Python 3.5 because it's a pain to deal with different python versions in SWIG + cmake. 

# Building

The `pybind` and `swig` folders are separate cmake projects. To build `pybind`, just do:

	cd pybind
	mkdir build
	cd build
	cmake ..
	make

Test it by running:

	cd pybind
	python3 demo.py

To build the `swig` version, the steps are the same:

	cd swig
	mkdir build
	cd build
	cmake ..
	make

Test it by running:

	cd swig
	python3 demo.py

(this will error out, because the SWIG bindings don't totally work yet). 





