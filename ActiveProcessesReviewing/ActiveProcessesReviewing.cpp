#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <tchar.h>
#include <math.h>
#include "ActiveProcessesReviewing.h"

using namespace std;

string PageProtection[32] = { "Not accessed", "Read-only", "Executable", "Executable and read-only", "Read/write", "Copy-on-write",
	"Executable and read/write", "Executable and copy-on-write", "Not accessed", "Non-cacheable and read-only", "Non-cacheable and executable",
	"Non-cacheable, executable, and read-only", "Non-cacheable and read/write", "Non-cacheable and copy-on-write",
	"Non-cacheable, executable, and read/write", "Non-cacheable, executable, and copy-on-write", "Not accessed" , "Guard page and read-only",
	"Guard page and executable", "Guard page, executable, and read-only", "Guard page and read/write" , "Guard page and copy-on-write" ,
	"Guard page, executable, and read/write" , "Guard page, executable, and copy-on-write" , "Not accessed" ,
	"Non-cacheable, guard page, and read-only" , "Non-cacheable, guard page, and executable" , "Non-cacheable, guard page, executable, and read-only" ,
	"Non-cacheable, guard page, and read/write" , "Non-cacheable, guard page, and copy-on-write" ,
	"Non-cacheable, guard page, executable, and read/write" , "Non-cacheable, guard page, executable, and copy-on-write" };

string MemoryDimensionParticles[2] = { "Kb", "Mb" };

ActiveProcessesReviewing::ActiveProcessesReviewing()
{
		pProcessInformationVector = new std::vector<ProcessInformation *>;
}

void ActiveProcessesReviewing::ClearMemoryOccupiedByProcessesInformation()
{
	cout << "Clearing memory starts" << endl;
	for (auto pProcessInformation : *pProcessInformationVector)
	{
		for (auto pProcessHeapInformation : *(pProcessInformation->GetpProcessHeapInformationVector()))
		{
			delete pProcessHeapInformation;
		}

		for (auto pProcessModulesInformation : *(pProcessInformation->GetpProcessModulesInformationVector()))
		{
			delete[] pProcessModulesInformation->GetmoduleName();
			delete pProcessModulesInformation;
		}

		for (auto pProcessThreadsInformation : *(pProcessInformation->GetpProcessThreadsInformationVector()))
		{
			delete pProcessThreadsInformation;
		}

		for (auto pPageInformation : *(pProcessInformation->GetpProcessMemoryInformation()->GetpPageInformation()))
		{
			delete pPageInformation;
		}
		pProcessInformation->GetpProcessMemoryInformation()->GetpPageInformation()->clear();
		delete pProcessInformation->GetpProcessMemoryInformation()->GetpPageInformation();
		delete pProcessInformation->GetpProcessMemoryInformation();

		pProcessInformation->GetpProcessHeapInformationVector()->clear();
		pProcessInformation->GetpProcessModulesInformationVector()->clear();
		pProcessInformation->GetpProcessThreadsInformationVector()->clear();
		delete pProcessInformation->GetpProcessHeapInformationVector();
		delete pProcessInformation->GetpProcessModulesInformationVector();
		delete pProcessInformation->GetpProcessThreadsInformationVector();

		delete [] pProcessInformation->GetprocessName();
		delete pProcessInformation;
	}

	pProcessInformationVector->clear();
	delete pProcessInformationVector;

	cout << "Clearing memory ended" << endl;
}

int ActiveProcessesReviewing::FindProcessInformationWithCorrespondingID(DWORD PID)
{
	int result = 0;
	int vectorSize = pProcessInformationVector->size();
	while ( (result < vectorSize) && (pProcessInformationVector->at(result)->GetprocessID() != PID) )
	{
		result++;
	}

	if (result == vectorSize)
	{
		cout << "!!! PID - " << PID << " Failed to find information" << endl;
		return -1;
	}
	else
	{
		return result;
	}
}

void ActiveProcessesReviewing::ConvertMemoryValue(string *resultValue, SIZE_T value)
{
	SIZE_T valueCopy = value;
	int counter = 0;
	while (valueCopy > 1023)
	{
		valueCopy /= 1024;
		counter++;
	}

	SIZE_T rankValue;
	SIZE_T NumberOfAccumulatedBytes = 0;
	SIZE_T remainder = value;
	bool lessFlag = false;

	if (counter < 3) 
	{
		for (int i = counter; (i > 0) && !lessFlag; i--)
		{
			if (remainder > (SIZE_T)(pow(1024, i)))
			{
				rankValue = remainder / (SIZE_T)(pow(1024,i));
				char *str = new char[20];
				_itoa(rankValue, str, 10);
				*resultValue += str;
				delete str;
				*resultValue += " " + MemoryDimensionParticles[i - 1] + " ";
				NumberOfAccumulatedBytes = rankValue * (SIZE_T)(pow(1024, i));
				remainder %= NumberOfAccumulatedBytes;
			}
			else
			{
				lessFlag = true;
			}
		
		}
	}
	
	char *str= new char[20];
	_itoa(remainder, str, 10);
	*resultValue += str;
	delete str;
	*resultValue += " bytes";
}

