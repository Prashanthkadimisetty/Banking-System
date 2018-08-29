#include<iostream>
#include<conio.h>
#include<fstream>
#include<String>
#include<iomanip>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<stdio.h>

char gch='a';
bool ret=true;

using namespace std;
class ACC
{
	public:
		 long long int accnum;
		 int pin;
  	private:
	char accname[50];
    int age;
    char type[20];
    char phno[10];
    char add[100];
    double bal;
    
    public:
    	void createAcc();
    	void debbal();
    	void credbal();
    	void display();
	  	void modify();
	  	void displaybal();
		/*void admindisplay(int); */ 	
};

/*void ACC::admindisplay(int x)
{
	cout<<"ACCOUNT no. "<<x<<endl;
	cout<<"ACCOUNT HOLDER NAME:"<<accname<<endl;
	cout<<"ACCOUNT NUMBER:"<<accnum<<endl;
	cout<<"AGE:"<<age<<endl;
	cout<<"ADDRESS:"<<add<<endl;
	cout<<"MOBILE NUMBER:"<<phno<<endl;
	cout<<"TYPE OF ACCOUNT:"<<type<<endl;
	cout<<"CURRENT BALANCE:"<<bal<<endl;
}*/

   
void account()
{
    ACC obj;
	obj.createAcc();
	ofstream outFile;
	outFile.open("AccountList.dat",ios::app|ios::binary);
	outFile.write((char*) (&obj), sizeof(ACC));
	outFile.close();	
}

 void search(int choice)
{
	try_again:
  long long int accno;
  system("cls");
  cout<<"\n\n\n\n\t\t\t\tPLEASE ENTER YOUR ACCOUNT NUMBER:";
  cin>>accno;
  fstream file_obj;
  ACC obj;
  int flag=0;
  int pos;
  file_obj.open("AccountList.dat",ios::in|ios::binary|ios::out);
  file_obj.read((char*)&obj, sizeof(obj));
   while (!file_obj.eof()) 
   {
   	    if(accno==obj.accnum)
   	    {
   	    	flag=1;
   	    	switch(choice)
   	    	{
   	    		case 1:
   	    			obj.debbal();
   	    			if(ret==true)
   	    			{
   	    			pos=(-1)*static_cast<int>(sizeof(ACC));
			        file_obj.seekp(pos,ios::cur);
		            file_obj.write(reinterpret_cast<char *> (&obj), sizeof(ACC));
		        }
   	    			break;
   	    		case 2:
   	    			obj.credbal();
   	    		    pos=(-1)*static_cast<int>(sizeof(ACC));
			        file_obj.seekp(pos,ios::cur);
		            file_obj.write(reinterpret_cast<char *> (&obj), sizeof(ACC));
   	    			break;
   	    		case 3:
   	    			obj.display();
   	    			break;
   	    		case 4:
   	    			obj.modify();
   	    			if(ret==true)
   	    			{
   	    			pos=(-1)*static_cast<int>(sizeof(ACC));
			        file_obj.seekp(pos,ios::cur);
		            file_obj.write(reinterpret_cast<char *> (&obj), sizeof(ACC));
		            }
   	    			break;
   	    		case 5:
   	    			obj.displaybal();
			   }
		   }
       file_obj.read((char*)&obj, sizeof(ACC));
    }   
    file_obj.close();
	if(flag==0)
	{
		char ch;
		cout<<"ACCOUNT NOT FOUND!!";
		cout<<"PRESS \"*\" to go to main menu"<<endl;
		cout<<"PRESS \"$\" try again"<<endl;
		ch=getch();
		if(ch=='$')
		{
		 goto try_again;
	    }
		else if(ch=='*')
		{
			file_obj.close();
			system("cls");
			gch='*';
		}
	}
	    char ch;
	    cout<<"\nPRESS \"*\" to go to main menu"<<endl;
	    ch=getch();
		if(ch=='*')
		{
			file_obj.close();
			system("cls");
			gch='*';
		}
}

 void ACC::createAcc()
 {
 	srand(time(NULL));
 	int op;
 	system("cls");
 	cout<<"*******************ACCOUNT CREATION PORTAL*******************";
 	cin.ignore();
 	cout<<"\nPLEASE ENTER YOUR NAME:";
 	cin.getline(accname,50);
 	cout<<"\nENTER YOUR ADDRESS:";
 	cin.getline(add,100);
 	option:
 cout<<"ENTER YOUR AGE:";
 	cin>>age;
 	cout<<"\t1.SAVINGS\n\t2.CURRENT\n";	
   cout<<"\nSELECT THE TYPE OF ACCOUNT WHCH YOU WANT TO CREATE:";
 	cin>>op;
 	switch(op)
 	{
 		case 1:
 			strcpy(type,"SAVINGS");
 			break;
 		case 2:
 			strcpy(type,"CURRENT");
 			break;
 	    default:
 	    	cout<<"\nINVALID OPTION";
 	    	goto option;
 	    	break;
    }
    cout<<"ENTER YOUR PHONE NUMBER:";
	cin>>phno;
	cout<<"ENTER YOUR SECRET PIN:";
	cin>>pin;
	cout<<"ENTER YOUR INITIAL BALANCE:";
	cin>>bal;
	accnum=1000000000+(rand()%9000000000);
	cout<<"YOUR UNIQUE ID IS:"<<accnum;
	char o;
	cout<<"PRESS ANY KEY TO EXIT";
	cout<<"\nPRESS \'*\' to go to main menu;";
	o=getch();
	if(o=='*')
	{
		gch='*';
	}
}

