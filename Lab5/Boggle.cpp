#include <iostream>
#include "lexicon.h"
#include <string>
#include <vector>
#include <ctype.h>
#include <set>
#include <algorithm>

using namespace std;

bool JudgeIn(string *Boggle, string test, unsigned int pos, int a, int b, int n, bool **table);

void computer(string *Boggle, set<string> &Cset, vector<string> &Cvec, set<string> &Pset, string result, int a, int b, int &Cscore, int n, bool **table, Lexicon &dic);

void dicSort(vector<string> &Cset);

int main(){
    int n, num = 0;
    int score = 0;
    int Cscore = 0;
    bool flag = true;
    bool in = true;
    bool judge = true;
    bool repeat = false;
    string result;
    string test;
    vector<string> vec;
    vector<string> Cvec;
    vector<int> x;
    vector<int> y;
    set<string> pset;
    set<string> Pset;
    set<string> Cset;
    vector<string>::iterator it;
    set<string>::iterator sit;
    vector<int>::iterator d;
    Lexicon dic("EnglishWords.txt");
    char a;
    cin >> n;
    string *Boggle = new string[n];
    bool **table = new bool* [n];
    for(int i=0;i<n;++i)
        table[i] = new bool [n];
    for(int i=0;i<n;++i)
        cin >> Boggle[i];
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j){
            table[i][j] = true;
            Boggle[i][j]=toupper(Boggle[i][j]);
        }
    while(flag){
        for(int i=0;i<n;++i)
            cout << Boggle[i] << endl;
        cout << "Your Score: " << score << endl;
        cout << "Your Words: ";
        for(it = vec.begin();it != vec.end();++it)
            cout << *it << ' ';
        cout << endl;
        cin >> test;
        if(test == "???"){
            for(int i=0;i<n;++i)
                for(int j=0;j<n;++j){
                    computer(Boggle, Cset, Cvec, Pset, result, i, j, Cscore, n, table, dic);
                }
            cout << "Computer Score: "<< Cscore << endl;
            cout << "Computer Words: ";
            sort(Cvec.begin(), Cvec.end());
            for(it = Cvec.begin();it != Cvec.end();++it)
                cout << *it << ' ';
            cout << endl;
            break;
        }
        in = dic.contains(test);
        if(test.size() <= 3){
            cout << test << " is too short." << endl;
            continue;
        }
        if(!in){
            cout << test << " is not a word." << endl;
            continue;
        }
        a = toupper(test[0]);
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j){
                if(Boggle[i][j] == a){
                    x.push_back(i);
                    y.push_back(j);
                }
            }
        if(x.size() == 0){
            cout << test << " is not on board." << endl;
            continue;
        }
        for(d = x.begin();d != x.end();++d){
            judge = JudgeIn(Boggle, test, 1, x[num], y[num], n, table);
            if(judge == true){
                break;
            }
            num = num + 1;
        }
        x.clear();
        y.clear();
        num = 0;
        if(judge == true){
            for(unsigned int i=0;i<test.size();++i)
                test[i] = tolower(test[i]);
            if(pset.find(test) != pset.end()){
                repeat = true;
                cout << test << " is already found." << endl;
            }
            if(repeat == false){
                vec.push_back(test);
                pset.insert(test);
                for(unsigned int i=0;i<test.length();++i)
                    test[i] = toupper(test[i]);
                Pset.insert(test);
                score = score + test.size() - 3;
            }
            repeat = false;
        }
        else cout << test << " is not on board." << endl;
        judge = false;
    }
    return 0;
}


bool JudgeIn(string *Boggle, string test, unsigned int pos, int a, int b, int n, bool **table){
    if(pos >= test.length())
        return true;
    char c = toupper(test[pos]);
    bool result = false;
    for(int i=-1;i<2;++i){
        for(int j=-1;j<2;++j){
            table[a][b] = false;
            if(a+i >= 0 && a+i < n && b+j >= 0 && b+j < n && table[a+i][b+j] && Boggle[a+i][b+j] == c)
                if(i != 0 || j != 0)
                    result = JudgeIn(Boggle, test, pos+1, a+i, b+j, n, table);
            table[a][b] = true;
            if(result) break;
        }
        if(result) break;
    }
    return result;
}

void computer(string *Boggle, set<string> &Cset, vector<string> &Cvec ,set<string> &pset, string result, int a, int b, int &Cscore, int n, bool **table, Lexicon &dic){
    bool repeat = false;
    string tmp = result + Boggle[a][b];
    if(Cset.find(tmp) != Cset.end())
        repeat = true;
    if(pset.find(tmp) != pset.end())
        repeat = true;
    if(tmp.length() > 3)
        if(!repeat && dic.contains(tmp)){
            Cvec.push_back(tmp);
            Cset.insert(tmp);
            Cscore = Cscore + tmp.length() - 3;
        }
    for(int i=-1;i<2;++i)
        for(int j=-1;j<2;++j)
            if(i!=0 || j!=0){
                table[a][b] = false;
                if(a+i >= 0 && a+i < n && b+j >= 0 && b+j < n && table[a+i][b+j] && dic.containsPrefix(tmp))
                    computer(Boggle, Cset, Cvec, pset, tmp, a+i, b+j, Cscore, n, table, dic);
                table[a][b] = true;
            }
    return;
}


