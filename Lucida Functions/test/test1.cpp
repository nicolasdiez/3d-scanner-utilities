
#include <iostream>
#include <fstream>
#include <cstring>

#include <windows.h>

#include <PowrProf.h>
using namespace std;

/*
BOOLEAN WINAPI GetActivePwrScheme(
  _Out_  PUINT puiID
);

BOOLEAN WINAPI SetActivePwrScheme(
  _In_      UINT uiID,
  _In_opt_  PGLOBAL_POWER_POLICY lpGlobalPowerPolicy,
  _In_opt_  PPOWER_POLICY lpPowerPolicy
);
*/

int main()
{
  ofstream fichero("FileWriteTesting.txt", ios::out | ios::binary);

  if(!fichero) {
    cout << "Cannot open output file.\n";
    return 1;
  }

  double num = 1985;
  char str[] = "Nico is writing this file to test. Test number:";
  int counter = 0;
  PUINT puiID = 0;

  fichero.write((char *) &num, sizeof(double));
  fichero.write(str, strlen(str));



 std::cin.get(); 


  fichero.close();


  

  return 0;
}