void ActiveProcessesReviewing::WriteActiveProcessesInformation()
{
	cout << "Processes information..." << endl;
	cout << "____________________________________________________________________________________________________" <<
		"__________________________________________________" << endl;
	cout << "|" << setw(6) << left << "Number" << "|" << setw(36) << left << "Name" << "|"
		<< setw(6) << left << "ID" << "|" << setw(7) << left << "Threads" << "|"
		<< setw(9) << left << "Parent ID" << "|" << setw(13) << left << "Base priority" << "|"
		<< setw(14) << left << "Priority class" << "|" << setw(12) << left << "Handle count" << "|"
		<< setw(13) << left << "Isnot boosted" << "|" << setw(11) << left << "Kernel time" << "|" 
		<< setw(11) << left << "User time" << "|" << endl;
	int counter = 1;
	for (auto pProcessInformation : *pProcessInformationVector)
	{
		string priority;
		if (pProcessInformation->GetprocessPriorityClass() == ABOVE_NORMAL_PRIORITY_CLASS)
		{
			priority = "ABOVE_NORMAL";
		}
		else if (pProcessInformation->GetprocessPriorityClass() == BELOW_NORMAL_PRIORITY_CLASS)
		{
			priority = "BELOW_NORMAL";
		}
		else if (pProcessInformation->GetprocessPriorityClass() == HIGH_PRIORITY_CLASS)
		{
			priority = "HIGH";
		}
		else if (pProcessInformation->GetprocessPriorityClass() == IDLE_PRIORITY_CLASS)
		{
			priority = "IDLE";
		}
		else if (pProcessInformation->GetprocessPriorityClass() == NORMAL_PRIORITY_CLASS)
		{
			priority = "NORMAL";
		}
		else if (pProcessInformation->GetprocessPriorityClass() == REALTIME_PRIORITY_CLASS)
		{
			priority = "REALTIME";
		}
		else
		{
			priority = "Undefined";
		}

		cout << "|" << setw(6) << left << counter << "|";
		wprintf(L"%-36s", pProcessInformation->GetprocessName());
		cout << "|"
			<< setw(6) << left << pProcessInformation->GetprocessID() << "|" << setw(7) << left << pProcessInformation->GetprocessThreadsNumber() << "|"
			<< setw(9) << left << pProcessInformation->GetprocessParentID() << "|"
			<< setw(13) << left << pProcessInformation->GetprocessbaseThreadsPriority() << "|"
			<< setw(14) << left << priority << "|" << setw(12) << left << pProcessInformation->GetprocessHandleCount() << "|"
			<< setw(13) << left << boolalpha << pProcessInformation->GetprocessPriorityBoost() << "|"
			<< setw(11) << left << pProcessInformation->GetprocessKernelTime() << "|"
			<< setw(11) << left << pProcessInformation->GetprocessUserTime() << "|" << endl;
		counter++;
	}
	cout << "____________________________________________________________________________________________________" <<
		"__________________________________________________" << endl;
	cout << "" << endl;
}

void ActiveProcessesReviewing::WriteActiveProcessesHeapInformation(DWORD PID)
{
	int numberOfProcessInformationInVector;
	numberOfProcessInformationInVector = FindProcessInformationWithCorrespondingID(PID);
	if (numberOfProcessInformationInVector != -1)
	{
		cout << "PID - " << PID << " heap blocks information..." << endl;
		cout << "_______________________________________________________________________" << endl;
		cout << "|" << setw(6) << left << "Number" << "|" << setw(20) << left << "Start address" << "|"
			<< setw(20) << left << "Size" << "|" << setw(20) << left << "Memory block flag" << "|" << endl;
		int counter = 1;
		for (auto pProcessesHeapInformation : *(pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessHeapInformationVector()))
		{
			string flag;
			if (pProcessesHeapInformation->GetheapBlockFlag() == LF32_FIXED)
			{
				flag = "LF32_FIXED";
			}
			else if (pProcessesHeapInformation->GetheapBlockFlag() == LF32_FREE)
			{
				flag = "LF32_FREE";
			}
			else if (pProcessesHeapInformation->GetheapBlockFlag() == LF32_MOVEABLE)
			{
				flag = "LF32_MOVEABLE";
			}
			else
			{
				flag = "Undefined";
			}
			string *str = new string();
			ConvertMemoryValue(str, pProcessesHeapInformation->GetheapBlockSize());
			cout << "|" << setw(6) << left << counter << "|" << setw(20) << left << showbase << hex << pProcessesHeapInformation->GetheapStartAddress() << "|"
				<< setw(20) << left << noshowbase << dec << *str << "|" << setw(20) << left << flag << "|" << endl;
			delete str;
			counter++;
		}
		cout << "_______________________________________________________________________" << endl;
		cout << "" << endl;
	}
}

