#include "ProcessThreadsInformation.h"

ProcessThreadsInformation::ProcessThreadsInformation()
{
	threadStartAddress = 0;
	threadBasePriority = -1;
	threadID = 0;
	threadIOPending = 0;
	threadKernelTime = 0;
	threadUserTime = 0;
}

DWORD ProcessThreadsInformation::GetthreadStartAddress()
{
	return threadStartAddress;
}

LONG ProcessThreadsInformation::GetthreadBasePriority()
{
	return threadBasePriority;
}

DWORD ProcessThreadsInformation::GetthreadID() 
{
	return threadID;
}

ULONG ProcessThreadsInformation::GetthreadIOPending()
{
	return threadIOPending;
}

DWORD ProcessThreadsInformation::GetthreadKernelTime()
{
	return threadKernelTime;
}

DWORD ProcessThreadsInformation::GetthreadUserTime()
{
	return threadUserTime;
}


void ProcessThreadsInformation::SetthreadStartAddress(DWORD value)
{
	threadStartAddress = value;
}

void ProcessThreadsInformation::SetthreadBasePriority(LONG value)
{
	threadBasePriority = value;
}

void ProcessThreadsInformation::SetthreadID(DWORD value)
{
	threadID = value;
}

void ProcessThreadsInformation::SetthreadIOPending(ULONG value)
{
	threadIOPending = value;
}

void ProcessThreadsInformation::SetthreadKernelTime(DWORD value)
{
	threadKernelTime = value;
}

void ProcessThreadsInformation::SetthreadUserTime(DWORD value)
{
	threadUserTime = value;
}
