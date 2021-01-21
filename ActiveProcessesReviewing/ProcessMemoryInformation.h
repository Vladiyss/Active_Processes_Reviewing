#pragma 
#include <vector>
#include <Windows.h>

class ProcessMemoryInformation
{
public:

	class PageInformation
	{
	public:
		PageInformation();
		ULONG_PTR pageProtection;
		ULONG_PTR pageShareCount;
		ULONG_PTR pageShared;
	};

	ProcessMemoryInformation();
	DWORD GetpageFaultCount();
	SIZE_T GetworkingSetSize();
	SIZE_T GetpeakWorkingSetSize();
	SIZE_T GetquotaPagedPoolUsage();
	SIZE_T GetquotaPeakPagedPoolUsage();
	SIZE_T GetquotaNonPagedPoolUsage();
	SIZE_T GetquotaPeakNonPagedPoolUsage();
	SIZE_T GetpagefileUsage();
	SIZE_T GetpeakPagefileUsage();
	std::vector<PageInformation *> *GetpPageInformation();

	void SetpageFaultCount(DWORD value);
	void SetworkingSetSize(SIZE_T value);
	void SetpeakWorkingSetSize(SIZE_T value);
	void SetquotaPagedPoolUsage(SIZE_T value);
	void SetquotaPeakPagedPoolUsage(SIZE_T value);
	void SetquotaNonPagedPoolUsage(SIZE_T value);
	void SetquotaPeakNonPagedPoolUsage(SIZE_T value);
	void SetpagefileUsage(SIZE_T value);
	void SetpeakPagefileUsage(SIZE_T value);
	void SetValueToPageInformationVector(PageInformation *value);

private:
	DWORD pageFaultCount;
	SIZE_T workingSetSize;
	SIZE_T peakWorkingSetSize;
	SIZE_T quotaPagedPoolUsage;
	SIZE_T quotaPeakPagedPoolUsage;
	SIZE_T quotaNonPagedPoolUsage;
	SIZE_T quotaPeakNonPagedPoolUsage;
	SIZE_T pagefileUsage;
	SIZE_T peakPagefileUsage;

	std::vector<PageInformation *> *pPageInformationVector;
};