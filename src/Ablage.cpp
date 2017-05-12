
void fill_map2(Map &map, block_table &btab, int x, int y, const char* p){
  int i;
  int x0=x;
  int h = map.n;
  Img *bb, *bg, *bf;
  bb=btab.bb;
  bg=btab.bg;
  bf=btab.bf;
  for(i=0; p[i]!=0; i++){
    if(isalpha(p[i])){
      if(0<=x and x<=map.m and 0<=y and y<=map.n){
        if(p[i]=='x'){
          map.p[h*y+x].block = bb;
          map.p[h*y+x].solid=2;
        }else if(p[i]=='m'){
          map.p[h*y+x].block = bg;
          map.p[h*y+x].solid=2;
        }else if(p[i]=='g'){
          map.p[h*y+x].block = bb;
        }else if(p[i]=='u'){
          map.p[h*y+x].block = bg;
          map.p[h*y+x].solid=1;
        }else if(p[i]=='f'){
          map.p[h*y+x].block = bf;
          map.p[h*y+x].solid=2;
        }
      }else{
        cout << "Unzulaessige Unterschreitung in fill_map" << endl;
      }
    }else if(p[i]=='\n'){
      x=x0-1;
      y-=1;
    }
    x+=1;
  }
}


/*
  fill_map(map,btab,0,10,
"                                                           u    xuux\n"
"                                            mm                  xuux\n"
"     uuffffuu                               xx             u    xuux\n"
"                  mm  mmmm  mm        mmmm       mm             xuux\n"
"                 mxx  x  x  xxm       xxxx       xxfffmm   u    xuux\n"
"mmmmmmmmmmmmmmmmmxxx  x  x  xxxm                      xx        \n"
"xxxxxxxxxxxxxxxxxxxx  g  x  xxxxm         \n"
"xxxxxxxxxxxxxxxxxxxx  g  x  xxxxxmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n"
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
//*/

/*
  fill_map2(map,btab,0,20,
"\n"
"   xux  \n"
"   xux          uu\n"
"   xux  uu                  uu\n"
"   xux            uu\n"
"   xux     uu                             u           u\n"
"   xux\n"
"   xux                    uu                                    u\n"
"   xux      u      u                u                 u      u        u\n"
"   xux                                  uu\n"
"   xux            uu\n"
"                            uuffffuu\n"
"                            \n"
"     x                                     uu\n"
"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n"
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
//*/

/*
  map.mbsize = 8;
  string s1 =
"#........b1"
"#b1b1b1b1b1........b1|"
"#st......st........st|"
"#sm......sm........sb|"
"#sb......sb........st|"
"#b1b1b1b1b1b1b1....sb"
"#st......st........st|"
"#sm......sm........sm"
"#sb......sb........sb"
"#b1b1b1b1b1b1b1b1b1b1|";
  fill_map(map, btab, 0, 0, s1);
*/


//
// altes Programm
//


using namespace std;
using namespace apus;

using tk::itos;

struct Img{
  int w,h;
  unsigned char* p;
};

struct block_table{
  Img *bb, *bg, *bf;
};

int posx0=0, posy0=200;
int posx=0, posy=0;
int go_left, go_right;
int jump, go_down;
int main_loop_end;
int mirror;
int ktype;
int jump_counter;
int jump_m;
bool dark;

int cup, cdown, cleft, cright;

const int key_down=1, key_up=2;

struct map_element{
  int solid;
  Img* block;
};

struct Map{
  map_element* p;
  int m,n;
};

void init_pos(){
  posx=posx0;
  posy=posy0;
}

