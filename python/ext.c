
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "zcrypto/sm3.h"
#include "zcrypto/sm4.h"

typedef struct {
    PyObject_HEAD
    sm3_ctx_t ctx;
} SM3Object;

static int SM3_init(SM3Object *self, PyObject *args, PyObject *kwargs) {
    if (PyTuple_Size(args) != 0 || kwargs != NULL) {
        PyErr_SetString(PyExc_ValueError, "no args/kwargs");
        return -1;
    }
    sm3_init(&self->ctx);
    return 0;
}

static void SM3_dealloc(SM3Object *self) {
    memset(&self->ctx, 0, sizeof(sm3_ctx_t));
}

static PyObject *SM3_update(SM3Object *self, PyObject *data) {
    if (!PyBytes_Check(data)) {
        PyErr_SetString(PyExc_ValueError, "data MUST be bytes");
        return NULL;
    }
    Py_ssize_t len = PyBytes_Size(data);
    char *dd = PyBytes_AsString(data);
    sm3_update(&self->ctx, (const uint8_t *)dd, len);
    return Py_None;
}

static PyObject *SM3_digest(SM3Object *self) {
    uint8_t digest[32] = {0};
    sm3_digest(&self->ctx, digest);
    return PyBytes_FromStringAndSize((const char *)digest, 32);
}

static PyObject *SM3_hexdigest(SM3Object *self) {
    uint8_t digest[64] = {0};
    sm3_hexdigest(&self->ctx, digest);
    return PyUnicode_FromStringAndSize((const char *)digest, 64);
}

static PyMethodDef SM3_methods[] = {
    {
        "update",
        (PyCFunction)SM3_update,
        METH_O,
        "feed data"
    },
    {
        "digest",
        (PyCFunction)SM3_digest,
        METH_NOARGS,
        "digest"
    },
    {
        "hexdigest",
        (PyCFunction)SM3_hexdigest,
        METH_NOARGS,
        "hexdigest"
    },
    {NULL}
};

static PyTypeObject SM3Type = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "zcrypto.SM3",
    .tp_doc = "sm3_ctx_t",
    .tp_basicsize = sizeof(SM3Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)SM3_init,
    .tp_dealloc = (destructor)SM3_dealloc,
    .tp_methods = SM3_methods,
};

typedef struct {
    PyObject_HEAD
    sm4_ctx_t ctx;
} SM4Object;

static int SM4_init(SM4Object *self, PyObject *args, PyObject *kwargs) {
    static char *kwlist[] = {"", "", "iv", NULL};
    PyObject *key = NULL;
    PyObject *iv = NULL;
    int mode = 0;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Si|S", kwlist, &key, &mode, &iv)) {
        PyErr_SetString(PyExc_ValueError, "(key:bytes, mode:int, iv:bytes=?) is required");
        return -1;
    }
    if (PyBytes_Size(key) != 16) {
        PyErr_SetString(PyExc_ValueError, "len(key) == 16 is required");
        return -1;
    }
    if (mode < SM4_MIN_MODE || mode > SM4_MAX_MODE) {
        PyErr_Format(PyExc_ValueError, "mode MUST in %d...%d", SM4_MIN_MODE, SM4_MAX_MODE);
        return -1;
    }
    if (mode == SM4_ECB_MODE && iv != NULL) {
        PyErr_SetString(PyExc_ValueError, "ECB_MODE requires no iv");
        return -1;
    }