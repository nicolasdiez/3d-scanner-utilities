//Author: Nicolas Diez
//Desciption: This file contains all the methods needed to set active the windows' high performance power plan 
//and some other power settings such as turn off wifi connectivity, turn off BT, turn off monitor sleeping state 
//and turn off fixed hard drives if needed.


// system header
#include <windows.h>
//#include <math.h>
//#include <stdio.h>
#include <iostream>
#include <wlanapi.h>
#include <string>

// power management headers
#include <powrprof.h>
#pragma comment(lib, "powrprof.lib")

// main header
#include "PowerPlan.h"
//#include "WifiHandler.h"   commented by Nico check

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

#include <tchar.h>
#include <stdio.h>

void PowerPlan:: SaveCurrentPowerScheme()
{
	DWORD			displayBufferSize = sizeof(displayBuffer);

	PowerGetActiveScheme(NULL,&pp_power_plan);
	PowerReadFriendlyName(NULL,pp_power_plan,&NO_SUBGROUP_GUID,NULL,displayBuffer,&displayBufferSize);
	wprintf(L"Saving Current Power Plan: %s\n", (wchar_t*)displayBuffer);
}


GUID PowerPlan:: GetCurrentPowerScheme()
{
	DWORD	displayBufferSize = sizeof(displayBuffer);

	PowerGetActiveScheme(NULL,&pp_power_plan);
	PowerReadFriendlyName(NULL,pp_power_plan,&NO_SUBGROUP_GUID,NULL,displayBuffer,&displayBufferSize);
	wprintf(L"Current Power Plan: %s\n", (wchar_t*)displayBuffer);
	return (*pp_power_plan);
	
}

void PowerPlan:: SetHighPerformancePowerScheme()
{	
	//Set active high performance power plan
	PowerSetActiveScheme(0, &GUID_MIN_POWER_SAVINGS);
	std::cout << "** Setting Active High Performance Power Plan **\n";
}

void PowerPlan:: SetPowerScheme(GUID *plan)
{	
	DWORD	displayBufferSize = sizeof(displayBuffer);

	//Set power plan
	PowerSetActiveScheme(0, plan);
	PowerReadFriendlyName(NULL, plan, &NO_SUBGROUP_GUID, NULL, displayBuffer, &displayBufferSize);
	wprintf(L"Setting Power Plan: %s\n", (wchar_t*)displayBuffer);
}

void Memory:: FreeGlobalMemoryStatus()
{	
	statex.dwLength	= sizeof (statex);
	GlobalMemoryStatusEx (&statex);
	
	_tprintf (TEXT("There is  %*ld percent of memory in use.\n"), WIDTH, statex.dwMemoryLoad);
	_tprintf (TEXT("There are %*I64d total KB of physical memory.\n"),WIDTH, statex.ullTotalPhys/DIV);
  	_tprintf (TEXT("There are %*I64d free  KB of physical memory.\n"), WIDTH, statex.ullAvailPhys/DIV);
	_tprintf (TEXT("There are %*I64d total KB of paging file.\n"), WIDTH, statex.ullTotalPageFile/DIV);
	_tprintf (TEXT("There are %*I64d free  KB of paging file.\n"), WIDTH, statex.ullAvailPageFile/DIV);
	_tprintf (TEXT("There are %*I64d total KB of virtual memory.\n"), WIDTH, statex.ullTotalVirtual/DIV);
	_tprintf (TEXT("There are %*I64d free  KB of virtual memory.\n"), WIDTH, statex.ullAvailVirtual/DIV);
	//_tprintf (TEXT("There are %*I64d free  KB of extended memory.\n"), WIDTH, statex.ullAvailExtendedVirtual/DIV);		
	//The parameter ullAvailExtendedVirtual is reserved and always 0
}

void Memory:: WarnNotEnoughFreeMemory()
{	

	
	int		MinRAMneeded			= 2800;													//Mininum RAM needed in MB
	float	FreeRAMpercen			= statex.ullAvailPhys * 100 / statex.ullTotalPhys;		//Free RAM in percentage
	float	FreeRAMabsolute			= statex.ullAvailPhys/DIV/DIV;							//Free RAM absolute in MB

	if (FreeRAMabsolute < MinRAMneeded)
	{
		wprintf(L"ERROR: Not Enough RAM Memory Available (Needed: %i MB  Available: %.0f MB)\n", MinRAMneeded, FreeRAMabsolute);
	}


}