void ActiveProcessesReviewing::WriteActiveProcessesModulesInformation(DWORD PID)
{
	int numberOfProcessInformationInVector;
	numberOfProcessInformationInVector = FindProcessInformationWithCorrespondingID(PID);
	if (numberOfProcessInformationInVector != -1)
	{
		cout << "PID - " << PID << " modules information..." << endl;
		cout << "_________________________________________________________________________________" << endl;
		cout << "|" << setw(6) << left << "Number" << "|" << setw(30) << left << "Name" << "|" 
			<< setw(20) << left << "Size" << "|" << setw(20) << left << "Base Address" << "|" << endl;
		int counter = 1;
		for (auto pProcessModulesInformation : *(pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessModulesInformationVector()))
		{
			string *str = new string();
			ConvertMemoryValue(str, pProcessModulesInformation->GetmoduleSize());
			cout << "|" << setw(6) << left << counter << "|"; 
			wprintf(L"%-30s", pProcessModulesInformation->GetmoduleName());
			cout << "|"
				<< setw(20) << left << *str << "|"
				<< setw(20) << left << showbase << hex << pProcessModulesInformation->GetpModuleBaseAddress() << "|" << endl;
			cout << noshowbase << dec;
			delete str;
			counter++;
		}
		cout << "_________________________________________________________________________________" << endl;
		cout << "" << endl;
	}
}

void ActiveProcessesReviewing::WriteActiveProcessesMemoryInformation(DWORD PID)
{
	int numberOfProcessInformationInVector;
	numberOfProcessInformationInVector = FindProcessInformationWithCorrespondingID(PID);
	if (numberOfProcessInformationInVector != -1)
	{
		cout << "PID - " << PID << " memory information..." << endl;
		
		string *str = new string[8];
		cout << setw(40) << left << "Page fault count" << "-- " << setw(20) << left <<
			pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessMemoryInformation()->GetpageFaultCount() << endl;
		ConvertMemoryValue(&str[0], pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessMemoryInformation()->GetworkingSetSize());
		cout << setw(40) << left << "Working set size" << "-- " << setw(20) << left <<
			str[0] << endl;
		ConvertMemoryValue(&str[1], pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessMemoryInformation()->GetpeakWorkingSetSize());
		cout << setw(40) << left << "Peak working set size" << "-- " << setw(20) << left <<
			str[1] << endl;
		ConvertMemoryValue(&str[2], pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessMemoryInformation()->GetquotaPagedPoolUsage());
		cout << setw(40) << left << "Quota paged pool usage" << "-- " << setw(20) << left <<
			str[2] << endl;
		ConvertMemoryValue(&str[3], pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessMemoryInformation()->GetquotaPeakPagedPoolUsage());
		cout << setw(40) << left << "Quota peak paged pool usage" << "-- " << setw(20) << left <<
			str[3] << endl;
		ConvertMemoryValue(&str[4], pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessMemoryInformation()->GetquotaNonPagedPoolUsage());
		cout << setw(40) << left << "Quota non paged pool usage" << "-- " << setw(20) << left <<
			str[4] << endl;
		ConvertMemoryValue(&str[5], pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessMemoryInformation()->GetquotaPeakNonPagedPoolUsage());
		cout << setw(40) << left << "Quota peak non paged pool usage" << "-- " << setw(20) << left <<
			str[5] << endl;
		ConvertMemoryValue(&str[6], pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessMemoryInformation()->GetpagefileUsage());
		cout << setw(40) << left << "Page file usage" << "-- " << setw(20) << left <<
			str[6] << endl;
		ConvertMemoryValue(&str[7], pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessMemoryInformation()->GetpeakPagefileUsage());
		cout << setw(40) << left << "Peak page file usage" << "-- " << setw(20) << left <<
			str[7] << endl;
		delete [] str;
		
		cout << "Pages..." << endl;
		cout << "____________________________________________________________________________________________" << endl;
		cout << "|" << setw(6) << left << "Number" << "|" << setw(60) << left << "Protection" << "|"
			<< setw(11) << left << "Share count" << "|" << setw(10) << left << "Is shared" << "|" << endl;
		int counter = 1;
		for (auto pPageInformation : *(pProcessInformationVector->at(numberOfProcessInformationInVector)->
			GetpProcessMemoryInformation()->GetpPageInformation()))
		{
			cout << "|" << setw(6) << left << counter << "|" << setw(2) << left << pPageInformation->pageProtection << "- "
				<< setw(56) << left << PageProtection[pPageInformation->pageProtection] << "|"
				<< setw(11) << left << pPageInformation->pageShareCount << "|"
				<< setw(10) << left << pPageInformation->pageShared << "|" << endl;
			counter++;
		}
		cout << "____________________________________________________________________________________________" << endl;
		cout << "" << endl;
	}
}

