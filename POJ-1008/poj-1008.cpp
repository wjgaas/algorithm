#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	// pop, no, zip, zotz, tzec, xul, yoxkin, mol, chen, 
	//yax, zac, ceh, mac, kankin, muan, pax, koyab, cumhu
	map<string, int> Haab;
	Haab["pop"] = 0;	Haab["no"] = 1;		Haab["zip"] = 2; 
	Haab["zotz"] = 3;	Haab["tzec"] = 4;	Haab["xul"] = 5; 
	Haab["yoxkin"] = 6;	Haab["mol"] = 7;	Haab["chen"] = 8; 
	Haab["yax"] = 9;	Haab["zac"] = 10;	Haab["ceh"] = 11; 
	Haab["mac"] = 12;	Haab["kankin"] = 13;	Haab["muan"] = 14; 
	Haab["pax"] = 15;	Haab["koyab"] = 16;	Haab["cumhu"] = 17; 
	Haab["uayet"] = 18;

	// imix, ik, akbal, kan, chicchan, cimi, manik, lamat, muluk, 
	//ok, chuen, eb, ben, ix, mem, cib, caban, eznab, canac, ahau
	map<int, string> Tzolkin;
	Tzolkin[0] = "imix"; Tzolkin[1] = "ik";       Tzolkin[2] = "akbal"; 
	Tzolkin[3] = "kan";	 Tzolkin[4] = "chicchan"; Tzolkin[5] = "cimi";
	Tzolkin[6] = "manik"; Tzolkin[7] = "lamat";   Tzolkin[8] = "muluk";
	Tzolkin[9] = "ok";   Tzolkin[10] = "chuen";   Tzolkin[11] = "eb";
	Tzolkin[12] = "ben";  Tzolkin[13] = "ix";     Tzolkin[14] = "mem";
	Tzolkin[15] = "cib";   Tzolkin[16] = "caban"; Tzolkin[17] = "eznab";
	Tzolkin[18] = "canac"; Tzolkin[19] = "ahau";

	int T;
	cin >> T;
	cout << T << endl;

	int _day, _year;
	char _doc;
	string _mon;
	for(int i=0; i<T; i++)
	{
		cin >> _day >> _doc >> _mon >> _year;

		int day = 365*_year + 20*Haab[_mon] + _day;

		int year = day/260;
		day %= 260;

		int mon = day%20;
		day = day%13 + 1;

		cout << day << " " << Tzolkin[mon] << " " << year << endl;
	}
}