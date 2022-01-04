#include"Flights.h"
//#include<gra>
#include"Graph.h"

int main()
{
	//testing construction of graph
	Graph a(17);

	a.MakeGraph("temp.txt", "HotelCharges_perday.txt");

	

	system("CLS");
	cout << endl << endl << endl;
	

	cout << "                                 __" << endl;
	cout << "                                 \\\ \\ " << endl;
	cout << "                                  \\\ `\\ " << endl;
	cout << "               ___                 \\\  \\ " << endl;
	cout << "              |    \\                \\\  `\\ " << endl;
	cout << "              |_____\\                \\    \\ " << endl;
	cout << "              |______\\                \\    `\\ " << endl;
	cout << "              |       \\                \\     \\ " << endl;
	cout << "              |      __\\__---------------------------------._. " << endl;
	cout << "            __|---~~~__o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_o_[][\__ " << endl;
	cout << "           |___                         /~      )                \\__ " << endl;
	cout << "               ~~~---..._______________/      ,/_________________/ " << endl;
	cout << "                                      /      / " << endl;
	cout << "                                     /     ,/ " << endl;
	cout << "                                    /     / " << endl;
	cout << "                                   /    ,/ " << endl;
	cout << "                                  /    / " << endl;
	cout << "                                 //  ,/ " << endl;
	cout << "                                //  / " << endl;
	cout << "                               // ,/ " << endl;
	cout << "                              //_/ " << endl;


	cout << endl << endl;

	cout << "            __        _______ _     ____ ___  __  __ _____  " << endl;
	cout << "            \\ \\      / / ____| |   / ___/ _ \\|  \\/  | ____| " << endl;
	cout << "             \\ \\ /\\ / /|  _| | |  | |  | | | | |\\/| |  _| " << endl;
	cout << "              \\ V  V / | |___| |__| |__| |_| | |  | | |___  " << endl;
	cout << "               \\_/\\_/  |_____|_____\\____\\___/|_|  |_|_____| " << endl;

	cout << endl << endl;

	int d;
	cout << "Press a key and enter to start " << endl;
	cin >> d;
	
	system("CLS");

	cout << endl << endl;

	cout << "            __        _______ _     ____ ___  __  __ _____  " << endl;
	cout << "            \\ \\      / / ____| |   / ___/ _ \\|  \\/  | ____| " << endl;
	cout << "             \\ \\ /\\ / /|  _| | |  | |  | | | | |\\/| |  _| " << endl;
	cout << "              \\ V  V / | |___| |__| |__| |_| | |  | | |___  " << endl;
	cout << "               \\_/\\_/  |_____|_____\\____\\___/|_|  |_|_____| " << endl;

	cout << endl << endl;
	cout << "Select 1 if you want only direct flights, Select 0 if you want connected flights as well" << endl;
	cin >> d;

	switch (d)
	{
	case 1:
		cout << "Press 1 if you want a specific airline as well, press 0 if not" << endl;
		int aa;
		cin >> aa;
		if (aa == 1)
			a.DirectFlightsAirline();
		else if (aa == 0)
			a.DirectFlights();
		break;
	case 0:
		cout << "Enter origin " << endl;
		string o;
		cin >> o;
		cout << "Enter destination " << endl;
		string des;
		cin >> des;


		a.Print(o, des);
	}

	return 0;



}