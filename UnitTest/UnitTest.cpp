#include "pch.h"
#include "CppUnitTest.h"
#include "../ActiveProcessesReviewing/ActiveProcessesReviewing.h"
#include "../ActiveProcessesReviewing/ProcessInformation.h"
#include "../ActiveProcessesReviewing/ProcessThreadsInformation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		ActiveProcessesReviewing *activeProcessesReviewing;

		TEST_METHOD_INITIALIZE(SetMethod)
		{
			activeProcessesReviewing = new ActiveProcessesReviewing();
		}

		TEST_METHOD_CLEANUP(CleanMethod)
		{
			activeProcessesReviewing->ClearMemoryOccupiedByProcessesInformation();
			delete activeProcessesReviewing;
		}

		TEST_METHOD(TestProcessInformationVector)
		{
			activeProcessesReviewing->CollectActiveProcessesInformation();

			Assert::IsNotNull(activeProcessesReviewing->pProcessInformationVector->at(0));
		}

		TEST_METHOD(TestThreadInformationInProcessInformationVector)
		{
			activeProcessesReviewing->CollectActiveProcessesInformation();
			activeProcessesReviewing->CollectActiveProcessesThreadsInformation();

			Assert::IsNotNull(activeProcessesReviewing->pProcessInformationVector->at(20)->GetpProcessThreadsInformationVector()->at(0));
		}

		TEST_METHOD(TestFindProcessInformationWithCorrespondingID)
		{
			activeProcessesReviewing->CollectActiveProcessesInformation();
			int processInformationNumberInVector = 17;
			DWORD PIDUnderAssignedValue = activeProcessesReviewing->pProcessInformationVector->at(processInformationNumberInVector)->GetprocessID();

			Assert::AreEqual(processInformationNumberInVector, activeProcessesReviewing->FindProcessInformationWithCorrespondingID(PIDUnderAssignedValue));
		}
	};
}
