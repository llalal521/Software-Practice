#pragma once

#include <string>
#include <exception>

using std::string;

class Buffer {
private:
    int currentLineNum;
    struct ListBuffer{
        ListBuffer *next;
        string a;
        ListBuffer() {next=NULL;}
        ListBuffer(const string &text): next(NULL),a(text){}
        ~ListBuffer() {}
        void insert(int &n,const string &text);
        void add(int &n,const string &text);
        int showAll();
        const string moveToLine(int i);
        void showlines(int from,int to);
        void deletelines(int from,int to);
        int getMaxsize();
    }* Head=new ListBuffer ();

public:
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;

    const string moveToLine(int idx);

    void showLines(int from, int to);

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
    void showAll();
};
