//Author: Nicolas Diez

#ifndef _WIFI_HANDLER_


class WifiHandler
{

public:

	DWORD								dwClientVersion;
	PWLAN_INTERFACE_INFO_LIST			ppInterfaceList;
	HANDLE								hClient;
    DWORD								dwMaxClient;			//Out: The version of the WLAN API that will be used in this session    
    DWORD								dwCurVersion;
	DWORD								dwResult;
	PWLAN_INTERFACE_CAPABILITY			ppCapability;
	_WLAN_PHY_RADIO_STATE				RadioStruct;			//To handle the radio state of the wifi interfaces

	void								SwitchOffWifiAdapter();
	void								SwitchOnWifiAdapter();
	void								DisconnectFromNetwork();

	void								HandleLastError(const char *msg);
	void								PrintAdapterInfo ();

};


#endif