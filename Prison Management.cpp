#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define MAX_PRISONER 30
#define MAX_GUARD 10

class admin;
class guard;
class prisoner;
class activity;

class prisoner {
    string name;
    int id;
    string offence;
    int sentence;
    int cell;
public:
    prisoner () {}
    ~prisoner() {}
    void set () {
        string n, o; int i, s, c;
        cout << "\nEnter name: "; getline (cin, n); name = n;
        cout << "Enter ID: "; cin >> i; getchar(); id = i;
        cout << "Enter offence: "; getline (cin, o); offence = o;
        cout << "Enter sentence: "; cin >> s; sentence = s;
        cout << "Enter assigned cell: "; cin >> c; cell = c;
        getchar();
    }
    void increaseSentence () {
        int n;
        cout << "How many months? ";
        cin >> n;
        sentence += n;
    }
    void decreaseSentence () {
        int n;
        cout << "How many months? ";
        cin >> n;
        sentence -= n;
    }
    void setCell () {
        int n;
        cout << "Which cell? ";
        cin >> n;
        cell = n;
    }
    void awardSentence (int n) {
        sentence -= n;
    }
    void penaliseSentence (int n) {
        sentence += n;
    }
    string getName () {return name;}
    int getId () {return id;}
    string getOffence () {return offence;}
    int getSentence () {return sentence;}
    int getCell () {return cell;}
    void display () {
        cout << "\nName: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Offence: " << offence << endl;
        cout << "Sentence: " << sentence << endl;
        cout << "Cell: " << cell << endl;
    }
    friend int search (admin &adm, string name, int type);
    friend admin;
};

class activity {
    friend admin;
public:
    int library (prisoner &p, int duration, int serial) {
        p.awardSentence(duration*0.5);
        return duration*0.5;
    }
    int cleaning (prisoner &p, int duration, int serial) {
        p.awardSentence(duration*0.2);
        return duration*0.2;
    }
    int gardening (prisoner &p , int duration, int serial) {
        p.awardSentence(duration*0.3);
        return duration*0.3;
    }
    int misconduct (prisoner &p, int degree, int serial) {
        p.penaliseSentence(degree*1);
        return degree*1;
    }
    int breaking_attempt (prisoner &p, int degree, int serial) {
        p.penaliseSentence(degree*10);
        return degree*10;
    }
    int violence (prisoner &p, int degree, int serial) {
        p.penaliseSentence(degree*5);
        return degree*5;
    }
};

class guard {
    int id;
    string name;
    int salary;
    string post;
public:
    guard () {};
    ~guard () {}
    void set () {
        string n, p; int i, s;
        cout << "\nEnter name: "; getline (cin, n); name = n;
        cout << "\nEnter ID: "; cin >> i; getchar(); id = i;
        cout << "\nEnter post: "; getline (cin, p); post = p;
        cout << "\nEnter salary: "; cin >> s; salary = s;
        getchar();
    }
    void setPost () {
        getchar();
        string new_post;
        cout << "Enter new post: "; 
        getline (cin, new_post);
        post = new_post;
    }
    void setSalary () {
        int n;
        cout << "Enter new salary: ";
        cin >> n;
        salary = n;
    }
    string getName () {return name;}
    int getId () {return id;}
    string getPost () {return post;}
    int getSalary () {return salary;}
    void display () {
        cout << "\nName: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Post: " << post << endl;
        cout << "Salary: " << salary << endl;
    }
    friend int search (admin &adm, string name, int type);
};

