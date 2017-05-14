

// reverse map blocks

void reverse_blocks(string &s){
  vector<string> stack;
  string s2;
  int i=0;
  while(i<s.size() and s[i]!='#'){
    s2+=s[i];
    i++;
  }
  while(i<s.size()){
    if(s[i]=='#'){
      stack.push_back("#");
      i++;
    }else if(s[i]=='*'){
      while(not stack.empty()){
        s2 += stack.back();
        stack.pop_back();
      }
      while(i<s.size() and s[i]!='#'){
        s2+=s[i];
        i++;
      }
    }else{
      stack.back()+=s[i];
      i++;
    }
  }
  while(not stack.empty()){
    s2 += stack.back();
    stack.pop_back();
  }
  s=s2;
}

void mtest(int x, int y, int m, int n){
  if(x<0 || x>=n){
    cout << "(x, y) == (" << x << ", " << y << ")" << endl;
    cout << "Error in fill_map: x is out of bounds " << 0 << ".." << n-1 << "." << endl;
    exit(1);
  }
  if(y<0 || y>=m){
    cout << "(x, y) == (" << x << ", " << y << ")" << endl;
    cout << "Error in fill_map: y is out of bounds " << 0 << ".." << m-1 << "." << endl;
    exit(1);
  }
}

void fill_map(Map &map, block_table &btab, int x, int y, const string &sp){

  Img *b1, *bg, *bf, *s1;
  b1 = btab.b1;
  bg = btab.bg;
  bf = btab.bf;

  int m = map.h;
  int n = map.w;
  
  int x0=x;
  int y0=y-1;

  string s = sp;
  reverse_blocks(s);

  y=y0;
  for(int i=0; i<s.size(); i++){
    if(s[i]=='#'){
      x=x0; y++;
    }else if(s[i]=='*'){
      y=y0;
      x0+=map.mbsize;
    }else if(s[i]=='.' and s[i+1]=='.'){
      i++;
      x++;
    }else if(s[i]=='b'){
      mtest(x,y,m,n);
      if(s[i+1]=='1'){
        map.p[n*y+x].block = b1;
        map.p[n*y+x].solid = 2;
      }else if(s[i+1]=='p'){
        map.p[n*y+x].block = btab.portal;
        map.p[n*y+x].solid = 0;
      }
      i++;
      x++;
    }else if(s[i]=='m' and s[i+1]=='1'){
      mtest(x,y,m,n);
      map.p[n*y+x].block = bg;
      map.p[n*y+x].solid = 2;
      i++;
      x++;
    }else if(s[i]=='m' and s[i+1]=='2'){
      mtest(x,y,m,n);
      map.p[n*y+x].block = bg;
      map.p[n*y+x].solid = 1;
      i++;
      x++;
    }else if(s[i]=='f' and s[i+1]=='1'){
      mtest(x,y,m,n);
      map.p[n*y+x].block = bf;
      map.p[n*y+x].solid = 2;
      i++;
      x++;
    }else if(s[i]=='s'){
      mtest(x,y,m,n);
      i++;
      if(s[i]=='t'){
        map.p[n*y+x].block = btab.st;
      }else if(s[i]=='m'){
        map.p[n*y+x].block = btab.sm;
      }else if(s[i]=='b'){
        map.p[n*y+x].block = btab.sb;
      }
      map.p[n*y+x].solid = 0;
      x++;
    }else if(s[i]=='g' and s[i+1]=='1'){
      mtest(x,y,m,n);
      map.p[n*y+x].block = btab.g1;
      map.p[n*y+x].solid = 3;
      i++;
      x++;
    }else if(s[i]=='a' and s[i+1]=='1'){
      mtest(x,y,m,n);
      map.p[n*y+x].block = btab.a1;
      map.p[n*y+x].solid = 4;
      i++;
      x++;
    }else if(s[i]=='t'){
      mtest(x,y,m,n);
      char c = s[i+1];
      if(c=='1'){
        map.p[n*y+x].block = btab.t1;
        map.p[n*y+x].solid = -1;
      }else if(c=='2'){
        map.p[n*y+x].block = btab.t2;
        map.p[n*y+x].solid = -2;
      }else if(c=='3'){
        map.p[n*y+x].block = btab.t3;
        map.p[n*y+x].solid = -3;
      }
      i++;
      x++;
    }else if(s[i]=='d'){
      mtest(x,y,m,n);
      char c = s[i+1];
      if(c=='1'){
        map.p[n*y+x].block = 0;
        map.p[n*y+x].solid = -10;
      }else if(c=='u'){
        map.p[n*y+x].block = btab.du;
        map.p[n*y+x].solid = 0;
      }else if(c=='2'){
        map.p[n*y+x].block = btab.b1;
        map.p[n*y+x].solid = -10;
      }else if(c=='3'){
        map.p[n*y+x].block = btab.du;
        map.p[n*y+x].solid = -20;
      }
      i++;
      x++;
    }else if(s[i]=='e' and s[i+1]=='1'){
      mtest(x,y,m,n);
      Enemy* p = new Enemy(x*24, y*24);
      p->img = btab.enemy1;
      aenemy.append(p);
      i++;
      x++;
    }else if(s[i]=='p'){
      int index = s[i+1]-'0';
      if(index<0 || index>9){
        cout << "Error in map file: expected p0 upto p9." << endl;
      }else{
        pos[index].x = x*24;
        pos[index].y = y*24;
      }
      i++;
      x++;
    }else if(s[i]=='P'){
      mtest(x,y,m,n);
      int index = s[i+1]-'0';
      if(index<0 || index>9){
        cout << "Error in map file: xpected P0 upto P9." << endl;
      }else{
        map.p[n*y+x].block = NULL;
        map.p[n*y+x].solid = -40-(s[i+1]-'0');
      }
      i++;
      x++;
    }
  }
}

void load_map(const string &id, Map &map, block_table &btab){
  ifstream is;
  is.open(id.c_str(), ios::binary);
  if(not is){
    cout << "Konnte Datei " << id << " nicht oeffnen." << endl;
    exit(1);
  }
  string m1;
  tk::read(is,m1);
  is.close();
  fill_map(map,btab,0,0,m1);
}

