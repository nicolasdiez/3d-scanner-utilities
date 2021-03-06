//Author: Nicolas Diez
//Script which sets active the windows' high performance power plan and some other settings such as turn off
//wifi connectivity, turn off BT, turn off monitor sleeping state and turn off fixed hard drives if needed.

//#include <test.h>
//#include <powrprof.h>
//#include <iostream>
//#include "stdio.h"
//#include <ntstatus.h>
//#include <string>
//#pragma comment(lib, "powrprof.lib")
//#include <shellapi.h>
//#include <wlanapi.h>
//#include <objbase.h>
//#include <wtypes.h>

//#include <stdio.h>
//#include <stdlib.h>

//using namespace std;


// system header
#include <windows.h>
//#include <math.h>
//#include <stdio.h>
#include <iostream>
#include <wlanapi.h>
#include <string>

// for COM port detection
#include <vector>
#include <string.h>
#include <wchar.h>
#include <tchar.h>
#ifdef _UNICODE
  #define tstring std::wstring
#else
  #define tstring std::string
#endif 

#include <stdio.h>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include<algorithm> //to sort strings

// power management headers
#include <powrprof.h>
#pragma comment(lib, "powrprof.lib")

// main header
#include "PowerPlan.h"
#include "WifiHandler.h"
#include "COMDetect.h"

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

//No tienen mucho sentido las funciones de la clase PowerPlan, tengo que limpiarlas.

//Main funciona con PowerPlan y WifiHandler
int main(int argc, char **argv)
{
	PowerPlan plan;
	WifiHandler wifi;
	COMDetect ArduinoCOM;
	Memory MemoryStatus;

	//Get the user´s active power plan
	GUID current_plan = plan.GetCurrentPowerScheme();

	//Set Active the high performance power plan
	plan.SetHighPerformancePowerScheme();
	
	//Set back the user´s power plan
	plan.SetPowerScheme(&current_plan);
	
	/*
	//Switch Off Wifi adapter
	wifi.SwitchOffWifiAdapter();
	system("pause");

	//Switch On Wifi adapter
	wifi.SwitchOnWifiAdapter();
	system("pause");
	*/

	//Detect COM Ports being used
	std::vector< tstring > ports;
	ArduinoCOM.DetectComPorts(ports);
	for(std::vector< tstring >::const_iterator it = ports.begin(); it != ports.end(); ++it)
	{
		std::cout << " -> COM ports being used: "<< *it << std::endl;
	} 

	//Detect COM Arduino Ports and print info 
	ArduinoCOM.GetArduinoCOMPorts();
	printf(" -> Arduino Board/s connected to port/s:");
	for (size_t it = 0 ; it < ArduinoCOM.DetectedCOM->length() ; ++it)
	{
		printf(" [COM %c]", ArduinoCOM.DetectedCOM->at(it));
	}	

	//Show free memoery status
	//MemoryStatus.FreeGlobalMemoryStatus();
	//MemoryStatus.WarnNotEnoughFreeMemory();
	//system("pause");

	//Display message box	
	//MessageBox(0, "WiFi Off \nMonitor Sleep Off \nFixed Hard Drives Off \nBluetooth Off","Power Plan Changed         ", MB_OK);

	return 0;

}



int main_2(int argc, char **argv) {
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
	
	//Variables
	//HANDLE hClientHandle;
	//PVOID pReserved;
	PWLAN_INTERFACE_INFO_LIST ppInterfaceList;

	DWORD dwClientVersion=1;
	PDWORD pdwNegotiatedVersion;	
	PHANDLE phClientHandle;	 //ID to be used within wifi handling functions set

	//PWLAN_INTERFACE_INFO_LIST ppInterfaceList;
	
	//Establish connection to the Wifi server
	HANDLE hClient = NULL;
    DWORD dwMaxClient = 2;      //    
    DWORD dwCurVersion = 0;
	DWORD dwResult = 0;

	//WlanOpenHandle(dwClientVersion,NULL,pdwNegotiatedVersion,phClientHandle);

	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
    if (dwResult != ERROR_SUCCESS) {
        wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
		//FormatMessage(dwResult);
        return 1;
        // You can use FormatMessage here to find out why the function failed
    }


	WlanEnumInterfaces(hClient,NULL,&ppInterfaceList);

	//DWORD WINAPI WlanDisconnect(phClientHandle, _In_        const GUID *pInterfaceGuid,NULL);

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
	//Display message box	
	//MessageBox(0, "WiFi Off \nMonitor Sleep Off \nFixed Hard Drives Off \nBluetooth Off","Power Plan Changed         ", MB_OK);
	
/*
	UCHAR displayBuffer[64] = " ";
	DWORD displayBufferSize = sizeof(displayBuffer);
	GUID *pp_former;
	GUID *pp_aux;

	//Save current active power plan
	PowerGetActiveScheme(NULL,&pp_former);
	PowerReadFriendlyName(NULL,pp_former,&NO_SUBGROUP_GUID,NULL,displayBuffer,&displayBufferSize);
	wprintf(L"Current Power Plan: %s\n", (wchar_t*)displayBuffer);

	//Set active high performance power plan
	PowerSetActiveScheme(0, &GUID_MIN_POWER_SAVINGS);
	std::cout << "** Setting Active High Performance Power Plan **\n";


	//Set active former power plan
	PowerSetActiveScheme(0, pp_former);
	PowerGetActiveScheme(NULL,&pp_aux);
	PowerReadFriendlyName(NULL,pp_aux,&NO_SUBGROUP_GUID,NULL,displayBuffer,&displayBufferSize);
	wprintf(L"Setting Active Former Power Plan: %s\n", (wchar_t*)displayBuffer);
*/
	return 0;
}

