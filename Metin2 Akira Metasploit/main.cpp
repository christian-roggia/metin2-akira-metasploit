#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS 1

#include "PyAkiraModule.h"

int main(int argc, wchar_t *argv[])
{
	printf("=====[Metin2 Akira Metasploit]=====\n");

	PyImport_AppendInittab("akira", PyInit_Akira);

	Py_Initialize();
	
	PyImport_ImportModule("akira");

	FILE *pPyFile = _Py_fopen(Py_BuildValue("s", "main.py"), "r+");
	if(pPyFile != NULL) {
		PyRun_SimpleFile(pPyFile, "main.py");
	}

	Py_Finalize();

	system("pause");

	return 0;
}