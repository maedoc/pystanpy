import numpy as np
cimport numpy as np
import importlib
import os
mname = os.environ.get('PYSTANPY_MODULE', 'model')
model = importlib.import_module(mname)
np.import_array()

# void foo(int n, const double *x, double *c_lp, double *c_glp) {
cdef public api void call_python_lp(int n, const double *theta_in, double *lp_out, double *glp_out):
    cdef int i
    cdef double f
    cdef np.ndarray[np.double_t, ndim=1] g
    cdef np.npy_intp shape[1]
    shape[0] = <np.npy_intp> n
    lp = model.lp
    theta = np.PyArray_SimpleNewFromData(1, shape, np.NPY_DOUBLE, theta_in);
    f, g = model.lp(theta)
    lp_out[0] = f
    for i in range(n):
        glp_out[i] = g[i]

cdef public api void check():
    cdef int n = 5
    cdef double theta[5]
    theta[:] = [1.0, 2.0, 3.0, 4.0, 5.0]
    cdef double lp = 0.0
    cdef double glp[5]
    glp[:] = [0.0, 0.0, 0.0, 0.0, 0.0]
    call_python_lp(n, theta, &lp, glp);
    print(lp, glp)

if __name__ == '__main__':
    check()
