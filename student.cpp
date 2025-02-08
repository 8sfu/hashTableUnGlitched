#include "student.h"
#include <cstring>

using namespace std;

Student::Student(int newID){
  firstname = (char*)"cheap";
  lastname = (char*)"eggs";
  id = newID;
  gpa = static_cast<float>(rand() % 300);
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
