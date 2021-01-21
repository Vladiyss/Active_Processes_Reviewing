#pragma once
#include <vector>
#include <string>
#include "ProcessInformation.h"
#include <TlHelp32.h>
#include <Psapi.h>
#include <winternl.h>

#define _WIN32_WINNT 0x0A00
typedef NTSTATUS(WINAPI *pFunc)(HANDLE, LONG, PVOID, ULONG, PULONG);

class ActiveProcessesReviewing
{
public:
	std::vector<ProcessInformation *> *pProcessInformationVector;
	
	ActiveProcessesReviewing();
	void CollectActiveProcessesInformation();
	void SetProcessPriorityClass(ProcessInformation *pProcessInformation, HANDLE handle, DWORD PID);
	void SetProcessHandleCount(ProcessInformation *pProcessInformation, HANDLE handle, DWORD PID);
	void SetProcessPriorityBoost(ProcessInformation *pProcessInformation, HANDLE handle, DWORD PID);
	void SetProcessTime(ProcessInformation *pProcessInformation, HANDLE handle, DWORD PID);

	void SetThreadTime(ProcessThreadsInformation *pProcessThreadsInformation, HANDLE handle, DWORD TID);
	void SetThreadInfoUsingNTDLL(ProcessThreadsInformation *pProcessThreadsInformation, HANDLE handle, DWORD TID, pFunc NtQueryInformationThread);
	void AddThreadInformationToProcessInformation(ProcessThreadsInformation *pProcessThreadsInformation, int k, int vectorSize, DWORD TID, DWORD ownerProcessID);

	void CollectActiveProcessesModulesInformation();
	void CollectActiveProcessesHeapsInformation();
	void CollectActiveProcessesMemoryInformation();
	void CollectActiveProcessesThreadsInformation();

	void WriteActiveProcessesInformation();
	void WriteActiveProcessesHeapInformation(DWORD PID);
	void WriteActiveProcessesModulesInformation(DWORD PID);
	void WriteActiveProcessesMemoryInformation(DWORD PID);
	void WriteActiveProcessesThreadsInformation(DWORD PID);

	int FindProcessInformationWithCorrespondingID(DWORD PID);
	void ConvertMemoryValue(std::string *resultValue, SIZE_T value);

	void ClearMemoryOccupiedByProcessesInformation();
};
