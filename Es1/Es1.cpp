/**
* Name:    Francesco
* Surname: Longo
* ID:      223428
* Lab:     8
* Ex:      1
*
* Familiarize with the Visual Studio Program Environment
*
* The following program copies a file, whose name is received as
* first parameter on the command line, into another file, whose
* name is passed as the second parameter on the command line.
*
* Perform the following steps:
* - Cut-and-paste the program into a .cpp file
* - Create a new project and insert the program within the MS Visual
*   Studio environment.
* - Set the command line parameters.
* - Build (compile) the project.
* - As it contains (3?) syntax errors correct them.
* - Once obtained the executable code, run it.
* - As it contains a bug, debug it using the basic features of
*   the Visual Studio debugger.
*
* Learn how to:
* - set a break-point in the code
* - proceed step-by-step
* - visualize variable values
* - see thread configuration
* - etc.
**/

#include <windows.h>
#include <tchar.h>  // Added tchar.h
#include <stdio.h>

// constants
#define SECONDS 10
#define BUF_SIZE 100

// prototypes
int Return(int value);

// Main
INT _tmain(INT argc, LPTSTR argv[]) {
	// Variables
	HANDLE hIn, hOut; // Modify Hon to hIn
	DWORD nIn, nOut;
	CHAR buffer[BUF_SIZE];

	// Check parameters passed from command line
	printf("I have %d parameters:\n", argc);
	for (int i = 0; i < argc; i++) {
		printf(" - param %d is: %S\n", i, argv[i]);
	}

	if (argc != 3) {
		printf("Usage: cp file1 file2\n"); // Added L for wide strings
		return Return(1);
	}

	// Create file for reading file passed from command line
	hIn = CreateFile(argv[1], 
		GENERIC_READ, 
		FILE_SHARE_READ, 
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	// check if the file is opened correctly
	if (hIn == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Cannot open input file. Error: %x\n", GetLastError()); // Added stderr
		return Return(2);
	} else {
		printf("-> File %S open correctly.\n", argv[1]);
	}

	// create output file
	hOut = CreateFile(argv[2], 
		GENERIC_WRITE, 
		0, 
		NULL,
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	// check if the file is opened correctly
	if (hOut == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Cannot open output file. Error: %x\n", GetLastError());
		CloseHandle(hIn);
		return Return(3);
	} else {
		printf("-> File %S open correctly.\n", argv[2]);
	}

	// read BUF_SIZE each time and write to the output file, check it nIn is >0 (I read something)
	while (ReadFile(hIn, buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
		// Write what I read, not all the buffer but only the size I read
		WriteFile(hOut, buffer, nIn, &nOut, NULL); // Modified BUF_SIZE into nIn

		// check ifsize of what I read is the same of what O wrote
		if (nIn != nOut) {
			printf("Fatal write error: %x\n", GetLastError());
			fprintf(stderr, "Fatal write error: %x\n", GetLastError());
			CloseHandle(hIn); 
			CloseHandle(hOut);
			return Return(4);
		}
	}

	// close HANDLE
	CloseHandle(hIn);
	CloseHandle(hOut);

	printf("-> Done!\n");
	
	// Return with sleep
	return Return(0);
}

int Return(int value) {
	Sleep(SECONDS * 1000);
	return value;
}
