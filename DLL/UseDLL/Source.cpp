
/* [IMPORT DLL METHOD 01]
#include "main.h"

#pragma comment(lib, "dllDemo.lib")
extern "C" __declspec(dllimport) void ExportFunction();

int main(int argc, char* argv[]) {

	ExportFunction();
	return 0;
}

*/

/* [IMPORT DLL METHOD 02] */
#include "main.h"

int main(int argc, char* argv[]) {
	typedef void (*lpTest)();
	lpTest MyFunction;

	// Load DLL
	HINSTANCE hModule = LoadLibrary("dllDemo.dll");

	// Get function address
	MyFunction = (lpTest)GetProcAddress(hModule, "ExportFunction");

	// Use function
	MyFunction();

	// Free Dll
	FreeLibrary(hModule);

	return 0;
}