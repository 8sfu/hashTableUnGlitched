#include "node.h"

Node::Node(Student *newStudent) {
  next = NULL;
  studentValue = newStudent;
}

Node::~Node(){
  delete &studentValue;
  next = NULL;
}

void Node::print(){
  cout << studentValue->getFirstName() << " " << studentValue->getLastName() << " " << studentValue->getID() << " " << studentValue->getGPA() << " ";
  if(this->getNext() == nullptr){
    return;
  }
  this->getNext()->print();
}

void Node::setStudent(Student* newStudent) {
  studentValue = newStudent;
}

Student* Node::getStudent() {
  return studentValue;
}

void Node::setNext(Node* newNode){
  next = newNode;
}

void Node::append(Node* newNode){
  collisions++;
  if(this->getNext() == nullptr){
    this->setNext(newNode);
    return;
  } else {
    this->getNext()->append(newNode);
    return;
  }
}

void Node::depend(int checkId){
  if(this->getNext()->getStudent()->getID() == checkId){
    this->setNext(this->getNext()->getNext());
  } else {
    this->getNext()->depend(checkId);
  }
}

Node* Node::getNext() {
  return next;
}

int Node::getCollisions(){
  return collisions;
}
