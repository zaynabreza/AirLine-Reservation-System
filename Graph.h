#pragma once
#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include"Flights.h"
using namespace std;

struct connected
{
	bool check;
	string city;
};

struct Hotel
{
	string c;
	int h;
};
struct Time
{
	int hours;
	int min;

	void get(string x) //This converts a string to time, needed since from the file the time has been read as string
	{
		char a[10] = { '/0' };
		for (int i = 0; i < 2 && i < x.length(); i++)
		{
			a[i] = x[i];
		}
		stringstream lol(a);
		lol >> hours;

		for (int i = 0, j = 3; i < 2 && j < x.length(); i++, j++)
		{
			a[i] = x[j];
		}
		cout << endl;
		stringstream lolz(a);
		lolz >> min;

	}

	Time& operator- (Time& a)  //this subtracts two times (landing and takeoff) to get their difference
	{
		Time x;
		x.hours = hours - a.hours;
		x.min = min - a.min;

		return x;

	}

	void display() //this outputs the time;
	{
		cout << hours << ":" << min << endl;
	}

	bool operator> (Time& a) //This checks if one object of Time is greater than the other
	{
		if (a.hours < hours)
		{
			return true;
		}
		else if (a.hours == hours && a.min < min)
			return true;
		else
			return false;
	}

	Time& operator+ (int x)//this is used to add number of days to time to calculate transit time
	{
		Time a = *this;
		a.hours = a.hours + 24 * x;

		return a;
	}
};

struct Date
{
	int day;
	int month;
	int year;

	void get(string x) //This converts a string to date, needed since from the file the date has been read as string
	{
		char a[10] = { '/0' };
		for (int i = 0; i < 1 && i < x.length(); i++)
		{
			a[i] = x[i];
		}
		stringstream lol(a);
		lol >> day;

		for (int i = 0, j = 2; i < 2 && j < x.length(); i++, j++)
		{
			a[i] = x[j];
		}
		stringstream lolz(a);
		lolz >> month;

		for (int i = 0, j = 5; i < 4 && j < x.length(); i++, j++)
		{
			a[i] = x[j];
		}
		stringstream lola(a);
		lola >> year;

	}

	bool operator==(Date& d) //to check if two dates are equal...use this after adding and subtracting 1 from the given date to check nearby dates
	{
		if (day == d.day && month == d.month && year == d.year)
		{
			return 1;
		}
		else
			return 0;
	}
	Date& operator-(int x) //use this by sending parameter as 1 to get the date before
	{
		Date a;
		if (day == 1)
		{
			a.day = 30;
			a.month = month - 1;
			a.year = year;
		}
		else
		{
			a.day = day - x;
			a.month = month;
			a.year = year;
		}

		return a;
	}

	Date& operator+(int x) //use this by sending parameter as 1 to get the date after
	{
		Date a;
		a.day = day + x;
		a.month = month;
		a.year = year;

		return a;
	}
	void display()
	{
		cout << day << "/" << month << "/" << year << endl;
	}
};

struct Flight //This class is used to store flight data in nodes
{
	string date;
	string ttime;
	string ltime;
	int cost;
	string airline;
	Time total; //transit time

	void display()
	{
		Time a, b, c;
		a.get(ltime);
		b.get(ttime);
		c = a - b;
		cout <<"Date: "<<date<<" Airline: " << airline << " TakeOff: " << ttime << " Landing: " << ltime << " Cost: " << cost << " Total time: "; c.display();
	}

	void totalTime() //calculate transit time
	{
		Time a, b;
		a.get(ltime);
		b.get(ttime);
		total = a - b;
	}
};
struct Node
{
	string City;
	Node* next;
	int hotel;
	int f=0; //number of flights coming to this city from head of list
	Flight routes[100]; //store flight info
};



class AdjList
{
public:
	Node* head;
	Node* tail;

