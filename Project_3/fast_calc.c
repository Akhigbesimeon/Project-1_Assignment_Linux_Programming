#define PY_SSIZE_T_CLEAN
#include <Python.h>

// The C function that performs the computation 
static PyObject* fast_calc_sum_of_squares(PyObject* self, PyObject* args) {
    PyObject* list_obj;
    
    // Parse the input tuple to extract the Python list 
    if (!PyArg_ParseTuple(args, "O", &list_obj)) {
        return NULL;
    }

    // Ensure the argument is actually a list 
    if (!PyList_Check(list_obj)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a list.");
        return NULL;
    }

    Py_ssize_t size = PyList_Size(list_obj);
    double total = 0.0;

    // Iterate through the list, unpack the float, and compute 
    for (Py_ssize_t i = 0; i < size; i++) {
        PyObject* item = PyList_GetItem(list_obj, i);
        if (!PyFloat_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "List items must be floats.");
            return NULL;
        }
        double val = PyFloat_AsDouble(item);
        total += val * val;
    }

    // Convert the C double back to a Python float and return
    return PyFloat_FromDouble(total);
}

// Method definitions for the module 
static PyMethodDef FastCalcMethods[] = {
    {"sum_of_squares", fast_calc_sum_of_squares, METH_VARARGS, "Calculate the sum of squares of a list."},
    {NULL, NULL, 0, NULL} 
};

// Module definition structure 
static struct PyModuleDef fastcalcmodule = {
    PyModuleDef_HEAD_INIT,
    "fast_calc",
    NULL,        
    -1,          
    FastCalcMethods
};

// Module initialization function 
PyMODINIT_FUNC PyInit_fast_calc(void) {
    return PyModule_Create(&fastcalcmodule);
}