Img* load_ppm(const string &path){
  ifstream in;
  vector<unsigned char> v;
  int w,h;
  string s;
  Img* img;
  in.open(path.c_str(), ios::in|ios::binary);
  if(not in){
    cout << "Konnte ppm-Datei " << path << " nicht oeffnen.\n"; 
    exit(1);
  }
  tk::read(in,v);
  in.close();
  int i=0;
  while(v[i]!='\n') i++;
  i++;
  while(v[i]!=' '){s+=v[i]; i++;}
  i++;
  w=tk::stoi(s);
  s="";
  while(v[i]!='\n'){s+=v[i]; i++;}
  i++;
  h=tk::stoi(s);
  while(v[i]!='\n') i++;
  i++;
  img = new Img;
  img->w = w;
  img->h = h;
  img->p = new unsigned char[w*h*3];
  memcpy(img->p,&v[i],w*h*3);
  return img;
}

void draw_img(Img* img, int x, int y){
  int w,h,n;
  if(!img) return;
  unsigned char* p = img->p;
  unsigned char r,g,b;
  w = img->w;
  h = img->h;
  n = w*h;
  int i,j;
  for(i=0; i<h; i++){
    for(j=0; j<w; j++){
      r = p[0]; g = p[1]; b = p[2];
      if(r!=255 and g!=255 and b!=255){
        gx::cset(r,g,b);
        gx::psets(x+j,y+h-i-1);
      }
      p+=3;
    }
  }
}

void update_pos(){
  if(go_left && cleft==0) posx-=1;
  if(go_right && cright==0) posx+=1;
  if(jump_counter>0 && cup==0){
    if(jump_counter<=40){
      jump_m+=2;
      if(jump_m%4==0){
        jump_counter--;
        posy+=1;
      }
    }else{
      jump_counter--;
      posy+=1;
    }
  }else if(cdown==0 && posy>0){
    posy-=1;
  }
  if(cup) jump_counter=0;
  // else if(go_down && cdown==0 && posy>=1) posy-=1;
}

void key_events(int type, int key){
  if(type==key_down){
    switch(key){
    case SDLK_LEFT:
      go_left=1;
      mirror=1;
      break;
    case SDLK_RIGHT:
      go_right=1;
      mirror=0;
      break;
    case SDLK_UP:
      jump=1;
      if(cdown){
        jump_counter=100;
      }
      break;
    case SDLK_DOWN:
      go_down=1;
      break;
    case SDLK_ESCAPE:
      main_loop_end=1;
      break;
    case SDLK_0:
      if(dark) dark=0;
      else dark=1;
      break;
    case SDLK_1:
      init_pos();
      break;
    default:;
    }
  }
  if(type==key_up){
    switch(key){
    case SDLK_LEFT:
      go_left=0;
      break;
    case SDLK_RIGHT:
      go_right=0;
      break;
    case SDLK_UP:
      jump=0;
      jump_counter=0;
      break;
    case SDLK_DOWN:
      go_down=0;
      break;
    default:;
    }
  }
}

void events(){
  int type, key;
  while(gx::questEvent(type, key)){
    key_events(type,key);
  }
}

void draw(Img* img, int x, int y, char* p){
  int i,w,h;
  int x0=x;
  w = img->w;
  h = img->h;
  for(i=0; p[i]!=0; i++){
    if(p[i]=='x'){
      draw_img(img,x,y);
    }else if(p[i]=='\n'){
      x=x0-w;
      y-=h;
    }
    x+=w;
  }
}

void draw_map(Map &map){
  int px, py, x, y;
  px=posx/24; py=posy/24;
  int m=map.m, n=map.n;
  map_element* p = map.p;
  Img* timg;
  for(int i=py-5; i<=py+5; i++){
    for(int j=px-7; j<=px+8; j++){
      x=170-posx+j*24; y=120-posy+i*24;
      if(0<=i and i<m and 0<=j and j<n){
        draw_img(p[i*n+j].block,x,y);
      }
    }
  }
}

void init_map(Map &map, int m, int n){
  map.p = new map_element[m*n];
  map.m = m;
  map.n = n;
  int i,j;
  map_element* p = map.p;
  for(i=0; i<m; i++){
    for(j=0; j<n; j++){
      p[i*n+j].block=0;
      p[i*n+j].solid=0;
    }
  }
}