	AdjList()
	{
		head = NULL;
		tail = NULL;
	}
	void New(string x)  //to create vertices
	{
		Node* temp = new Node;
		temp->City = x;
		temp->next = NULL;
		temp->f = 0;

		if (head == NULL)
		{
			head = temp;
			tail = head;
		}
		else
			cout << "Vertex already exists" << endl;
	}
	void Insert(Flights a, Hotel h[])
	{
		Node* curr = head;
		bool found = false;
		if (head->City != a.source) //checks if flight being inserted into correct list
			cout << "This flight isn't from this city" << endl;
		else
		{
			//cout << "Entering flight for " << head->City << endl;
			while (curr)
			{
				if (curr->City == a.dest) //if flights to this destination already exist, only add into the flight array
				{
					//cout << "This destination exists " <<a.dest<< endl;
					curr->routes[curr->f].airline = a.airline;
					curr->routes[curr->f].cost = a.cost;
					curr->routes[curr->f].ltime = a.ltime;
					curr->routes[curr->f].date = a.date;
					curr->routes[curr->f].ttime = a.ttime;
					curr->f++;

					int i = 0;
					while (i < 11)
					{
						if (h[i].c == curr->City)
						{
							curr->hotel = h[i].h;
							break;
						}
						i++;
					}


					found = true;
					break;
				}
				curr = curr->next;
			}

			if (found == false) //if this destination doesnt already exist, create new node and inser flight into that
			{
				Node* temp;
				temp = new Node;
				temp->next = NULL;
				temp->City = a.dest;
				
				tail->next = temp;
				tail = temp;

				tail->f = 0;
				tail->routes[tail->f].airline = a.airline;
				tail->routes[tail->f].cost = a.cost;
				tail->routes[tail->f].ltime = a.ltime;
				tail->routes[tail->f].date = a.date;
				tail->routes[tail->f].ttime = a.ttime;
				
				int i = 0;
				while (i < 11)
				{
					if (h[i].c == tail->City)
					{
						tail->hotel = h[i].h;
						break;
					}
					i++;
				}

				tail->f++;

				
			}
		}
	}

};

struct Option //this class is used to store the possible direct flights user can take between to cities
{
	Flight a;
	Date b;
	string s;
	int h;
	string d;
	Time t;
};


class Graph
{
	int v;
	AdjList* array;
	int size;

public:
	Graph(int v)
	{
		this->v = v;
		array = new AdjList[v];
		size = 0;
	}

	void CreateVertex(string city)
	{
		for (int i = 0; i < size; i++)
		{
			if (array[i].head->City==city)
			{
				cout << "Already exists" << endl;
				return;
			}
		}
		for (int i = 0; i < v; i++)
		{
			if (array[i].head == NULL)
			{
				array[i].New(city);
				//cout << city << " inserted" << endl;
				size++;
				return;
			}
		}
	}

	void InsertEdge(Flights a, Hotel h[])
	{
		for (int i = 0; i < v; i++)
		{
			if (array[i].head->City == a.source)
			{
				array[i].Insert(a, h);
				//cout << a.dest << " inserted via " << a.airline << " on " << a.date<< " from "<<array[i].head->City << endl;
				return;
			}
		}
	}


	void MakeGraph(string name, string name2)
	{
		fstream a;
		int total = 0;
		a.open(name.c_str());
		Flights x[110];

		int i = 0;
		while (!a.eof() && i < 110) //reading the file
		{
			a >> x[i].source;
			//cout << x[i].source << " ";
			a >> x[i].dest;
			//cout << x[i].dest << " ";
			a >> x[i].date;
			//cout << x[i].date << " ";
			a >> x[i].ttime;
			//cout << x[i].ttime << " ";
			a >> x[i].ltime;
			//cout << x[i].ltime << " ";
			a >> x[i].cost;
			//cout << x[i].cost << " ";
			a >> x[i].airline;
			//cout << x[i].airline << " ";

			if (x[i].airline != "\0")
				total++;
			i++;

			//cout << endl;
		}

		a.close();


		ifstream b(name2.c_str());
		Hotel *h;
		h = new Hotel[100];

		int xyz = 0;
		while (!b.eof())
		{
			b >> h[xyz].c;
			b >> h[xyz].h;

			xyz++;
		}
	
		b.close();
		this->v = total; //number of flights inserted
		array = new AdjList[v];
		size = 0;

		for (int i = 0; i < v; i++)
			CreateVertex(x[i].source);

		cout << size << endl;

		for (int i = 0; i < v; i++)
		{
			InsertEdge(x[i], h);
		}


	}

