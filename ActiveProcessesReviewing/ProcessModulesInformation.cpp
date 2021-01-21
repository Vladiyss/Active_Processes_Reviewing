#include "ProcessModulesInformation.h"

ProcessModulesInformation::ProcessModulesInformation()
{
	moduleSize = 0;
	pModuleBaseAddress = 0;
}

DWORD ProcessModulesInformation::GetmoduleSize() 
{
	return moduleSize;
}

DWORD ProcessModulesInformation::GetpModuleBaseAddress()
{
	return pModuleBaseAddress;
}

WCHAR *ProcessModulesInformation::GetmoduleName()
{
	return moduleName;
}

void ProcessModulesInformation::SetmoduleSize(DWORD value)
{
	moduleSize = value;
}

void ProcessModulesInformation::SetpModuleBaseAddress(DWORD value)
{
	pModuleBaseAddress = value;
}

void ProcessModulesInformation::SetmoduleName(WCHAR *value)
{
	moduleName = value;
}