void fill_map2(Map &map, block_table &btab, int x, int y, const char* p){
  int i;
  int x0=x;
  int h = map.n;
  Img *bb, *bg, *bf;
  bb=btab.bb;
  bg=btab.bg;
  bf=btab.bf;
  for(i=0; p[i]!=0; i++){
    if(isalpha(p[i])){
      if(0<=x and x<=map.m and 0<=y and y<=map.n){
        if(p[i]=='x'){
          map.p[h*y+x].block = bb;
          map.p[h*y+x].solid=2;
        }else if(p[i]=='m'){
          map.p[h*y+x].block = bg;
          map.p[h*y+x].solid=2;
        }else if(p[i]=='g'){
          map.p[h*y+x].block = bb;
        }else if(p[i]=='u'){
          map.p[h*y+x].block = bg;
          map.p[h*y+x].solid=1;
        }else if(p[i]=='f'){
          map.p[h*y+x].block = bf;
          map.p[h*y+x].solid=2;
        }
      }else{
        cout << "Unzulaessige Unterschreitung in fill_map" << endl;
      }
    }else if(p[i]=='\n'){
      x=x0-1;
      y-=1;
    }
    x+=1;
  }
}

void reverse_vs(vector<string> &v){
  int n=v.size();
  int h=n/2;
  char c;
  for(int i=0; i<h; i++){
    swap(v[i], v[n-1-i]);
  }
}

void append(string &s, const vector<string> &v){
  for(int i=0; i<v.size(); i++){
    s+=v[i];
  }
}

void reverse(string &s){
  string s2;
  string s3;
  vector<string> v;
  s+="\n*";
  for(int i=0; i<s.size(); i++){
    if(s[i]=='\n'){
      v.push_back(s2+"\n");
      // cout << "[" << s2 << "]" << endl;
      s2.clear();
      while(s[i]=='\n' and i<s.size()) i++;
      i--;
    }else if(s[i]=='*'){
      v.push_back(s2);
      s2.clear();
      reverse_vs(v);
      append(s3,v);
      v.clear();
      s3+="*\n";
      i++;
      while(s[i]=='\n' and i<s.size()) i++;
      i--;
    }else{
      s2+=s[i];
    }
  }
  s=s3;
}

void fill_map(Map &map, block_table &btab, int x, int y,
  int bw, string &s
){
  int h = map.n;
  Img *bb, *bg, *bf;
  bb=btab.bb;
  bg=btab.bg;
  bf=btab.bf;
  int x0=x;
  int y0=y;
  reverse(s);
  cout << s << endl;
  for(int i=0; i<s.size(); i++){
    if(s[i]=='b' and s[i+1]=='1'){
      map.p[h*y+x].block = bb;
      map.p[h*y+x].solid=2;
      x++; i++;
    }else if(s[i]=='m' and s[i+1]=='1'){
      map.p[h*y+x].block = bg;
      map.p[h*y+x].solid=2;
      x++; i++;
    }else if(s[i]=='.' and s[i+1]=='.'){
      x++; i++;
    }else if(s[i]=='\n'){
      y++;
      x=x0;
    }else if(s[i]=='|'){
      // nichts
    }else if(s[i]=='*'){
      return;
      i++;
      y=y0;
      x0+=bw;
      x=x0;
    }
  }
}

int ctest(Map &map, int px, int py){
  int x=px/24, y=py/24;
  int n=map.n;
  return map.p[y*n+x].solid;
}