class admin {
    prisoner p[MAX_PRISONER];
    guard g[MAX_GUARD];
    int prisoner_count = 0;
    int guard_count = 0;
    activity act;
public: 
    admin () {};
    ~admin () {};
    int getPrisoner_count () {
        return prisoner_count;
    }
    int getGuard_count () {
        return guard_count;
    }
    void addGuard () {
        g[guard_count].set();
        guard_count++;
        cout << "Guard added.\n";
    }
    void addPrisoner () {
        p[prisoner_count].set();
        prisoner_count++;
        cout << "\nPrisoner added.\n\n";
    }
    void changePost (int i) {
        g[i].setPost(); 
        cout << "Post changed successfully.\n";
    }
    void changeSalary (int i) {
        g[i].setSalary();
        cout << "Salary changed successfully.\n";
    }
    void increase_sentence (int i) {
        p[i].increaseSentence();
        cout << "Total sentence for " <<  p[i].getName() << " is " << p[i].getSentence() << " months.\n";
    }
    void derease_sentence (int i) {
        p[i].decreaseSentence();
        if (p[i].getSentence() <= 0) {
            cout << "Prisoner has served his sentence.\n";
            removePrisoner(i);
        }
        else  {
            cout << "Total sentence for " <<  p[i].getName() << " is " << p[i].getSentence() << " months.\n";
        }
    }
    void change_cell (int i) {
        p[i].setCell();
        cout << "Cell changed successfully.\n";
    }
    void removePrisoner (int i) {
        prisoner_count--;
        for (i; i < prisoner_count; i++) {
                for (int j = i; j < prisoner_count; j++)
                    p[j] = p[j+1];
            }
            cout << "Prisoner has been removed.\n";
        }
    void removeGuard (int i) {
        guard_count--;
        for (i; i < guard_count; i++) {
                for (int j = i; j < guard_count; j++)
                    g[j] = g[j+1];
            }
            cout << "Guard has been removed.\n";
        }
    void search_by_crime (string crime) {
        for (int i = 0; i < prisoner_count; i++)
            if (p[i].getOffence() == crime)
                p[i].display();
    }
    void displayAll () {
        cout << "\t\t\t\tPrisoner's list\n";
        if (prisoner_count == 0) cout << "No data available.\n";
        for (int i = 0; i < prisoner_count; i++) p[i].display();
        cout << "\t\t\t\tGuard's list\n";
        if (guard_count == 0) cout << "No data available.\n";
        for (int i = 0; i < guard_count; i++) g[i].display();
    }

    int prisoner_search (string name) {
        bool found = 0;
        for (int i = 0; i < prisoner_count; i++)
            if (p[i].getName() == name) {
                found = 1;
                return i;
            }            
        if (!found) {cout << "Prisoner not found.\n"; return -1;}
    }
    void report_activity (admin &adm) {
        int choice;
        
        cout << "\n1. Library work\n2. Cleaning\n3. Gardening\n4. Misconduct\n5. Breaking attempt\n6. Violence\n";
        cout << "\nEnter activity: ";
        cin >> choice;
        getchar ();
        switch (choice) {
            case 1: {
                string name;
                int service_duration;
                cout << "Enter prisoner name: "; getline (cin, name);
                int serial = prisoner_search (name); 
                if (serial < 0) break;

                cout << "Enter service duration: "; cin >> service_duration;
                int change = act.library (p[serial], service_duration, serial);
                cout << "Prisoner " << p[serial].getName() << " was rewarded with a decrease of " << change << " months.\n";
                break;
            }
            case 2: {
                string name;
                int service_duration;
                cout << "Enter prisoner name: "; getline (cin, name);
                int serial = prisoner_search (name); 
                if (serial < 0) break;

                cout << "Enter service duration: "; cin >> service_duration;
                int change = act.cleaning (p[serial], service_duration, serial);
                cout << "Prisoner " << p[serial].getName() << " was rewarded with a decrease of " << change << " months.\n";
                break;                
            }
            case 3: {
                string name;
                int service_duration;
                cout << "Enter prisoner name: "; getline (cin, name);
                int serial = prisoner_search (name); 
                if (serial < 0) break;

                cout << "Enter service duration: "; cin >> service_duration;
                int change = act.gardening (p[serial], service_duration, serial);
                cout << "Prisoner " << p[serial].getName() << " was rewarded with a decrease of " << change << " months.\n";
                break;                
            }
            case 4: {
                string name;
                int service_duration;
                cout << "Enter prisoner name: "; getline (cin, name);
                int serial = prisoner_search (name); 
                if (serial < 0) break;

                cout << "Enter degree of offence: "; cin >> service_duration;
                int change = act.misconduct (p[serial], service_duration, serial);
                cout << "Prisoner " << p[serial].getName() << " was penalised with an increase of " << change << " months.\n";
                break;                
            }
            case 5: {
                string name;
                int service_duration;
                cout << "Enter prisoner name: "; getline (cin, name);
                int serial = prisoner_search (name); 
                if (serial < 0) break;

                cout << "Enter degree of offence: "; cin >> service_duration;
                int change = act.breaking_attempt (p[serial], service_duration, serial);
                cout << "Prisoner " << p[serial].getName() << " was penalised with an increase of " << change << " months.\n";
                break;                
            }     
            case 6: {
                string name;
                int service_duration;
                cout << "Enter prisoner name: "; getline (cin, name);
                int serial = prisoner_search (name); 
                if (serial < 0) break;

                cout << "Enter degree of offence: "; cin >> service_duration;
                int change = act.violence (p[serial], service_duration, serial);
                cout << "Prisoner " << p[serial].getName() << " was penalised with an increase of " << change << " months.\n";
                break;                
            }  
            default:
                cout << "Not a valid command.\n";
        }
    }
    friend int search (admin &adm, string name, int type);
};

