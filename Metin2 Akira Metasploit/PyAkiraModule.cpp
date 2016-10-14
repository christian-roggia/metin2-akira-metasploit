#include "PyAkiraModule.h"

static PyMethodDef pPyAkiraMethods[] = {
	{"SetPong"			,  PySetPong			, METH_VARARGS, NULL},
	{"XTEA_Decrypt"		,  PyXTEADecrypt		, METH_VARARGS, NULL},
	{"ResetSequence"	,  PyResetSequence		, METH_VARARGS, NULL},

	{"Handshake"		,  PyHandshake			, METH_VARARGS, NULL},
	{"GetHandshake"		,  PyGetHandshake		, METH_VARARGS, NULL},

	{"GetPhase"			,  PyGetPhase			, METH_VARARGS, NULL},

	{"Authenticate"		,  PyAuthenticate		, METH_VARARGS, NULL},
	{"GetAuthFailure"	,  PyGetAuthFailed		, METH_VARARGS, NULL},
	{"GetAuthSuccess"	,  PyGetAuthSuccess		, METH_VARARGS, NULL},

	{"Login"			,  PyLogin				, METH_VARARGS, NULL},

	{"ChangeName"		,  PyChangeName			, METH_VARARGS, NULL},
	{"PasspodAnswer"	,  PyPasspodAnswer		, METH_VARARGS, NULL},
	{"SelectEmpire"		,  PySelectEmpire		, METH_VARARGS, NULL},
	{"CreateCharacter"	,  PyCreateCharacter	, METH_VARARGS, NULL},
	{"SelectCharacter"	,  PySelectCharacter	, METH_VARARGS, NULL},
	{"EnterGame"		,  PyEnterGame			, METH_VARARGS, NULL},
	{"Version"			,  PyVersion			, METH_VARARGS, NULL},
	{"GetXY"			,  PyGetXY				, METH_VARARGS, NULL},
	{"Move"				,  PyMove				, METH_VARARGS, NULL},
	{"QuestInputString"	,  PyQuestInputString	, METH_VARARGS, NULL},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pPyAkiraModule =
{
	PyModuleDef_HEAD_INIT,
	"akira",
	NULL,
	-1,
	pPyAkiraMethods
};

PyMODINIT_FUNC PyInit_Akira(void)
{
    return PyModule_Create(&pPyAkiraModule);
}

PyObject *PySetPong(PyObject *self, PyObject *args)
{
	unsigned int pKey[4] = {};
	int nLen = 0;

	if(!PyArg_ParseTuple(args, "iiii", &pKey[0], &pKey[1], &pKey[2], &pKey[3]))
        return NULL;

	MCP_SetPongKey(pKey);

	return Py_BuildValue("s", NULL);
}

PyObject *PyResetSequence(PyObject *self, PyObject *args)
{
	g_seq_counter = 0;

	return Py_BuildValue("s", NULL);
}

PyObject *PyXTEADecrypt(PyObject *self, PyObject *args)
{
	unsigned char *pRawData = NULL;
	int nLen = 0, nType = 0;

	if(!PyArg_ParseTuple(args, "y#i", &pRawData, &nLen, &nType))
        return NULL;

	if(nType == 1)
		TEA::Decrypt((char *)pRawData, nLen, s_decrypt_key);
	else
		TEA::Decrypt((char *)pRawData, nLen, s_pong_key);

	return Py_BuildValue("y#", pRawData, nLen);
}

PyObject *PyHandshake(PyObject *self, PyObject *args)
{
	unsigned int nHandshake, nTime, nDelta;

    if(!PyArg_ParseTuple(args, "iii", &nHandshake, &nTime, &nDelta))
        return NULL;

    int nLen = MCP_HandShake(nHandshake, nTime, nDelta);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PyGetHandshake(PyObject *self, PyObject *args)
{
	unsigned char *pRawData = NULL;
	int nLen = 0;

	if(!PyArg_ParseTuple(args, "y#", &pRawData, &nLen))
        return NULL;

	return Py_BuildValue("(iii)", *(int *)(pRawData + 1), *(int *)(pRawData + 5), *(int *)(pRawData + 9));
}

PyObject *PyGetPhase(PyObject *self, PyObject *args)
{
	unsigned char *pRawData = NULL;
	int nLen = 0;

	if(!PyArg_ParseTuple(args, "y#", &pRawData, &nLen))
        return NULL;

	return Py_BuildValue("i", pRawData[1]);
}

PyObject *PyAuthenticate(PyObject *self, PyObject *args)
{
	char *szUsername, *szPassword;

    if(!PyArg_ParseTuple(args, "ss", &szUsername, &szPassword))
        return NULL;

    int nLen = MCP_Auth(szUsername, szPassword);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PyGetAuthFailed(PyObject *self, PyObject *args)
{
	unsigned char *pRawData = NULL;
	int nLen = 0;

	if(!PyArg_ParseTuple(args, "y#", &pRawData, &nLen))
        return NULL;

	return Py_BuildValue("s#", (char *)&pRawData[1], strlen((char *)&pRawData[1]));
}

PyObject *PyGetAuthSuccess(PyObject *self, PyObject *args)
{
	unsigned char *pRawData = NULL;
	int nLen = 0;

	if(!PyArg_ParseTuple(args, "y#", &pRawData, &nLen))
        return NULL;

	return Py_BuildValue("ii", *(int *)(pRawData + 1), (*(int *)(pRawData + 5) & 1));
}

PyObject *PyLogin(PyObject *self, PyObject *args)
{
	char *szUsername;
	unsigned int nKey;

    if(!PyArg_ParseTuple(args, "si", &szUsername, &nKey))
        return NULL;

    int nLen = MCP_Login(szUsername, nKey);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PyChangeName(PyObject *self, PyObject *args)
{
	unsigned char nIndex;
	char *szName;

    if(!PyArg_ParseTuple(args, "bs", &nIndex, &szName))
        return NULL;

    int nLen = MCP_ChangeName(nIndex, szName);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PyPasspodAnswer(PyObject *self, PyObject *args)
{
	char *szAnswer;

    if(!PyArg_ParseTuple(args, "s", &szAnswer))
        return NULL;

    int nLen = MCP_PasspodAnswer(szAnswer);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PySelectEmpire(PyObject *self, PyObject *args)
{
	unsigned char nEmpire;

    if(!PyArg_ParseTuple(args, "i", &nEmpire))
        return NULL;

    int nLen = MCP_Empire(nEmpire);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PyCreateCharacter(PyObject *self, PyObject *args)
{
	char *szName;
	unsigned char nPos, nJob, nShape;

    if(!PyArg_ParseTuple(args, "siii", &szName, &nPos, &nJob, &nShape))
        return NULL;

    int nLen = MCP_NewCharacter(szName, nPos, nJob, nShape);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PySelectCharacter(PyObject *self, PyObject *args)
{
	unsigned char nIndex;

    if(!PyArg_ParseTuple(args, "i", &nIndex))
        return NULL;

    int nLen = MCP_SelectCharacter(nIndex);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PyEnterGame(PyObject *self, PyObject *args)
{
    int nLen = MCP_EnterGame();
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PyVersion(PyObject *self, PyObject *args)
{
	char *szLauncherName, *szVersion;

    if(!PyArg_ParseTuple(args, "ss", &szLauncherName, &szVersion))
        return NULL;

    int nLen = MCP_Version(szLauncherName, szVersion);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PyGetXY(PyObject *self, PyObject *args)
{
	unsigned char *pRawData = NULL;
	int nLen = 0;

	if(!PyArg_ParseTuple(args, "y#", &pRawData, &nLen))
        return NULL;

	return Py_BuildValue("ii", *(int *)(pRawData + 281), *(int *)(pRawData + 285));
}

PyObject *PyMove(PyObject *self, PyObject *args)
{
	unsigned char nMoveType, nUnk, nRotation;
	unsigned int nX, nY, nClientTime;

	if(!PyArg_ParseTuple(args, "iiiiii", &nMoveType, &nUnk, &nRotation, &nX, &nY, &nClientTime))
        return NULL;

	int nLen = MCP_Move(nMoveType, nUnk, nRotation, nX, nY, nClientTime);
	return Py_BuildValue("y#", g_buffer, nLen);
}

PyObject *PyQuestInputString(PyObject *self, PyObject *args)
{
	char *szString;

	if(!PyArg_ParseTuple(args, "s", &szString))
        return NULL;

	int nLen = MCP_QuestInputString(szString);
	return Py_BuildValue("y#", g_buffer, nLen);
}