#include "ProcessMemoryInformation.h"

ProcessMemoryInformation::ProcessMemoryInformation()
{
	pageFaultCount = 0;
	workingSetSize = 0;
	peakWorkingSetSize = 0;
	quotaPagedPoolUsage = 0;
	quotaPeakPagedPoolUsage = 0;
	quotaNonPagedPoolUsage = 0;
	quotaPeakNonPagedPoolUsage = 0;
	pagefileUsage = 0;
	peakPagefileUsage = 0;

	pPageInformationVector = new std::vector<PageInformation *>();
}

ProcessMemoryInformation::PageInformation::PageInformation()
{
	pageProtection = 0;
	pageShareCount = 0;
	pageShared = 0;
}

DWORD ProcessMemoryInformation::GetpageFaultCount()
{
	return pageFaultCount;
}

SIZE_T ProcessMemoryInformation::GetworkingSetSize()
{
	return workingSetSize;
}

SIZE_T ProcessMemoryInformation::GetpeakWorkingSetSize()
{
	return peakWorkingSetSize;
}

SIZE_T ProcessMemoryInformation::GetquotaPagedPoolUsage()
{
	return quotaPagedPoolUsage;
}

SIZE_T ProcessMemoryInformation::GetquotaPeakPagedPoolUsage()
{
	return quotaPeakPagedPoolUsage;
}

SIZE_T ProcessMemoryInformation::GetquotaNonPagedPoolUsage()
{
	return quotaNonPagedPoolUsage;
}

SIZE_T ProcessMemoryInformation::GetquotaPeakNonPagedPoolUsage()
{
	return quotaPeakNonPagedPoolUsage;
}

SIZE_T ProcessMemoryInformation::GetpagefileUsage()
{
	return pagefileUsage;
}

SIZE_T ProcessMemoryInformation::GetpeakPagefileUsage()
{
	return peakPagefileUsage;
}

std::vector<ProcessMemoryInformation::PageInformation *> *ProcessMemoryInformation::GetpPageInformation()
{
	return pPageInformationVector;
}


void ProcessMemoryInformation::SetpageFaultCount(DWORD value)
{
	pageFaultCount = value;
}

void ProcessMemoryInformation::SetworkingSetSize(SIZE_T value)
{
	workingSetSize = value;
}

void ProcessMemoryInformation::SetpeakWorkingSetSize(SIZE_T value)
{
	peakWorkingSetSize = value;
}

void ProcessMemoryInformation::SetquotaPagedPoolUsage(SIZE_T value)
{
	quotaPagedPoolUsage = value;
}

void ProcessMemoryInformation::SetquotaPeakPagedPoolUsage(SIZE_T value)
{
	quotaPeakPagedPoolUsage = value;
}

void ProcessMemoryInformation::SetquotaNonPagedPoolUsage(SIZE_T value)
{
	quotaNonPagedPoolUsage = value;
}

void ProcessMemoryInformation::SetquotaPeakNonPagedPoolUsage(SIZE_T value)
{
	quotaPeakNonPagedPoolUsage = value;
}

void ProcessMemoryInformation::SetpagefileUsage(SIZE_T value)
{
	pagefileUsage = value;
}

void ProcessMemoryInformation::SetpeakPagefileUsage(SIZE_T value)
{
	peakPagefileUsage = value;
}

void ProcessMemoryInformation::SetValueToPageInformationVector(PageInformation *value)
{
	pPageInformationVector->push_back(value);
}
