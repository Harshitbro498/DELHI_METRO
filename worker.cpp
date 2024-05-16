#include"headers/Graph.h"
#include "Graph.cpp"
#include<iostream>
#include<string.h>
#include<climits>
#include<fstream>
#include<Windows.h>
using namespace std;
#include<map>
int login()
{
    char dum,u_name[30],name[30],g_pwd[30],pwd[30];
    int flag=0,s=1;
 cout<<"\n\n\n\n\n\n\t\t\t\t\t  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb"<<endl;
    cout<<"\t\t\t\t\t\t*WELCOME TO LOGIN*"<<endl;
    cout<<"\t\t\t\t\t  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb "<<endl;
    if(s==1){

cout<<"Enter your USER NAME  : "<<endl;
    cin>>name;
}

        cout<< "Enter the PASSWORD   : "<<endl;
    cin>>pwd;
    fstream f;
    f.open("user_logins.txt",ios::in);
    f.seekg(0);
    while(f)
    {
        f.get(dum);
        f.get(u_name,30);
        f.get(dum);
        f.get(g_pwd,30);
        if(strcmp(u_name,name)==0&&strcmp(pwd,g_pwd)==0)
        {
            flag=1;
           cout<<"\n\t\t\tYou have Successfully LOGGED IN ";
            break;
        }
        else if(strcmp(u_name,name)==0&&strcmp(pwd,g_pwd)!=0)
        {
            do
            {
                cout<<"\t\t\t----INCORRECT PASSWORD!!!----";
                           cout<<"Re-Enter the PASSWORD : "<<endl;
       
                cin>>pwd;
            }while(strcmp(pwd,g_pwd)!=0);
    
            flag=1;
            break;
        }
    }
    if(flag==0)
        cout<<"\n\t\t\tSORRY!!! USER NAME and PASSWORD does not Exist"<<endl;
    system("CLS");
    f.close();
    return flag;
}

