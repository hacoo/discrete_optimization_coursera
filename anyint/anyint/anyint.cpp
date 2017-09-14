/*
<%
cfg['compiler_args'] = ['-std=c++11', '-Wall']
cfg['include_dirs'] = ['/usr/local/include/pybind11']
setup_pybind11(cfg)
%>
*/

#include <pybind11/pybind11.h>

int add(int a, int b)
{
  return a + b;
}

PYBIND11_MODULE(anyint, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");
}
