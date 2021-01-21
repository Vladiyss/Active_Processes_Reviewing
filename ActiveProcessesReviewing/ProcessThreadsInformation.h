#pragma once
#include <Windows.h>

class ProcessThreadsInformation
{
public:
	ProcessThreadsInformation();
	DWORD GetthreadStartAddress();
	LONG GetthreadBasePriority();
	DWORD GetthreadID();
	ULONG GetthreadIOPending();
	DWORD GetthreadKernelTime();
	DWORD GetthreadUserTime();

	void SetthreadStartAddress(DWORD value);
	void SetthreadBasePriority(LONG value);
	void SetthreadID(DWORD value);
	void SetthreadIOPending(ULONG value);
	void SetthreadKernelTime(DWORD value);
	void SetthreadUserTime(DWORD value);
private:
	DWORD threadStartAddress;
	LONG threadBasePriority;
	DWORD threadID;
	ULONG threadIOPending;
	DWORD threadKernelTime;
	DWORD threadUserTime;
};
