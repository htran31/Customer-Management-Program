#include <iostream>
#include<stdio.h>
#include <string.h>
#include<conio.h>
#include <ctime>
#include<cmath>
#define MAX 1000                              
using namespace std;


struct Customer{
	int id;
	char name[30];
	int day, month;
	char slash;
	char phoneNum[10];
	int numVisit;
	char vipLevel[10];
	char appt[5];
	char service[10];
};

typedef Customer CUST;

int idMaximum(CUST a[], int n);
void signUp(CUST a[], int id, int n);
void enterInfo(CUST &cust, int id);

void checkBirthday(CUST &cust);
void updateVIP(CUST &cust);
void updateService(CUST &cust);
void showCustomer(CUST a[], int n);

void checkIn(CUST a[], char phoneNum[], int n);
void updateInfo(CUST &cust, int n);

void searchName(CUST a[], char name[], int n);
void searchPhoneNum(CUST a[], char phoneNum[], int n);
void searchMonth(CUST a[], int search, int n);
void sortDay(CUST a[], int n);
void sortName(CUST a[], int n);
void sortNumVisit(CUST a[], int n);

int readFile(CUST a[], char fileName[]);
void writeFile(CUST a[], int n, char fileName[]);
void printHeart();
void printLine(int n);
void pressAnyKey();



int main(){
	int option;
	int numCUST = 0;
	int idCount = 0;
	char fileName[] = "customer_record.txt";
	CUST arrayCUST[MAX];

	//import customer list from readFile
	numCUST = readFile(arrayCUST, fileName);
	idCount = idMaximum(arrayCUST, numCUST);

	while(true){
		cout << "________________________________________________\n";
		cout << "|          Customer Management Program         |\n";
		cout << "|                - ROSE NAILS -                |\n";
		cout << "|                                              |\n";
		cout << "|---Customer-----------------------------------|\n";
		cout << "|            1. Sign-up (first time)           |\n";
		cout << "|            2. Check-in                       |\n";
		cout << "|                                              |\n";
		cout << "|---Manager------------------------------------|\n";
		cout << "|            3. Show Customer Record           |\n";
		cout << "|            4. Search Info by Name            |\n";
		cout << "|            5. Search Info by Phone Number    |\n";
		cout << "|            6. Search Info by D.O.B           |\n";
		cout << "|            7. Sort Info by Name              |\n";
		cout << "|            8. Sort Info by Number of Visits  |\n";
		cout << "|            9. Exit                           |\n";
		cout << "|______________________________________________|\n";
		cout << "Enter an option: ";
		cin >> option;

		switch(option){
			case 1:
				printLine(60);
				cout << "\n\tWelcome to ROSE NAILS Salon !!!";
				printLine(60);
				idCount++;
				signUp(arrayCUST, idCount, numCUST);
				numCUST++;
				if(numCUST > 0){
                    writeFile(arrayCUST, numCUST, fileName);
                }else{
                    cout << "\nCustomer List is empty now!";
                }
                printf("\nSaved Info Successfully!", fileName);
				pressAnyKey();
				break;
			case 2:
				printLine(60);
				cout << "\n\tWelcome to ROSE NAILS Salon !!!";
				printLine(60);
				if (numCUST > 0){
					char strname[30];
					char strPhoneNum[10];
					cout << "\nCHECK-IN: ";
					cout << "\n > Your first name: "; 
					fflush(stdin); 
					gets(strname);
					cout << " > Phone Number: "; 
					fflush(stdin); 
					gets(strPhoneNum);
                    checkIn(arrayCUST, strPhoneNum, numCUST);
                    writeFile(arrayCUST, numCUST, fileName);
                }else{
                    cout << "\nCustomer List is empty now!";
                }
                printf("\nSaved Info Successfully!", fileName);
                pressAnyKey();
                break;
			case 3:
				if (numCUST > 0){
					cout << "\nCustomer Record:";
					showCustomer(arrayCUST, numCUST);
				}else{
					cout << "\nCustomer List is empty now!";
				}
				pressAnyKey();
				break;
			case 4:
				cout << "\nSEARCH INFO BY NAME: ";
				if (numCUST > 0){                 
                    char strName[30];
                    cout << "\nEnter a first name to search: "; 
                    fflush(stdin); 
                    gets(strName);
                    searchName(arrayCUST, strName, numCUST);
                }else{
                    cout << "\nCustomer List is empty now!";
                }
                pressAnyKey();
                break;
            case 5:
            	cout << "\nSEARCH INFO BY PHONE NUMBER: ";
				if (numCUST > 0){                 
                    char strPhoneNum[10];
                    cout << "\nEnter a phone number to search: "; 
                    fflush(stdin); 
                    gets(strPhoneNum);
                    searchPhoneNum(arrayCUST, strPhoneNum, numCUST);
                }else{
                    cout << "\nCustomer List is empty now!";
                }
                pressAnyKey();
                break;
            case 6:
            	cout << "\nSEARCH INFO BY DATE OF BIRTH: ";
            	int search;
            	cout << "\nEnter the month to search: "; 
                    cin >> search;
            	if (numCUST > 0){
					searchMonth(arrayCUST, search, numCUST);       
                }else{
                    cout << "\nCustomer List is empty now!";
                }
                pressAnyKey();
                break;
            case 7:
            	cout << "\nSORT INFO BY NAME: ";
            	if (numCUST > 0){ 
                    sortName(arrayCUST, numCUST);
                    showCustomer(arrayCUST, numCUST);
                } else {
                    cout << "\nCustomer List is empty now!";
                }
                pressAnyKey();
                break;
            case 8:
            	cout << "\nSORT INFO BY NUMBER OF VISITS: ";
            	if (numCUST > 0){                    
                    sortNumVisit(arrayCUST, numCUST);
                    showCustomer(arrayCUST, numCUST);
                }else{
                    cout << "\nCustomer List is empty now!";
                }
                pressAnyKey();
                break;
            case 9:
                cout << "\nExit the program...";
                getch();
                return 0;
            default:
                cout << "\nSorry, this function is not available!";
                cout << "\nTRY AGAIN !!";
                pressAnyKey();
                break;
		}
	}
}