	void SituationA()
	{
		cout << "Enter your source" << endl;
		cout << "Enter destination" << endl;
		cout << "Enter preferred airline" << endl;
		cout << "Enter your date of travel" << endl;

		//now traverse the array of for the list whose head is source, find if it goes to the required destination.
		//when found, find if date and airline are available, if yes create new array of type flight and put all options there.
		//sort the new array based on cost and output :)
	}

	void DirectFlights()
	{
		string src, dest, date;
		cout << "Enter source" << endl;
		cin >> src;
		cout << "Enter destination" << endl;
		cin >> dest;
		cout << "Enter your preffered date of travel (d/mm/yyyy)" << endl;
		cin >> date;

		Flight paths[10];
		Node* curr;
		bool found = false;
		for (int i = 0; i < size; i++)
		{
			if (array[i].head->City == src)
			{
				curr = array[i].head;
				while (curr)
				{
					if (curr->City == dest)
					{
						cout << "***********************************************************************************************" << endl;
						cout << "Here are you options for direct flights: " << endl;
						for (int j = 0; j < curr->f; j++)
						{
							if (curr->routes[j].date == date)
							{
								cout << "***********************************************************************************************" << endl;
								curr->routes[j].display();
								found = true;
							}
						}
						if (found == false)
						{
							Date a, b, c, d, e;
							a.get(date);
							b = a + 1;
							c = a - 1;

							cout << "***********************************************************************************************" << endl;
							cout << "Couldnt find options for the date you specified. Here are alternate options: " << endl;

							cout << "***********************************************************************************************" << endl;
							cout << "For "; c.display();
							for (int j = 0; j < curr->f; j++)
							{
								e.get(curr->routes[j].date);
								if (e == c)
								{
									cout << "***********************************************************************************************" << endl;
									curr->routes[j].display();
								}
							}
							cout << "***********************************************************************************************" << endl;

							cout << "For "; b.display();
							for (int j = 0; j < curr->f; j++)
							{
								e.get(curr->routes[j].date);
								if (e == b)
								{
									cout << "***********************************************************************************************" << endl;
									curr->routes[j].display();
								}
							}
							

						}
						cout << "***********************************************************************************************" << endl;
						return;
					}
					curr = curr->next;
				}
				cout << "This destination does not exist in out database" << endl;
				return;
			}
		}
		cout << "This origin city does not exist in out database" << endl;
	}

	void DirectFlightsAirline()
	{
		string src, dest, date, air;
		cout << "Enter source" << endl;
		cin >> src;
		cout << "Enter destination" << endl;
		cin >> dest;
		cout << "Enter your preffered date of travel (d/mm/yyyy)" << endl;
		cin >> date;
		cout << "Enter preferred airline" << endl;
		cin >> air;

		Flight paths[10];
		Node* curr;
		bool found = false;
		for (int i = 0; i < size; i++)
		{
			if (array[i].head->City == src)
			{
				curr = array[i].head;
				while (curr)
				{
					if (curr->City == dest)
					{
						cout << "***********************************************************************************************" << endl;
						cout << "Here are you options for direct flights: " << endl;
						for (int j = 0; j < curr->f; j++)
						{
							if (curr->routes[j].date == date && curr->routes[j].airline==air)
							{
								cout << "***********************************************************************************************" << endl;
								curr->routes[j].display();
								found = true;
							}
						}
						if (found == false)
						{
							Date a, b, c, d, e;
							a.get(date);
							b = a + 1;
							c = a - 1;

							cout << "***********************************************************************************************" << endl;
							cout << "Couldnt find options for the date you specified. Here are alternate options: " << endl;

							cout << "***********************************************************************************************" << endl;
							cout << "For "; c.display();
							for (int j = 0; j < curr->f; j++)
							{
								e.get(curr->routes[j].date);
								if (e == c && curr->routes[j].airline == air)
								{
									cout << "***********************************************************************************************" << endl;
									curr->routes[j].display();
								}
							}
							cout << "***********************************************************************************************" << endl;

							cout << "For "; b.display();
							for (int j = 0; j < curr->f; j++)
							{
								e.get(curr->routes[j].date);
								if (e == b && curr->routes[j].airline == air)
								{
									cout << "***********************************************************************************************" << endl;
									curr->routes[j].display();
								}
							}


						}
						cout << "***********************************************************************************************" << endl;
						return;
					}
					curr = curr->next;
				}
				cout << "This destination does not exist in out database" << endl;
				return;
			}
		}
		cout << "This origin city does not exist in out database" << endl;
	}