void signup()
{
 cout<<"\n\n\n\n\n\n\t\t\t\t\t  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb "<<endl;
    cout<<"\t\t\t\t\t\t*WELCOME TO SIGNUP*"<<endl;
    cout<<"\t\t\t\t\t  \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb "<<endl;
    char name[30],pwd[30],check_pwd[30];
    fstream f;
    f.open("user_logins.txt",ios::in);
    char g_name[30],g_pwd[30],dum;
    int flag;
    cout<<"Enter your USER NAME : ";
    cin>>name;
    do
    {
        f.seekg(0);
        while(f)
        {
            flag=1;
            f.get(dum);
            f.get(g_name,30);
            f.get(dum);
            f.get(g_pwd,30);
            if(strcmp(g_name,name)==0)
            {
                flag=0;
                break;
            }
        }
        if(flag==0)
        {
            cout<<"\n\t\t\t----USER-NAME ALREADY EXIST!!----"<<endl;
            cout<<"Enter your USER NAME : ";
            cin>>name;
        }
    }while(flag==0);
    f.close();
    f.open("user_logins.txt",ios::out|ios::app);
    cout<<"Enter your PASSWORD : ";
    cin>>pwd;
    cout<<"Re-Enter your PASSWORD : ";
    cin>>check_pwd;
    while(strcmp(pwd,check_pwd)!=0)
    {
        cout<<"\t\t\t----INCORRECT PASSWORD!!!----"<<endl;
        cout<<"Enter your PASSWORD : ";
        cin>>pwd;
        cout<<"Re-Enter your PASSWORD : ";
        cin>>check_pwd;
    }
    f<<endl<<name<<endl<<pwd;
 cout<<"\n\t\t\t\t\t  YOUR NEW ID IS CREATING PLEASE WAIT";
for(int i=0;i<6;i++)
{
cout<<".";
Sleep(500);
    }
cout<<"\n\n\t\t\t\t\t\aCONGRATULATION!!!YOUR ID CREATED SUCCESSFULLY....Please wait";
Sleep(5000);
system("CLS");
    f.close();
}
int main() {
    
    map< pairstr, int > m;
    vector< string >station_name;
    vector<string> line;
    map< pairstr, set< string >> intersecting_stations;
    map<int, string>line_num;
    load_lines(line);
    vector<vector< int >> graph(line.size());
    hashes(m, station_name);
    line_hash_function(line_num, line);
    intersecting_stations_funtion(intersecting_stations, line, m, station_name);
    graph_function(graph);
   int ch,flag;
    char s;
    cout<<"----------------------------------------WELCOME TO DELHI METRO ASSISTANCE----------------------------------------\n\n";
    do
    {
        cout<<endl;
        cout<<"\t\t\t\t\t\t\t \t\t\t\t\t\n";
        cout<<"\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb \n";
        cout<<"\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb \n";
        cout<<"\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb 1) LOGIN    \xdb\xdb\xdb\xdb\xdb\xdb\n";
        cout<<"\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb 2) REGISTER \xdb\xdb\xdb\xdb\xdb\xdb\n";
        cout<<"\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb 3) EXIT     \xdb\xdb\xdb\xdb\xdb\xdb\n";
        cout<<"\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb \n";
        cout<<"\t\t\t\t\t\t\t \t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb \n";
        cout<<"Enter your Choice : ";
        cin>>ch;
        system("cls");
        switch(ch)
        {
            case 1:
                flag=login();
                break;
            case 2:
                signup();
                cout<<"Do you want to LOGIN (Y/N)? : ";
                cin>>s;
                if(s=='y'||s=='Y')
                    flag=login();
                else
                {
                    cout<<"\t\t\t\t\t\t\t \t\t\t\t\t ___________ \n";
                    cout<<"\t\t\t\t\t\t\t \t\t\t\t\t| THANK YOU |\n";
                    cout<<"\t\t\t\t\t\t\t \t\t\t\t\t|_|\n";
                    exit(1);
                }
                break;
            case 3:
                cout<<"\t\t\t\t\t\t\t \t\t\t\t\t ___________ \n";
                cout<<"\t\t\t\t\t\t\t \t\t\t\t\t| THANK YOU |\n";
                cout<<"\t\t\t\t\t\t\t \t\t\t\t\t|_|\n";
                exit(0);
                break;
            default:
                cout<<"\t\t\t----INCORRECT CHOICE!!!----"<<endl;
                break;
        }
    }while(flag!=1);
    if(flag)
    {
        cout<<"\n\t\t\t\t\t  LOGGING IN";
        for(int i=0;i<6;i++)
{
cout<<".";
Sleep(500);
    }
    cout<<endl;
    cout<<"----------------------------------------WELCOME TO  Delhi Metro Assistant----------------------------------------\n\n";
    cout<<"                                      We are here to find you the best route                                        \n\n";
    cout <<"                                      Please enter the stations accordingly  :                                         " << endl << endl;
     // Clear the newline character left by std::cin >>
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // taking input from user.
    string station1, station2;
    
    cout << "     Enter the Source/Staring station  :- ";
     getline(cin, station1);
    cout << "\n\n     enter the Destination/Ending station :- ";
    getline(cin, station2);
    cout << endl;
    //for checking the input station lines.
    string line1 = line_name(line, m, station1);
    string line2 = line_name(line, m, station2);

    //for lines to their line number.
    int line_num1 = line_num_function(line_num, line1);
    int line_num2 = line_num_function(line_num, line2);
    //cout<<line_num1<<" "<<line_num2<<endl;

    if (line_num1 == -1 || line_num2 == -1) {
        cout << "     Sorry! You entered wrong station name . Please Try again." << endl;
    }
    else {
        if (line_num1 == line_num2) {
            int num = abs(m[{station1, line1}] - m[{station2, line1}]);
            cout << "     -Both of these stations are on the same line ("<<line1<<") so we do not need to change any lines" << endl;
            cout << "     -There is only one Path which makes sense" << endl;
            cout << "     -Start from station '" << station1 << "' to station '" << station2 << "' via " << line1 << "line" << endl;
            cout << "     -Total number of station u have to cover are :" << num << endl;
            cout << "-----------------------------------THANK YOU. HAVE A SAFE JOURNEY!!-------------------------------------- " << endl;
        }
        else {

            // for finding the paths with a limit or interchanging stations.
            vector<vector<int >>dfs_paths;
            dfs_paths = path_function(graph, line_num1, line_num2);


            //for output of paths according to the line number.
            // cout<<"total number of paths are : "<<endl;
            // cout<<dfs_paths.size()<<endl;
            // for(auto i:dfs_paths){
            //      //cout<<i.size()<<endl;
            //     for(auto j:i){
            //         cout<<j<<" ";
            //     }
            //     cout<<endl;
            // }


            //finding path with station's name .
            vector<node>routes;
            routes = path_with_station(dfs_paths, intersecting_stations, m, line_num, station1, station2);

            //for sorting the path on the basis of their station numbers.
            sorting(routes);


            // for printing all the routes.
             // cout<<routes.size()<<endl;
             // for(auto i:routes){
             //     cout<<i.val<<endl;
             //     for(auto j:i.route){
             //         cout<<j<<" ";
             //     }
             //     cout<<endl;
             // }

             // for printing the output
            int path_number = 0;
            int n = routes.size();
            for (auto i : routes) {


                if (path_number == 0) {

                    path_number++;
                    cout << "     -The shortest path from station " << station1 << "  to station  " << station2 << " is :" << endl;
                    cout << "     ";
                    bool flag = true;
                    for (auto j : i.route) {
                        if (flag) {
                            cout << j;
                            flag = false;
                        }
                        else {
                            cout << "  -->  " << j;
                        }
                    }
                    cout << endl;
                    cout << "     -Total number of stations travelled during this route are : " << i.val << endl;
                    cout << endl;
                }
                else if (path_number < n && path_number < 3) {
                    path_number++;
                    if (path_number == 2)
                        cout << "     -" << path_number << "nd shortest  path from station " << station1 << "  to station  " << station2 << " is :" << endl;
                    if (path_number == 3)
                        cout << "     -" << path_number << "rd shortest  path from station " << station1 << "  to station  " << station2 << " is :" << endl;

                    cout << "     ";
                    bool flag = true;
                    for (auto j : i.route) {
                        if (flag) {
                            cout << j;
                            flag = false;
                        }
                        else {
                            cout << "  -->  " << j;
                        }
                    }
                    cout << endl;
                    cout << "     -Total number of stations travelled during this route are : " << i.val << endl;
                    cout << endl;

                }
                else if (path_number < n && path_number>2) {
                    path_number++;
                    char c;
                    cout << "     Do you want one more path. Enter y/n : ";
                    cin >> c;
                    if (c == 'y') {
                        cout << endl;
                        cout << "     -" << path_number << "th shortest  path from station " << station1 << "  to station  " << station2 << " is :" << endl;
                        cout << "     ";
                        bool flag = true;
                        for (auto j : i.route) {
                            if (flag) {
                                cout << j;
                                flag = false;
                            }
                            else {
                                cout << "  -->  " << j;
                            }
                        }
                        cout << endl;
                        cout << "     -Total number of stations travelled during this route are : " << i.val << endl;
                        cout << endl;
                    }
                    else {
                        cout << "-----------------------------------THANK YOU. HAVE A SAFE JOURNEY!!-------------------------------------- " << endl<<endl;
        
                        break;
                    }
                }
                if (path_number == n) {
                  cout << "-----------------------------------THANK YOU. HAVE A SAFE JOURNEY!!-------------------------------------- " << endl<<endl;
         break;
                }
            }
            }
        }

    }
}