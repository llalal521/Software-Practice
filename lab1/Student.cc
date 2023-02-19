#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

std::string Student::toString() const
{
    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
    return "";
}
double Graduate::getGrade() const
{
    double record;
    int spoint=0;
    double gpa=0.0;
    for(unsigned int i=0;i<classes.size();++i)
    {
        spoint=spoint+classes[i]->point;
    }
    for(unsigned int i=0;i<classes.size();++i)
    {
        record=classes[i]->getStudentWrapper(id).getScore();
        if(record >=90 && record<=100) gpa=gpa+(4.0*classes[i]->point)/spoint;
        if(record >=80 && record<=89) gpa=gpa+(3.5*classes[i]->point)/spoint;
        if(record >=70 && record<=79) gpa=gpa+(3.0*classes[i]->point)/spoint;
        if(record >=60 && record<=69) gpa=gpa+(2.5*classes[i]->point)/spoint;
        if(record <60 && record>=0) gpa=gpa+(2.0*classes[i]->point)/spoint;
    }
    return gpa;
}
double Undergraduate::getGrade() const
{
    double record;
    int spoint=0;
    double gpa=0.0;
    for(unsigned int i=0;i<classes.size();++i)
    {
        spoint = spoint+classes[i]->point;
    }
    for(unsigned int i=0;i<classes.size();++i)
    {
        record=classes[i]->getStudentWrapper(id).getScore();
        gpa=gpa+record/20*classes[i]->point/spoint;
    }
    return gpa;
}
void Student::addClass(Class *C)
{
    classes.push_back(C);
}