int collision(Map &map){
  int p11x, p11y, p12x, p12y;
  int p21x, p21y, p22x, p22y;
  p11x=posx+4; p11y=posy+24;
  p12x=posx+24; p12y=posy+24;
  p21x=posx+4; p21y=posy;
  p22x=posx+24; p22y=posy;
  cup=0; cdown=0; cleft=0; cright=0;
  if(ctest(map,p11x,p11y+1)>1) cup=1;
  if(ctest(map,p11x-1,p11y)>1) cleft=1;
  if(ctest(map,p12x,p12y+1)>1) cup=1;
  if(ctest(map,p12x+1,p12y)>1) cright=1;
  if(ctest(map,p22x,p22y-1)>0) cdown=1;
  if(ctest(map,p22x+1,p22y)>1) cright=1;
  if(ctest(map,p21x,p21y-1)>0) cdown=1;
  if(ctest(map,p21x-1,p21y)>1) cleft=1;
  return 0;
}

void print_info(){
  string s, sx, sy, spx, spy;
  gx::cset(160, 160, 160);
  gx::setxy(10,230);
  itos(spx,posx);
  itos(spy,posy);
  itos(sx,posx/24);
  itos(sy,posy/24);
  s = "px="+spx+"\npy="+spy+"\nx="+sx+"\ny="+sy;
  gx::print(s);
}

#include "Level.cpp"




int main(){
  Img *mario, *mariom;
  block_table btab;
  btab.bb = load_ppm("img/bb.ppm");
  btab.bg = load_ppm("img/bg.ppm");
  btab.bf = load_ppm("img/bt.ppm");
  mario = load_ppm("img/mario.ppm");
  mariom = load_ppm("img/mariom.ppm");
  // gx::mode(1280,1024);
  // gx::fullscreen=1;
  Map map;
  init_map(map,100,10);

/*
  fill_map2(map,btab,0,10,
"                                                           u    xuux\n"
"                                            mm                  xuux\n"
"     uuuufff                                xx             u    xuux\n"
"    ............. mm  mmmmmmmm        mmmm       mm             xuux\n"
"    .............mxx..x..x..xxm       xxxx       xxfffmm   u    xuux\n"
"mmmmmmmmmmmmmmmmmxxx..x..x..xxxm                      xx        \n"
"xxxxxxxxxxxxxxxxxxxx..g..x..xxxxm         \n"
"xxxxxxxxxxxxxxxxxxxx..g..x..xxxxxmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n"
"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
//*/

  string s = Welt1;

  fill_map(map,btab,0,0,Welt1_bw,s);

  init_pos();

  gx::init();

  int m=0;
  int speed=10;
  while(1){
    if(m%speed==0){
      if(dark){
        gx::clear(0,0,0);        
      }else{
        gx::clear(0xff,0xff,0xe0);
      }

    }
    events();

    collision(map);

    update_pos();
    if(main_loop_end) break;

    if(m%speed==0){
      print_info();
      draw_map(map);
      if(mirror){
        draw_img(mariom,170,120);
      }else{
        draw_img(mario,170,120);
      }
    }
    if(m%speed==0){
      gx::flush();
      gx::wait(20);
    }
    m++;
  }
  gx::gxexit();
}

//
//
//



/*
void strip(string &s){
  int i=0;
  while(isspace(s[i])) i++;
  s = s.substr(i,s.size()-i);
  int j=s.size()-1;
  while(isspace(s[j])) j--;
  s = s.substr(0,j+1);
}

void reverse(string &s){
  vector< vector<string> > vv;
  vector<string> v;
  s+="\n";
  string s2;
  for(int i=0; i<s.size(); i++){
    if(s[i]=='\n'){
      cout << "[" << s2 << "]" << endl;
      v.push_back(s2);
      s2.clear();
    }else if(s[i]=='*'){
      v.push_back("*");
      s2.clear();
      vv.push_back(v);
    }else{
       s2+=s[i];
    }
  }
  if(not v.empty()){
    vv.push_back(v);
  }
  for(int i=0; i<vv.size(); i++){
    reverse_vs(vv[i]);
  }
  s2.clear();
  for(int i=0; i<vv.size(); i++){
    for(int j=0; j<vv[i].size(); j++){
      s2+=vv[i][j]+"\n";
    }
    s2+="*\n";
  }
  s=s2;
}
*/


//
//
//

