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

Node** addNode(Node* node, Node** hashTable, int key, int* tblSize){ //add a node to the hash table based on its key
  if(hashTable[key] == nullptr){
    hashTable[key] = node;
    //cout << "SSETTING " << node->getStudent()->getID() << " AT " << &hashTable[key] << " @ " << key << endl;
    return hashTable;
  }else if(hashTable[key]->getCollisions() > 2){
    printTbl(hashTable,*tblSize);
    *tblSize *= 2;
    //    cout << "SETTTING TBLSIZE " << *tblSize << endl;
    cout << endl << "THIS IS THE NEW BIG TABLE" << endl;
    Node** hashTableNew = new Node* [*tblSize]{};
    printTbl(hashTableNew,*tblSize);

    /* cout << endl;
    printTbl(hashTable,*tblSize/2);
    cout << endl;
    printTbl(hashTableNew,*tblSize);
    cout << endl;*/

    
    for(int i = 0; i < *tblSize/2; i++){
      Node* n1 = new Node(hashTable[i]->getStudent());
      Node* n2 = new Node(hashTable[i]->getNext()->getStudent());
      Node* n3 = new Node(hashTable[i]->getNext()->getNext()->getStudent());
      
      cout << endl << "N1 ";
      n1->print();
      cout << endl;
      
      cout << "N2 ";
      n2->print();
      cout << endl;

      cout << "N3 ";
      n3->print();
      cout << endl;
      
      cout << endl;
      
      int k1 = keyGen(n1->getStudent()->getID(),*tblSize);
      n1->zeroCollisions();
      hashTableNew = addNode(n1,hashTableNew,k1,tblSize);

      int k2 = keyGen(n2->getStudent()->getID(),*tblSize);
      n2->zeroCollisions();
      hashTableNew = addNode(n2,hashTableNew,k2,tblSize);

      int k3 = keyGen(n3->getStudent()->getID(),*tblSize);
      n3->zeroCollisions();
      hashTableNew = addNode(n3,hashTableNew,k3,tblSize);
      
      printTbl(hashTableNew,*tblSize);
    }
    int key = keyGen(node->getStudent()->getID(),*tblSize);
    hashTableNew = addNode(node,hashTableNew,key,tblSize);
    

    cout << endl << "NEW TABLE" << endl;
    printTbl(hashTableNew,*tblSize);
    cout << endl << endl;
    
    delete[] hashTable;
    hashTable = new Node*[*tblSize]{};
    hashTable = hashTableNew;
    //cout << "OLD TABLE" << endl;
    //printTbl(hashTable,*tblSize);
    //cout << endl;
    return hashTable;
  }else{
    hashTable[key]->append(node);
    return hashTable;
    //cout << "ESETTING " << node->getStudent()->getID() << " AT " << &hashTable[key] << " @ " << key << endl;
  }
}

Node** deleteNode(int id, int tblSize, Node** hashTable){
  cout << "id " << id << endl;
  int key = keyGen(id,tblSize);
  cout << "key gen " << key << endl;
  if(hashTable[key]->getStudent()->getID() == id){
    hashTable[key] = hashTable[key]->getNext(); //if the head node needs deletion, delete it
  } else {
    hashTable[key]->depend(id); //else, check its chained nodes
  }
  return hashTable;
}
  
Node** manualAdd(Node* node, Node** hashTable, int* tblSize){ //manually add a node to the table
  int key = keyGen(node->getStudent()->getID(),*tblSize);
  hashTable = addNode(node,hashTable,key,tblSize);
  return hashTable;
}

Node** randomAdd(Node** hashTable, int* tblSize, int* randStart, int genSize){ //randomly generate a block of random students
  for(int i = *randStart; i < *randStart+genSize; i++){
    hashTable = addNode(new Node(new Student(i)),hashTable,i % *tblSize,tblSize);
  }
  *randStart += genSize;
  return hashTable;
}

int main(){
  char* input = new char[20];
  bool running = true;
  int tblSize = 3;
  int intput;
  int randStart = 0; //the random block of students will generate with ids greater than that of any manually generated students to prevent students from generating with the same ids, though this does not prevent conflicting manual student additions
  Node** hashTable = new Node* [tblSize]{};
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
	if(randStart <= intput){
	  randStart = intput+1;
	}
	hashTable = manualAdd(new Node(new Student(intput)),hashTable,&tblSize);
      }else if(cmp(input,"RAND GEN")){
	cout << "How many students would you like to add?" << endl;
	cin >> intput;
	cin.ignore();
	hashTable = randomAdd(hashTable,&tblSize,&randStart,intput);
      }
    }else if(cmp(input,"PRINT")){
      printTbl(hashTable,tblSize);
    }else if(cmp(input,"DELETE")){
      cout << "Who would you like to delete?" << endl;
      cin >> intput;
      cin.ignore();
      hashTable = deleteNode(intput,tblSize,hashTable);
    }else{
      running = false;
    }
  } 
  
  cout << endl;
  delete[] input;
  return 0;
}
