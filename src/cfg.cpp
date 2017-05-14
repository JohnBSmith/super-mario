
void error(const char* id){
  cout << "Error in config file '" << id << "':" << endl;
}

int load_cfg(std::map<string,void*> &m, const char* id){
  string s;
  ifstream is;
  is.open(id,ios::binary);
  if(is){
    tk::read(is,s);
    is.close();
  }else{
    cout << "Could not load file \"" << id << "\".\n";
    return 0;
  }
  int i;
  string key, value;
  m.clear();
  i=0;
  while(i<s.size()){
    if(isalpha(s[i])){
      key="";
      while(isalpha(s[i])){key+=s[i]; i++;}
    }else if(s[i]=='"'){
      i++;
      value="";
      while(s[i]!='"'){
        if(s[i]=='\\' and i+1<s.size()){
          i++;
          char c = s[i];
          if(c=='n') value+='\n';
          else if(c=='t') value+='\t';
          else if(c=='d') value+='"';
          else if(c=='q') value+='\'';
          else if(c=='s') value+=' ';
          else if(c=='b') value+='\\';
        }else if(s[i]=='\n'){
          error(id);
          cout << "line break inside of a string." << endl;
        }else{
          value+=s[i];
        }
        i++;
      }
      i++;
      if(m.count(key)>0) delete static_cast<string*>(m[key]);
      m[key] = new string(value);
    }else if(isspace(s[i])){
      i++;
    }else if(s[i]=='='){
      i++;
    }else if(s[i]=='#'){
      while(i<s.size() and s[i]!='\n') i++;
    }else{
      error(id);
      cout << "unexpected character: " << s[i] << endl;
    }
  }
  return 1;
}

int find(std::map<string,void*> &m, string &s, const string &key){
  if(m.count(key)>0){
    s = *static_cast<string*>(m[key]);
    return 1;
  }else{
    s="";
    return 0;
  }
}

int set_cfg(Map &map, const char* id){
  string s;
  std::map<string,void*> m;
  int success = load_cfg(m,id);
  if(success){
    if(m.count("map")) find(m,map_id,"map");
    if(m.count("w")){
      find(m,s,"w");
      map.w = tk::stoi(s);
    }
    if(m.count("h")){
      find(m,s,"h");
      map.h = tk::stoi(s);
    }
  }
  return 1-success;
}

