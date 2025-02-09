/* Hash Table - Aman Tesfu Feb 2024
Note: This hash table will not check if manual student inputs conflict with prior generated blocks of students. It handles collisions properly, but not UO error. Please be careful!
Thank you!
 */

#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <cmath>
#include "student.h"
#include "node.h"
#include <iomanip>
#include <fstream>

using namespace std;

bool cmp(char* input, const char* check){ //simplified cstring to "const char" comparison function
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
      // cout << hashTable[i]->getCollisions();
    }
    cout << endl;
  }
}

Node** addNode(Node* node, Node** hashTable, int key, int* tblSize){ //add a node to the hash table based on its key
  if(hashTable[key] == nullptr){ //if the bucket is empty, drop the node straight in
    hashTable[key] = node;
    return hashTable;
  }else if(hashTable[key]->getCollisions() > 2){ //if a node has been chained to three times and is hit a third time, the list needs rehashing
    printTbl(hashTable,*tblSize);
    *tblSize *= 2;
    Node** hashTableNew = new Node* [*tblSize]{};
    // printTbl(hashTableNew,*tblSize);

    for(int i = 0; i < *tblSize/2; i++){ //could iterate through the nodes chained in a bucket more simply, but this is a holdover from when the code was seg-faulting due to the new hash table not being resized, and it works fine. would be terrible to program in this way for anything tolerating more than a dozen collisions, though.
      if(hashTable[i] != nullptr){
	Node* n1 = new Node(hashTable[i]->getStudent()); //for each potential node in a bucket, check that it exists, and then copy it to the placeholder table
	int k1 = keyGen(n1->getStudent()->getID(),*tblSize);
	n1->zeroCollisions();
	hashTableNew = addNode(n1,hashTableNew,k1,tblSize);
	if(hashTable[i]->getNext() != nullptr){
	  Node* n2 = new Node(hashTable[i]->getNext()->getStudent());
	  int k2 = keyGen(n2->getStudent()->getID(),*tblSize);
	  n2->zeroCollisions();
	  hashTableNew = addNode(n2,hashTableNew,k2,tblSize);
	  if(hashTable[i]->getNext()->getNext() != nullptr){
	    Node* n3 = new Node(hashTable[i]->getNext()->getNext()->getStudent());
	    int k3 = keyGen(n3->getStudent()->getID(),*tblSize);
	    n3->zeroCollisions();
	    hashTableNew = addNode(n3,hashTableNew,k3,tblSize);
	  }
	}
      }
      //printTbl(hashTableNew,*tblSize);
    }
    int key = keyGen(node->getStudent()->getID(),*tblSize);
    hashTableNew = addNode(node,hashTableNew,key,tblSize);
    //    printTbl(hashTableNew,*tblSize);
        
    delete[] hashTable; //copy placeholder table contents to the original expanded hash table
    hashTable = new Node*[*tblSize]{};
    hashTable = hashTableNew;
    return hashTable;
  }else{ //if the bucket already has node(s), recurse through any chained nodes to put the new node at the end
    hashTable[key]->append(node);
    return hashTable;
  }
}

Node** deleteNode(int id, int tblSize, Node** hashTable){
  cout << "id " << id << endl;
  int key = keyGen(id,tblSize);
  cout << "key gen " << key << endl;
  if(hashTable[key]->getStudent()->getID() == id){ //check in the appropriate bucket using the key
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

Node** randomAdd(Node** hashTable, int* tblSize, int* randStart, int genSize,char flist[25][10], char llist[25][10]){ //randomly generate a block of random students
  for(int i = *randStart; i < *randStart+genSize; i++){
    hashTable = addNode(new Node(new Student(flist[rand()%25],llist[rand()%25],i)),hashTable,i % *tblSize,tblSize);
  }
  *randStart += genSize;
  return hashTable;
}

int main(){
  char* input = new char[20];
  char* word = new char[10];
  bool running = true;
  int tblSize = 3;
  int intput;
  int randStart = 0; //the random block of students will generate with ids greater than that of any manually generated students to prevent students from generating with the same ids, though this does not prevent conflicting manual student additions
  Node** hashTable = new Node* [tblSize]{};
  srand(time(NULL));
  
  fstream f;
  fstream l;

  f.open("f.txt",fstream::in);
  l.open("l.txt",fstream::in);
  
  char fist[25][10] = {};
  char list[25][10] = {};
  
  for(int i = 0; i < 25; i++){
    f >> word;
    strcpy(fist[i],word);
    
    l >> word;
    strcpy(list[i],word);
  }

  cout << fist[rand() % 25] << " " << list[rand() % 25] << endl;
  
  while(running){ //take inputs and call appropriate functions
    cout << endl << "Available commands - ADD,PRINT,DELETE,QUIT" << endl;
    cin.getline(input,20);
    if(cmp(input,"ADD")){
      cout << "Available commands - MANUAL,RAND GEN" << endl;
      cin.getline(input,20);
      if(cmp(input,"MANUAL")){
	cout << "What is this student's id number?" << endl;
	cin >> intput;
	cin.ignore();
	if(randStart <= intput){ //increment the random gen student block above the last manually added student
	  randStart = intput+1;
	}
	char* firstname = new char[10]; //Take inputs for the id, first, last name
	cout << "First name?" << endl;
	cin.getline(firstname,10);
	char* lastname = new char[10];
	cout << "Last name?" << endl;
	cin.getline(lastname,10);
	hashTable = manualAdd(new Node(new Student(firstname,lastname,intput)),hashTable,&tblSize);
	delete[] firstname;
	delete[] lastname;
      }else if(cmp(input,"RAND GEN")){
	cout << "How many students would you like to add?" << endl;
	cin >> intput;
	cin.ignore();
	hashTable = randomAdd(hashTable,&tblSize,&randStart,intput,fist,list);
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

  f.close();
  l.close();
  cout << endl;
  delete[] input;
  return 0;
}
