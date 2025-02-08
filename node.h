#ifndef NODE_H
#define NODE_H
#include "student.h"

#include <iostream>
#include <cstring>

using namespace std;

class Node{
 public:
  Node(Student* newStudent);
  ~Node();
  void print();
  void setStudent(Student* newStudent);
  Student* getStudent();
  void setNext(Node* newNode);
  void append(Node* newNode);
  void depend(int checkID);
  Node* getNext();
  int getCollisions();
 private:
  Student* studentValue;
  Node* next;
  int collisions = 0;
};
#endif

