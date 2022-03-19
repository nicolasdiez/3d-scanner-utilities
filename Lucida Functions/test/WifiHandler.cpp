//Author: Nicolas Diez
//Description: This file contains all the methods needed to enable and disable the WiFi network interfaces from a Windows computer.

// system header
#include <windows.h>
//#include <math.h>
//#include <stdio.h>
#include <iostream>
#include <wlanapi.h>
#include <string>

//Networking
#include <iphlpapi.h>
//#include <ws2tcpip.h>
//#include <winsock2.h>
//#include "stdafx.h"
//#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "iphlpapi.lib")

// power management headers
#include <powrprof.h>
#pragma comment(lib, "powrprof.lib")

// main header
#include "WifiHandler.h"

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")



void WifiHandler:: SwitchOffWifiAdapter()
{

    dwMaxClient = 2;		//The highest version of the WLAN API that the client supports.(2 for Vista and on)
	dwResult = 0;			//Error message handler
	hClient = NULL;			//Handler ID for the session

	//Display output
	wprintf(L"Switching OFF the Wifi Adapter\n");

	//Open a network session to get the handler
	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
    if (dwResult != ERROR_SUCCESS) 
		{
			//HandleLastError(dwResult);
			wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
			return;
		}
	
	//Get all the interfaces
	dwResult = WlanEnumInterfaces(hClient,NULL,&ppInterfaceList);
	if (dwResult != ERROR_SUCCESS)
		{
			wprintf(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
			return;
		}

	//Loop to Dissable all capabilities of all the WiFi interfaces
	for (int i=0; i < ppInterfaceList->dwNumberOfItems ; i++)
	{
		//Get capabilities of the interface
		dwResult = WlanGetInterfaceCapability( hClient, &ppInterfaceList->InterfaceInfo[i].InterfaceGuid , NULL, &ppCapability);
		if (dwResult != ERROR_SUCCESS)
			{
				wprintf(L"WlanGetInterfaceCapability failed with error: %u\n", dwResult);
				return;
			}
				//Dissable all the capabilities of the interface	
				for (int j=0; j < ppCapability->dwNumberOfSupportedPhys ; j++)
				{
					//Set the parameters to Handle the radio adapter
					RadioStruct.dwPhyIndex = j;									//Dissable the capability with index j
					RadioStruct.dot11SoftwareRadioState = dot11_radio_state_off;	//Set the software state for the capability OFF
					RadioStruct.dot11HardwareRadioState = dot11_radio_state_off;	//Set the hardware state for the capability OFF
				
					const PVOID pData = &RadioStruct;
					DWORD dwDataSize = sizeof(RadioStruct);
					
					//Set the parameters to the interface
					dwResult = WlanSetInterface( hClient, &ppInterfaceList->InterfaceInfo[i].InterfaceGuid, wlan_intf_opcode_radio_state, dwDataSize, pData, NULL);
					if (dwResult != ERROR_SUCCESS)
						{
							wprintf(L"WlanSetInterface failed with error: %u\n", dwResult);
							return;
						}
				}
		}

	//Close the network session
	dwResult = WlanCloseHandle( hClient , NULL);
	if (dwResult != ERROR_SUCCESS)
		{
			wprintf(L"WlanCloseHandle failed with error: %u\n", dwResult);
			return;
		}
}




void WifiHandler::SwitchOnWifiAdapter()
{

    dwMaxClient = 2;		//The highest version of the WLAN API that the client supports.(2 for Vista and on)
	dwResult = 0;			//Error message handler
	hClient = NULL;			//Handler ID for the session

	//Display info
	wprintf(L"Switching ON the Wifi Adapter\n");

	//Open a network session to get the handler
	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
    if (dwResult != ERROR_SUCCESS) 
		{
			wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
			return;
		}
	
	//Get all the interfaces
	dwResult = WlanEnumInterfaces(hClient,NULL,&ppInterfaceList);
	if (dwResult != ERROR_SUCCESS)
		{
			wprintf(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
			return;
		}

	//Loop to Enable all capabilities of all the WiFi interfaces
	for (int i=0; i < ppInterfaceList->dwNumberOfItems ; i++)
	{
		//Get capabilities of the interface
		dwResult = WlanGetInterfaceCapability( hClient, &ppInterfaceList->InterfaceInfo[i].InterfaceGuid , NULL, &ppCapability);
		if (dwResult != ERROR_SUCCESS)
			{
				wprintf(L"WlanGetInterfaceCapability failed with error: %u\n", dwResult);
				return;
			}
				//Dissable all the capabilities of the interface	
				for (int j=0; j < ppCapability->dwNumberOfSupportedPhys ; j++)
				{
					//Set the parameters to Handle the radio adapter
					RadioStruct.dwPhyIndex = j;									//Enable the capability with index j
					RadioStruct.dot11SoftwareRadioState = dot11_radio_state_on;	//Set the software state for the capability ON
					RadioStruct.dot11HardwareRadioState = dot11_radio_state_on;	//Set the hardware state for the capability ON
				
					const PVOID pData = &RadioStruct;
					DWORD dwDataSize = sizeof(RadioStruct);
					
					//Set the parameters to the interface
					dwResult = WlanSetInterface( hClient, &ppInterfaceList->InterfaceInfo[i].InterfaceGuid, wlan_intf_opcode_radio_state, dwDataSize, pData, NULL);
					if (dwResult != ERROR_SUCCESS)
						{
							wprintf(L"WlanSetInterface failed with error: %u\n", dwResult);
							return;
						}
				}
		}

	//Close the network session
	dwResult = WlanCloseHandle( hClient , NULL);
	if (dwResult != ERROR_SUCCESS)
		{
			wprintf(L"WlanCloseHandle failed with error: %u\n", dwResult);
			return;
		}
}


void WifiHandler::DisconnectFromNetwork()
{

    dwMaxClient = 2;		//The highest version of the WLAN API that the client supports.(2 for Vista and on)
	dwResult = 0;			//Error message handler
	hClient = NULL;			//Handler ID for the session

	//Display info
	wprintf(L"Disconnecting From Current Network\n");

	//Open a network session to get the handler
	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
    if (dwResult != ERROR_SUCCESS) 
		{
			wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
			return;
		}
	
	//Get all the interfaces
	dwResult = WlanEnumInterfaces(hClient,NULL,&ppInterfaceList);
	if (dwResult != ERROR_SUCCESS)
		{
			wprintf(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
			return;
		}
	
	//TODO: Disconnect all the interfaces from the networks
	//Disconnect from current wifi network
	dwResult = WlanDisconnect( hClient, &ppInterfaceList->InterfaceInfo->InterfaceGuid  , NULL);
	if (dwResult != ERROR_SUCCESS)
		{
			wprintf(L"WlanDisconnect failed with error: %u\n", dwResult);
			//return 1;
		}
	
}





void HandleLastError(const char *msg /* = "Error occured" */) {
        DWORD errCode = GetLastError();
        char *err;
        if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           errCode,
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
                           (LPTSTR) &err,
                           0,
                           NULL))
            return;

        //TRACE("ERROR: %s: %s", msg, err);
        static char buffer[1024];
        _snprintf(buffer, sizeof(buffer), "ERROR: %s: %s\n", msg, err);
        OutputDebugString(buffer);
        LocalFree(err);
}

/*
void PrintAdapterInfo (){

	
	DWORD rv, size;
	PIP_ADAPTER_ADDRESSES adapter_addresses;
	size = sizeof (&adapter_addresses);
 
	rv = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, adapter_addresses, &size);
	if (rv != ERROR_BUFFER_OVERFLOW) 
		{
			fprintf(stderr, "GetAdaptersAddresses() failed...");
			return false;
		}

}
*/