void ActiveProcessesReviewing::WriteActiveProcessesThreadsInformation(DWORD PID)
{
	int numberOfProcessInformationInVector;
	numberOfProcessInformationInVector = FindProcessInformationWithCorrespondingID(PID);
	if (numberOfProcessInformationInVector != -1)
	{
		cout << "PID - " << PID << " threads information..." << endl;
		cout << "_______________________________________________________________________________________________________" << endl;
		cout << "|" << setw(6) << left << "Number" << "|" << setw(6) << left << "ID" << "|"
			<< setw(13) << left << "Base priority" << "|" << setw(20) << left << "Start Address" << "|" 
			<< setw(10) << left << "IO pending" << "|" << setw(20) << left << "Kernel time" << "|"
			<< setw(20) << left << "User time" << "|" << endl;
		int counter = 1;
		for (auto pProcessThreadsInformation : *(pProcessInformationVector->at(numberOfProcessInformationInVector)->GetpProcessThreadsInformationVector()))
		{
			cout << "|" << setw(6) << left << counter << "|" << setw(6) << left << pProcessThreadsInformation->GetthreadID() << "|"
				<< setw(13) << left << pProcessThreadsInformation->GetthreadBasePriority() << "|"
				<< setw(20) << left << showbase << hex << pProcessThreadsInformation->GetthreadStartAddress() << "|"
				<< setw(10) << left << noshowbase << dec << pProcessThreadsInformation->GetthreadIOPending() << "|"
				<< setw(20) << left << pProcessThreadsInformation->GetthreadKernelTime() << "|"
				<< setw(20) << left << pProcessThreadsInformation->GetthreadUserTime() << "|" << endl;
			counter++;
		}
		cout << "_______________________________________________________________________________________________________" << endl;
		cout << "" << endl;
	}
}


void ActiveProcessesReviewing::SetProcessPriorityClass(ProcessInformation *pProcessInformation, HANDLE handle, DWORD PID)
{
	DWORD priorityClass;
	priorityClass = GetPriorityClass(handle);
	if (priorityClass == 0)
	{
		cout << "!!! PID - " << PID << " Failed to get priority class" << endl;
	}
	else
	{
		pProcessInformation->SetprocessPriorityClass(priorityClass);
	}
}

void ActiveProcessesReviewing::SetProcessHandleCount(ProcessInformation *pProcessInformation, HANDLE handle, DWORD PID)
{
	DWORD handleCount;
	BOOL result;
	result = GetProcessHandleCount(handle, &handleCount);
	if (result == 0)
	{
		cout << "!!! PID - " << PID << " Failed to get hanlle count" << endl;
	}
	else
	{
		pProcessInformation->SetprocessHandleCount(handleCount);
	}
}

void ActiveProcessesReviewing::SetProcessPriorityBoost(ProcessInformation *pProcessInformation, HANDLE handle, DWORD PID)
{
	BOOL priorityBoost;
	BOOL result;
	result = GetProcessPriorityBoost(handle, &priorityBoost);
	if (result == 0)
	{
		cout << "!!! PID - " << PID << " Failed to get priority boost" << endl;
	}
	else
	{
		pProcessInformation->SetprocessPriorityBoost(priorityBoost);
	}
}

void ActiveProcessesReviewing::SetProcessTime(ProcessInformation *pProcessInformation, HANDLE handle, DWORD PID)
{
	FILETIME kernelFileTime, userFileTime, notUsed1, notUsed2;
	BOOL result;

	result = GetProcessTimes(handle, &notUsed1, &notUsed2, &kernelFileTime, &userFileTime);
	if (result == 0)
	{
		cout << "!!! PID - " << PID << " Failed to get process time" << endl;
	}
	else
	{
		ULARGE_INTEGER ulargeintKernel, ulargeintUser;
		ulargeintKernel.LowPart = kernelFileTime.dwLowDateTime;
		ulargeintKernel.HighPart = kernelFileTime.dwHighDateTime;
		ulargeintUser.LowPart = userFileTime.dwLowDateTime;
		ulargeintUser.HighPart = userFileTime.dwHighDateTime;
		unsigned __int64 uint64Kernel = ulargeintKernel.QuadPart;
		unsigned __int64 uint64User = ulargeintUser.QuadPart;
		DWORD resultingKernelTime = uint64Kernel / 10000;
		DWORD resultingUserTime = uint64User / 10000;

		pProcessInformation->SetprocessKernelTime(resultingKernelTime);
		pProcessInformation->SetprocessUserTime(resultingUserTime);
	}

}

