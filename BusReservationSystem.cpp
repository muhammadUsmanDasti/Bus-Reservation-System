#include<iostream>
#include<fstream>
#include<conio.h>   //for getch()
#include<iomanip>   //for setw()
#include<sstream>  //for string stream
#include<windows.h>
using namespace std;
void mainMenu();
void adminLogin(bool &flag1);
void adminPanel(int &check1);
void addNewBus();
void printHeader(string title);
void viewBuses();
void viewBooking();
void removeBus();
void customerLogin(bool &flag2);
void customerSignup();
void customerPanel(int &check2);
void seatBooking();
void viewMyBooking();
void cancelBooking();
void stopBeforeMove(string panel);
void seatUpdate(string busNumber,int change);
int convertToMinutes(string departureTime);
void sortBusesByTime();
void setColor(int colorCode){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,colorCode);
}



int main(){
    bool flag=true;        //controls main loop
    bool flag1=false;      //controls admin panel loop
    bool flag2=false;      //controls cutomer panel loop
    int check;             //main menu selector
    int check1;            //admin panel selector
    int check2;            //Customer panel selectors
    while(flag){
        printHeader("BUS RESERVATION SYSTEM");
        mainMenu();
        cin>>check;
        cin.ignore();
        if(check==1){
            printHeader("ADMIN LOGIN");
            adminLogin(flag1);
            while(flag1==true){
                sortBusesByTime();
                printHeader("ADMIN PANEL");
                adminPanel(check1);
                if(check1==1){
                    printHeader("ADD NEW BUS");
                    addNewBus();
                }
                else if(check1==2){
                    printHeader("BUSES LIST");
                    viewBuses();
                    stopBeforeMove("Admin Panel");
                }
                else if(check1==3){
                    printHeader("BOOKING RECORDS");
                    viewBooking();
                }
                else if(check1==4){
                    printHeader("REMOVE BUS");
                    removeBus();
                }
                else if(check1==5){
                    flag1=false;
                }
            }
            
    
        }
        else if(check==2){
            printHeader("CUSTOMER LOGIN");
            customerLogin(flag2);
            while(flag2){
                sortBusesByTime();
                printHeader("CUSTOMER PANEL");
                customerPanel(check2);
                if(check2==1){
                    printHeader("BUSES LIST");
                    viewBuses();
                    stopBeforeMove("Customer Panel");
                }
                else if(check2==2){
                    printHeader("BOOK A SEAT");
                    seatBooking();
                }
                else if(check2==3){
                    printHeader("CANCEL BOOKING");
                    cancelBooking();
                }
                else if(check2==4){
                    printHeader("MY BOOKINGS");
                    viewMyBooking();
                }
                else if(check2==5){
                    flag2=false;

                }
                
            }
        }
        else if(check==3){
            printHeader("CUSTOMER SIGNUP");
            customerSignup();
        }
        else if(check==4){
            printHeader("THANK YOU FOR USING OUR SYSTEM");
            flag=false;
        }
        else{
            cout<<"Invalid option, Try again"<<endl;
        }
        
    }

}
//to print section headers
void printHeader(string title){
    setColor(11);
    cout<<"##-----------------------------------------------------------------------------------##"<<endl;
	cout<<"##-----------------------------------------------------------------------------------##"<<endl;
	cout<<"##                                                                                   ##"<<endl;
	cout<<"##"<<setw(46)<<right<<title<<" "<<setw(36)<<" "<<"##"<<endl;
	cout<<"##                                                                                   ##"<<endl;
	cout<<"##-----------------------------------------------------------------------------------##"<<endl;
	cout<<"##-----------------------------------------------------------------------------------##"<<endl;
	cout<<endl;
    setColor(7);
}
//Displays the main menu
void mainMenu(){
    setColor(13);
    cout<<"1.Admin Login"<<endl;
    cout<<"2.Customer Login"<<endl;
    cout<<"3.Customer Signup"<<endl;
    cout<<"4.Exit"<<endl;
    cout<<endl;
    setColor(14);
    cout<<"Enter your Choice: ";
    setColor(7);
}
//for taking admin login info and checking from text file 'adminlogin.txt
void adminLogin(bool &flag1){
    setColor(10);
    string username,password;
    cout<<"Enter Username: ";
    getline(cin,username);
    cout<<"Enter Password: ";
    getline(cin,password);
    setColor(7);
    fstream newfile;
    newfile.open("adminlogin.txt",ios::in);
    string data;
    while(getline(newfile,data)){
        if(data==username+","+password){
            flag1=true;
            break;
            
        }

    }
    newfile.close();
    if(flag1){
        setColor(10);
        cout<<"You have successfully Login"<<endl;
        setColor(7);
        cout<<"Press any key to move to Admin Panel"<<endl;
        getch();
    }
    else{
        setColor(12);
        cout<<"Incorrect UserName or Password"<<endl;
        setColor(7);
        cout<<"Press any key to move to Admin Panel"<<endl;
        getch();
    }
    
}
//display admin panel options
void adminPanel(int &check1){
    setColor(13);
    cout<<"1.Add new bus"<<endl;
    cout<<"2.View all buses"<<endl;
    cout<<"3.View all bookings"<<endl;
    cout<<"4.Remove Bus"<<endl;
    cout<<"5.Back to Main menu"<<endl;
    cout<<endl;
    setColor(14);
    cout<<"Enter your choice: ";
    cin>>check1;
    setColor(7);
    cin.ignore();
}
//adds a new bus entry to the file
void addNewBus(){
    int busNumber,seats,availableSeats;
    string busName,departureCity,destinationCity;
    string departureTime;
    bool alreadyPresent=false;
    setColor(10);
    cout<<"Enter Bus number: ";
    setColor(7);
    cin>>busNumber;
    cin.ignore();
    string line;
    //check if bus already exists
    fstream newfile;
    newfile.open("busesDetails.txt",ios::in);
    while(getline(newfile,line)){
        stringstream ss(line);
        string tempBusNo,tempBusName,from,to,time,tempSeats,tempAvailableSeats;
        getline(ss,tempBusNo,',');
        getline(ss,tempBusName,',');
        getline(ss,from,',');
        getline(ss,to,',');
        getline(ss,time,',');
        getline(ss,tempSeats,',');
        getline(ss,tempAvailableSeats);
        int busNo=stoi(tempBusNo);
        if(busNo==busNumber){
            alreadyPresent=true;
        }
    }
    newfile.close();
    if(alreadyPresent){
        setColor(12);
        cout<<"This bus number Already exists, try Again"<<endl;
        stopBeforeMove("Admin Panel");
        setColor(7);
        return;
    }
    if(!alreadyPresent){
        setColor(10);
        cout<<"Enter Bus name: ";
        getline(cin,busName);
        cout<<"Enter Departure city: ";
        getline(cin,departureCity);
        cout<<"Enter Destination city: ";
        getline(cin,destinationCity);
        cout<<"Enter Departure time: ";
        getline(cin,departureTime);
        cout<<"Enter total seats: ";
        cin>>seats;
        cout<<"Enter Available Seats: ";
        cin>>availableSeats;
        setColor(7);
        cin.ignore();
        cout<<endl;
        fstream newfile;
        newfile.open("busesDetails.txt",ios::app);
        newfile<<busNumber<<","<<busName<<","<<departureCity<<","<<destinationCity<<","<<departureTime<<","<<seats<<","<<availableSeats<<endl;
        newfile.close();
        setColor(14);
        cout<<"[*] Bus added successfully!"<<endl;
        cout<<endl;
        setColor(7);
    }
    
    stopBeforeMove("Admin panel");
}
//displays all busses details
void viewBuses(){
    cout<<left<<"|"<<setw(7)<<"Bus No."<<"|"<<setw(14)<<"Bus name"<<"|"<<setw(10)<<"From"<<"|"<<setw(11)<<"To"<<"|"<<setw(12)<<"Time"<<"|"<<setw(5)<<"seats"<<"|"<<setw(15)<<"Available seats"<<"|"<<endl;
    cout<<string(83,'-')<<endl;
    string line;
    fstream newfile;
    setColor(1);
    newfile.open("busesDetails.txt",ios::in);
    while(getline(newfile,line)){
        stringstream ss(line);
        string busNo,busName,from,to,time,seats,availableSeats;
        getline(ss,busNo,',');
        getline(ss,busName,',');
        getline(ss,from,',');
        getline(ss,to,',');
        getline(ss,time,',');
        getline(ss,seats,',');
        getline(ss,availableSeats);
        cout<<left<<"|"<<setw(7)<<busNo<<"|"<<setw(14)<<busName<<"|"<<setw(10)<<from<<"|"<<setw(11)<<to<<"|"<<setw(12)<<time<<"|"<<setw(5)<<seats<<"|"<<setw(15)<<availableSeats<<"|"<<endl;
    }
    newfile.close();
    cout<<endl;
    setColor(7);

}
//displays all booking records
void viewBooking(){
    cout<<left<<"|"<<setw(10)<<"Bus Number"<<"|"<<setw(15)<<"Customer Name"<<"|"<<setw(13)<<"CNIC"<<"|"<<setw(5)<<"Seats"<<"|"<<setw(10)<<"Ticket ID"<<"|"<<endl;
    cout<<string(60,'-')<<endl;
    fstream newfile;
    newfile.open("bookingRecord.txt",ios::in);
    if(!newfile.is_open()){
        setColor(12);
        cout<<"Error file not Found"<<endl;
        setColor(7);
        return;
    }
    string line;
    setColor(1);
    while(getline(newfile,line)){
        stringstream ss(line);
        string busNo,customerName,CNIC,seats,ticketId;
        getline(ss,busNo,',');
        getline(ss,customerName,',');
        getline(ss,CNIC,',');
        getline(ss,seats,',');
        getline(ss,ticketId);
        cout<<left<<"|"<<setw(10)<<busNo<<"|"<<setw(15)<<customerName<<"|"<<setw(13)<<CNIC<<"|"<<setw(5)<<seats<<"|"<<setw(10)<<ticketId<<"|"<<endl;
    }
    setColor(7);
    newfile.close();
    stopBeforeMove("Admin panel");
}
//removes a specific bus based on the bus number
void removeBus(){
    viewBuses();      //displays buses details for reference
    string busNumber;
    setColor(10);
    cout<<"Enter Bus Number to Remove: ";
    getline(cin,busNumber);
    setColor(7);
    bool found=false;
    fstream temp; 
    fstream newfile;
    string line="";
    newfile.open("busesDetails.txt",ios::in);
    if(!newfile.is_open()){
        setColor(12);
        cout<<"Error file not Found"<<endl;
        setColor(7);
        return;
    }
    temp.open("temporary.txt",ios::out);
    while(getline(newfile,line)){
        stringstream ss(line);
        string busNo,name,from,to,time,seats;
        getline(ss,busNo,',');
        getline(ss,name,',');
        getline(ss,from,',');
        getline(ss,to,',');
        getline(ss,time,',');
        getline(ss,seats,',');
        if(busNo==busNumber){
            found=true;
            continue;   //skip this line to remove it
        }
        temp<<line<<endl;
    }
    newfile.close();
    temp.close();
    remove("busesDetails.txt");
    rename("temporary.txt","busesDetails.txt");
    if(found){
        setColor(14);
        cout<<"Bus removed successfully!"<<endl;
        setColor(7);

    }
    else{
        setColor(12);
        cout<<"Bus number not found"<<endl;
        setColor(7);
    }
    stopBeforeMove("Admin panel");
}
//for customer login
void customerLogin(bool &flag2){
    string name,password;
    setColor(10);
	cout<<"Enter the Name: ";
	getline(cin,name);
	cout<<"Enter the Password: ";
	getline(cin,password);
    setColor(7);
	fstream newfile;
	newfile.open("signUpData.txt",ios::in);
	string data;
	while(getline(newfile,data)){
		if(data==name+","+password){
            setColor(14);
			cout<<"You have successfully Sign In"<<endl;
            setColor(7);
			flag2=true;
            cout<<"Press any key to move towards Customer Panel"<<endl;
            getch();

			return;
		}
	}
    setColor(12);
    cout<<"Wrong your name or password"<<endl;
    setColor(7);
	newfile.close();
    stopBeforeMove("Main menu");
}
// for newcustomer signup and stores data in signup.txt
void customerSignup(){
    setColor(10);
    string name,password;
	cout<<"Enter the Name: ";
	getline(cin,name);
	cout<<"Enter the Password: ";
	getline(cin,password);
    setColor(7);
	fstream newfile;
	newfile.open("signUpData.txt",ios::app);
	newfile<<name<<","<<password<<endl;
	newfile.close();
    setColor(14);
    cout<<"You have Successfully SIGNUP"<<endl;
    setColor(7);
    stopBeforeMove("Main menu");
}
//displays the the options on the customer panel
void customerPanel(int &check2){
    setColor(13);
    cout<<"1.View all buses"<<endl;
    cout<<"2.Book a seat"<<endl;
    cout<<"3.Cancel Booking"<<endl;
    cout<<"4.View my Booking"<<endl;
    cout<<"5.Back to Main menu"<<endl;
    cout<<endl;
    setColor(7);
    setColor(14);
    cout<<"Enter your choice: ";
    cin>>check2;
    cin.ignore();
    setColor(7);
}
//for seat booking
void seatBooking(){
    viewBuses();     //show available buses to the customer
    string busNumber,name,cnic,noOfSeats;
    setColor(10);
    cout<<"Enter Bus number: ";
    getline(cin,busNumber);
    int avaSeats=0;
    // compairing the bus number from the busDetails.txt text file and printing the available seats
    bool busFound=false;
    string line;
    fstream newfile;
    newfile.open("busesDetails.txt",ios::in);
    while(getline(newfile,line)){
        stringstream ss(line);
        string busNo,busname,from,to,time,seats,availableSeats;
        getline(ss,busNo,',');
        getline(ss,busname,',');
        getline(ss,from,',');
        getline(ss,to,',');
        getline(ss,time,',');
        getline(ss,seats,',');
        getline(ss,availableSeats);
        if(busNumber==busNo){
            avaSeats=stoi(availableSeats);
            setColor(14);
            cout<<"Available seats: "<<avaSeats<<endl;
            busFound=true;
            break;
        }
    }
    newfile.close();
    if(!busFound){
        setColor(12);
        cout<<"Bus not Found!"<<endl;
        setColor(7);
        stopBeforeMove("Customer Panel");
        return;
    }
    //if seats are available
    if(avaSeats>0){
        setColor(10);
        cout<<"Enter your name: ";
        getline(cin,name);
        cout<<"Enter your CNIC: ";
        getline(cin,cnic);
        cout<<"Enter number of seats: ";
        getline(cin,noOfSeats);
        if(stoi(noOfSeats)>avaSeats){
            setColor(12);
            cout<<"Only "<<avaSeats<<" seats are available. Booking failed!"<<endl;
            setColor(7);
            stopBeforeMove("Customer Panel");
            return;
        }
        //generate unique ticket ID
        int ticketId=2222;
        string idLine="";
        fstream idfile;
        idfile.open("bookingRecord.txt",ios::in);
        while(getline(idfile,idLine)){
            stringstream ss(idLine);
            string tempBusNo,tempCusName,tempCNIC,tempNoOfSeats,tempId;
            getline(ss,tempBusNo,',');
            getline(ss,tempCusName,',');
            getline(ss,tempCNIC,',');
            getline(ss,tempNoOfSeats,',');
            getline(ss,tempId);
            if(!tempId.empty()){
                ticketId=stoi(tempId);    //last id in the file
            }
        }
        idfile.close();
        ticketId++;
        setColor(14);
        cout<<"Your ticket ID: "<<ticketId<<endl;
        fstream file;
        setColor(7);
        file.open("bookingRecord.txt",ios::app);
        file<<busNumber<<","<<name<<","<<cnic<<","<<noOfSeats<<","<<ticketId<<endl;
        file.close();

        //updating the available seats in the text file
        int change=stoi(noOfSeats)*-1;      //negative because we are reducing seats
        seatUpdate(busNumber,change);
        setColor(10);
        cout<<"Seat Booked successfully "<<endl;
        setColor(7);
    }
    else{
        setColor(12);
        cout<<"No seats available"<<endl;
        setColor(7);
    }
    
    stopBeforeMove("Customer Panel");
}
//cancel a booking based on ticket ID
void cancelBooking(){
    string enteredTicketId,enteredName,enteredSeats,enteredBusNo;
    setColor(10);
    cout<<"Enter Ticket ID: ";
    getline(cin,enteredTicketId);
    setColor(7);
    bool idFound=false;
    string line;
    fstream newfile;        //original booking file
    fstream tempfile;       //temporary file to hold updated records
    tempfile.open("temporary.txt",ios::out);
    newfile.open("bookingRecord.txt",ios::in);
    if(!newfile.is_open()){
        setColor(12);
        cout<<"Error file not found"<<endl;
        setColor(7);
        return;
    }
    while(getline(newfile,line)){
        stringstream ss(line);
        string busNo,customerName,CNIC,seats,ticketId;
        getline(ss,busNo,',');
        getline(ss,customerName,',');
        getline(ss,CNIC,',');
        getline(ss,seats,',');
        getline(ss,ticketId);
        if(ticketId==enteredTicketId){
            setColor(14);
            cout<<"Ticket ID found"<<endl;
            setColor(10);
            cout<<"Enter your Name: ";
            getline(cin,enteredName);
            setColor(7);
            if(enteredName==customerName){    //match customer name to confirm identity
                idFound=true;
                enteredSeats=seats;           //save seat count to update availability
                enteredBusNo=busNo;           //save bus no to update bus record
                continue;                     //skip writing this line
            }
            else{
                setColor(12);
                cout<<"Name doesn't match. Cannot cancel Booking"<<endl;
                setColor(7);
                tempfile<<busNo<<","<<customerName<<","<<CNIC<<","<<seats<<","<<ticketId<<endl;
            }
            
        }
        else{
            tempfile<<busNo<<","<<customerName<<","<<CNIC<<","<<seats<<","<<ticketId<<endl;
        }
        
    }
    if(idFound){
        setColor(10);
        cout<<"Booking Cancelled Sccessfully"<<endl;
        setColor(7);
    }
    else{
        setColor(12);
        cout<<"Ticket ID not Found"<<endl;
        setColor(7);
    }
    newfile.close();
    tempfile.close();
    if(idFound){
        remove("bookingRecord.txt");
        rename("temporary.txt","bookingRecord.txt");
    }
    else{
        remove("temporary.txt");
    }


    //updating the available seats in the text file
    if(idFound){
        int change=stoi(enteredSeats);
        seatUpdate(enteredBusNo,change);
        stopBeforeMove("Customer Panel");
    }
}
// display bookings for a specific customer based on CNIC
void viewMyBooking(){
    string customerCNIC;
    setColor(10);
    cout<<"Enter your CNIC No. : ";
    getline(cin,customerCNIC);
    setColor(7);
    cout<<endl;
    cout<<left<<"|"<<setw(10)<<"Bus Number"<<"|"<<setw(15)<<"Customer Name"<<"|"<<setw(13)<<"CNIC"<<"|"<<setw(5)<<"Seats"<<"|"<<setw(10)<<"Ticket ID"<<"|"<<endl;
    cout<<string(60,'-')<<endl;
    fstream newfile;
    newfile.open("bookingRecord.txt",ios::in);
    if(!newfile.is_open()){
        setColor(12);
        cout<<"Error file not Found"<<endl;
        setColor(7);
        return;
    }
    string line;
    bool record=false;
    setColor(1);
    while(getline(newfile,line)){
        stringstream ss(line);
        string busNo,customerName,CNIC,seats,ticketId;
        getline(ss,busNo,',');
        getline(ss,customerName,',');
        getline(ss,CNIC,',');
        getline(ss,seats,',');
        getline(ss,ticketId);
        if(CNIC==customerCNIC){
            record=true;
            cout<<left<<"|"<<setw(10)<<busNo<<"|"<<setw(15)<<customerName<<"|"<<setw(13)<<CNIC<<"|"<<setw(5)<<seats<<"|"<<setw(10)<<ticketId<<"|"<<endl;
            cout<<endl;
            
        }
        
    }
    setColor(7);
    if(!record){
        setColor(12);
        cout<<"No Bookings Found"<<endl;
        setColor(7);
    }
    newfile.close();
    stopBeforeMove("Customer Panel");
}
//wait for any key before moving back to a specific panel
void stopBeforeMove(string panel){
    cout<<"Press Any key to return to "<<panel<<endl;
    getch();
}
//updating the available seats in the text file
void seatUpdate(string busNumber,int change){
    fstream newfile;
    fstream temp;
    newfile.open("busesDetails.txt",ios::in);
    temp.open("temporary.txt",ios::out);
    string line="";
    while(getline(newfile,line)){
        stringstream ss(line);
        string busNo,busName,from,to,time,seats,availableSeats;
        getline(ss,busNo,',');
        getline(ss,busName,',');
        getline(ss,from,',');
        getline(ss,to,',');
        getline(ss,time,',');
        getline(ss,seats,',');
        getline(ss,availableSeats);
        if(busNo==busNumber){
            int updatedSeats=stoi(availableSeats)+change;
            temp<<busNo<<","<<busName<<","<<from<<","<<to<<","<<time<<","<<seats<<","<<updatedSeats<<endl;
        }
        else{
            temp<<line<<endl;
        }
    }
    newfile.close();
    temp.close();
    remove("busesDetails.txt");
    rename("temporary.txt","busesDetails.txt");
}
int convertToMinutes(string departureTime){
    stringstream ss(departureTime);
    int hours,minutes;
    char colon;
    ss>>hours>>colon>>minutes;
    return (hours*60)+minutes;
}
void sortBusesByTime(){
    const int max=100;
    string lines[max];
    int timeInMinutes[max];
    int count=0;
    string line="";
    fstream newfile;
    newfile.open("busesDetails.txt",ios::in);
    if(!newfile.is_open()){
        cout<<"Error file not fount"<<endl;
        return;
    }
    while(getline(newfile,line)&&count<max){
        lines[count]=line;
        stringstream ss(line);
        string temp,departureTime;
        for(int i=0;i<5;i++){
            getline(ss,temp,',');
            if(i==4){           //5th value is time
                departureTime=temp;
            }
        }
        timeInMinutes[count]=convertToMinutes(departureTime);
        count++;
    }
    newfile.close();
    //selection Sort
    int smallestInx;
    for(int i=0;i<count-1;i++){
        smallestInx=i;
        for(int j=i+1;j<count;j++){
            if(timeInMinutes[j]<timeInMinutes[smallestInx]){
                smallestInx=j;
            }
            
        }
        swap(timeInMinutes[i],timeInMinutes[smallestInx]);
        swap(lines[i],lines[smallestInx]);
    }
    newfile.open("busesDetails.txt",ios::out);
    for (int i=0;i<count;i++){
        newfile<<lines[i]<<endl;
    }
    newfile.close();
}