//Author: Nicolas Diez

#ifndef _COM_DETECT_


class COMDetect
{

public:

	std::string		DetectedCOM[100];									//Output string with the Arduino COM port/s detected
	DWORD			dwResult;											//Error message handler


	void			GetArduinoCOMPorts();								//Execute Arduino COM Port detection
	void			DetectComPorts(std::vector< tstring >& ports);		//Detects which COMs are being used


};


#endif