void ActiveProcessesReviewing::CollectActiveProcessesInformation()
{
	cout << "Start collecting process information..." << endl;

	PROCESSENTRY32 processEntry;
	SecureZeroMemory(&processEntry, sizeof(processEntry));
	HANDLE currentSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (currentSnapshot == INVALID_HANDLE_VALUE)
	{
		cout << "!!! Failed to get snapshot" << endl;
		return;
	}

	processEntry.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(currentSnapshot, &processEntry))
	{
		cout << "!!! There are no structures in snapshot" << endl;
		CloseHandle(currentSnapshot);
		return;
	}

	do
	{
		ProcessInformation *pProcessInformation = new ProcessInformation();

		WCHAR *processName = new WCHAR[260];
		wcscpy(processName, processEntry.szExeFile);
		pProcessInformation->SetprocessID(processEntry.th32ProcessID);
		pProcessInformation->SetprocessName(processName);

		pProcessInformation->SetprocessThreadsNumber(processEntry.cntThreads);
		pProcessInformation->SetprocessParentID(processEntry.th32ParentProcessID);
		pProcessInformation->SetprocessbaseThreadsPriority(processEntry.pcPriClassBase);

		DWORD PID = processEntry.th32ProcessID;
		HANDLE openedProcess;
		openedProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processEntry.th32ProcessID);

		if (openedProcess == NULL)
		{
			cout << "!!! PID - " << PID << " Failed to open, system or idle or CSRSS or 64bit process" << endl;
		}
		else
		{
			SetProcessPriorityClass(pProcessInformation, openedProcess, PID);
			SetProcessHandleCount(pProcessInformation, openedProcess, PID);
			SetProcessPriorityBoost(pProcessInformation, openedProcess, PID);
			SetProcessTime(pProcessInformation, openedProcess, PID);

			CloseHandle(openedProcess);
		}

		pProcessInformationVector->push_back(pProcessInformation);
	} while (Process32Next(currentSnapshot, &processEntry)); //other case - != ERROR_NO_MORE_FILES

	CloseHandle(currentSnapshot);

	cout << "End of collection process information..." << endl;
}

void ActiveProcessesReviewing::CollectActiveProcessesModulesInformation()
{
	for (auto pProcessInformation : *pProcessInformationVector)
	{
		DWORD PID;
		PID = pProcessInformation->GetprocessID();
		MODULEENTRY32 moduleEntry;
		SecureZeroMemory(&moduleEntry, sizeof(moduleEntry));
		HANDLE currentModulesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);

		if (currentModulesSnapshot == INVALID_HANDLE_VALUE)
		{
			cout << "!!! Failed to get modules snapshot" << endl;
		}
		else
		{
			moduleEntry.dwSize = sizeof(MODULEENTRY32);
			if (!Module32First(currentModulesSnapshot, &moduleEntry))
			{
				cout << "!!! There are no structures in modules snapshot" << endl;
				CloseHandle(currentModulesSnapshot);
			}
			else
			{
				int counter = 0;
				do
				{
					counter++;
					ProcessModulesInformation *pProcessModulesInformation = new ProcessModulesInformation();

					WCHAR *moduleName = new WCHAR[260];
					wcscpy(moduleName, moduleEntry.szModule);
					pProcessModulesInformation->SetmoduleName(moduleName);
					pProcessModulesInformation->SetmoduleSize(moduleEntry.modBaseSize);
					pProcessModulesInformation->SetpModuleBaseAddress((DWORD)moduleEntry.modBaseAddr);

					pProcessInformation->SetValueToProcessModulesInformationVector(pProcessModulesInformation);
				} while ((Module32Next(currentModulesSnapshot, &moduleEntry)) && (counter < 6)); //other case - != ERROR_NO_MORE_FILES
			}

			CloseHandle(currentModulesSnapshot);
		}	
	}
}

void ActiveProcessesReviewing::CollectActiveProcessesHeapsInformation()
{
	for (auto pProcessInformation : *pProcessInformationVector)
	{
		DWORD PID;
		PID = pProcessInformation->GetprocessID();
		HEAPLIST32 heapList;
		SecureZeroMemory(&heapList, sizeof(heapList));
		HANDLE currentHeapSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, PID);

		if (currentHeapSnapshot == INVALID_HANDLE_VALUE)
		{
			cout << "!!! Failed to get heaps snapshot" << endl;
		}
		else
		{
			heapList.dwSize = sizeof(HEAPLIST32);
			if (!Heap32ListFirst(currentHeapSnapshot, &heapList))
			{
				cout << "!!! There are no structures in heaps snapshot" << endl;
				CloseHandle(currentHeapSnapshot);
			}
			else
			{
				int counterEx = 0;
				do
				{
					counterEx++;
					HEAPENTRY32 heapEntry;
					SecureZeroMemory(&heapEntry, sizeof(HEAPENTRY32));
					heapEntry.dwSize = sizeof(HEAPENTRY32);

					if (Heap32First(&heapEntry, PID, heapList.th32HeapID))
					{
						int counter = 0;
						do
						{
							counter++;
							ProcessHeapInformation *pProcessHeapInformation = new ProcessHeapInformation();
							pProcessHeapInformation->SetheapBlockSize(heapEntry.dwBlockSize);
							pProcessHeapInformation->SetheapStartAddress(heapEntry.dwAddress);
							pProcessHeapInformation->SetheapBlockFlag(heapEntry.dwFlags);

							pProcessInformation->SetValueToProcessHeapInformationVector(pProcessHeapInformation);
							heapEntry.dwSize = sizeof(HEAPENTRY32);
						} while ((Heap32Next(&heapEntry)) && (counter < 10));
					}
					else
					{
						cout << "!!! There are no blocks in this heap" << endl;
					}

					heapList.dwSize = sizeof(HEAPLIST32);
				} while ((Heap32ListNext(currentHeapSnapshot, &heapList)) && (counterEx < 10));

				CloseHandle(currentHeapSnapshot);
			}
		}
		
	}
}

