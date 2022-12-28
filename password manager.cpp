#include<iostream>
#include<fstream>
#include <stdio.h>

using namespace std;

ifstream fin;

char ch;
char mp;

string corpass;
string inpass;
string masterpass;

void readmaster(){
    fin.open("masterpass.TXT", ios::in);
    while(fin.get(mp)){
    masterpass += mp;
    }
    fin.close();
}


int resmaster(){
    string maspass;
    cout<<"Set your Master password(used to reset your password)"<<endl;
    cin>>maspass;
    {ofstream outfile("masterpass.TXT", ios::app);
    outfile<<maspass;
    outfile.close();
    }
    return true;
}


int setpass(){
    string password;
    readmaster();
    if (masterpass == ""){
        resmaster();
    }
    cout<<"Set your password"<<endl;
    cin>>password;
    {ofstream outfile("password.TXT", ios::app);
    outfile<<password;
    outfile.close();
    }
    return true;
}


int passcheck(){
    for(int i=0; i<3; i++){
            
        cout<<"Enter the Password"<<endl;
        cin>>inpass;
        if (inpass == corpass){
            return true;    
        }
        else{
                cout<<"please enter the correct password"<<endl;
        };
    }
    cout<<"you have exceeded the number of password attemps"<<endl;
    cout<<"restart the program or"<<endl;
    cout<<"To reset your account Type RESET"<<endl;
    string res;
    cin>>res;
    if (res == "RESET"){
        return false;
    }
    else{
        exit(0);
    }
}


int resetpass(){
    string resetpass;
    cout<<"To reset your account enter the Master password."<<endl;
    cout<<"If you don't have it contact the admin."<<endl;
    readmaster();    
    cout<<"Master password: ";
    cin>>resetpass;
    if (resetpass == masterpass){        
        remove("password.TXT");
        cout<<"your account have been reseted"<<endl;
        return 1;
    }
    else{
        cout<<"Incorrect master password"<<endl;
        exit(0);
    }
}


int main()
{
    fin.open("password.TXT", ios::in);
    while(fin.get(ch)){
        corpass += ch;
    }
    fin.close();
    if (corpass!= ""){
        switch (passcheck())
        {
        case 1:
            cout<<true;
            break;
        default:
            switch(resetpass()){
                case 1:
                    setpass();
                    break;
                default:
                    cout<<"Unexpected Error: Run the application again"<<endl;
                    break;
            }
            break;
        }
    }
    else{
        setpass();
    }  
}