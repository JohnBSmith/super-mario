
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "gx.hpp"
#include "tk.hpp"
#include <SDL/SDL.h>
#include "list.cpp"

#ifdef _WIN32
#undef main
#endif
#define cast static_cast

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::swap;

using tk::itos;

struct Img{
  int w,h;
  unsigned char* p;
};

struct block_table{
  Img *b1, *bg, *bf, *st, *sm, *sb, *g1, *a1;
  Img *t1, *t2, *t3;
  Img *du, *enemy1, *enemy1f;
  Img *portal;
};

void (*ppsets)(int,int) = gx::psets;

Img *mario, *mariom;
Img *mario1, *mario2;
Img *mariom1, *mariom2;
Img *marioj, *mariomj;
int go_counter;

Img *img_game_over;
struct Position{
  int x,y;
};

Position pos[20];
int posx, posy;
int go_left, go_right;
int jump, go_down;
int main_loop_end;
int mirror;
int ktype;
int jump_counter;
int jump_m;

#define SPEED 16
int speed=SPEED;
bool dark;
bool input;
bool input_pos;
bool ghost_mode;
bool fly_mode;
bool info_on;
int Schaden;
int Schaden_Zeit;
int Lebenspunkte;
string input_s;
string map_id;
int cash;
int cmd_x, cmd_y;
int cash_x, cash_y;
int info_x, info_y;
int anti_alias;

// center pixel
int cpx=170, cpy=120;

int cup, cdown, cleft, cright;

const int key_down=1, key_up=2;
const int dir_up=1, dir_down=2, dir_right=3, dir_left=4;

struct map_element{
  int solid;
  Img* block;
};

// mbsize: map_block_size

struct Map{
  map_element* p;
  int w,h;
  int mbsize;
};

block_table btab;
Map map;
void draw_img(Img*,int,int);

void draw_cross(int px, int py){
  gx::cset(0,0,0);
  for(int x=px-10; x<=px+10; x++){
    ppsets(x,py);
  }
  for(int y=py-10; y<=py+10; y++){
      ppsets(px,y);
  }
}

#include "enemy.cpp"

list aenemy;
list aanimation;

#include "cfg.cpp"
#include "map.cpp"
#include "img.cpp"
#include "animation.cpp"


int get_time(){
  return SDL_GetTicks();
}

void init_pos(){
  posx=pos[0].x;
  posy=pos[0].y;
  go_left=0;
  go_right=0;
}

void init_map(Map &map){
  int m,n;
  m = map.h;
  n = map.w;
  map.p = new map_element[m*n];
  int i,j;
  map_element* p = map.p;
  for(i=0; i<m; i++){
    for(j=0; j<n; j++){
      p[i*n+j].block=NULL;
      p[i*n+j].solid=0;
    }
  }
}

void dispose_map(Map &map){
  if(map.p) delete map.p;
  map.p = NULL;
}

int load_world(const string &id){
  string s = string("cfg/")+id+".txt";
  if(set_cfg(map,s.c_str())) return 1;
  dispose_map(map);
  init_map(map);
  load_map("maps/"+map_id, map, btab);
  init_pos();
  return 0;
}

void pset4(int x, int y){
  x=2*x; y=2*y;
  gx::psets(x,y); gx::psets(x+1,y);
  gx::psets(x,y+1); gx::psets(x+1,y+1);
}

void pset16(int x, int y){
  x=2*x; y=2*y;
  pset4(x,y); pset4(x+1,y);
  pset4(x,y+1); pset4(x+1,y+1);
}

void psets_v2(int x, int y){
  x=2*x; y=2*y;
  gx::pxsets(x,y); gx::pxsets(x+1,y);
  gx::pxsets(x,y+1); gx::pxsets(x+1,y+1);
}

int gm_counter=10;

void set_gx_mode(int n){
  cpx=170; cpy=120;
  if(n==9){
    gx::gxexit();
    gx::mode(360,240);
    gx::init();
    ppsets = gx::pxsets;
  }else if(n==10){
    gx::gxexit();
    gx::mode(720,480);
    gx::init();
    ppsets = gx::psets;
  }else if(n==11){
    gx::gxexit();
    gx::mode(1280,1024);
    gx::init();
    ppsets = pset4;
    cmd_x = 140;
    cmd_y = 80;
    cpx=150;
  }else if(n==12){
    gx::gxexit();
    gx::mode(1280,1024);
    gx::init();
    ppsets = pset16;
    cpx=70;
    cpy=40;
  }
}

