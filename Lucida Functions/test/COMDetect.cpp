//Author: Nicolas Diez
//Description: This file contains all the methods needed to detect the COM port that is being used by the Arduino controller.

#include <windows.h>
//#include <math.h>
//#include <stdio.h>
#include <iostream>
#include <wlanapi.h>
#include <string>

// for COM port detection
#include <vector>
#include <string>
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
//#include <powrprof.h>
//#pragma comment(lib, "powrprof.lib")

// main header
#include "COMDetect.h"

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")


void COMDetect:: GetArduinoCOMPorts()
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
    DWORD i;

	hDevInfo = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES );	// Create a HDEVINFO with all present devices.
	if (hDevInfo == INVALID_HANDLE_VALUE)
      {
           wprintf(L"SetupDiGetClassDevs failed with error: %u\n", GetLastError());
		   std::cout << "Error Opening port" << std::endl;
           return;
      }
	
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	std::string search = "Arduino";
	std::string searchCOM = "COM";
	size_t pos = 0;
	size_t posCOM = 0;
	std::string DetectedCOMaux[100];
	

	//Loop to get friendly names of all devices present into system. Save lines where 'Arduino' is present
    for (i=0 ; dwResult = SetupDiEnumDeviceInfo(hDevInfo,i,&DeviceInfoData) ; i++)
	{
		if (dwResult == FALSE)
		{
           wprintf(L"SetupDiEnumDeviceInfo failed with error: %u\n", GetLastError());
           return;
		 }
		
		DWORD DataType;
		DWORD RequiredBufferSize = 0;
		BYTE PropertyBuffer[300];
		std::string sPropertyBuffer(reinterpret_cast<char*>(PropertyBuffer));
		
		
		if (SetupDiGetDeviceRegistryProperty( hDevInfo , &DeviceInfoData , SPDRP_FRIENDLYNAME , &DataType , (PBYTE)PropertyBuffer , sizeof(PropertyBuffer) , &RequiredBufferSize ) != FALSE)
		{
			pos = sPropertyBuffer.find(search);
			printf("Device Registry Property: [%s]\n",PropertyBuffer);

			if (pos != std::string::npos)
			{
				//std::cout << "**** Sentence contains: " << search << " ****" << std::endl;
				posCOM = sPropertyBuffer.find(searchCOM);
				DetectedCOMaux->push_back(sPropertyBuffer[posCOM+3]);
			}
		}
		else
		{
			//wprintf(L"SetupDiGetDeviceRegistryProperty failed with error: %u\n", GetLastError());
		}
	}

	//Get rid of duplicated port numbers
	for(size_t it = 0 ; it < DetectedCOMaux->length() ; it++)
	{
		if (DetectedCOM->find(DetectedCOMaux->at(it)) == std::string::npos)
		{
			DetectedCOM->push_back(DetectedCOMaux->at(it));
		}
	}
	std::sort(DetectedCOM->begin(), DetectedCOM->end());

	SetupDiDestroyDeviceInfoList(hDevInfo);

}


//Detects which COM ports are being used in the computer
void COMDetect:: DetectComPorts(std::vector< tstring >& ports)
{
	size_t upperLimit = 128;
  for(size_t i=1; i<=upperLimit; i++)
  {
	TCHAR strPort[32] = {0};
	_stprintf(strPort, _T("COM%d"), i); 

	DWORD dwSize = 0;
	LPCOMMCONFIG lpCC = (LPCOMMCONFIG) new BYTE[1];
	BOOL ret = GetDefaultCommConfig(strPort, lpCC, &dwSize);
	delete [] lpCC;	   

	lpCC = (LPCOMMCONFIG) new BYTE[dwSize];
	ret = GetDefaultCommConfig(strPort, lpCC, &dwSize);
	delete [] lpCC;   

	if(ret) ports.push_back(strPort);
  }
}