int idMaximum(CUST a[], int n){
    int idMax = 0;
    if (n > 0){
        idMax = a[0].id;
        for (int i = 0; i < n; i++){
            if (a[i].id > idMax){
                idMax = a[i].id;
            }
        }
    }
    return idMax;
}

void signUp(CUST a[], int id, int n){
    printf("\nSIGN UP at id = %d:", n + 1);
    enterInfo(a[n], id);
}

void enterInfo(CUST &cust, int id){
    cout << "\n > Your First Name: "; 
	fflush(stdin); 
	gets(cust.name);
    cout << " > Phone Number: "; 
	cin >> cust.phoneNum;
    cout << " > Date Of Birth (MM/DD): ";
    cin >> cust.month >> cust.slash >> cust.day;

    cust.id = id;
    cust.numVisit = 1;
    checkBirthday(cust);
    updateVIP(cust);
    updateService(cust);
    
    printLine(60);
    printf("\n\tThank You Very Much, %s!", cust.name);
    printLine(60);
}

void checkBirthday(CUST &cust){
 	time_t now = time(0);
    tm *ltm = localtime(&now);
   
  	int dayMax;
    int year = 1900 + ltm->tm_year;
    char slash; 
    
    if (year<0 || cust.month<0 || cust.month>12 || cust.day<0 || cust.day>31){
        cout << "Sorry, Invalid date!";
    }else{
        switch(cust.month){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
              	dayMax=31;
              	break;
            case 2:
                if ((year%4==0 && year%100!=0) || (year%400==0))
                    dayMax=29;
                else 
                    dayMax=28;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                dayMax=30;
                break;
        }
    }
    if (cust.day==ltm->tm_mday && cust.month==1+ltm->tm_mon){
    	printHeart();
	}
}