	void Connected(string source, string destination)
	{
		connected* visited;
		visited = new connected[size];
		Node* nodeArray[30][30];
		Node** path;
		path = new Node*[v];
		string u = source;
		Node* x;
		for (int i = 0; i < size; i++)
		{
			if (array[i].head->City == source)
				x = array[i].head;
		}
		string d = destination;

		int path_index = 0;
		int arraycount = 0;
		for (int i = 0; i < size; i++)
		{
			visited[i].city = array[i].head->City;
			visited[i].check = false;
		}
		//printAllPathsUtil(u, d, visited, path, path_index, nodeArray, arraycount);
	}

	
	int getSourcePos(string u, connected* visited)
	{
		int i;
		for (i = 0; i < size; i++)
		{
			if (u == visited[i].city)
			{
				//cout << "City " << u << " position is " << i << endl;
				break;
			}
		}
		if (i == size)
			return -1;
		else
			return i;
	}
	bool getBool(Node* i, connected* visited)
	{
		for (int j = 0; j < size; j++)
		{
			if (i->City == visited[j].city)
			{
				if (visited[j].check == true)
				{
					return true;
				}

			}
		}
		return false;
	}
	void printAllPathsUtil(Node* x, string d, connected* visited, Node* path[], int& path_index, Node*** nodearray, int& arraycount)
	{
		// Mark the current node and store it in path[] 
		string u = x->City;
		//cout << "NOW AT " << u << endl;
		int s = getSourcePos(u, visited);
		visited[s].check = true;
		//cout << path_index << endl;
		path[path_index] = x;

		//cout << size << endl;
		path_index++;

		
		//cout << "Checking if destination reached" << endl;
		// If current vertex is same as destination, then print 
		// current path[] 
		

		if (u == d)
		{
			//cout << "Destination reached" << endl;
			//cout << "******************************************" << endl;
			//cout << "Path " << arraycount + 1 << ": " << endl;
			for (int i = 0; i < path_index; i++)
			{
				nodearray[arraycount][i] = path[i];
				//cout << nodearray[arraycount][i]->City << " ";
			}

			arraycount++;
			cout << endl;

		}
		else // If current vertex is not destination 
		{
			//cout << "Not yet at destination" << endl;
			// Recur for all the vertices adjacent to current vertex 
			int z;
			for (z = 0; z < size; z++)
			{
				if (array[z].head->City == u)
					break;
			}
			s = z;
			Node* curr = array[s].head;
			Node* end = array[s].tail;
			//for (Node* i = curr; i != end; i= i->next)
			while(curr && curr->next)
			{
				//cout << "Traversing the list" << endl;
				bool val = getBool(curr->next, visited);
				//cout << "        next  City is " << curr->next->City <<val << endl;
				if (!val)
				{
					printAllPathsUtil(curr->next, d, visited, path, path_index, nodearray, arraycount);
				}

				curr = curr->next;
			}
		}

		// Remove current vertex from path[] and mark it as unvisited 
		path_index--;
		s = getSourcePos(u, visited);
		visited[s].check = false;
	}

