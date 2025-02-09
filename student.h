#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

class Student {
 public:
  Student(char* setfName, char* setLname, int setID);
  ~Student();
  char* getFirstName();
  char* getLastName();
  int getID();
  float getGPA();
 private:
  char* firstname = new char[10];
  char* lastname = new char[10];
  long id;
  float gpa;
};

#endif
