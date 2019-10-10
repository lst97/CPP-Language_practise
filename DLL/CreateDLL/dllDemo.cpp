#include "pch.h"
#include "dllDemo.h"

void Init() {
	MessageBox(0, L"Init", L"Init", MB_OK);
	return;
}

void Destroy() {
	MessageBox(0, L"Destroy", L"Destroy", MB_OK);
	return;
}

void ExportFunction() {

	MessageBox(0, L"Export Function", L"Export Function", MB_OK);
	return;
}
