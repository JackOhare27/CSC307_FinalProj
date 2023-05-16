//Jack O'Hare
//jmohare@cn.edu
//0589474
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string usn;
int tm;

class Client
{
private:
    float total;
    string username,name,password,notes;

    public:
        void addInfo(float tot, string usern, string n,string pass, string note)
        {
            total = tot;
            username = usern;
            name = n;
            notes = note;
            password = pass;
        }

        //GET INFO
        float returnTotal()
        {
            return total;
        }
        string returnUsername()
        {
            return username;
        }
        string returnName()
        {
            return name;
        }
        string returnPassword()
        {
            return password;
        }
        string returnNotes()
        {
            return notes;
        }
        //ADD INFO
        void addbBio(string st);
        void addBalance(float difference);
        void subBalance(float difference);
        //CHECK INFO
        bool checkNeg(float difference);
};


void Client::addbBio(string st)
{
    notes = st;
}
void Client::addBalance(float difference)
{
    total  = total + difference;
    cout << "You're new balance is $" << total << endl;
}

void Client::subBalance(float difference)
{
    total  = total - difference;
    cout << "You're new balance is $" << total << endl;
}

bool Client::checkNeg(float difference)
{
    if (total - difference < 0)
    {
        //cout << "invalid";
        return true;
    }
    else{//cout << "valid";
            return false;
        }

}
void valid(string str)
{
    //
    string dir,user;
    ifstream file;
    // creates string using username(from param) and turns it into a textfile
    dir = str+".txt";
    //creates text file of each individual user
    file.open(dir.c_str());
    //if file is not open and fails return nothing
    if(!file.is_open() && file.fail())
    {
        return;
    }
    else
    {

        tm++; // An attempt meter, if it happens more than 3 times user gets booted from current menu
        if(tm==3)
        {
            cout<<"\nThis username already exists\nPlease try Again.";

            return;
        }
        cout<<"\nThis username already exists!\nCreate a username:";

        // If invalid, then loopback with a new username
        cin>>usn;
        valid(usn);
    }
}