/*
  if(ctest(map,p11x,p11y+1)>1) cup=1;
  if(ctest(map,p11x-1,p11y)>1) cleft=1;
  if(ctest(map,p12x,p12y+1)>1) cup=1;
  if(ctest(map,p12x+1,p12y)>1) cright=1;
  if(ctest(map,p22x,p22y-1)>0) cdown=1;
  if(ctest(map,p22x+1,p22y)>1) cright=1;
  if(ctest(map,p21x,p21y-1)>0) cdown=1;
  if(ctest(map,p21x-1,p21y)>1) cleft=1;
//*/



/*
  btab.b1 = load_ppm("img/b1.ppm");
  btab.bg = load_ppm("img/bg.ppm");
  btab.bf = load_ppm("img/bf.ppm");
  btab.st = load_ppm("img/st.ppm");
  btab.sm = load_ppm("img/sm.ppm");
  btab.sb = load_ppm("img/sb.ppm");
  btab.g1 = load_ppm("img/g1.ppm");
  btab.a1 = load_ppm("img/bblue.ppm");
  btab.t1 = load_ppm("img/ts1.ppm");
  btab.t2 = load_ppm("img/ts2.ppm");
  btab.t3 = load_ppm("img/ts3.ppm");
  btab.d2 = load_ppm("img/bblack.ppm");
  img_game_over = load_ppm("img/gameover.ppm");
  mario = load_ppm("img/mario.ppm");
  mariom = load_ppm("img/mariom.ppm");
*/

void load_map_rand(){
  int k;
  map_element* p = map.p;
  map_element* p2;
  int n = map_w;
  for(int i=0; i<map_h; i++){
    for(int j=0; j<map_w; j++){
      k = rand()%6;
      p2 = p+i*n+j;
      if(k==0){
        p2->block = btab.b1;
        p2->solid = 2;
      }else if(k==1){
        p2->block = btab.t1;
        p2->solid = -1;
      }else{
        p2->block = 0;
        p2->solid = 0;
      }
    }
  }
}

//
//
//

typedef int color3[3];

void color_sum(color3 &y, color3 &a, color3 &b){
  y[0]=a[0]+b[0];
  y[1]=a[1]+b[1];
  y[2]=a[2]+b[2];
}

int limit(int x, int n){
  if(x>=n) return n-1;
  else if(x<0) return 0;
  else return x;
}



void color_mean(color3 &c, color3* a, int x, int y){
  int n=360;
  int i,j,k;
  int px,py;
  k=anti_alias;
  for(j=x-k; j<=x+k; j++){
    px = limit(j,360);
    for(i=y-k; i<=y+k; i++){
      py = limit(i,240);
      color_sum(c,c,a[px+n*py]);
    }
  }
  int d = (2*k+1);
  d=d*d;
  c[0]=c[0]/d;
  c[1]=c[1]/d;
  c[2]=c[2]/d;
}

void smooth(){
  color3 a[360*240], a2[360*240];
  color3 c;
  int n=360;
  int r,g,b;
  int px,py;
  int k;
  for(int x=0; x<360; x++){
    for(int y=0; y<240; y++){
      gx::pget(x,y,r,g,b);
      k = x+n*y;
      a[k][0]=r;
      a[k][1]=g;
      a[k][2]=b;
    }
  }
  for(int x=0; x<360; x++){
    for(int y=0; y<240; y++){
      c[0]=0; c[1]=0; c[2]=0;
      // color_sum(c,c,a[x+n*y]);

      color_mean(c,a,x,y);

      /*
      px = limit(x-1,360);
      color_sum(c,c,a[px+n*y]);
      px = limit(x+1,360);
      color_sum(c,c,a[px+n*y]);
      py = limit(y-1,240);
      color_sum(c,c,a[x+n*py]);
      py = limit(y+1,240);
      color_sum(c,c,a[x+n*py]);
      */

      gx::cset(c[0],c[1],c[2]);
      gx::pset(x,y);
    }
  }
}
