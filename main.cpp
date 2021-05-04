#include <iostream>
#include <fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include <cmath>

//05/02/2021
//J. Chegwidden - Tccd
//node/tree tutorial
//class practice

using namespace std;
struct node{
  // string AS a name
  string name;
  string parent;
  // can have multiple child no one child policy here fuck cpp
  vector<node> child;
};

bool addChild(node &head, string parent, string child){
  // do you want to check if the child exist
  // assumption no duplicates entries
  // asumption Where parent always exist before child

  // if parent is same as 
  if(head.name == parent){
    // add the child
    node c;
    c.parent = parent;
    c.name = child;
    head.child.push_back(c);
    return true;
  }

  //now iterate through children if the parent 
  for(int i=0; i<head.child.size(); i++){
    if(addChild(head.child[i], parent, child)){
      return true;
    }
  }
  return false;    
}

void printTree(node head, int numSpaces){
  for(int i=0; i < numSpaces; i++){
    cout<<" ";
  }
  cout<<head.name<<"\n"<<endl;
  if(head.child.size() == 0){
    return;
  }
  for(int i=0; i < head.child.size(); i++){ 
    printTree(head.child[i], numSpaces+4);
  }
}

void makeTree(vector<string> names, node &head){
  if(names.size() < 1){
    return;
  }
  head.name = names[0];
  cout<< names.size()<<endl;
  for(int i = 1; i < names.size(); i++ ){
    int firstSpace = -1;
    for(int j=0; j<names[i].length(); j++){
      if(names[i][j] == ' '){
        firstSpace = j;
        break;
      }
    }
    if(firstSpace != -1){
      string child = names[i].substr(0, firstSpace);
      string parent = names[i].substr(firstSpace+1);
      // since paremnt and child are found let's fill it up
      if(!addChild(head, parent, child)){
        cout<<"Parent "<<parent<<"\n"<<endl;
        cout<<"Child "<<child<<"\n"<<endl;
        cout<<"Parent not found"<<endl;
      }
    }
  }
  printTree(head, 0);
  return;
}

int findLevel(node head, string name, int previousLevel){
  if(head.name == name){
    return previousLevel+1;
  }

  //now iterate through children if the parent 
  for(int i=0; i<head.child.size(); i++){
    int LevelFound = findLevel(head.child[i], name, previousLevel+1); 
    if(LevelFound > 0){
      return LevelFound;
    }
  }
  return 0; 
}

string getParent(node head, string name){

  for(int i=0; i<head.child.size(); i++){
    if(head.child[i].name == name){
      return head.name;
    }
     string p = getParent(head.child[i], name);
     if(p.length() > 0){
       return p;
     }
    }
  
    return "";
  }


int main() {
string name, fam;
ifstream fin;
vector<string> family;
node head;
cout << "Enter the name of the file: ";
cin >> name;
fin.open(name);
//fin.open("relations.txt");
if(!fin.is_open()){
  cout<< "Error reading the file";
}
else{
  while(std::getline(fin, fam)){
    family.push_back(fam);
   // cout<< fam << endl;

  }
  makeTree(family, head);
  // now relationships 
  // What we have here: The HEAD of the tree
  // You get two names
  // find level of every name
  // 1 and second is 3
  string name1;
  string name2;

  

  bool keepFinding = true;
  do{
    cout << endl;
    cout << "Enter two names (Type Q to end): ";
    cin >> name1;
    cout << endl;
    if (name1 == "q"  || name1 == "Q"){
      keepFinding = false;
    }
    else{
      cin >> name2;
    }

    if(name1 != "Q" && name1 != "q"){
  
  
  int nameOneLevel = findLevel(head, name1, 0);
  if(nameOneLevel == 0){
    cout<<"Name 1 not found: "<<name1<<"\n"<<endl;
  }

  int nameTwoLevel = findLevel(head, name2, 0);
  if(nameTwoLevel == 0){
    cout<<"Name 2 not found: "<<name2<<"\n"<<endl;
  }  

  if(nameOneLevel == 1){
    int levelDiff = nameTwoLevel - nameOneLevel;

    if(levelDiff == 2){
      cout << name1 << " is " << name2 << "'s Grandmother" << endl; 
    }
    if(levelDiff == 3){
      cout << name1 << " is " << name2 << "'s Great Grandmother" << endl; 
    }
  }

  if(nameTwoLevel == 1){
    int levelDiff = nameOneLevel - nameTwoLevel;

    if(levelDiff == 2){
      cout << name1 << " is " << name2 << "'s Granddaughter" << endl; 
    }
    if(levelDiff == 3){
      cout << name1 << " is " << name2 << "'s Great Granddaughter" << endl; 
    }
  }


  if(nameOneLevel == nameTwoLevel){
    if(getParent(head, name2) == (getParent(head, name1))){
      cout << name1 << " and " << name2 << " are Sisters" << endl;
    }
    else{
      cout << name1 << " and " << name2 << " are 1st Cousins" << endl;
    }

  }

  int check = abs(nameOneLevel - nameTwoLevel);

    if(check == 1){

      if(nameOneLevel < nameTwoLevel){
        if(getParent(head, name2) == name1){
          cout << name1 << " is " << name2 << "'s Mother" << endl;
        }
        else{
          cout << name1 << " is " << name2 << "'s Aunt" << endl;
        }

      }
    if(nameOneLevel > nameTwoLevel){
        if(getParent(head, name1) == name2){
          cout << name1 << " is " << name2 << "'s Daughter" << endl;
        }
        else{
          cout << name1 << " is " << name2 << "'s Neice" << endl;
        }

      }
    }

    if(check == 2){

      if(nameOneLevel < nameTwoLevel){
        string temp = getParent(head, name2);
        if(getParent(head, temp) == name1){
          cout << name1 << " is " << name2 << "'s Grandmother" << endl;
        }
        else{
          cout << name1 << " is " << name2 << "'s Great Aunt" << endl;
        }
      }

    if(nameOneLevel > nameTwoLevel){

        string temp = getParent(head, name1);
        if(getParent(head, temp) == name2){
          cout << name1 << " is " << name2 << "'s Grand Daughter" << endl;
        }
        else{
          cout << name1 << " is " << name2 << "'s Great Neice" << endl;
        }

      }




    }
    }
  }while(keepFinding);



  // if any of those two names have level as one **
  // if name one has level one 1 then mother + grand depends on the level deifference **
  // if the name two has level 1 then daughter + grand depends on the level deifference **
  // if same level then check for the parents if parents same sister otherwise cousins
  // if diffrent level but no one consist 1 then 
}
 return 0;
}