int main()
{

    Client client;
    int choice,i,exit=0;
    string ans,psd,name,fname,bio,usern,pw,line,total_StringFormat;
    float total;
    ofstream fileo;
    ifstream filei;
    cout<<"----------------------------------------------Welcome to our system!------------------------------------------------------\n";
    while(exit==0)
    {
        cout<<"\nChoose one option:\n1. SignIn/LogIn(press 1 to select this)\n2. SignUp/Register(press 2 to select this)\n\npress any key and enter to exit\n";
        cin>>choice;
        ///////////////////////////////////////////////////////////////////////////////////
        //LOGIN
        if(choice==1)
        {
            //grab username and password
            cout<<"Enter your username:";
            cin>>usn;
            cout<<"\nEnter your password:";
            cin>>psd;
            //Take username and make it into a text file string
            fname=usn+".txt";
            //attempt to open it
            filei.open(fname.c_str());
            //If file cannot be found then user most likely doesnt exist
            if(!filei.is_open() && filei.fail())
            {
                cout<<"\nYou are not registered, please register before logging in.\n";
                filei.close();
                //Leaves back to switch case
                continue;
            }
            //grabs already existing info
            getline(filei,usern);
            getline(filei,name);
            getline(filei,pw);

            //if username and password are correct display info
            if(usn==usern && psd==pw)
            {
                cout<<"\nYou are successfully logged in:)\nYOUR PROFILE SAYS:\n";
                cout<<"User-name:"<<usern<<endl;
                cout<<"Name:"<<name<<endl;
                getline(filei,total_StringFormat);
                total = stof(total_StringFormat);
                cout<<"ATM Total: $"<<total<<endl;
                getline(filei,bio);
                cout << "Notes:" << bio << endl;

                client.addInfo(total,usern,name,pw,bio);


                    while(true)
                    {
                        cout<< "____________________________________________________________________________"
                        << "\nWhat would you like to do today?\n"
                        << "1. Deposit \n" << "2. Withdraw \n" << "3. Change notes \n" << "4. Save and Exit\n";
                            cin>>choice;

                        switch (choice)
                        {
                        //Add
                        case 1:
                         {
                            float diff;
                            cout << "How much money would you like to deposit\n";
                            cin >> diff;
                            client.addBalance(diff);
                            break;
                         }

                         //Subtract
                        case 2:
                        {
                            bool invalidWithdraw = true;
                            while(invalidWithdraw)
                            {
                                int diff;
                                cout << "How much would you like to withdraw?";
                                cin >> diff;
                                invalidWithdraw = client.checkNeg(diff);
                                if(invalidWithdraw)
                                {
                                    cout << "ERROR: BALANCE WILL GO NEGATIVE IF AMOUNT IS WITHDRAWN; MAX IS $" << client.returnTotal() << endl;
                                }
                                else
                                {
                                    client.subBalance(diff);
                                }
                            }
                            break;
                        }

                        //Notes
                        case 3:
                            cout << "Please type what you would like to say\n";
                            cin.ignore();
                            getline(cin,bio);
                            client.addbBio(bio);

                            break;
                        case 4:
                            fileo.open(fname.c_str(), ofstream::out | ofstream::trunc);
                            fileo<<client.returnUsername() << endl;
                            fileo<<client.returnName()<<endl;
                            fileo<<client.returnPassword()<<endl;
                            fileo<<client.returnTotal()<<endl;
                            fileo<<client.returnNotes()<<endl;
                            fileo.close();
                            cout<<"\n----------------------------------------------Thank you for visiting:)----------------------------------------------------\n";
                            return 0;
                     }



                    }

               filei.close();

            }





            else{
                cout<<"\nWrong username or password!\nPlease try Again.\n";
            }
            cout<<endl;

        }
        //////////////////////////////////////////////////////////////////////////
        //REGISTER
        else if(choice==2)
        {
            cout<<"\nEnter your name:";
            cin.ignore();
            getline(cin,name);
            cout<<"\nCreate a username:";
            cin>>usn;
            tm=0;
            valid(usn);
            if(tm>=3)
            {
                continue;
            }
            cout<<"\nCreate a password:";
            cin>>psd;
            fname=usn+".txt";
            //cout<<fname;
            fileo.open(fname.c_str());
            fileo<<usn<<endl<<name<<endl<<psd<<endl;
            cout<<"\nYou are successfully registered:)";\

            cout<<"\nHow much money would you like to insert into your new account? (ex. 3, 20.34):";
            cin.ignore();
            getline(cin,line);

            cout<<"\nYou now have: $"<<line << " in your account\n";

            //ADDING TO CLASS
            float amount = std::stof(line);
            client.addInfo(amount,usn, name, psd, bio);

        //creates infinite loop until person leaves the program
        while(true)
        {

            cout << "What would you like to do in your account?\n"
            << "1. Deposit money\n"
            << "2. Withdraw money\n"
            << "3. Create note\n"
            << "4. Exit and save details\n";
            cin >> choice;
              switch (choice)
              {
                //Add
                case 1:
                 {
                    float diff;
                    cout << "How much money would you like to deposit\n";
                    cin >> diff;
                    client.addBalance(diff);
                    break;
                 }

                 //Subtract
                case 2:
                {
                    bool invalidWithdraw = true;
                    while(invalidWithdraw)
                    {
                        int diff;
                        cout << "How much would you like to withdraw?";
                        cin >> diff;
                        invalidWithdraw = client.checkNeg(diff);
                        if(invalidWithdraw)
                        {
                            cout << "ERROR: BALANCE WILL GO NEGATIVE IF AMOUNT IS WITHDRAWN; MAX IS $" << client.returnTotal() << endl;
                        }
                        else
                        {
                            client.subBalance(diff);
                        }
                    }
                    break;
                }

                //Notes
                case 3:
                    cout << "Please type what you would like to say\n";
                    cin.ignore();
                    getline(cin,bio);
                    client.addbBio(bio);

                    break;
                case 4:
                    fileo<<line<<endl;
                    fileo<<bio<<endl;
                    fileo.close();
                    cout<<"\n----------------------------------------------Thank you for visiting----------------------------------------------------\n";
                    return 0;
             }

        }

        }
        else
        {
            exit=1;
        }
    }
    //Exit case if person leaves but not registered or logged in
    cout<<"\n----------------------------------------------Thank you for visiting----------------------------------------------------\n";
}
