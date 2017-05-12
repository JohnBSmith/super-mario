
int load_cfg(std::map<string,void*> &m, const char* id){
  string s;
  ifstream is;
  is.open(id,ios::binary);
  if(is){
    tk::read(is,s);
    is.close();
  }else{
    cout << "Konnte Datei \"" << id << "\" nicht laden.";
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
          cout << "Fehler: Zeilenumbruch in Zeichenkette." << endl;
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
      cout << "Fehler: unbekanntes Zeichen " << s[i] << endl;
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

void set_cfg(const char* id){
  string s;
  std::map<string,void*> m;
  int success = load_cfg(m,id);
  if(success){
    if(m.count("map")) find(m,map_id,"map");
    if(m.count("posx")){
      find(m,s,"posx");
      posx0 = tk::stoi(s);
    }
    if(m.count("posy")){
      find(m,s,"posy");
      posy0 = tk::stoi(s);
    }
  }
}

