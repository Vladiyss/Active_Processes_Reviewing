#pragma once
#include <Windows.h>

class ProcessHeapInformation
{
public:
	ProcessHeapInformation();
	SIZE_T GetheapBlockSize();
	ULONG_PTR GetheapStartAddress();
	DWORD GetheapBlockFlag();
	void SetheapBlockSize(SIZE_T value);
	void SetheapStartAddress(ULONG_PTR value);
	void SetheapBlockFlag(DWORD value);
private:
	SIZE_T heapBlockSize;
	ULONG_PTR heapStartAddress;
	DWORD heapBlockFlag;
};