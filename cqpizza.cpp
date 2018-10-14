/*
C++ program to implement circular queue using linked list.
It is a real time application program for a pizza delivery parlour.
*/
#include<iostream>
#include<string.h>
#include<ctime>
using namespace std;

//Node structure for a circular queue 
typedef struct cqueue_node
{
	int orderno, n, price, pizza[30], quantity[30];
	char name[20];
	struct cqueue_node *next;
}node;

//cqueue class to implement circular queue using linked list
class cqueue
{
	private:
	node *front, *rear;
	public :
	cqueue()
	{
	front = rear = NULL;
	}
	char* systime();
	void enqueue(int ono,char nm[20],int pizza[30],int pr,int quantity[30],int n);
	void dequeue(); 
	void displayCQueue(); 
};

//systime function to written the system date, time
char* cqueue :: systime()
{
	time_t tt; 
	struct tm * ti; 
	time (&tt); 
	ti = localtime(&tt); 
	return asctime(ti); 
}

//enqueue function to create a node and add it to the queue i.e. add to the rear end of the queue
void cqueue :: enqueue(int ono, char nm[20], int pz[30], int pr, int quan[30],int n)
{
	node *new_element = new node;
	new_element->orderno = ono;
	new_element->n = n;
	strcpy(new_element->name,nm);
	for(int i=0;i<n;i++)
	{
		new_element->pizza[i] = pz[i];
	}
	new_element->price = pr;
	for(int i=0;i<n;i++)
	{
		new_element->quantity[i] = quan[i];
	}	
	new_element->next = NULL;
	//if the queue is empty, then add the element to the queue at the rear end and point front to the same node
	if (front == NULL)
	{
		front = rear = new_element;
	}
	//if the queue already has some nodes in it then simply just add new element at the rear end and update the new rear end
	else
	{
		rear->next = new_element;
		rear = new_element;
	}
	//as it is circular queue, rear end points to the front
	rear->next = front;
	cout<<"Order for "<<nm<<" is placed on "<<systime();
	cout<<nm<<", you have to pay Rs. "<<new_element->price<<endl;
}

//dequeue function to delete a node from the queue i.e. delete from front of the queue
void cqueue :: dequeue()
{
	int ono, pr, n, quan[30];
	char nm[20], pz[20];
	if (front == NULL)
	{
		cout<<"No orders available"<<endl; 
		return;
	}
	//if first order is to be delivered i.e. front and rear point to the same position
	else if (front == rear)
	{
		ono = front->orderno;
		strcpy(nm,front->name);
		for(int i=0;i<n;i++)
			pz[i] = front->pizza[i];
		pr=front->price;
		for(int i=0;i<n;i++)
			quan[i] = front->quantity[i];
		n = front->n;
		delete front;
		front = rear = NULL;
	}
	//if the order number is other than 1 that means the front and rear are pointing to differrent nodes
	//hence, we remove the node from rear end
	else
	{
		node *ptr = front;
		ono = front->orderno;
		n = front->n;
		strcpy(nm,front->name);
		for(int i=0;i<front->n;i++)
			pz[i] = front->pizza[i];
		pr = front->price;
		for(int i=0;i<front->n;i++)
			quan[i] = front->quantity[i];
		front = front->next;
		rear->next = front;
		delete ptr;
	}
	cout<<"Order for "<<nm<<" is delivered on "<<systime()<<endl;
}

//displayCQueue function to display the circular queue
void cqueue :: displayCQueue()
{
	if (front == NULL)
	{
		cout<<"No orders available"<<endl; 
		return;
	}
	node *ptr = front;
	cout<<"\nRemaining Orders: \n";
	cout<<"+---------------------------------------------------------------+\n";
	cout<<"|Order No.\t|Name\t\t|Pizza Type(Quantity)\t|Price\t|\n";
	cout<<"+---------------------------------------------------------------+\n";
	do
	{
		cout<<"|"<<ptr->orderno<<"\t\t|"<<ptr->name<<"\t\t|";
		for(int i=0;i<ptr->n;i++)
			cout<<ptr->pizza[i]<<" ("<<ptr->quantity[i]<<"), ";
		cout<<"\b\b  \t\t|"<<ptr->price<<"\t|"<<endl;
		ptr = ptr->next;
	}while (ptr != front);
	cout<<"+---------------------------------------------------------------+\n";
}

int main()
{
	cqueue cq;
	int ch, pri, np=0, o=0, i=0, q[30]={0}, p[30]={0};
	char nm[20], pi[20], ch2, cho;
	do
	{ 
		cout<<"\n*********************************************************\n";
		cout<<"\t\tDipti's Pizza Parlour \n";
		cout<<"*********************************************************\n";
		cout<<"1.Order\n2.Deliver\n3.Remaining orders\n4.Exit";
		cout<<"\n*********************************************************\n";
		l3: cout<<"\nChoice: ";
		cin>>ch;
		switch(ch)
		{
			case 1: 
				pri = 0;
				cout<<"\n*********************************************************\n";
				cout<<"\t\t\tMenu \n";
				cout<<"*********************************************************\n";
				cout<<"+-------------------------------------------------------+\n";
				cout<<"|\tPizza Type\t|\tPizza Name\t|\tPrice\t|\n";
				cout<<"+-------------------------------------------------------+\n";
				cout<<"|\t1.\t|\tOnion Pizza\t|\t20\t|\n|\t2.\t|\tTomato Pizza\t|\t30\t|\n|\t3.\t|\tCheese Pizza\t|\t40\t|\n";
				cout<<"+-------------------------------------------------------+\n";
				o++;
				cout<<"Enter your name (first name only): ";
				//you can use getline function to accept a name with spaces i.e. first name and surname
				cin>>nm;
				do
				{
					l1: cout<<"Enter Pizza type: ";
					cin>>p[i];
					np++;
					if(p[i] == 1)
					{
						cout<<"Enter quantity: ";
						cin>>q[i];
						pri = pri+(20*q[i]);
					}
					else if(p[i] == 2)
					{						
						cout<<"Enter quantity: ";
						cin>>q[i];
						pri = pri+(30*q[i]);
					}
					else if(p[i] == 3)
					{
						cout<<"Enter quantity: ";
						cin>>q[i];
						pri = pri+(40*q[i]);
					}
					else
					{
						cout<<"Invalid choice!\n";
						goto l1;
					}
					i++;
					l2: cout<<"Do you want to order more? (Y/N): ";
					cin>>cho;
					if (cho!='y' && cho!='Y' && cho!='n' && cho!='N')
					{
						cout<<"Incorrect!\n";
						goto l2;
					}
				}while(cho=='y' || cho=='Y');
				cq.enqueue(o,nm,p,pri,q,np);
				i=0;
				np=0;
				break;
			case 2: 
				cq.dequeue();
				break;
			case 3: 
				cq.displayCQueue();
				break;
			case 4:
				exit(1);
				break;
			default: 
				cout<<"Invalid choice!\n";
				goto l3;
		}
	}while(ch>=0 && ch<=3);
	return 0;
}