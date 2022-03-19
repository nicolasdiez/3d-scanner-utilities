#include <windows.h>
#include <powrprof.h>
#include <iostream>
#include "stdio.h"
#include <ntstatus.h>
#include <string>
#pragma comment(lib, "powrprof.lib")

using namespace std;


int main(int argc, char **argv) {
	

	//////////////////  SET ACTIVE HIGH PERFORMANCE PLAN  ///////////////////

		
	//Variables
	UCHAR displayBuffer[64] = " ";
	DWORD displayBufferSize = sizeof(displayBuffer);
	GUID buffer;
	DWORD bufferSize = sizeof(buffer);

	//Go throught the machine's power plans and activate the high performance one
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
			}
			
		}
		else break;
	}


	return 0;
}