void cset2(int r, int g, int b){
  int c = (r+g+b)/3;
  gx::cset(c,c,c);
}

void cset3(int r, int g, int b){
  gx::cset(r, b, g); 
}


void cset4(int r, int g, int b){
  gx::cset(g, r, b);
}

void (*pcset)(int, int, int) = gx::cset;

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
      if(r!=255 or g!=255 or b!=255){
        // gx::cset(r,g,b);
        pcset(r,g,b);
        ppsets(x+j,y+h-i-1);
      }
      p+=3;
    }
  }
}

void cls(){
  if(dark){
    gx::clear(0,0,0x20);
  }else{
    gx::clear(0xff,0xff,0xe0);
  }
}

void draw_mushroom(){
  static int loaded;
  static Img* mushroom;
  if(not loaded){
    mushroom = load_ppm("img/enemy1.ppm");
  }
  draw_img(mushroom,cpx,cpy);
}

void draw_mario_v1(){
  if(mirror){
    draw_img(mariom,cpx,cpy);
  }else{
    draw_img(mario,cpx,cpy);
  }
}

void draw_mario_v2(){
  Img *img_mario=0;
  if(mirror){
    if(jump and not cdown){
      img_mario = mariomj;
    }else if(not cdown and go_left){
      img_mario = mariom1;
    }else if(go_left){
      if(go_counter==0) img_mario = mariom1;
      if(go_counter==1) img_mario = mariom2;
      if(go_counter==2) img_mario = mariom2;
      if(go_counter==3) img_mario = mariom1;
      go_counter++;
      if(go_counter>3) go_counter=0;
    }else{
      img_mario = mariom;
    }
  }else{
    if(jump and not cdown){
      img_mario = marioj;
    }else if(not cdown and go_right){
      img_mario = mario1;
    }else if(go_right){
      if(go_counter==0) img_mario = mario1;
      if(go_counter==1) img_mario = mario2;
      if(go_counter==2) img_mario = mario2;
      if(go_counter==3) img_mario = mario1;
      go_counter++;
      if(go_counter>3) go_counter=0;
    }else{
      img_mario = mario;
    }
  }
  draw_img(img_mario,cpx,cpy);
}

void (*draw_mario)() = draw_mario_v2;