void ActiveProcessesReviewing::CollectActiveProcessesMemoryInformation()
{
	for (auto pProcessInformation : *pProcessInformationVector)
	{
		DWORD PID;
		PID = pProcessInformation->GetprocessID();
		HANDLE openedProcess;
		openedProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, PID);

		if (openedProcess == NULL)
		{
			cout << "!!! PID - " << PID << " Failed to open, system or idle or CSRSS or 64bit process" << endl;
		}
		else
		{
			PROCESS_MEMORY_COUNTERS processMemoryCounters;
			BOOL resultGettingMemoryInfo;
			resultGettingMemoryInfo = GetProcessMemoryInfo(openedProcess, &processMemoryCounters, sizeof(processMemoryCounters));

			if (resultGettingMemoryInfo == 0)
			{
				cout << "!!! PID - " << PID << " Failed to get memory information" << endl;
			}
			else
			{
				ProcessMemoryInformation *pProcessMemoryInformation = new ProcessMemoryInformation();
				pProcessMemoryInformation->SetpageFaultCount(processMemoryCounters.PageFaultCount);
				pProcessMemoryInformation->SetworkingSetSize(processMemoryCounters.WorkingSetSize);
				pProcessMemoryInformation->SetpeakWorkingSetSize(processMemoryCounters.PeakWorkingSetSize);
				pProcessMemoryInformation->SetquotaPagedPoolUsage(processMemoryCounters.QuotaPagedPoolUsage);
				pProcessMemoryInformation->SetquotaPeakPagedPoolUsage(processMemoryCounters.QuotaPeakPagedPoolUsage);
				pProcessMemoryInformation->SetquotaNonPagedPoolUsage(processMemoryCounters.QuotaNonPagedPoolUsage);
				pProcessMemoryInformation->SetquotaPeakNonPagedPoolUsage(processMemoryCounters.QuotaPeakNonPagedPoolUsage);
				pProcessMemoryInformation->SetpagefileUsage(processMemoryCounters.PagefileUsage);
				pProcessMemoryInformation->SetpeakPagefileUsage(processMemoryCounters.PeakPagefileUsage);

				BOOL resultGettingWorkingSet;
				DWORD workingSetBufferSize = 131072;
				DWORD *workingSetBuffer = new DWORD[workingSetBufferSize];
				PSAPI_WORKING_SET_INFORMATION  *pWorkingSetBuffer;
				resultGettingWorkingSet = QueryWorkingSet(openedProcess, workingSetBuffer, workingSetBufferSize);
				if (resultGettingWorkingSet == 0)
				{
					DWORD lastError = GetLastError();
					if (lastError == ERROR_BAD_LENGTH)
					{
						cout << "!!! PID - " << PID << " Failed to get working set, not enough memory was allocated" << endl;
					}
					else
					{
						cout << "!!! PID - " << PID << " Failed to get working set, undefined problem occured" << endl;
					}
				}
				else
				{
					pWorkingSetBuffer = reinterpret_cast<PSAPI_WORKING_SET_INFORMATION*>(workingSetBuffer);
					ULONG_PTR blocksNumber = pWorkingSetBuffer->NumberOfEntries;
					blocksNumber /= 10;
					for (ULONG_PTR i = 0; i < blocksNumber; i++)
					{
						ProcessMemoryInformation::PageInformation *pPageInformation = new ProcessMemoryInformation::PageInformation();
						pPageInformation->pageProtection = pWorkingSetBuffer->WorkingSetInfo[i].Protection;
						pPageInformation->pageShareCount = pWorkingSetBuffer->WorkingSetInfo[i].ShareCount;
						pPageInformation->pageShared = pWorkingSetBuffer->WorkingSetInfo[i].Shared;

						pProcessMemoryInformation->SetValueToPageInformationVector(pPageInformation);
					}
				}
				delete [] workingSetBuffer;

				pProcessInformation->SetpProcessMemoryInformation(pProcessMemoryInformation);
			}

			CloseHandle(openedProcess);
		}
	}
}