void updateVIP(CUST &cust){
	if(cust.numVisit >= 20) strcpy(cust.vipLevel, "A");
    else if(cust.numVisit >= 10) strcpy(cust.vipLevel, "B");
    else if(cust.numVisit >= 2) strcpy(cust.vipLevel, "C");
    else strcpy(cust.vipLevel, "new");
}

void showCustomer(CUST a[], int n){
    printLine(100);
    cout <<"\nID\tFirstName\tPhoneNumber\tD.O.B\tAppointment\tService\t\tNumberOfVisits\tVIP";
    printLine(100);
    for(int i = 0; i < n; i++){
        printf("\n %d", a[i].id);
        printf("\t%s", a[i].name);
        printf("\t\t%s", a[i].phoneNum);
        printf("\t%d%s%d", a[i].month, "/", a[i].day);
        printf("\t%s", a[i].appt);
        printf("\t\t%s", a[i].service);
        printf("\t\t%d", a[i].numVisit);
        printf("\t%s", a[i].vipLevel);
    }
    printLine(100);
}

void checkIn(CUST a[], char phoneNum[], int n){
    int found = 0;
    char name[30];
    char phoneCUST[10];
    for(int i = 0; i < n; i++){
    	strcpy(phoneCUST, a[i].phoneNum);
        if(strstr(strupr(phoneCUST), strupr(phoneNum))) {
            found++;
            updateInfo(a[i], found);
            break;
        }
    }
    if (found == 0) {
        printf("\nThis account does not exist!");
        printf("\nPlease try to Sign Up instead!\n");
    }
}

void updateInfo(CUST &cust, int n){
    for (int i = 0; i < n; i++){
    	cust.numVisit = cust.numVisit + n;
    	updateVIP(cust);
    	updateService(cust);
    	checkBirthday(cust);
	}
	printLine(60);
    printf("\n\tWelcome back, %s!", cust.name);
    printLine(60);
}
			
void updateService(CUST &cust){
	int n;
	cout << " > Do you have appointment? ";
	cin >> cust.appt;
	
    cout << "\n_________________________________________\n";
	cout << "|.............Service Menu..............|\n";
	cout << "|                                       |\n";
	cout << "|  Manicure:   1. Regular_________$20   |\n";
	cout << "|              2. Gel_____________$35   |\n";
	cout << "|              3. Dip Powder______$45   |\n";
	cout << "|              4. Acrylic_________$40+  |\n";
	cout << "|                                       |\n";
	cout << "|  Pedicure:   5. Regular_________$30   |\n";
	cout << "|              6. Gel_____________$45   |\n";
	cout << "|              7. Deluxe__________$50   |\n";
	cout << "|_______________________________________|\n";
	cout << "Enter your service: ";
	cin >> n;
	
	if(n == 1) strcpy(cust.service, "Reg-Mani");
    else if(n == 2) strcpy(cust.service, "Gel-Mani");
    else if(n == 3) strcpy(cust.service, "Dip-Mani");
    else if(n == 4) strcpy(cust.service, "Acrylic-Nail");
    else if(n == 5) strcpy(cust.service, "Reg-Pedi");
    else if(n == 6) strcpy(cust.service, "Gel-Pedi");
    else strcpy(cust.service, "Deluxe-Pedi");
    cout << " > Your Service today: " << cust.service << "\n";
}
				
void searchName(CUST a[], char name[], int n){
    CUST arrayFound[MAX];
    char nameCUST[30];
    int found = 0;
    for(int i = 0; i < n; i++){
        strcpy(nameCUST, a[i].name);
        if(strstr(strupr(nameCUST), strupr(name))) {
            arrayFound[found] = a[i];
            found++;
        }
    }
    showCustomer(arrayFound, found);
}