	void Print(string source, string dest)
	{
		connected* visited;
		visited = new connected[size];
		for (int i = 0; i < size; i++)
		{
			visited[i].check = 0;
			visited[i].city = array[i].head->City;
		}
		Node*** nodeArray;
		nodeArray = new Node * *[100];
		for (int i = 0; i < 100; i++)
		{
			nodeArray[i] = new Node * [30];
			for (int j = 0; j < 30; j++)
			{
				nodeArray[i][j] = NULL;
			}
		}
		Node** path;
		path = new Node * [size];

		for (int i = 0; i < size; i++)
			path[i] = new Node;
		string u = source;
		Node* x;
		x = new Node;
		for (int i = 0; i < size; i++)
		{
			if (array[i].head->City == source)
				x = array[i].head;
		}
		string d = dest;
		int path_index = 0;
		int arraycount = 0;
		for (int i = 0; i < size; i++)
		{
			visited[i].city = array[i].head->City;
			visited[i].check = false;
		}
		printAllPathsUtil(x, d, visited, path, path_index, nodeArray, arraycount);
		
		int num = arraycount - 1;
		
		
		for (int i = 0; i < num-1; i++)
		{
			for (int i = 0; i < num - 1; i++)
			{
				int a = 0, b = 0;
				for (int j = 0; nodeArray[i][j] != NULL; j++)
				{
					a++;
				}
				for (int j = 0; nodeArray[i + 1][j] != NULL; j++)
				{
					b++;
				}

				if (a > b)
				{
					Node** temp;
					temp = nodeArray[i];
					nodeArray[i] = nodeArray[i + 1];
					nodeArray[i + 1] = temp;
					
				}
			}
		}
		
		string dd;
		cout << "Enter date of travel (d/mm/yyyy)" << endl;
		cin >> dd;
		Date da;
		da.get(dd);
		int available = 0;
		bool avail[30] = { 0 };
		bool av = false;
		Flight tmp[10];
		Date dx;
		Option** Final;
		Final = new Option * [10];
		dx.get(dd);
		

		cout << "Do you have a minimum and maximum transit time at each location? Press 1 if yes" << endl;
		int tim;
		cin >> tim;
		int min, max;

		if (tim != 1)
		{
			min = 0;
			max = 1000;
		}
		else
		{
			cout << "Enter minimum number of hours of transit time at any one location" << endl;
			cin >> min;
			cout << "Enter max number of hours of transit time at any one location" << endl;
			cin >> max;
		}
		int air;
		cout << "Do you want a specific airline? Press 1 is yes, 0 if not " << endl;
		cin >> air;
		switch (air)
		{
		case 0:

			cout << "Do you want a specific transit location? Press 1 if yes" << endl;
			int tr;
			cin >> tr;

			if (tr != 1)
			{
				for (int i = 0; i < num; i++)
				{
					//cout << "Path " << i + 1 << endl;
					//av = true;
					av = true;
					int j = 1;
					int nn;
					for (; nodeArray[i][j] != NULL; j++)
					{
						Option* xx = NULL;
						avail[j] = false;
						//int k = 0;
						if (Check(nodeArray[i][j], nodeArray[i][j + 1], dx, xx, min, max))
						{
							avail[j] = true;
							Final[j] = xx;

							//cout << "CHECK" << endl;
							//xx[0].a.display();
						}

					}

					nn = j;
					for (; j < 30; j++)
						avail[j] = true;
					for (int j = 1; j < 30; j++)
					{
						if (avail[j] == false)
						{
							av = false;
							//cout << "Path is false " << endl;
						}

					}

					if (av == true )
					{
						cout << "**********************" << endl;
						cout << "Path " << available + 1 << endl;
						int j;
						for (j = 0; nodeArray[i][j] != NULL; j++)
						{
							cout << nodeArray[i][j]->City << " ";
						}
						cout << endl;
						cout << "Your possible Iteneraries: " << endl;
						cout << "????????????????????????????????????????????" << endl;

						cout << nn << endl;


						//sorting by time

						for (int j = 1; j < nn; j++)
						{
							for (int k = 0; Final[j][k + 1].s != " "; k++)
							{
								for (int k = 0; Final[j][k + 1].s != " "; k++)
								{
									Final[j][k].a.totalTime();
									Final[j][k + 1].a.totalTime();
									if (Final[j][k].a.total > Final[j][k + 1].a.total)
									{
										Option temp = Final[j][k];
										Final[j][k] = Final[j][k + 1];
										Final[j][k + 1] = temp;
									}
								}
							}
						}

						for (int j = 1; j < nn; j++)
						{
							for (int k = 0; Final[j][k].s != " "; k++)
							{
								cout << "To " << Final[j][k].s << endl << endl;
								Final[j][k].a.display();
								if (Final[j][k].b.day != 0)
								{
									cout << "If leaving next destination on "; Final[j][k].b.display();
									cout << "With transit time as "; Final[j][k].t.display();

									cout << "And hotel charges " << Final[j][k].h << endl;

									cout << endl << endl;
								}
							}
						}



						cout << endl;
						available++;
						cout << "**********************" << endl;

					}
				}
			}
			else
			{

			string transit;
			cout << "Enter transit location " << endl;
			cin >> transit;
				for (int i = 0; i < num; i++)
				{
					//cout << "Path " << i + 1 << endl;
					//av = true;
					av = true;
					int j = 1;
					int nn;
					for (; nodeArray[i][j] != NULL; j++)
					{
						Option* xx = NULL;
						avail[j] = false;
						//int k = 0;
						if (Check(nodeArray[i][j], nodeArray[i][j + 1], dx, xx, min, max))
						{
							avail[j] = true;
							Final[j] = xx;

							//cout << "CHECK" << endl;
							//xx[0].a.display();
						}

					}

					nn = j;
					for (; j < 30; j++)
						avail[j] = true;
					for (int j = 1; j < 30; j++)
					{
						if (avail[j] == false)
						{
							av = false;
							//cout << "Path is false " << endl;
						}

					}

					bool tt = false;

					for (int j = 0; nodeArray[i][j] != NULL; j++)
					{
						if (nodeArray[i][j]->City == transit)
							tt = true;
					}



					if (av == true && tt == true)
					{
						cout << "**********************" << endl;
						cout << "Path " << available + 1 << endl;
						int j;
						for (j = 0; nodeArray[i][j] != NULL; j++)
						{
							cout << nodeArray[i][j]->City << " ";
						}
						cout << endl;
						cout << "Your possible Iteneraries: " << endl;
						cout << "????????????????????????????????????????????" << endl;

						cout << nn << endl;


						//sorting by time

						for (int j = 1; j < nn; j++)
						{
							for (int k = 0; Final[j][k + 1].s != " "; k++)
							{
								for (int k = 0; Final[j][k + 1].s != " "; k++)
								{
									Final[j][k].a.totalTime();
									Final[j][k + 1].a.totalTime();
									if (Final[j][k].a.total > Final[j][k + 1].a.total)
									{
										Option temp = Final[j][k];
										Final[j][k] = Final[j][k + 1];
										Final[j][k + 1] = temp;
									}
								}
							}
						}

						for (int j = 1; j < nn; j++)
						{
							for (int k = 0; Final[j][k].s != " "; k++)
							{
								cout << "To " << Final[j][k].s << endl << endl;
								Final[j][k].a.display();
								if (Final[j][k].b.day != 0)
								{
									cout << "If leaving next destination on "; Final[j][k].b.display();
									cout << "With transit time as "; Final[j][k].t.display();

									cout << "And hotel charges " << Final[j][k].h << endl;

									cout << endl << endl;
								}
							}
						}



						cout << endl;
						available++;
						cout << "**********************" << endl;

					}
				}

			}
			break;

		case 1:
			cout << "Enter your preferred airline" << endl;
			string aa;
			cin >> aa;

			cout << "Do you have a specific transit location you want to stop at? If yes, press 1, if no, press 0" << endl;
			int ttr;
			cin >> ttr;

			if (ttr != 1)
			{
				for (int i = 0; i < num; i++)
				{
					//cout << "Path " << i + 1 << endl;
					//av = true;
					av = true;
					int j = 1;
					int nn;
					for (; nodeArray[i][j] != NULL; j++)
					{
						Option* xx = NULL;
						avail[j] = false;
						//int k = 0;
						if (Check(nodeArray[i][j], nodeArray[i][j + 1], dx, xx, min, max))
						{
							avail[j] = true;
							Final[j] = xx;

							//cout << "CHECK" << endl;
							//xx[0].a.display();
						}

					}

					nn = j;
					for (; j < 30; j++)
						avail[j] = true;
					for (int j = 1; j < 30; j++)
					{
						if (avail[j] == false)
						{
							av = false;
							//cout << "Path is false " << endl;
						}

					}





					if (av == true)
					{
						cout << "**********************" << endl;
						cout << "Path " << available + 1 << endl;
						int j;
						for (j = 0; nodeArray[i][j] != NULL; j++)
						{
							cout << nodeArray[i][j]->City << " ";
						}
						cout << endl;
						cout << "Your possible Iteneraries: " << endl;
						cout << "????????????????????????????????????????????" << endl;

						cout << nn << endl;

						//sorting by price

						for (int j = 1; j < nn; j++)
						{
							for (int k = 0; Final[j][k + 1].s != " "; k++)
							{
								for (int k = 0; Final[j][k + 1].s != " "; k++)
								{
									if (Final[j][k].a.cost > Final[j][k + 1].a.cost)
									{
										Option temp = Final[j][k];
										Final[j][k] = Final[j][k + 1];
										Final[j][k + 1] = temp;
									}
								}
							}
						}
						for (int j = 1; j < nn; j++)
						{
							for (int k = 0; Final[j][k].s != " "; k++)
							{

								if (Final[j][k].a.airline == aa)
								{
									cout << "To " << Final[j][k].s << endl;
									Final[j][k].a.display();
									if (Final[j][k].b.day != 0)
									{
										cout << "If leaving next destination on "; Final[j][k].b.display();

										cout << "With transit time as "; Final[j][k].t.display();

										cout << "And hotel charges " << Final[j][k].h << endl;
									}
									cout << endl << endl;
								}
							}
						}



						cout << endl;
						available++;
						cout << "**********************" << endl;

					}
				}
			}
			else
			{

			string transit;
			cout << "Enter transit location " << endl;
			cin >> transit;
				for (int i = 0; i < num; i++)
				{
					//cout << "Path " << i + 1 << endl;
					//av = true;
					av = true;
					int j = 1;
					int nn;
					for (; nodeArray[i][j] != NULL; j++)
					{
						Option* xx = NULL;
						avail[j] = false;
						//int k = 0;
						if (Check(nodeArray[i][j], nodeArray[i][j + 1], dx, xx, min, max))
						{
							avail[j] = true;
							Final[j] = xx;

							//cout << "CHECK" << endl;
							//xx[0].a.display();
						}

					}

					nn = j;
					for (; j < 30; j++)
						avail[j] = true;
					for (int j = 1; j < 30; j++)
					{
						if (avail[j] == false)
						{
							av = false;
							//cout << "Path is false " << endl;
						}

					}

					bool tt = false;

					for (int j = 0; nodeArray[i][j] != NULL; j++)
					{
						if (nodeArray[i][j]->City == transit)
							tt = true;
					}



					if (av == true && tt==true)
					{
						cout << "**********************" << endl;
						cout << "Path " << available + 1 << endl;
						int j;
						for (j = 0; nodeArray[i][j] != NULL; j++)
						{
							cout << nodeArray[i][j]->City << " ";
						}
						cout << endl;
						cout << "Your possible Iteneraries: " << endl;
						cout << "????????????????????????????????????????????" << endl;

						cout << nn << endl;

						//sorting by price

						for (int j = 1; j < nn; j++)
						{
							for (int k = 0; Final[j][k + 1].s != " "; k++)
							{
								for (int k = 0; Final[j][k + 1].s != " "; k++)
								{
									if (Final[j][k].a.cost > Final[j][k + 1].a.cost)
									{
										Option temp = Final[j][k];
										Final[j][k] = Final[j][k + 1];
										Final[j][k + 1] = temp;
									}
								}
							}
						}
						for (int j = 1; j < nn; j++)
						{
							for (int k = 0; Final[j][k].s != " "; k++)
							{

								if (Final[j][k].a.airline == aa)
								{
									cout << "To " << Final[j][k].s << endl;
									Final[j][k].a.display();
									if (Final[j][k].b.day != 0)
									{
										cout << "If leaving next destination on "; Final[j][k].b.display();

										cout << "With transit time as "; Final[j][k].t.display();

										cout << "And hotel charges " << Final[j][k].h << endl;
									}
									cout << endl << endl;
								}
							}
						}



						cout << endl;
						available++;
						cout << "**********************" << endl;

					}
				}




			}
			break;
		}
		cout << "Available routes on this date are: " << endl;
		cout << available << endl;

		
		
		/*int i = 0;
		while (nodeArray[0][i+1] != NULL)
		{
			Check(nodeArray[0][i], nodeArray[0][i+1], dx, xx);
			i++;
		}
		cout << "******************************************" << endl;*/
	}


