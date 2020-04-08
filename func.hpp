namespace callpy {

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "object.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include <math.h>

void foo(int n, const double *x, double *c_lp, double *c_glp) {
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();
	_import_array();

	PyObject *main = PyImport_ImportModule("__main__");

	npy_intp shape[1] = {n};
	PyObject *np_x = PyArray_SimpleNewFromData(1, shape, NPY_DOUBLE, (void*) x);


	if (c_lp != NULL)
	{
		PyObject *lp = PyObject_GetAttrString(main, "lp");
		PyArrayObject *lp_val = (PyArrayObject*) PyObject_CallFunctionObjArgs(lp, np_x, NULL);
		PyArray_ScalarAsCtype((PyObject*) lp_val, (void*) &c_lp);
		Py_DECREF(lp);
		Py_DECREF(lp_val);
	}

	if (c_glp != NULL)
	{
		PyObject *glp = PyObject_GetAttrString(main, "glp");
		PyArrayObject *glp_val = (PyArrayObject*) PyObject_CallFunctionObjArgs(glp, np_x, NULL);
		double *c_glp_val = (double*) PyArray_DATA(glp_val);
		for (int i=0; i<n; i++)
			c_glp[i] = c_glp_val[i];
		Py_DECREF(glp);
		Py_DECREF(glp_val);
	}

	PyGILState_Release(gstate);
}

}

template <typename T0__>
typename boost::math::tools::promote_args<T0__>::type
userfunc2(const Eigen::Matrix<T0__, Eigen::Dynamic, 1>& theta, std::ostream* pstream__) {
	throw std::logic_error("not implemented");
}

template <> double userfunc2(const Eigen::Matrix<double, -1, 1>& theta, std::ostream* pstream__) {
	double out;
	callpy::foo(theta.rows(), theta.data(), &out, NULL);
	return out;
}

template <> var userfunc2(const Eigen::Matrix<var, -1, 1>& theta, std::ostream* pstream__) {
    const Eigen::Matrix<double, -1, 1> theta_val = value_of(theta);
    double fa;
    double *ga = new double[theta.rows()];
    callpy::foo(theta.rows(), theta_val.data(), &fa, ga);
    std::vector<double> std_ga(theta.rows());
    std_ga.assign(ga, ga + theta.rows());
    delete ga;
    vector<var> theta_std(theta.data(), theta.data() + theta.rows());
    return precomputed_gradients(fa, theta_std, std_ga);
}
