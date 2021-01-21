#include "ProcessInformation.h"

ProcessInformation::ProcessInformation()
{
	processID = 0;
	processThreadsNumber = 0;
	processParentID = 0;
	processPriorityClass = 0;
	processHandleCount = 0;
	processKernelTime = 0;
	processUserTime = 0;
	processbaseThreadsPriority = 0;
	processPriorityBoost = false;
	pProcessHeapInformationVector = new std::vector<ProcessHeapInformation *>();
	pProcessMemoryInformation = new ProcessMemoryInformation();
	pProcessModulesInformationVector = new std::vector<ProcessModulesInformation *>();
	pProcessThreadsInformationVector = new std::vector<ProcessThreadsInformation *>();
}

DWORD ProcessInformation::GetprocessID()
{
	return processID;
}

DWORD ProcessInformation::GetprocessThreadsNumber()
{
	return processThreadsNumber;
}

DWORD ProcessInformation::GetprocessParentID()
{
	return processParentID;
}

DWORD ProcessInformation::GetprocessPriorityClass()
{
	return processPriorityClass;
}

DWORD ProcessInformation::GetprocessHandleCount()
{
	return processHandleCount;
}

DWORD ProcessInformation::GetprocessKernelTime()
{
	return processKernelTime;
}

DWORD ProcessInformation::GetprocessUserTime()
{
	return processUserTime;
}

WCHAR *ProcessInformation::GetprocessName()
{
	return processName;
}

LONG ProcessInformation::GetprocessbaseThreadsPriority()
{
	return processbaseThreadsPriority;
}

BOOL ProcessInformation::GetprocessPriorityBoost()
{
	return processPriorityBoost;
}

std::vector<ProcessHeapInformation *> *ProcessInformation::GetpProcessHeapInformationVector()
{
	return pProcessHeapInformationVector;
}

ProcessMemoryInformation *ProcessInformation::GetpProcessMemoryInformation()
{
	return pProcessMemoryInformation;
}

std::vector<ProcessModulesInformation *> *ProcessInformation::GetpProcessModulesInformationVector()
{
	return pProcessModulesInformationVector;
}

std::vector<ProcessThreadsInformation *> *ProcessInformation::GetpProcessThreadsInformationVector()
{
	return pProcessThreadsInformationVector;
}


void ProcessInformation::SetprocessID(DWORD value)
{
	processID = value;
}

void ProcessInformation::SetprocessThreadsNumber(DWORD value)
{
	processThreadsNumber = value;
}

void ProcessInformation::SetprocessParentID(DWORD value)
{
	processParentID = value;
}

void ProcessInformation::SetprocessPriorityClass(DWORD value)
{
	processPriorityClass = value;
}

void ProcessInformation::SetprocessHandleCount(DWORD value)
{
	processHandleCount = value;
}

void ProcessInformation::SetprocessKernelTime(DWORD value)
{
	processKernelTime = value;
}

void ProcessInformation::SetprocessUserTime(DWORD value)
{
	processUserTime = value;
}

void ProcessInformation::SetprocessName(WCHAR *value)
{
	processName = value;
}

void ProcessInformation::SetprocessbaseThreadsPriority(LONG value)
{
	processbaseThreadsPriority = value;
}

void ProcessInformation::SetprocessPriorityBoost(BOOL value)
{
	processPriorityBoost = value;
}

void ProcessInformation::SetValueToProcessHeapInformationVector(ProcessHeapInformation *value)
{
	pProcessHeapInformationVector->push_back(value);
}

void ProcessInformation::SetpProcessMemoryInformation(ProcessMemoryInformation *value)
{
	pProcessMemoryInformation = value;
}

void ProcessInformation::SetValueToProcessModulesInformationVector(ProcessModulesInformation *value)
{
	pProcessModulesInformationVector->push_back(value);
}

void ProcessInformation::SetValueToProcessThreadsInformationVector(ProcessThreadsInformation *value)
{
	pProcessThreadsInformationVector->push_back(value);
}