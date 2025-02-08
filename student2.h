#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

class Student {
 public:
  Student(int newID);
  ~Student();
  char* getFirstName();
  char* getLastName();
  int getID();
  float getGPA();
 private:
  char* firstname = new char[20];
  char* lastname = new char[20];
  long id;
  float gpa;
};

#endif
