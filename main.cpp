#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <cmath>
#include "student.h"
#include "node.h"
#include <iomanip>

using namespace std;

bool cmp(char* input, const char* check){
  if(!strcmp(input,(char*)check)){
    return true;
  }
  return false;
}

int keyGen(int id,int tblSize){ //generate a key for a node from its ID                                    
  return id % tblSize;
}

void addNode(Node* node, Node** hashTable, int key, int* tblSize){ //add a node to the hash table based on its ke\
y                                                                                                                 
  if(hashTable[key] == nullptr){
    hashTable[key] = node;
  }else if(hashTable[key]->getCollisions() > 2){
    hashTable = reHash(hashTable,tblSize);
  }else{
    hashTable[key]->append(node);
  }
}

Node** reHash(Node** hashTableOld, int* tblSize){
  cout << "NEW TABLE OF DOUBLE SIZE" << endl;
  *tblSize *= 2;
  cout << *tblSize << endl;
  Node** hashTableNew = new Node* [*tblSize];
  for(int i = 0; i < *tblSize/2; i++){
    Node* n1 = hashTableOld[i];
    int k1 = keyGen(n1->getStudent()->getID(),*tblSize);
    Node* n2 = n1->getNext();
    int k2 = keyGen(n2->getStudent()->getID(),*tblSize);
    Node* n3 = n2->getNext();
    int k3 = keyGen(n3->getStudent()->getID(),*tblSize);
    
    addNode(n1,hashTableNew,k1,tblSize);
    addNode(n2,hashTableNew,k2,tblSize);
    addNode(n3,hashTableNew,k3,tblSize);
    
    n1->zeroCollisions();
    n2->zeroCollisions();
    n3->zeroCollisions();
  }
  return hashTableNew;
}

void deleteNode(int id, int tblSize, Node** hashTable){
  cout << "id " << id << endl;
  int key = keyGen(id,tblSize);
  cout << "key gen " << key << endl;
  if(hashTable[key]->getStudent()->getID() == id){
    hashTable[key] = hashTable[key]->getNext(); //if the head node needs deletion, delete it
  } else {
    hashTable[key]->depend(id); //else, check its chained nodes
  }
  return;
}
  
void manualAdd(Node* node, Node** hashTable, int* tblSize){ //manually add a node to the table
  int key = keyGen(node->getStudent()->getID(),*tblSize);
  addNode(node,hashTable,key,tblSize);
}

void randomAdd(Node** hashTable, int* tblSize, int* randStart, int genSize){ //randomly generate a block of random students
  for(int i = *randStart; i < *randStart+genSize; i++){
    addNode(new Node(new Student(i)),hashTable,i % *tblSize,tblSize);
  }
  *randStart += genSize;
}

void printTbl(Node** hashTable, int tblSize){ //print out the chained nodes in each bucket of the table
  for(int i = 0; i < tblSize; i++){
    cout << "key/col " << i << " ";
    if(hashTable[i] != nullptr){
      hashTable[i]->print();
      cout << hashTable[i]->getCollisions();
    }
    cout << endl;
  }
}

int main(){
  char* input = new char[20];
  bool running = true;
  int tblSize = 100;
  int intput;
  int randStart = 0; //the random block of students will generate with ids greater than that of any manually generated students to prevent students from generating with the same ids, though this does not prevent conflicting manual student additions
  Node** hashTable = new Node* [tblSize];
  srand(time(NULL));
  
  
  while(running){
    cout << endl << "Available commands - ADD,PRINT,DELETE,QUIT" << endl;
    cin.getline(input,20);
    if(cmp(input,"ADD")){
      cout << "Available commands - MANUAL,RAND GEN" << endl;
      cin.getline(input,20);
      if(cmp(input,"MANUAL")){
	cout << "What is this student's id number?" << endl;
	cin >> intput;
	cin.ignore();
	if(randStart < intput){
	  randStart = intput+1;
	}
	manualAdd(new Node(new Student(intput)),hashTable,&tblSize);
      }else if(cmp(input,"RAND GEN")){
	cout << "How many students would you like to add?" << endl;
	cin >> intput;
	cin.ignore();
	randomAdd(hashTable,&tblSize,&randStart,intput);
      }
    }else if(cmp(input,"PRINT")){
      printTbl(hashTable,tblSize);
    }else if(cmp(input,"DELETE")){
      cout << "Who would you like to delete?" << endl;
      cin >> intput;
      cin.ignore();
      deleteNode(intput,tblSize,hashTable);
    }else{
      running = false;
    }
  } 
  
  cout << endl;
  delete[] input;
  return 0;
}
