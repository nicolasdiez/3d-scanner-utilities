//Author: Nicolas Diez

#ifndef _POWER_PLAN_


class PowerPlan
{

public:

	UCHAR			displayBuffer[64];
	GUID			*pp_power_plan;

	void			SaveCurrentPowerScheme();
	GUID			GetCurrentPowerScheme();
	void			SetHighPerformancePowerScheme();
	void			SetPowerScheme(GUID *plan);
};




class Memory
{

public:
		
	#define				DIV 1024		// Use to convert bytes to KB and KB to MB
	#define				WIDTH 7			// Specify the width of the field in which to print the numbers.

	MEMORYSTATUSEX		statex;

	void				FreeGlobalMemoryStatus();
	void				WarnNotEnoughFreeMemory();
};

#endif