void ACC::credbal()
{
	double money;
	cout<<"ENTER THE AMOUNT WHICH YOU WANT TO CREDIT:";
	cin>>money;
	bal=bal+money;
	cout<<"\nBALANCE UPDATED......";
	cout<<"REMAINING BALANCE="<<bal;
	Sleep(5000);
	
}

void ACC::debbal()
{
	int trypin;
	cout<<"ENTER YOUR SECRET PIN:";
	cin>>trypin;
	if(trypin!=pin)
	{
		ret=false;
		cout<<"YOU HAVE ENTERED WRONG PIN";
    	cout<<"\nYou will be redirected to mainmenu in 5 seconds..";
    	Sleep(5000);
    	return;
	}
	double money;
	cout<<"ENTER THE AMOUNT WHICH YOU WANT TO DEBIT:";
	cin>>money;
	bal=bal-money;
	cout<<"\nBALANCE UPDATED......";
	cout<<"REMAINING BALANCE="<<bal;
	
}

/*void admin()
{
	int f=1,i=0;
	int count=0;
	char y;
	system("cls");
	cout<<"\n\n\n\n\n\n\n\n\t\t\t********************ADMIN LOGIN*************************";
	tryagain:
	char temp[21];
	char pass[20];
	char check[20];
	cout<<"\n\t\t\t\tPASSWORD:";
	for(i=0;i<21;i++)               //PAssWOrd Store and check it
	{
		temp[i]=getch();
		if(temp[i]=='\b')
		{
			cout<<"\b";
			cout<<" ";
			cout<<"\b";
			i--;
			continue;
		}
		if(temp[i]==13)
		{
		temp[i]='\0';
		break;
	    }
		cout<<"*";
	}
	strcpy(pass,temp);
	ifstream fp;
	fp.open("PASSWORD.txt",ios::in);
    fp>>check;
	if(strcmp(pass,check)==0)
	goto mainmenu1;
	else
	{
	 f=0;
	 count++; //COunt No. of TImes user enters Wrong Password
    }
    
	if(f==0)
	{
		cout<<"\n\t\t\t\tWRONG PASSWORD ENTERED!!";
		cout<<"\n\t\t\t\t%d Trails left:"<<(3-count);
		if(count<3)   //Allow the user to try for only 3 trails
		{
			goto tryagain;
		}
		else{
			cout<<"\n\t\t\t\tSORRY PLEASE TRY AGAIN....";
			Sleep(2000);                             
			gch='*';                              
	    	goto doom;  //Return the user to the main menu if he fail	                             // to enter password within 3 trails
		}
	    
	}
	fp.close();
	 mainmenu1:
   char c;
   ifstream adm;
   system("cls");
   adm.open("adminmenu.txt",ios::in);
   adm.seekg(0);
   while(!adm.eof())
   {
   	   adm.get(c);
   	   cout<<c;
   }
   adm.close();
   cout<<"Select Your Choice:";
   c=getch();
   switch(c)
   {
   	   case '1':
   	   	       remove("AccountList.dat");
   	   	       break;
   	   case '2':
   	   	{
			  
   	   	    char tem[11];
			char pass1[10];
			char pass2[10];
			ofstream t3;
			tent3:
			system("cls");
		    cout<<"\n\n\n\n\n\n\t\t\t\tENTER NEW PASSWORD:";
		    for(i=0;i<11;i++)
         	{
		    tem[i]=getch();
		    if(tem[i]=='\b')
		     {
			 cout<<"\b";
			 cout<<" ";
			 cout<<"\b";
			 i--;
			 continue;
		     }
		    if(tem[i]==13)
		     {
		      tem[i]='\0';
		      break;
	         }
	        cout<<"*";
	        }
	        strcpy(pass1,tem);  
			cout<<"\n\t\t\t\tCONFIRM NEW PASSWORD:"; 
			 for(i=0;i<11;i++)
         	{
		    tem[i]=getch();
		    if(tem[i]=='\b')
		     {
			 cout<<"\b";
			 cout<<" ";
			 cout<<"\b";
			 i--;
			 continue;
		     }
		    if(tem[i]==13)
		     {
		      tem[i]='\0';
		      break;
	         }
	        cout<<"*";
	        }
	        strcpy(pass2,tem); 
        	if(strcmp(pass1,pass2)==0)
        	{
        		t3.open("PASSWORD.txt",ios::out);
        		t3<<pass2;
        		t3.close();
        		cout<<"\n\t\t\t\tPASSWORD CHANGED SUCCESSFULLY!!";
        		cout<<"\nPress any key for main menu.....";
        		y=getch();
        		goto mainmenu1;
        		
			}
			else
			{
				cout<<"\n\n\t\t\t\tPASSWORDS DID NOT MATCH";
				Sleep(3000);
				cout<<"\n\t\t\t\tPress '*' to go to TRYAGAIN,Press any other key for mainmenu....";
				y=getch();
				if(y=='*')
				 goto tent3;
				else
				 goto mainmenu1;
		}
			break;
		}
		case '3':
			{
			system("cls");
	    	printf("\n\n\n\n\n\n\n\n\n\t\t\t\tLOGGING OUT......");
	    	Sleep(5000);
	    	gch='*';
	    	goto doom;
	    	break;
	        }
	    case '4':
	    	{
			ifstream  detail;
	    	int i=1;
	    	ACC tem;
	    	detail.open("AccountList.dat",ios::in|ios::binary);
	    	detail.read((char*)&tem,sizeof(tem));
	    	while(!detail.eof())
	    	{
	    		tem.admindisplay(i);
	    		i++;
	    		
			}
			detail.close();
			break;
		   } 
		default:
			break;
   }
	doom:
		char doop;
		doop=' ';
		cout<<doop;
}*/

