#include "student.h"
#include <cstring>

using namespace std;

Student::Student(char* setFname, char* setLname, int setID){
  firstname = setFname;
  lastname = setLname;
  id = setID;
  gpa = static_cast<float>(rand() % 401)/100;
}

char* Student::getFirstName(){
  return firstname;
}

char* Student::getLastName(){
  return lastname;
}

int Student::getID(){
  return id;
}

float Student::getGPA(){
  return gpa;
}

Student::~Student(){
  delete[] firstname;
  delete[] lastname;
}
