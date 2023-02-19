#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>

class Class; //decleration of a uncommon class

enum Degree {
    undergraduate,
    graduate
};

class Student {
private:
    const std::string name;
    const std::string year;
    const Degree degree;
protected:
    std::vector<Class*> classes;
public:
    Student(const std::string id,const std::string name, const std::string year,const Degree degree):name(name),year(year),degree(degree),id(id) {};
    const std::string id;
    std::string toString() const;
    virtual double getGrade() const =0;
    void addClass (Class* C);
};

class Graduate: public Student
{
public:
    Graduate(const std::string a,const std::string b,const std::string c):Student(a,b,c,graduate){};
    double getGrade() const;
};

class Undergraduate: public Student
{
public:
    Undergraduate(const std::string a,const std::string b,const std::string c):Student(a,b,c,undergraduate){};
    double getGrade() const;
};

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    StudentWrapper(const std::string &id, const Student &student): student(student),id(id){}
    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Invalid Score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
