
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include "tk.hpp"

namespace tk{

using namespace std;

void input(string &s){
  getline(cin,s);
}

void itos(string &s, int n){
  char buffer[20];
  snprintf(buffer, 20, "%i", n);
  s=buffer;
}

int stoi(const string &s){
  return atoi(s.c_str());
}

void lstrip(string &s, bool test(char)){
  int k=0;
  while(k<s.size() and test(s[k])) k++;
  s = s.substr(k,s.size()-k);
}

void rstrip(string &s, bool test(char)){
  int k=s.size()-1;
  while(k>=0 and test(s[k])) k--;
  s = s.substr(0,k+1);
}

void strip(string &s, bool test(char)){
  lstrip(s,test);
  rstrip(s,test);
}

void load(string &s, const char* id){
  FILE* f;
  int size;
  char* buffer;
  f = fopen(id,"rb");
  if(f==0){
    cout << "File " << id << " could not be opened." << endl;
    exit(1);
  }else{
    fseek(f,0,SEEK_END);
    size = ftell(f);
    buffer = new char[size];
    fseek(f,0,SEEK_SET);
    fread(buffer,1,size,f);
    s=string(buffer,size);
    delete[] buffer;
  }
}

void save(const string &s, const char* id){
  FILE* f = fopen(id,"wb");
  if(f==0){
    cout << "File " << id << " could not be opened." << endl;
    exit(1);
  }else{
    fputs(s.c_str(),f);
    fclose(f);
  }
}

void read(ifstream &is, string &s){
  int size;
  char *buffer;
  is.seekg(0, ios::end);
  size = is.tellg();
  is.seekg(0, ios::beg);
  if(size==0){
    s.clear();
    return;
  }
  buffer = new char [size];
  is.read(buffer,size);
  s = string(buffer,size);
  delete[] buffer;
}

void read(ifstream &is, vector<unsigned char> &v){
  int size;
  char *buffer;
  is.seekg(0, ios::end);
  size = is.tellg();
  is.seekg(0, ios::beg);
  if(size==0){
    v.clear();
    return;
  }
  buffer = new char [size];
  is.read(buffer,size);
  for(int i=0; i<size; i++){
    v.push_back(buffer[i]);
  }
  delete[] buffer;
}

}
// namespace