void ACC::modify()
{
	int trypin;
	cout<<"PLEASE ENTER YOUR PIN:";
	cin>>trypin;
	if(trypin!=pin)
    {
    	ret=false;
    	cout<<"YOU HAVE ENTERED WRONG PIN";
    	cout<<"\nYou will be redirected to mainmenu in 5 seconds..";
    	Sleep(5000);
    	
    	return;
	}
	char op;
     ifstream modinfile;
     char c;
     modinfile.open("modifymenu.txt",ios::in);
     modinfile.seekg(0);
     while(!modinfile.eof())
     {
   	   modinfile.get(c);
   	   cout<<c;
     }
     modinfile.close();
     try1:
     cout<<"\n\t\t\t\tSELECT  WHAT YOU WANT TO MODIFY IN YOUR ACCOUNT:";
     op=getche();
     fflush(stdin);
     switch(op)
     {
     	case '1':
     		  cout<<"THIS IS YOUR OLD ADDRESS:"<<add;
     		  cout<<"\nENTER YOUR NEW ADDRESS:";
     		  cin.getline(add,100);
     		  break;
     	case '2':
     		  cout<<"THIS IS YOUR OLD PHONE NUMBER"<<phno;
     		  cout<<"\nENTER YOUR NEW PHONE NUMBER:";
     		  cin>>phno;
     		  break;
     	case '3':
     	      cout<<"THIS IS YOUR NAME:"<<accname;
     	      cout<<"\n ENTER NEW NAME:";
     	      cin.getline(accname,50);
     	      break;
        case '4':
               cout<<"THIS IS YOUR PIN:"<<pin;
     	      cout<<"\n ENTER NEW PIN:";
     	      cin>>pin;
     	      break;
        default:
        	cout<<"\nINVALID OPTION";
        	goto try1;
	  } 
	  cout<<"RECORD UPDATED....";
	 	
}

