#include "Class.h"
#include <string>
#include "Student.h"

void Class::addStudent(const Student &st)//done
{
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)//done
{
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No matching student!";
}

double Class::getAvgScore()//done
{
    double score=0.0;
    int num=0;
    double avg;
    for(std::vector<StudentWrapper>::iterator it = students.begin();
        it !=students.end();
        ++it)
    {
        score=score+it->getScore();
        num=num+1;
    }
    avg=score/num;
    return avg;
}
