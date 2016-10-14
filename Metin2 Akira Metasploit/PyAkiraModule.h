#include <C:/Python33/include/Python.h>
#include "Packet.h"

PyMODINIT_FUNC PyInit_Akira(void);

PyObject *PySetPong(PyObject *self, PyObject *args);
PyObject *PyResetSequence(PyObject *self, PyObject *args);
PyObject *PyXTEADecrypt(PyObject *self, PyObject *args);

PyObject *PyHandshake(PyObject *self, PyObject *args);
PyObject *PyGetHandshake(PyObject *self, PyObject *args);

PyObject *PyGetPhase(PyObject *self, PyObject *args);

PyObject *PyAuthenticate(PyObject *self, PyObject *args);
PyObject *PyGetAuthFailed(PyObject *self, PyObject *args);
PyObject *PyGetAuthSuccess(PyObject *self, PyObject *args);

PyObject *PyLogin(PyObject *self, PyObject *args);

PyObject *PyChangeName(PyObject *self, PyObject *args);
PyObject *PyPasspodAnswer(PyObject *self, PyObject *args);
PyObject *PySelectEmpire(PyObject *self, PyObject *args);
PyObject *PyCreateCharacter(PyObject *self, PyObject *args);
PyObject *PySelectCharacter(PyObject *self, PyObject *args);
PyObject *PyEnterGame(PyObject *self, PyObject *args);
PyObject *PyVersion(PyObject *self, PyObject *args);
PyObject *PyGetXY(PyObject *self, PyObject *args);
PyObject *PyMove(PyObject *self, PyObject *args);
PyObject *PyQuestInputString(PyObject *self, PyObject *args);