void ACC::display()
{
	cout<<"\nACCOUNT HOLDER NAME:"<<accname;
	cout<<"\nACCOUNT NUMBER:"<<accnum;
	cout<<"\nADDRESS:"<<add;
	cout<<"\nPHONE NUMBER:"<<phno;
	cout<<"\nAGE:"<<age;
	cout<<"\nACCOUNT TYPE:"<<type;
}
void ACC::displaybal()
{
	system("cls");
	cout<<"YOUR ACCOUNT BALANCE IS:"<<bal;
}

int main()
{
   int op;
   ifstream ost("bank.txt");
    char weltext;
    if(ost.is_open())
    {
	   while(!ost.eof())
       {
           ost.get(weltext);
           cout << weltext;
        }
    }
    ost.close();
     system("COLOR 01");          //TO cReate a colour changing welcome to the user
    Sleep(800);
    system("COLOR 02");
    Sleep(800);
    system("COLOR 0D");
    Sleep(800);
    system("COLOR 0C");
    Sleep(800);
    system("COLOR 0A");
    Sleep(800);
    system("COLOR 03");
    Sleep(2000);
    system("cls");
   ifstream infile;
   char c;
   mainmenu:
   system("cls");
   infile.open("mainmenu.txt",ios::in);
   infile.seekg(0);
   while(!infile.eof())
   {
   	   infile.get(c);
   	   cout<<c;
   }
   infile.close();
   tryagain:
   cout<<"\nSelect your option:"<<endl;
   cin>>op;
   switch(op)
   {
   	   case 1:
   	    	   account();
   	    	   break;
   	   case 2:
   	   	       search(1);//debit
   	    	   break;
   	   case 3:
   	   	       search(2);//credit
   	   	       break;
   	   case 4:
   	   	       search(3);//display
   	   	       break;
   	   case 5:
   	   	       search(4);//modify
   	   	       break;
   	   case 6:
   	   	       search(5);//displaybal
   	   	       break;
   	  /*case 7:
   	   	      admin();//admin
   	   	      break;*/
   	   case 7:
   	   	      system("cls");
   	   	      cout<<"THANKS FOR USING CALCULATOR";
   	   	      exit(0);
   	   	      break;
   	   default:
   	   	   cout<<"\n\nINVALID OPTION:";
   	   	   goto tryagain;
   	   	   break;
	 }  
	 if(gch=='*')
	 {  
	    gch='a';
	 	goto mainmenu;
	 }
	 else if(gch=='$')
	 {
	 	exit(0);
	 }
	 
}