void init_gx(){
  btab.b1 = load_ppm("img/b1.ppm");
  btab.bg = load_ppm("img/bg.ppm");
  btab.bf = load_ppm("img/bf.ppm");
  btab.st = load_ppm("img/st.ppm");
  btab.sm = load_ppm("img/sm.ppm");
  btab.sb = load_ppm("img/sb.ppm");
  btab.g1 = load_ppm("img/g1.ppm");
  btab.a1 = load_ppm("img/enemy2.ppm");
  btab.t1 = load_ppm("img/ts1.ppm");
  btab.t2 = load_ppm("img/ts2.ppm");
  btab.t3 = load_ppm("img/ts3.ppm");
  btab.du = load_ppm("img/spike.ppm");
  btab.portal = load_ppm("img/portal.ppm");
  img_game_over = load_ppm("img/gameover.ppm");
  btab.enemy1 = load_ppm("img/enemy1.ppm");
  btab.enemy1f = copy_img(btab.enemy1);
  flip(btab.enemy1f);

/*
  btab.bt = load_ppm("img/bt.ppm");
  btab.bm = load_ppm("img/bm.ppm");  
  btab.bl = load_ppm("img/bl.ppm");
  btab.c3 = load_ppm("img/c3.ppm");

  btab.bb = copy_img(btab.bt);
  flip(btab.bb);
  btab.br = copy_img(btab.bl);
  mirror_img(btab.br);
  btab.c1 = copy_img(btab.c3);
  flip(btab.c1);
  btab.c2 = copy_img(btab.c1);
  mirror_img(btab.c2);
  btab.c4 = copy_img(btab.c3);
  mirror_img(btab.c4);

  btab.d1 = load_ppm("img/spike.ppm");
  btab.d2 = load_ppm("img/hspike.ppm");
*/

  mario = load_ppm("img/mario.ppm");
  mario1 = load_ppm("img/mario1.ppm");
  mario2 = load_ppm("img/mario2.ppm");
  marioj = load_ppm("img/marioj.ppm");

  mariom = copy_img(mario);
  mariom1 = copy_img(mario1);
  mariom2 = copy_img(mario2);
  mariomj = copy_img(marioj);
  mirror_img(mariom);
  mirror_img(mariom1);
  mirror_img(mariom2);
  mirror_img(mariomj);
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

int caps;

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
      if(cdown or fly_mode){
        jump_counter=110;
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
    case SDLK_9:      
      pcset = gx::cset;
      break;
    case SDLK_8:
      pcset = cset2;
      break;
    case SDLK_7:
      pcset = cset3;
      break;
    case SDLK_6:
      pcset = cset4;
      break;
    case SDLK_RIGHTBRACKET:
    // case SDLK_PLUS:
      if(gm_counter<12){
        gm_counter++;
        set_gx_mode(gm_counter);
      }
      break;
    case SDLK_SLASH:
    // case SDLK_MINUS:
      if(gm_counter>9){
        gm_counter--;
        set_gx_mode(gm_counter);
      }
      break;
    case SDLK_RETURN:
      input=1;
      input_pos=160;
      input_s="";
      caps=0;
      break;
    case SDLK_j:
      anti_alias++;
      break;
    case SDLK_k:
      if(anti_alias>0) anti_alias--;
      break;
    case SDLK_s:
      speed = 2*speed;
      if(speed>4*SPEED) speed=SPEED;
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
  while(gx::quest_event(type, key)){
    key_events(type,key);
  }
}

void cmd_ghost(){
  if(ghost_mode){
    pcset=gx::cset;
    ghost_mode=0;
    dark=0;
  }else{
    pcset=cset2;
    ghost_mode=1;
    dark=1;
  }
}

void eval(string &s){
  if(s=="dark"){
    dark=1;
  }else if(s=="light"){
    dark=0; 
  }else if(s=="gray"){
    pcset = cset2;
  }else if(s=="c1"){
    pcset = gx::cset; 
  }else if(s=="c3"){
    pcset = cset3; 
  }else if(s=="ghost"){
    cmd_ghost();
  }else if(s=="fly"){
    fly_mode = not fly_mode;
  }else if(s=="speed"){
    if(speed>SPEED) speed=SPEED;
    else speed=2*SPEED; 
  }else if(s=="gf"){
    cmd_ghost();
    fly_mode = not fly_mode;
  }else if(s=="info"){
    info_on = not info_on;
  }else if(s=="small"){
    set_gx_mode(9);
  }else if(s=="noraml"){
    set_gx_mode(10);
  }else if(s=="big"){
    set_gx_mode(11);
  }else if(s=="large"){
    set_gx_mode(12);
  }else if(s=="mushroom"){
    draw_mario = draw_mushroom;
  }else if(s=="mario"){
    draw_mario = draw_mario_v2;
  }else if(s.substr(0,4)=="load" || s.substr(0,1)=="."){
    int i = s[0]=='.'? 1: 4;
    while(i<s.size() and isspace(s[i])) i++;
    string id;
    while(i<s.size() and (isalpha(s[i]) or isdigit(s[i]) or s[i]=='.')){
      id+=s[i];
      i++;
    }
    load_world(id);
  }
}

void input_events(int type, int key){
  gx::cset(0x40,0x40,0x40);
  if(type==key_down){
    if(key==SDLK_LSHIFT or key==SDLK_RSHIFT){
      caps=1;
    }else if(isprint(key)){
      if(key=='z') key='y';
      else if(key=='y') key='z';
      if(caps>0){
        key=toupper(key);
      }
      input_s+=key;
    }else if(key==SDLK_SPACE){
      input_s+=' ';
    }else if(key==SDLK_BACKSPACE){
      if(not input_s.empty()){
        input_s = input_s.substr(0,input_s.size()-1);
      }
    }else if(key==SDLK_RETURN){
      input=0;
      eval(input_s);
    }else if(key==SDLK_ESCAPE){
      main_loop_end=1;
    }
  }else if(type==key_up){
    if(key==SDLK_LSHIFT or key==SDLK_RSHIFT){
      caps=0;
    }
  }
}

void get_input(){
  int type, key;
  while(gx::quest_event(type, key)){
    input_events(type,key);
  }
}

void rect(int x, int y, int a, int b){
  gx::cset(0,0,0);  
  int m = x+a;
  int n = y+b;
  for(int i=x; i<m; i++){
    for(int j=y; j<n; j++){
      gx::pset(i,j);
    } 
  }
}

void print_io(){
  rect(cmd_x,cmd_y+28,360,20);
  gx::setxy(cmd_x+40,cmd_y+40);
  gx::cset(140,140,140);
  gx::print("/"+input_s);
}

void draw2(Img* img, int x, int y, char* p){
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
  int m=map.h, n=map.w;
  map_element* p = map.p;
  Img* timg;
  for(int i=py-5; i<=py+5; i++){
    for(int j=px-7; j<=px+8; j++){
      x=cpx-posx+j*24; y=cpy-posy+i*24;
      if(0<=i and i<m and 0<=j and j<n){
        draw_img(p[i*n+j].block,x,y);
      }
    }
  }
}

void move_enemys(){
  node* p;
  for(p=aenemy.first; p!=0; p=p->next){
    cast<Enemy*>(p->data)->move();
  }
}

void draw_enemys(){
  node* p;
  for(p=aenemy.first; p!=0; p=p->next){
    cast<Enemy*>(p->data)->draw();
  }
}

void update_animations(){
  animation* a;
  node* p;
  for(p=aanimation.first; p!=0; p=p->next){
    a = (animation*) p->data;
    a->next(a);
  }
}

void draw_animations(){
  node *p, *p2;
  animation* a;
  p=aanimation.first;
  while(p!=0){
    a = (animation*) p->data;
    if(a->done){
      delete a;
      p2=p;
      p = p->next;
      aanimation.remove(p2);
    }else{
      a->draw();
      p = p->next;
    }
  }
}

int game_over_event;
int damage_event;

void game_over(){
  cls();
  draw_map(map);
  draw_enemys();
  draw_mario();
  draw_img(img_game_over, 92, 40);
  gx::flush();
  gx::getkey();
  init_pos();
  Lebenspunkte=3;
  Schaden=0;
  damage_event=0;
}

void c_event(map_element &p){
  int n = -p.solid;
  if(n==1){
    p.block=NULL;
    p.solid=0;
    cash++;
    // cout << "\a";
  }else if(n==2){
    p.block=NULL;
    p.solid=0;
    cash+=10;
  }else if(n==3){
    p.block=NULL;
    p.solid=0;
    cash+=100;
  }else if(n==10){
    game_over_event=1;
  }else if(n==20){
    damage_event=1;
  }else if(40<=n && n<50){
    posx=pos[n-40].x;
    posy=pos[n-40].y;
  }
}

int ctest(int px, int py){
  int x=px/24, y=py/24;
  int n=map.w;
  int a = map.p[y*n+x].solid;
  if(a<0) c_event(map.p[y*n+x]);
  return a;
}

void damage(){
  if(Schaden==0){
    if(Lebenspunkte==1){
      game_over_event=1;
    }else{
      Schaden=1;
      Schaden_Zeit=get_time();
    }
  }
}

int collision(){
  int p11x, p11y, p12x, p12y;
  int p21x, p21y, p22x, p22y;
  int ul,ur,dl,dr,lu,ld,ru,rd;
  p11x=posx+4; p11y=posy+24;
  p12x=posx+24; p12y=posy+24;
  p21x=posx+4; p21y=posy;
  p22x=posx+24; p22y=posy;
  cup=0; cdown=0; cleft=0; cright=0;

  ul=ctest(p11x,p11y+1);
  ur=ctest(p12x,p12y+1);
  lu=ctest(p11x-1,p11y);
  ru=ctest(p12x+1,p12y);
  dr=ctest(p22x,p22y-1);
  rd=ctest(p22x+1,p22y);
  dl=ctest(p21x,p21y-1);
  ld=ctest(p21x-1,p21y);

  if(ul>1 or ur>1){
    cup=1;
    if(ul>2 or ur>2) damage();
  }
  if(lu>1 or ld>1){
    if(lu>2 or ld>2) damage();
    cleft=1;
  }
  if(ru>1 or rd>1){
    if(ru>2 or rd>2) damage();
    cright=1;
  }
  if(dl>0 or dr>0){
    cdown=1;
    if(dl>3 or dr>3) damage();
  }

  if(ghost_mode){
    cleft=0;
    cright=0;
    cup=0;
  }
  if(game_over_event){
    game_over_event=0;
    game_over();
  }
  if(damage_event){
    damage_event=0;
    damage();
  }
  return 0;
}

void print_info(){
  string s, sx, sy, spx, spy;
  gx::cset(160, 160, 160);
  gx::setxy(10,180);
  itos(spx,posx);
  itos(spy,posy);
  itos(sx,posx/24);
  itos(sy,posy/24);
  s = "px="+spx+"\npy="+spy+"\nx="+sx+"\ny="+sy;
  gx::print(s);
}

/*
void setcoin(){
gx::setv(
  ".....\n"
  ".xxx.\n"
  "xxxxx\n"
  "xxxxx\n"
  "xxxxx\n"
  ".xxx.\n"
  ".....\n"
);
}
// */

void print_cash(){
  string s;
  itos(s,cash);
  gx::cset(220,220,120);
  gx::setxy(10,230);
  // setcoin();
  // gx::print("  ");
  gx::print(s);
}

int rand_uniform(int a, int b){
  return rand()%(b-a+1)+a;
}

void rand_fill_map(){
  int x = rand_uniform(0,159);
  int y = rand_uniform(0,39);
  int n = map.w;
  map_element* p = map.p+y*n+x;
  if(p->solid==0 and p->block==NULL){
    p->solid=-1;
    p->block=btab.t1;
  }
}

void draw(Map &map){
  static int m;
  m++;
  cls();
  draw_map(map);
  draw_enemys();
  draw_animations();

  if(Schaden>0){
    if(m%2==0) draw_mario();
    if(get_time()-Schaden_Zeit>2000){
      Schaden=0;
      Lebenspunkte--;
    }
  }else{
    draw_mario();
  }
  if(info_on) print_info();
  if(input) print_io();
  print_cash();

  // smooth();
  gx::flush();
  gx::wait(60);
}

void print_enemys(){
  node *p;
  Enemy* enemy;
  cout << "[";
  for(p=aenemy.first; p!=0; p=p->next){
    enemy = cast<Enemy*>(p->data);
    cout << "(" << enemy->px << ", " << enemy->py << ")";
  }
  cout << "]\n";
}

void enemy_collision(){
  int px,py;
  int active;
  node *p, *p2;
  for(p=aenemy.first; p!=0; p=p->next){
    active = cast<Enemy*>(p->data)->active;
    if(active){
      px=cast<Enemy*>(p->data)->px;
      py=cast<Enemy*>(p->data)->py;
      if(abs(px-posx)<24 and posy-py>18 and posy-py<24 and not jump){
        animation* a = ani1(px,py);
        aanimation.append(a);
        p2 = p->next;
        delete cast<Enemy*>(p->data);
        aenemy.remove(p);
        p=p2;
        if(p==0) break;
      }else if(abs(px-posx)<20 and abs(py-posy)<20){
        damage();
      }
    }
  }
}

int main(){
  init_gx();
  // gx::mode(1280,1024);
  // gx::fullscreen=1;

  map.w = 400; map.h = 200;
  map.mbsize = 30;
  map.p = NULL;
  if(load_world("w1")){
    cout << "Error: could not load world w1." << endl;
    exit(1);
  }

  gx::init();
  Lebenspunkte=3;

  // aenemy[0] = new Enemy(200,200);
  // aenemy[0]->img = btab.enemy1;
  // aenemy_size++;

  int m=0;
  
  int k1=0;
  while(1){
    if(input){
      get_input();
    }else{
      events();
    }
    //if(k1%10==0) print_enemys();
    collision();
    update_pos();
    if(m%10==0){
      move_enemys();
      update_animations();
    }
    enemy_collision();

    if(main_loop_end) break;

    if(m%speed==0){
      draw(map);
    }
    m++;
    k1++;
  }
  gx::gxexit();
}