void searchPhoneNum(CUST a[], char phoneNum[], int n){
    CUST arrayFound[MAX];
    char phoneCUST[10];
    int found = 0;
    for(int i = 0; i < n; i++){
        strcpy(phoneCUST, a[i].phoneNum);
        if(strstr(strupr(phoneCUST), strupr(phoneNum))) {
            arrayFound[found] = a[i];
            found++;
        }
    }
    showCustomer(arrayFound, found);
}

void searchMonth(CUST a[], int search, int n){
	int found = 0;
	CUST arrayFound[MAX];
	for(int i = 0; i < n; i++){
        if (a[i].month == search) {
        	arrayFound[found] = a[i];
            found++;
        }
    }
    sortDay(arrayFound, found);
    showCustomer(arrayFound, found);
}

void sortDay(CUST a[], int n){
	CUST tmp;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++) {
            if(a[i].day > a[j].day) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void sortName(CUST a[], int n){
    // sort customer's names in ascending order A > Z
    CUST tmp;
    char nameCUST1[30];
    char nameCUST2[30];
    for(int i = 0; i < n; i++){
        strcpy(nameCUST1, a[i].name);
        for(int j = i+1; j < n; j++) {
            strcpy(nameCUST2, a[j].name);
            if(strcmp(strupr(nameCUST1), strupr(nameCUST2)) > 0) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void sortNumVisit(CUST a[], int n){ 
    // sort in descending order
    CUST tmp;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(a[i].numVisit < a[j].numVisit) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

int readFile(CUST a[], char fileName[]){
    FILE * fp;
    int i = 0;
    fp = fopen (fileName, "r");
    cout << "Read customer information from "; puts(fileName);
    // read information of customer
    while (fscanf(fp, "%5d%20s%20s%10d/%d%20s%10s%10d%10s\n", &a[i].id, &a[i].name, 
            &a[i].phoneNum,  &a[i].month, &a[i].day, &a[i].service, &a[i].appt,
			&a[i].numVisit, &a[i].vipLevel) != EOF) {
       	i++;
    }
    cout << "The number of customers on the list is: " << i << endl;
    cout << endl;
    fclose (fp);
    // return the number of customers read from file
    return i;
}
 
void writeFile(CUST a[], int n, char fileName[]){
    FILE * fp;
    fp = fopen (fileName,"w");
    for(int i = 0; i < n; i++){
        fprintf(fp, "%5d%20s%20s%10d/%d%20s%10s%10d%10s\n", a[i].id, a[i].name,
            a[i].phoneNum, a[i].month, a[i].day, a[i].service, a[i].appt,
			a[i].numVisit, a[i].vipLevel);
    }
    fclose (fp);
}

void printHeart(){
	double x, y, size=10;
	char ch='.';
	string message(" Happy Birthday ");
	int print_line = 4;
	
	if(message.length() % 2 != 0)
		message += " ";
		for(x=0;x<size;x++){
			for(y=0;y<=4*size;y++){
				double dist1 = sqrt( pow(x-size,2) + pow(y-size,2) );
				double dist2 = sqrt( pow(x-size,2) + pow(y-3*size,2) );
				if (dist1 < size + 0.5 || dist2 < size + 0.5 ) {
					cout<< ch;
				}
				else
					cout<< " ";
			}
			cout<<"\n";
		}
		for(x=1;x<2*size;x++){
			for(y=0;y<x;y++)
				cout << " ";
				for (y=0;y<4*size + 1 - 2*x; y++){
					if (x>= print_line - 1 && x <= print_line + 1) {
						int idx = y - (4*size - 2*x - message.length()) / 2;
						if(idx < message.length() && idx >= 0) {
							if (x == print_line)
								cout<<message[idx];
							else cout << " ";
						}
						else
							cout << ch;
						}
					else
						cout<< ch;
				}
				cout<<endl;
		}
}

void printLine(int n){
    cout << endl;
    for (int i = 0; i < n; i++){
        cout << "_";
    }
    cout << endl;
}
 
void pressAnyKey(){
    cout << "\nPress any key to continue...";
    getch();
    system("cls");
}