int main_3(int argc, char **argv)
{
		 
	
	/*-----------------------------------------------------------------------------

		HDEVINFO hDevInfo;
       SP_DEVINFO_DATA DeviceInfoData;
       DWORD i;

       // Create a HDEVINFO with all present devices.
       hDevInfo = SetupDiGetClassDevs(NULL,
           0, // Enumerator
           0,
           DIGCF_PRESENT | DIGCF_ALLCLASSES );
       
       if (hDevInfo == INVALID_HANDLE_VALUE)
       {
           // Insert error handling here.
           return 1;
       }
       
       // Enumerate through all devices in Set.
       
       DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
       for (i=0;SetupDiEnumDeviceInfo(hDevInfo,i,&DeviceInfoData);i++)
       {
           DWORD DataT;
           LPTSTR buffer = NULL;
           DWORD buffersize = 0;
           
           //
           // Call function with null to begin with, 
           // then use the returned buffer size (doubled)
           // to Alloc the buffer. Keep calling until
           // success or an unknown failure.
           //
           //  Double the returned buffersize to correct
           //  for underlying legacy CM functions that 
           //  return an incorrect buffersize value on 
           //  DBCS/MBCS systems.
           // 
           while (!SetupDiGetDeviceRegistryProperty(
               hDevInfo,
               &DeviceInfoData,
               SPDRP_DEVICEDESC,
               &DataT,
               (PBYTE)buffer,
               buffersize,
               &buffersize))
           {
               if (GetLastError() == 
                   ERROR_INSUFFICIENT_BUFFER)
               {
                   // Change the buffer size.
                   if (buffer) LocalFree(buffer);
                   // Double the size to avoid problems on 
                   // W2k MBCS systems per KB 888609. 
				   int a = 0;
                   buffer = LocalAlloc(LPTR,buffersize * 2);
               }
               else
               {
                   // Insert error handling here.
                   break;
               }
           }
           
           printf("Result:[%s]\n",buffer);
           
           if (buffer) LocalFree(buffer);
       }
       
       
       if ( GetLastError()!=NO_ERROR &&
            GetLastError()!=ERROR_NO_MORE_ITEMS )
       {
           // Insert error handling here.
           return 1;
       }
       
       //  Cleanup
       SetupDiDestroyDeviceInfoList(hDevInfo);
	   //-----------------------------------------------------------------------------
	   */

	/*
	//-----------------------------------------------------------------------------
	GUID guid = GUID_DEVCLASS_PORTS;
	uint nDevice = 0;

	SP_DEVICE_INTERFACE_DATA interfaceData;
	ZeroMemory(&interfaceData, sizeof(interfaceData));
	interfaceData.cbSize = sizeof(interfaceData);

	SP_DEVINFO_DATA devInfoData;
	ZeroMemory(&devInfoData, sizeof(devInfoData));
	devInfoData.cbSize = sizeof(devInfoData);

	if(SetupDiEnumDeviceInfo(hDeviceInfo , nDevice,&devInfoData))
	{
		DWORD regDataType;

		BYTE hardwareId[300];
		if(SetupDiGetDeviceRegistryProperty(hDeviceInfo, &devInfoData, SPDRP_HARDWAREID, &regDataType, hardwareId, sizeof(hardwareId), NULL))
		{}
	}
	//-----------------------------------------------------------------------------
	*/
       return 0;


}