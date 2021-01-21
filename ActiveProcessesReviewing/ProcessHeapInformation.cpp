#include "ProcessHeapInformation.h"

ProcessHeapInformation::ProcessHeapInformation()
{
	heapBlockSize = 0;
	heapStartAddress = 0;
	heapBlockFlag = 0;
}

SIZE_T ProcessHeapInformation::GetheapBlockSize()
{
	return heapBlockSize;
}

ULONG_PTR ProcessHeapInformation::GetheapStartAddress()
{
	return heapStartAddress;
}

DWORD ProcessHeapInformation::GetheapBlockFlag()
{
	return heapBlockFlag;
}

void ProcessHeapInformation::SetheapBlockSize(SIZE_T value)
{
	heapBlockSize = value;
}

void ProcessHeapInformation::SetheapStartAddress(ULONG_PTR value)
{
	heapStartAddress = value;
}

void ProcessHeapInformation::SetheapBlockFlag(DWORD value)
{
	heapBlockFlag = value;
}