int search (admin &adm, string name, int type) {
    if (type == 1) {
        int i;
        bool found = false;
        for (i = 0; i < adm.prisoner_count; i++) {
            if (adm.p[i].getName() == name) {
                adm.p[i].display();  
                cout << "\n\n" ;
                found = true;
                break;
            }
            if (!found) {cout << "\nPrisoner not found.\n"; return -1;}
        }
        return i;
    }
    else {
        int i;
        bool found = false;
        for (i = 0; i < adm.guard_count; i++) {
            if (adm.g[i].getName() == name) {
                adm.g[i].display(); 
                cout << "\n\n";
                found = true;
                break;
            }
            if (!found) {cout << "Guard not found.\n";return -1;}
        }
        return i;       
    }
}

int main ()
{
    int choice;
    admin adm;
    while (1) {
        cout << "\n\n1. Add prisoner.\n";
        cout << "2. Add guard.\n";
        cout << "3. Display All.\n";
        cout << "4. Search.\n";
        cout << "5. Search by crime.\n";
        cout << "6. Report an activity.\n";
        cout << "7. End programe.\n";

        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                int n;
                cout << "How many? ";
                cin >> n;
                if (adm.getPrisoner_count() + n > MAX_PRISONER) {cout << "Not enough room for prisoners.\n"; break;}
                getchar();
                while (n--) adm.addPrisoner();
                break;
            case 2:
                int m;
                cout << "How many? ";
                cin >> m;
                if (adm.getGuard_count() + m > MAX_GUARD) {cout << "Not enough room for guards.\n"; break;}
                getchar ();
                while (m--) adm.addGuard();
                break;           
            case 3:
                getchar();
                adm.displayAll();
                cout << "\n\n";
                break;  
            case 4: {
                int type, serial; string name; 
                cout << "1. Prisoner\n2. Guard\n";  
                cin >> type;
                getchar ();
                cout << "Enter name: ";
                getline (cin, name);
                serial = search (adm, name, type);
                if (serial < 0) break;
                if (type == 1) {
                    cout << "Choose one of the following:\n1. Increase sentence\n2. Decrease sentence\n3. Change cell\n4. Remove prisoner\n";
                    int choice;
                    cout << "Your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            adm.increase_sentence(serial);
                            break;
                        case 2:
                            adm.derease_sentence(serial);
                            break;
                        case 3:
                            adm.change_cell(serial);
                            break;
                        case 4:
                            adm.removePrisoner(serial);
                            break;
                        default:
                            cout << "Invalid command.\n";
                    }
                }
                else {
                    cout << "Choose one of the following:\n1. Change salary\n2. Change post\n3. Remove guard\n";
                    int choice;
                    cout << "Your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            adm.changeSalary(serial);
                            break;
                        case 2:
                            adm.changePost(serial);
                            break;
                        case 3:
                            adm.removeGuard(serial);
                            break;
                        default:
                            cout << "Invalid command.\n";
                    }      
                }
                break; }
            case 5: {
                string cr;
                getchar ();
                cout << "Enter crime you wanna search: ";
                getline (cin, cr);
                adm.search_by_crime (cr);
                break;
                }
            case 6:
                adm.report_activity(adm);
                break;
            case 7:
                cout << "Program ending.....\n";
                return 0;
        }
    }
}