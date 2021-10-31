// FINAL PROJECT - GROUP 7
// YAP SOON YU | FARHANNI NASUHA BINTI JUMANI | LEE YIK HONG | NORLIYANA AISYAH BINTI ZUBIR
// SECTION 28

// HEADER FILE //
#include <iostream>
#include<bits/stdc++.h>
#include <sstream>  
#include<fstream>
using namespace std;

// FIRST FUNCTION - PART A - CREATE A NEW BANK ACCOUNT //
void first ()	// Use function 
{
	int account_no=10001;									 	// variable declaration 
	bool exsist=true;	
	int i=0;	
	ostringstream str;	

	while(exsist!=false)										// pretest loop
	{
		str.str("");
		str<<account_no;
		string str1=str.str()+".txt"; 
		ifstream file;
		file.open(str1.c_str());
		if(file)												// if statement
		{
			exsist=true;						
			account_no++;										// account number will added 1 after creating new account - to have unique account
			file.close();
		}
		else
		{
			exsist=false;
		}
	}
			   
	ofstream signup;
	string str2=str.str()+".txt";								// txt file name
	signup.open(str2.c_str());
	signup<<"Account Number :\n"<<account_no<<endl;				// add account number to the file
			   
	cout<<"Account has been created succesfully! \nAccount number is : "<<account_no<<endl;
	char YN;
	cout<<"Do you want to deposit the cash now?(Y/N)Default is (N) ";cin>>YN;
	if(YN=='Y' || YN=='y')
	{
		double amount;
		cout<<"Enter amount : ";cin>>amount;
		cout<<"Your current balance is : RM"<<amount;
		signup<<"Current balance :\n"<<amount;					// add the balance to the file
		signup.clear();
	}
	else if(YN=='N' || YN=='n')
	{
		signup<<"current balance\n0";
		signup.close();
	}
	else
	{
		cout<<"Invalid operation ! Default selected !";
	}
}

 // SECOND FUNCTION - PART B - CASH DEPOSIT //
void second ()
{
	int cash;													//variable declaration 
	string account_no;
	bool check=false;
	cin.ignore();
	
	while(check!=true)											// pretest loop - to check the account number
	{
		cout<<"Enter your Account number : ";getline(cin,account_no);
		account_no=account_no+".txt";
		ifstream file;
		file.open(account_no.c_str());
		if(file)
		{
			check=true;
			file.close();
		}
		else
		{
          	cout<<"Invalid account number! Please try again \n";
          	check=false;
		}
	}
	ofstream Nfile;												// datatype - to write output in new file
	ifstream file;												// datatype - to read old file
	file.open(account_no.c_str());								// open old file
	Nfile.open("temp.txt");										// open new file
	int n=0;													// n is the number of line
	string str;
	
	while(getline(file,str))									// pretest loop - to read the balance in the file
	{
		n++;
		if(n<4)
		{
			Nfile<<str<<endl;
		}
		else if(n==4)											// read the balance (line 4)
		{
			char *oldcash=new char[str.length()+1];
			strcpy(oldcash,str.c_str());
			double oldcasH=atoi(oldcash);
			delete oldcash;
			bool validamount=false;								
	
			while(validamount!=true)							// Pretest loop - user need to enter the valid amount to proceed with another operation
			{
				cout<<"Enter amount : ";cin>>cash;
				if(cash>9 && cash%10==0)						// if statement - check the amount enter is valid or not
				{
					validamount=true;
				}
				else 
				{
					cout<<"Invalid deposit, We only accept amount that can be divisible by 10! \n";
				}
			}
			cash+=oldcasH;										// function to calculate the balance
			Nfile<<cash;										
		}
	}
	file.close();												// close new file
	Nfile.close();												// close old file
	remove(account_no.c_str());									// remove old file
	rename("temp.txt",account_no.c_str());						// rename new file
	cout<<" \nYour current balance : RM"<<cash;
}

// THIRD FUNCTION - PART C - CASH WITHDRAWAL //
void third ()													// use function
{
	int cash;													// variable declaration  
	double NewcasH;
	string account_no;
	bool check=false;
	cin.ignore();
	while(check!=true)											// pretest loop - check account number
	{
		cout<<"Enter Account number : ";getline(cin,account_no);
		account_no=account_no+".txt";
		ifstream file;											// use ifstream to read the file
		file.open(account_no.c_str());
		if(file)
		{ 
			check=true;
			file.close();
		}
		else
		{
         	cout<<"Invalid account number! Please try again. \n";
          	check=false;
		}
	}
	
	ofstream Nfile;												// datatype - to write output in new file
	ifstream file;												// datatype - to read old file
	file.open(account_no.c_str());							
	Nfile.open("temp.txt");										
	int n=0;
	string str;
	
	while(getline(file,str))									// Pretest loop - to read the balance
	{														
		n++;	
		if(n<4)													// if else statement - until reach the correct line in the file
		{														
			Nfile<<str<<endl;
		}
		else if(n==4)											// read the balance at line 4 in the file
		{										
			char *newcash=new char[str.length()+1]; 
			strcpy(newcash,str.c_str());
			NewcasH=atoi(newcash);
			delete newcash;
			bool validamount=false;
			
			while(validamount!=true)
			{													// pretest loop - to check the amount for withdrawal
				cout<<"Enter amount : ";cin>>cash;
				if(cash>9 && cash%10==0)						// if statement to check whether amount enter by user is valid or not
				{												
					validamount=true;	
				}
				else 
				{
					cout<<"Invalid amount, We only accept amount that can be divisible by 10! \n";
				}
			}
			NewcasH-=cash;										// calculate the new balance
			Nfile<<NewcasH;										// NewcasH = balance after withdraw
		}
	}
	file.close();												// close old file
	Nfile.close();												// close new file
	remove(account_no.c_str());									// remove old file
	rename("temp.txt",account_no.c_str());						// rename new file
	cout<<"Withdraw amount : RM"<<cash<<" \nYour current balance : RM"<<NewcasH;	
}

