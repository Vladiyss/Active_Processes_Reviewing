#pragma once
#include <Windows.h>

class ProcessModulesInformation
{
public:
	ProcessModulesInformation();
	DWORD GetmoduleSize();
	DWORD GetpModuleBaseAddress();
	WCHAR *GetmoduleName();
	void SetmoduleSize(DWORD value);
	void SetpModuleBaseAddress(DWORD value);
	void SetmoduleName(WCHAR *value);
private:
	DWORD moduleSize;
	DWORD pModuleBaseAddress;
	WCHAR *moduleName;
};