void ActiveProcessesReviewing::SetThreadTime(ProcessThreadsInformation *pProcessThreadsInformation, HANDLE handle, DWORD TID)
{
	FILETIME kernelFileTime, userFileTime, notUsed1, notUsed2;
	BOOL result;

	result = GetThreadTimes(handle, &notUsed1, &notUsed2, &kernelFileTime, &userFileTime);
	if (result == 0)
	{
		cout << "!!! TID - " << TID << " Failed to get thread time" << endl;
	}
	else
	{
		ULARGE_INTEGER ulargeintKernel, ulargeintUser;
		ulargeintKernel.LowPart = kernelFileTime.dwLowDateTime;
		ulargeintKernel.HighPart = kernelFileTime.dwHighDateTime;
		ulargeintUser.LowPart = userFileTime.dwLowDateTime;
		ulargeintUser.HighPart = userFileTime.dwHighDateTime;
		unsigned __int64 uint64Kernel = ulargeintKernel.QuadPart;
		unsigned __int64 uint64User = ulargeintUser.QuadPart;
		DWORD resultingKernelTime = uint64Kernel / 10000;
		DWORD resultingUserTime = uint64User / 10000;

		pProcessThreadsInformation->SetthreadKernelTime(resultingKernelTime);
		pProcessThreadsInformation->SetthreadUserTime(resultingUserTime);
	}
}

void ActiveProcessesReviewing::SetThreadInfoUsingNTDLL(ProcessThreadsInformation *pProcessThreadsInformation, HANDLE handle, DWORD TID, pFunc NtQueryInformationThread)
{
	__kernel_entry NTSTATUS queryIOPendingStatus, queryStartAddressStatus;
	ULONG pendingIOOperations, returnedSize;
	queryIOPendingStatus = NtQueryInformationThread(handle, ThreadIsIoPending, &pendingIOOperations, sizeof(ULONG), &returnedSize);

	if (queryIOPendingStatus != 0x00000000)
	{
		cout << "!!! TID - " << TID << " Failed to get thread pending IO operations" << endl;
	}
	else
	{
		pProcessThreadsInformation->SetthreadIOPending(pendingIOOperations);
	}

	DWORD startAddress;
	queryStartAddressStatus = NtQueryInformationThread(handle, 0x09, &startAddress, sizeof(DWORD), &returnedSize);

	if (queryStartAddressStatus != 0x00000000)
	{
		cout << "!!! TID - " << TID << " Failed to get thread start address" << endl;
	}
	else
	{
		pProcessThreadsInformation->SetthreadStartAddress(startAddress);
	}
}

void ActiveProcessesReviewing::AddThreadInformationToProcessInformation(ProcessThreadsInformation *pProcessThreadsInformation, int k, int vectorSize, DWORD TID, DWORD ownerProcessID)
{
	while ((k < vectorSize) && (pProcessInformationVector->at(k)->GetprocessID() != ownerProcessID))
	{
		k++;
	}
	if (k == vectorSize)
	{
		cout << "!!! TID - " << TID << " was not found among processes" << endl;
	}
	else
	{
		pProcessInformationVector->at(k)->SetValueToProcessThreadsInformationVector(pProcessThreadsInformation);
	}
}

void ActiveProcessesReviewing::CollectActiveProcessesThreadsInformation()
{
	THREADENTRY32 threadEntry;
	SecureZeroMemory(&threadEntry, sizeof(threadEntry));
	HANDLE currentThreadsSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

	if (currentThreadsSnapshot == INVALID_HANDLE_VALUE)
	{
		cout << "!!! Failed to get threads snapshot" << endl;
		return;
	}

	threadEntry.dwSize = sizeof(THREADENTRY32);
	if (!Thread32First(currentThreadsSnapshot, &threadEntry))
	{
		cout << "!!! There are no structures in threads snapshot" << endl;
		CloseHandle(currentThreadsSnapshot);
		return;
	}

	bool retrievingAddressFromNTDLL;
	pFunc NtQueryInformationThread = (pFunc)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationThread");
	if (NtQueryInformationThread == NULL)
	{
		cout << "!!! Failed to get NtQueryInformationThread" << endl;
		retrievingAddressFromNTDLL = false;
	}
	else
	{
		retrievingAddressFromNTDLL = true;
	}

	int k = 0;
	int vectorSize = pProcessInformationVector->size();

	do
	{
		ProcessThreadsInformation *pProcessThreadsInformation = new  ProcessThreadsInformation();
		pProcessThreadsInformation->SetthreadID(threadEntry.th32ThreadID);
		pProcessThreadsInformation->SetthreadBasePriority(threadEntry.tpBasePri);

		DWORD TID = threadEntry.th32ThreadID;
		DWORD ownerProcessID = threadEntry.th32OwnerProcessID;
		HANDLE openedThread;
		openedThread = OpenThread(THREAD_QUERY_INFORMATION | THREAD_QUERY_LIMITED_INFORMATION, FALSE, TID);

		if (openedThread == NULL)
		{
			cout << "!!! TID - " << TID << " was not opened" << endl;
		}
		else
		{
			SetThreadTime(pProcessThreadsInformation, openedThread, TID);
			if (retrievingAddressFromNTDLL)
			{
				SetThreadInfoUsingNTDLL(pProcessThreadsInformation, openedThread, TID, NtQueryInformationThread);
			}

			CloseHandle(openedThread);
		}

		AddThreadInformationToProcessInformation(pProcessThreadsInformation, 0, vectorSize, TID, ownerProcessID);
	} while (Thread32Next(currentThreadsSnapshot, &threadEntry)); //other case - != ERROR_NO_MORE_FILES

	CloseHandle(currentThreadsSnapshot);

}