// FORTH FUNCTION - PART D - FUND TRANSFER //
void forth ()
{
	string sender,reciver;										// variable declaration		
	double newcasH,oldcasH;
	bool check=false;
				
	while(check!=true)											// pretest loop - user enter correct account number for sender
	{
		cout<<"Enter sender account number: ";cin.ignore(); getline(cin,sender);
		sender=sender+".txt";									// the file
		ifstream send;
		
		send.open(sender.c_str());
		if(send)												// if statement - check whether the account number exist or not
		{
			check=true;
			send.close();
		}
		else if(!send)
		{
			cout<<"Sender account number is invalid! \n";
			check=false;
		}		
	}
	check=false;
	while(check!=true)											// pretest loop - user enter correct account number for receiver
	{
		cout<<"Enter receiver account number : ";getline(cin,reciver);
		ifstream rec;
		reciver=reciver+".txt";									// the file
		rec.open(reciver.c_str());								
		if(rec)													// if statement - check whether the account number exist or not
		{
			check=true;
			rec.close();
		}
		else if(!rec)
		{
			cout<<"Receiver account number is invalid! \n";
			check=false;
		}
	}
	check=false;
	double amount;
	while(check!=true)											
	{
		cout<<"Enter amount for transfer : ";cin>>amount;
		if(amount>0)											// if statement - check whether the amount is more than RM0 or not
		{
			check=true;
		}	
	}
	ofstream Nfile;												// create new file
	ifstream file;												// read sender's old file
	file.open(sender.c_str());									// open sender file
	Nfile.open("temp.txt");										// open new file
	int n=0;													// n is number of line
	string str;
	while(getline(file,str))									
	{
		n++;
		if(n<4)
		{
			Nfile<<str<<endl;
		}
		else if(n==4)											// user's current balance
		{
			char *Newcash=new char[str.length()+1];
			strcpy(Newcash,str.c_str());
			newcasH=atoi(Newcash);
			delete Newcash;
			bool validamount=false;
			while(validamount!=true)
			{
				if(newcasH>amount)								// if statement - balance must be more than the amount to transfer
				{
					validamount=true;
					newcasH-=amount;							// calculate the balance after transfer
				}
				else 
				{
					cout<<"You do not have enough balance! \n";
				}
			}	
		Nfile<<newcasH;											// update the new balance
		}
	}
	file.close();
	Nfile.close();
	remove(sender.c_str());
	rename("temp.txt",sender.c_str());
			
	ifstream File;												// read the reciever's old file
	ofstream Rfile;												// create new file for reciever
				
	File.open(reciver.c_str());									// open file	
	Rfile.open("temp.txt");
	n=0;
	str="";
	while(getline(File,str))									// find the balance in file
	{
		n++;
		if(n<4)
		{
			Rfile<<str<<endl;
		}
		else if(n==4)											// user's current balance
		{
			char *oldcash=new char[str.length()+1];
			strcpy(oldcash,str.c_str());
			oldcasH=atoi(oldcash);
			Rfile<<oldcasH+amount;								// calculate & update new balance 
		}
	}
	File.close();
	Rfile.close();
	remove(reciver.c_str());
	rename("temp.txt",reciver.c_str());
	cout<<"RM "<<amount<<" is successfully transfered!\n";
}

// MAIN FUNCTION //
int main()		// Main Menu
{	
	int choice;
	
	cout << "\n          Dear user, Welcome to ATM Machine.\n\n"
	      
	     << "           0. Log out\n "
	     << "          1. Create a new bank account\n "
	     << "          2. Cash deposit\n "
	     << "          3. Cash withdrawal\n "
	     << "          4. Fund transfer\n"
	     << " \n"
	     << "          GROUP 7 COMPUTER FINAL PROJECT\n"
	     << " \n"
	     << "          Please enter a number with the according function: ";
	cin >> choice;
	
	 switch(choice)		// Switch statement 
     	{
     		case 0:	
     			cout << "Thank you, Please come again\n";
			    break;
		    case 1:		// Part A
				first ();	// Call the function
		    	break;
		    case 2:		// Part B
		    	second ();
		    	break;
			case 3:		// Part C
			    third ();
				break;
			case 4:		// Part D
			    forth ();
				break;			
    	}   
	return 0;	        
}