	bool CheckTime(Flight a, Flight b)
	{
		Time x, y, z;
		x.get(a.ltime);
		y.get(b.ttime);


	//	cout << "Checking betweeen "; y.display(); cout << " and "; x.display();
		z = (y - x);
		if (z.hours < 0)
		{
			return 0;
			
		}
		else
		{
			return 1;

			
		}
	}
	
	bool Check(Node* a, Node* b, Date& d, Option*& x, int min, int max)
	{

		x = new Option[10];
		for (int i = 0; i < 10; i++)
			x[i].s = " ";
		int index = 0;
		bool is = false;
		//cout << " To:  " << a->City <<endl;

		Date d1, d2;

		if (b == NULL)
		{
			for (int i = 0; i < a->f; i++)
			{
				x[i].a = a->routes[i];
				x[i].s = a->City;
				x[i].b.day = 0;
				x[i].b.month = 0;
				x[i].b.year = 0;
				x[i].t.hours = 0;
				if (x[index].t.hours > 12)
				{
					x[index].h = a->hotel;
				}
				else
				{
					x[index].h = 0;
				}
			}
			return true;
		}
		for (int i = 0; i < a->f; i++)//traverse flights in first node
		{
			for (int j = 0; j < b->f; j++)//compare with flights in second node
			{
				d1.get(a->routes[i].date);
				d2.get(b->routes[j].date);

				if (d1 == d && d2 == d && CheckTime(a->routes[i], b->routes[j]))
				{

					Time aa, bb, cc;

					aa.get(b->routes[j].ttime);
					bb.get(a->routes[i].ltime);
					cc = aa - bb;

					if (cc.hours >= min && cc.hours <= max)
					{
						is = true;
						x[index].a = a->routes[i];
						x[index].b = d;
						x[index].s = a->City;
						x[index].t = aa - bb;
						if (x[index].t.hours > 12)
						{
							x[index].h = a->hotel;
						}
						else
						{
							x[index].h = 0;
						}

						index++;
						break;
					}
				}
				else if (d1 == d  && !CheckTime(a->routes[i], b->routes[j]))
				{
					bool ch = false;
					int da = d2.day;
					Date temp = d;
					while (da <= 8)
					{
						da = da + 1;
						temp = temp + 1;
						if (d2 == temp)
						{

							Time aa, bb, cc;

							aa.get(b->routes[j].ttime);
							bb.get(a->routes[i].ltime);
							cc = aa - bb;
							cc = cc + (temp.day - d1.day);

							if (cc.hours >= min && cc.hours <= max)
							{
								x[index].a = a->routes[i];
								x[index].b = d2;
								x[index].s = a->City;

								x[index].t = aa - bb;
								x[index].t = x[index].t + (temp.day - d1.day);

								if (x[index].t.hours > 12)
								{
									x[index].h = a->hotel;
								}
								else
								{
									x[index].h = 0;
								}
								ch = true;
								index++;
								break;
							}

						}
					}

					if (ch == true)
					{
						is = true;
						break;
					}
					
				}
			}
		}

		return is;
	}
	
};