bool KillProcess(DWORD PID)
{
	HANDLE openedProcess;
	openedProcess = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, FALSE, PID);

	if (openedProcess == NULL)
	{
		cout << "!!! Cannot kill this process" << endl;
		return false;
	}
	else
	{
		BOOL terminateResult;
		terminateResult = TerminateProcess(openedProcess, 777);
		if (terminateResult == 0)
		{
			CloseHandle(openedProcess);
			return false;
		}
		else
		{
			DWORD result = WaitForSingleObject(openedProcess, INFINITE);
			CloseHandle(openedProcess);
			if (result == WAIT_OBJECT_0)
			{
				return true;
			}
			else
			{
				return false;
			}
			
		}
	}
}

bool CheckIfPIDExists(DWORD PID, ActiveProcessesReviewing *activeProcessesReviewing)
{
	int counter = 0;
	int vectorSize = activeProcessesReviewing->pProcessInformationVector->size();
	while ((counter < vectorSize) && (activeProcessesReviewing->pProcessInformationVector->at(counter)->GetprocessID() != PID))
	{
		counter++;
	}

	if (counter == vectorSize)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void PrintManualInformation()
{
	cout << "Manual for course project working set:" << endl;
	cout << "info - to get information about all active processes" << endl;
	cout << "clear - to clear output window" << endl;
	cout << "exit - to exit programm" << endl;
	cout << "leave - to free memory after processes research" << endl;
	cout << "heap -  to get information about heap blocks of selected process" << endl;
	cout << "mem - to get information about memory of selected process" << endl;
	cout << "mod - to get information about modules of selected process" << endl;
	cout << "thrd - to get information about threads of selected process" << endl;
	cout << "kill - to terminate selected process" << endl << endl;

	cout << "What do you want?" << endl;
}

void main()
{
	PrintManualInformation();
	string consoleRequestedString = "";
	cin >> consoleRequestedString;

	while (consoleRequestedString != "exit")
	{
		if (consoleRequestedString == "info")
		{
			ActiveProcessesReviewing *activeProcessesReviewing = new ActiveProcessesReviewing();
			activeProcessesReviewing->CollectActiveProcessesInformation();
			activeProcessesReviewing->CollectActiveProcessesHeapsInformation();
			activeProcessesReviewing->CollectActiveProcessesModulesInformation();
			activeProcessesReviewing->CollectActiveProcessesThreadsInformation();
			activeProcessesReviewing->CollectActiveProcessesMemoryInformation();
			
			activeProcessesReviewing->WriteActiveProcessesInformation();

			cout << "Enter process information type or 'leave'..." << endl;
			string informationRequestedString = "";
			cin >> informationRequestedString;
			
			while (informationRequestedString != "leave")
			{
				cout << "Enter process ID..." << endl;
				int processID;
				cin >> processID;

				bool result = CheckIfPIDExists(processID, activeProcessesReviewing);
				if (result)
				{
					if (informationRequestedString == "heap")
					{
						activeProcessesReviewing->WriteActiveProcessesHeapInformation(processID);
					}
					else if (informationRequestedString == "mem")
					{
						activeProcessesReviewing->WriteActiveProcessesMemoryInformation(processID);
					}
					else if (informationRequestedString == "mod")
					{
						activeProcessesReviewing->WriteActiveProcessesModulesInformation(processID);
					}
					else if (informationRequestedString == "thrd")
					{
						activeProcessesReviewing->WriteActiveProcessesThreadsInformation(processID);
					}
					else if (informationRequestedString == "kill")
					{
						bool result = KillProcess(processID);
						if (result)
						{
							cout << "Process was successfully terminated" << endl;
						}
						else 
						{
							cout << "!!! Failed terminating this process" << endl;
						}
					}
					else
					{
						cout << "!!! Undefined operation" << endl;
					}
				}
				else
				{
					cout << "!!! This process does not exist" << endl;
				}
				

				cout << "Enter process information type or 'leave'..." << endl;
				cin >> informationRequestedString;
			}

			activeProcessesReviewing->ClearMemoryOccupiedByProcessesInformation();
			delete activeProcessesReviewing;
		}
		else if (consoleRequestedString == "clear")
		{
			system("cls");
		}
		else
		{
			cout << "!!! Bad request" << endl;
		}

		cout << "What do you want?" << endl;
		cin >> consoleRequestedString;
	}
}

