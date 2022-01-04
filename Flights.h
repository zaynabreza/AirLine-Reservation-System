#pragma once
#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
using namespace std;

struct Flights
{
	string source;
	string dest;
	string date;
	string ttime;
	string ltime;
	int cost;
	string airline;	

	void operator=(Flights& a)
	{
		source = a.source;
		dest = a.dest;
		date = a.date;
		ttime = a.ttime;
		ltime = a.ltime;
		cost = a.cost;
		airline = a.airline;
	}
};

Flights* ReadFile(string name, int& total)
{
	fstream a;
	total = 0;
	a.open(name.c_str());
	Flights x[110];

	int i = 0;
	while (!a.eof() && i<110)
	{
		a >> x[i].source;
		cout << x[i].source << " ";
		a >> x[i].dest;
		cout << x[i].dest << " ";
		a >> x[i].date;
		cout << x[i].date<< " ";
		a >> x[i].ttime;
		cout << x[i].ttime << " ";
		a >> x[i].ltime;
		cout << x[i].ltime<< " ";
		a >> x[i].cost;
		cout << x[i].cost << " ";
		a >> x[i].airline;
		cout << x[i].airline << " ";

		if(x[i].airline != "\0")
			total++;
		i++;

		cout<<endl;
	}

	a.close();

	return x;
}
