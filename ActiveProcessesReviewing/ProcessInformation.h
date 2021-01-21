#pragma once
#include <vector>
#include <string>
#include <Windows.h>

#include "ProcessHeapInformation.h"
#include "ProcessMemoryInformation.h"
#include "ProcessModulesInformation.h"
#include "ProcessThreadsInformation.h"

class ProcessInformation
{
public:
	ProcessInformation();
	DWORD GetprocessID();
	DWORD GetprocessThreadsNumber();
	DWORD GetprocessParentID();
	DWORD GetprocessPriorityClass();
	DWORD GetprocessHandleCount();
	DWORD GetprocessKernelTime();
	DWORD GetprocessUserTime();
	WCHAR *GetprocessName();
	LONG GetprocessbaseThreadsPriority();
	BOOL GetprocessPriorityBoost();
	std::vector<ProcessHeapInformation *> *GetpProcessHeapInformationVector();
	ProcessMemoryInformation *GetpProcessMemoryInformation();
	std::vector<ProcessModulesInformation *> *GetpProcessModulesInformationVector();
	std::vector<ProcessThreadsInformation *> *GetpProcessThreadsInformationVector();

	void SetprocessID(DWORD value);
	void SetprocessThreadsNumber(DWORD value);
	void SetprocessParentID(DWORD value);
	void SetprocessPriorityClass(DWORD value);
	void SetprocessHandleCount(DWORD value);
	void SetprocessKernelTime(DWORD value);
	void SetprocessUserTime(DWORD value);
	void SetprocessName(WCHAR *value);
	void SetprocessbaseThreadsPriority(LONG value);
	void SetprocessPriorityBoost(BOOL value);
	void ProcessInformation::SetValueToProcessHeapInformationVector(ProcessHeapInformation *value);
	void SetpProcessMemoryInformation(ProcessMemoryInformation *value);
	void ProcessInformation::SetValueToProcessModulesInformationVector(ProcessModulesInformation *value);
	void ProcessInformation::SetValueToProcessThreadsInformationVector(ProcessThreadsInformation *value);
private:
	DWORD processID;
	DWORD processThreadsNumber;
	DWORD processParentID;
	DWORD processPriorityClass;
	DWORD processHandleCount;
	WCHAR *processName;
	LONG processbaseThreadsPriority;
	BOOL processPriorityBoost;
	DWORD processKernelTime;
	DWORD processUserTime;
	std::vector<ProcessHeapInformation *> *pProcessHeapInformationVector;
	ProcessMemoryInformation *pProcessMemoryInformation;
	std::vector<ProcessModulesInformation *> *pProcessModulesInformationVector;
	std::vector<ProcessThreadsInformation *> *pProcessThreadsInformationVector;
};
