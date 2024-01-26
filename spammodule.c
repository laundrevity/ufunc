#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <math.h>
#include <stdbool.h>

/*
 * spammodule.c
 * This is the C code for a non-numpy Python extension to
 * define the logit function, where logit(p) = log(p/(1-p)).
 * This function will not work on numpy arrays automatically.
 * numpy.vectorize must be called in python to generate
 * a numpy-friendly function.
 *
 * Details explaining the Python-C API can be found under
 * 'Extending and Embedding' and 'Python/C API' at
 * docs.python.org .
 */


/* This declares the logit function */
static PyObject *spam_logit(PyObject *self, PyObject *args);

/* This declares the add function */
static PyObject *spam_add(PyObject *self, PyObject *args);

/* This declares the mystery function */
static PyObject *spam_mystery(PyObject *self, PyObject *args);

/*
 * This tells Python what methods this module has.
 * See the Python-C API for more information.
 */
static PyMethodDef SpamMethods[] = {
    {"logit",
        spam_logit,
        METH_VARARGS, "compute logit"},
    {"add", 
        spam_add,
        METH_VARARGS, "add two numbers"},
    {"mystery",
        spam_mystery,
        METH_VARARGS, "mystery operation"},
    {NULL, NULL, 0, NULL}
};

/*
 * This actually defines the logit function for
 * input args from Python.
 */

static PyObject *spam_logit(PyObject *self, PyObject *args)
{
    double p;

    /* This parses the Python argument into a double */
    if(!PyArg_ParseTuple(args, "d", &p)) {
        return NULL;
    }

    /* THE ACTUAL LOGIT FUNCTION */
    p = p/(1-p);
    p = log(p);

    /*This builds the answer back into a python object */
    return Py_BuildValue("d", p);
}

/* This initiates the module using the above definitions. */
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "spam",
    NULL,
    -1,
    SpamMethods,
    NULL,
    NULL,
    NULL,
    NULL
};

/* 
 * This defines the add function for input args from Python.
 */
static PyObject *spam_add(PyObject *self, PyObject *args)
{
    double x, y;

    /* This parses the Python arguments into two doubles */
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }

    /* THE ACTUAL ADDITION */
    double result = x + y;

    /* This builds the answer back into a python object */
    return Py_BuildValue("d", result);
}

/* 
 * This defines the mystery operation function for input args from Python.
 */
static PyObject *spam_mystery(PyObject *self, PyObject *args) {
    double x, y;
    int should_add;

    /* This parses the Python arguments into two doubles and a float */
    if (!PyArg_ParseTuple(args, "ddi", &x, &y, &should_add)) {
        return NULL;
    }


    double result;
    if (should_add) {
        result = x + y;
    } else {
        result = x - y;
    }

    return Py_BuildValue("d", result);
}

PyMODINIT_FUNC PyInit_spam(void)
{
    PyObject *m;
    m = PyModule_Create(&moduledef);
    if (!m) {
        return NULL;
    }
    return m;
}