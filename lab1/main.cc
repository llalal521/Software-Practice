#include <vector>
#include <iostream>
#include <fstream>
#include "Class.h"
#include "Student.h"
#include <iomanip>

using namespace std;
int transfer(string A);

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX() //done
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;// size_t is nearly equal to int
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");

    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining of the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));// npos shows the end of a string
                break;// substr is used to take a string which is needed form a string
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        if (bufv[3] == "U")
        {
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        }
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);

        studentVec.push_back(st);
    }
    stfile.close();
    ifstream clfile("./Classes.txt");
    bufv.clear();

    while (getline(clfile,line)){
        if(line[0]=='#')
            continue;

        pos1 = 0;
        while (true) {
            if(line.empty())
                break;
            pos2=line.find(':', pos1 + 1);
            if(pos2 != string::npos) {
                pos1=pos2 + 1;
                continue;
            }
            else {
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            }
        }

    if(line.empty())
    {
        clsname=bufv[0];
        point=transfer(bufv[1]);
        cl=new Class (clsname,point);
        for(unsigned int i=2;i<bufv.size();++i)
        {
            for(unsigned int j=0;j<studentVec.size();++j)
            {
                if(studentVec[j]->id==bufv[i])
                {
                    cl->addStudent(*studentVec[j]);
                    studentVec[j]->addClass(cl);
                }
            }
        }
        bufv.clear();
        classVec.push_back(cl);
        continue;
    }
    }
    clsname=bufv[0];
    point=transfer(bufv[1]);
    cl=new Class (clsname,point);
    for(unsigned int i=2;i<bufv.size();++i)
    {
        for(unsigned int j=0;j<studentVec.size();++j)
        {
            if(studentVec[j]->id==bufv[i])
            {
                cl->addStudent(*studentVec[j]);
                studentVec[j]->addClass(cl);
            }
        }
    }
    bufv.clear();
    classVec.push_back(cl);
    clfile.close();
}

void AppX::inputScore()
{
    string clsname;
    string id;
    Class *cl;
    StudentWrapper *st;
    double score;
    while(true){
    cout<< "please input the class name(or input q to quit):"<<endl ;
    cin>>clsname;
    if(clsname =="q")
        break;

    cl = nullptr;
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if ((*it)->name == clsname) {
            cl = *it;
            break;
        }
    }
    if (cl == nullptr) {
        cout << "No match class!\n";
        continue;
    }
    while(true){
    cout<< "please input the student's id and the score"<<endl ;
    cin>>id;
    if(id=="q") break;
    try{
        st=&cl->getStudentWrapper(id); //& is used to take the address!!!

    }
    catch(const char *){cout<<"No match student!\n";
                       continue;}
    cin>>score;
    try{
    st->setScore(score);
    cout<<st->toString();
    }
    catch(const char *){cout<<"Wrong score!\n";}
    }
}
}
void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!\n";
            continue;
        }

        avg = cl->getAvgScore();
        cout << "The average score is: " <<setiosflags(ios::fixed)<<setprecision(2)<< avg << endl;
    }
}

void AppX::printGpa()//done
{
    string id;
    Student *st;

    while(true)
    {
        cout<<"please input the student's id:(or input q to quit)"<<endl;
        cin>>id;
        if(id=="q")
            break;

        st = nullptr;
        for (vector<Student *>::iterator it = studentVec.begin();
             it != studentVec.end();
             ++it) {
            if ((*it)->id == id) {
                st = *it;
                break;
            }
        }
        if (st == nullptr) {
            cout << "No match student!\n";
            continue;
        }
        cout<< st->toString();
        cout<<"GPA = "<<setiosflags(ios::fixed)<<setprecision(2)<<st->getGrade()<<endl;
    }
}

int AppX::run()//done
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
int transfer(string A)
{
    int size=A.size();
    int result=0;
    for(int i=0;i<size;++i)
    {
        result=result*10 + A[i]-'0';
    }
    return result;
}
