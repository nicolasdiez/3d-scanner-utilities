//Nicolas Diez
//Script which sets active the windows' high performance power plan and some other settings such as turn off
//wifi connectivity, turn off BT, turn off monitor sleeping state and turn off fixed hard drives if needed.

#include <windows.h>
//#include <test.h>
#include <powrprof.h>
#include <iostream>
#include "stdio.h"
#include <ntstatus.h>
#include <string>
#pragma comment(lib, "powrprof.lib")

using namespace std;


int main(int argc, char **argv) {
/*
	//Variables
	//UINT pp=0;
	//GUID pp=0;
	//LONG status;
	//unsigned int ps;

	 POWER_POLICY pp_former;
	 PUCHAR Buffer;
	 LPDWORD BufferSize;
	 unsigned int ps;
	 POWER_POLICY pp;
	
	//Get the pointer address to the active power scheme
   GetActivePwrScheme(&ps);
   //PowerGetActiveScheme(NULL,&pp);

   //Load the attributes of the active power scheme
   ReadPwrScheme(ps, &pp);

   	//Save the user's current power plan
	pp_former = pp;

	// Set monitor sleeping timer greater than 50min (time to scan one full tile)
	pp.user.VideoTimeoutAc = 3060; //when PC running on AC
	pp.user.VideoTimeoutDc = 3060; //when PC running on batteries
	
	//Turn off power to fixed hard drives (activate when using SSD or external HD)
	//pp.user.SpindownTimeoutAc = 1;
	//pp.user.SpindownTimeoutDc = 1;

	//Write the new settings into the current power plan
	SetActivePwrScheme(ps, 0, &pp);
		
	cout << "Value of the Active Pwr Scheme Pointer:\n";
	cout << &pp;
	std::cin.get(); //pause

	//SetSuspendState(FALSE,FALSE,FALSE);
*/


	//////////////////////   Global Power Policy  ///////////////////
	/*
	//Variables
	PGLOBAL_POWER_POLICY pGlobalPowerPolicy;

	//Read the global power policy
	ReadGlobalPwrPolicy(pGlobalPowerPolicy);
	
	//Change parameters of the global power policy
	pGlobalPowerPolicy.user.DischargePolicy

	//Write back the new global power policy
	WriteGlobalPwrPolicy(pGlobalPowerPolicy);
	*/

	//////////////////////  TURN OFF WiFi   //////////////////////////////////
	/*
	//Variables
	HANDLE hClientHandle;
	PVOID pReserved;
	PWLAN_INTERFACE_INFO_LIST *ppInterfaceList;

	DWORD dwClientVersion=1;
	PDWORD pdwNegotiatedVersion;
	PHANDLE phClientHandle; //ID to be used within wifi handling functions set
	
	//Establish connection to the Wifi server
	WlanOpenHandle(dwClientVersion,NULL,pdwNegotiatedVersion,phClientHandle);

	/*
	WlanEnumInterfaces(
  _In_        HANDLE hClientHandle,
  _Reserved_  PVOID pReserved,
  _Out_       PWLAN_INTERFACE_INFO_LIST *ppInterfaceList
);

	WlanSetInterface(
  _In_        HANDLE hClientHandle,
  _In_        const GUID *pInterfaceGuid,
  _In_        WLAN_INTF_OPCODE OpCode,
  _In_        DWORD dwDataSize,
  _In_        const PVOID pData,
  _Reserved_  PVOID pReserved
);
	*/

	//////////////////////////////////  DISPLAY MESSAGE BOX  //////////////////
	
	//MessageBox(0, "WiFi Off \nMonitor Sleep Off \nFixed Hard Drives Off \nBluetooth Off","Power Plan Changed         ", MB_OK);
	

	//////////////////  SET ACTIVE HIGH PERFORMANCE PLAN  ///////////////////
	PowerSetActiveScheme(0, &GUID_MIN_POWER_SAVINGS);

	/*
	//High Performance GUID
	GUID HighPerfID;
	HighPerfID.Data1 = 2355003354;
	HighPerfID.Data2 = 59583;
	HighPerfID.Data3 = 19094;
	//HighPerfID.Data4 = "š…¦â:Œc\««««««««"; 
		
	//Variables
	UCHAR displayBuffer[64] = " ";
	DWORD displayBufferSize = sizeof(displayBuffer);
	GUID buffer;
	DWORD bufferSize = sizeof(buffer);

	//Get the current GUID power scheme and its friendly name
	GUID *scheme = 0;
	PowerGetActiveScheme( NULL, &scheme);
	PowerReadFriendlyName(NULL,scheme,&NO_SUBGROUP_GUID,NULL,displayBuffer,&displayBufferSize);

	//Go through the machine's power plans and activate the high performance one
	for(int index = 0; ; index++)
	{

		if (ERROR_SUCCESS == PowerEnumerate(NULL,NULL,&GUID_VIDEO_SUBGROUP,ACCESS_SCHEME,index,(UCHAR*)&buffer,&bufferSize) )
		{
			if (ERROR_SUCCESS == PowerReadFriendlyName(NULL,&buffer,&NO_SUBGROUP_GUID,NULL,displayBuffer,&displayBufferSize) )
			{
				wprintf(L"%s\n", (wchar_t*)displayBuffer);

				//if (buffer.Data2 == 59583) //Value of the Data2 GUID identifier of the high perf. plan
				if( 0 == wcscmp ( (wchar_t*)displayBuffer, L"High Performance" ) )
				{
					cout << "High Performance Plan Found!\n";
					if (ERROR_SUCCESS == PowerSetActiveScheme(NULL,&buffer) )
					{
						cout << "* Setting Active High Performance Power Plan *";
						//std::cin.get(); //pause
						break;
					}					
				}
				else 
				{
					DWORD LastError = GetLastError();
				}
			}
			
		}
		else break;
	}
	*/
	//DWORD PowerSettings;
	//PowerSettings = PowerReadSettingAttributes(&GUID_VIDEO_SUBGROUP,&buffer);

//UCHAR displayBuffer[]
//string str1 = displayBuffer;
//string str2 ("Balanced");
//Compare(str2,displayBuffer);

//if (str1.compare(str2) == 0){
//	cout << "Ok";
//std::cin.get(); //pause
//}
/*
if(ERROR_SUCCESS == PowerGetActiveScheme( NULL, &scheme))
	{
		GUID buffer;
		DWORD bufferSize = sizeof(buffer);
 
		for(int index = 0; ; index++)
		{
			if(ERROR_SUCCESS == PowerEnumerate(NULL,scheme,&GUID_VIDEO_SUBGROUP,ACCESS_INDIVIDUAL_SETTING,index,(UCHAR*)&buffer,&bufferSize))
			{
				UCHAR displayBuffer[1024];
				DWORD displayBufferSize = sizeof(displayBuffer);
				ULONG type = REG_DWORD;
 
				if(ERROR_SUCCESS == PowerReadFriendlyName(NULL,scheme,&NO_SUBGROUP_GUID,NULL,displayBuffer,&displayBufferSize))
				{

					wprintf(L"%s\n", (wchar_t*)displayBuffer);
					std::cin.get(); //pause
					if( 0 == wcscmp ( (wchar_t*)displayBuffer, L"Turn off display after" ) )
					{
                                           
                                         // HERE I SHOULD SET THE VALUE
                                         // FOR DISPLAY TIMEOUT 
					}
				}
                                else 
				{
					//error = GetLastError();
				}
			}
			else break;


		}

	}

*/
	return 0;
}
