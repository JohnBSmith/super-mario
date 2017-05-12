
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <SDL/SDL.h>
#include "gx.hpp"

using namespace std;
#include "font.cpp"

namespace gx{

int gxw=720, gxh=480;
int gxwd2=gxw/2, gxhd2=gxh/2;
int gxwd4=gxw/4, gxhd4=gxh/4;
int gxhm1=gxh-1;

int32_t paper = 0xfafada;
int32_t blue = 0x000060;
int32_t green = 0x004000;
int32_t purple = 0x500050;
int32_t greenblue = 0x004060;

bool fullscreen=false;
bool opengl=false;

SDL_Surface *screen;
SDL_Event event;
Uint32 gx_color = 0x00A0A0A0;

using std::cout;
using std::endl;

void gxexit(){
  SDL_Quit();
}

void wait(int n){
  SDL_Delay(n);
}

void flush(){
  SDL_Flip(screen);
}

int32_t getint(int r, int g, int b){
  return r<<16 | g<<8 | b;
}

void getcolor(int32_t n, int &r, int &g, int &b){
  r = (n>>16)&255;
  g = (n>>8)&255;
  b = n&255;
}

void mode(int x, int y){
  if(x%4==1 or y%4==1){
    cout << "x and y must be of the form 4*n in graphics mode." << endl;
    std::exit(1);
  }else{
    gxw=x; gxh=y;
    gxwd2=gxw/2; gxhd2=gxh/2;
    gxwd4=gxw/4; gxhd4=gxh/4;
    gxhm1=gxh-1;
  }
}

void init(){
  if(SDL_Init(SDL_INIT_VIDEO) == -1){
    cout << "cannot init graphics: " << SDL_GetError() << endl;
    std::exit(1);
  }
  atexit(SDL_Quit);
  SDL_putenv((char*)"SDL_VIDEO_WINDOW_POS=center");
  int mode = SDL_HWSURFACE;
  if(fullscreen) mode=mode|SDL_FULLSCREEN;
  if(opengl) mode=mode|SDL_OPENGL;

  screen = SDL_SetVideoMode(gxw, gxh, 32, mode);
  if(screen==NULL){
    cout << "cannot set video mode: " << SDL_GetError() << endl;
    SDL_Quit();
    std::exit(1);
  }
}

void begin(){
  if(SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
}

void end(){
  if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
}

int32_t cget(){
  return gx_color;
}

void pxsetf(int x, int y){
  Uint32 *pixmem;
  pixmem = (Uint32 *)screen->pixels+gxw*y+x;
  *pixmem = gx_color;  
}

void pxset(int x, int y){
  if(0<=x and x<gxw and 0<=y and y<gxh){
    pxsetf(x,y);
  }
}

void psetf(int x, int y){
  x=2*x; y=2*y;
  pxsetf(x,y); pxsetf(x+1,y);
  pxsetf(x,y+1); pxsetf(x+1,y+1);
}

void pset(int x, int y){
  if(0<=x and x<gxwd2 and 0<=y and y<gxhd2){
    psetf(x,y);
  }
}

void psets(int x, int y){
  pset(x,gxhd2-1-y);
}

void pxsets(int x, int y){
  pset(x,gxh-1-y);
}

void pget(int x, int y, int &r, int &g, int &b){
  if(0<=x and x<gxwd2 and 0<=y and y<gxhd2){
    x=2*x; y=2*y;
    Uint32 *pixmem;
    pixmem = (Uint32 *)screen->pixels + gxw*y + x;
    Uint32 color = *pixmem;
    b = 0xFF&color;
    g = (0xFF00&color)>>8;
    r = (0xFF0000&color)>>16;
  }
}

void pxget(int x, int y, int &r, int &g, int &b){
  if(0<=x and x<gxw and 0<=y and y<gxh){
    Uint32 *pixmem;
    pixmem = (Uint32 *)screen->pixels + gxw*y + x;
    Uint32 color = *pixmem;
    b = 0xFF&color;
    g = (0xFF00&color)>>8;
    r = (0xFF0000&color)>>16;
  }
}

void cset(int r, int g, int b){
  Uint8 r8=r, g8=g, b8=b;
  gx_color = SDL_MapRGB(screen->format, r8, g8, b8);
}

void pseta(int x, int y, int a){
  int r,g,b;
  int r1,g1,b1;
  Uint32 c1 = gx_color;
  b1 = 0xFF&gx_color;
  g1 = (0xFF00&gx_color)>>8;
  r1 = (0xFF0000&gx_color)>>16;
  pget(x,y,r,g,b);
  r=(r1-r)*a/255+r;
  g=(g1-g)*a/255+g;
  b=(b1-b)*a/255+b;
  cset(r,g,b);
  pset(x,y);
  gx_color=c1;
}

void pxseta(int x, int y, int a){
  int r,g,b;
  int r1,g1,b1;
  Uint32 c1 = gx_color;
  b1 = 0xFF&gx_color;
  g1 = (0xFF00&gx_color)>>8;
  r1 = (0xFF0000&gx_color)>>16;
  pxget(x,y,r,g,b);
  r=(r1-r)*a/255+r;
  g=(g1-g)*a/255+g;
  b=(b1-b)*a/255+b;
  cset(r,g,b);
  pxset(x,y);
  gx_color=c1;
}

void point(double x, double y, double m){
  int px,py;
  px = int(gxwd4*m*x)+gxwd4;
  py = -int(gxwd4*m*y)+gxhd4;
  pset(px,py);
}

void xpoint(double x, double y, double m){
  int px,py;
  px = int(gxwd2*m*x)+gxwd2;
  py = -int(gxwd2*m*y)+gxhd2;
  pxset(px,py);
}

void xpointa(double x, double y, double m, int a){
  int px,py;
  px = int(gxwd2*m*x)+gxwd2;
  py = -int(gxwd2*m*y)+gxhd2;
  pxseta(px,py,a);
}

void spoint(double x, double y, double m){
  int px,py;
  px = int(gxwd2*m*x)+gxwd2;
  py = -int(gxwd2*m*y)+gxhd2;
  pxseta(px,py,255);

  pxseta(px+1,py,128);
  pxseta(px-1,py,128);
  pxseta(px,py+1,128);
  pxseta(px,py-1,128);

  pxseta(px+1,py+1,64);
  pxseta(px-1,py+1,64);
  pxseta(px+1,py-1,64);
  pxseta(px-1,py-1,64);
}

void setmapa(int x, int y, const char* s){
  int x1=x;
  char c; int k;
  for(int i=0; s[i]!=0; i++){
    c=s[i];
    if(c=='n'){
      y++; x1=x;
      continue;
    }else if(c=='4'){
      k=255;
    }else if(c=='3'){
      k=192;
    }else if(c=='2'){
      k=128;
    }else if(c=='1'){
      k=64;
    }else{
      x1++;
      continue;
    }
    pxseta(x1,y,k);
    x1++;
  }
}

void clear(int r, int g, int b){
  register Uint32* a;
  Uint32 color = r<<16|g<<8|b;
  a = (Uint32*)gx::screen->pixels;
  Uint32* pe=a+gxw*gxh;
  while(a!=pe){
    *a=color;
    a++;
    *a=color;
    a++;
    *a=color;
    a++;
    *a=color;
    a++;
  }
}

int mod;

int quest_event(int &type, int &code){
  int n = SDL_PollEvent(&event);
  switch(event.type){
  case SDL_KEYDOWN:
    type = 1;
    code = event.key.keysym.sym;
    mod = event.key.keysym.mod;
    break;
  case SDL_KEYUP:
    type = 2;
    code = event.key.keysym.sym;
    mod = event.key.keysym.mod;
    break;
  default:
    type = 0;
    code = 0;
  }
  return n;
}

int was_event(){
  int type, code;
  while(quest_event(type, code)){
    if(type==2){
      return code;
    }
  }
  return 0;
}

int getkey(){
  int type,code;
  while(quest_event(type,code)){}
  while(1){
    while(quest_event(type,code)){
      if(type==1){return code;}
    }
    wait(40);
  }
}

void stobv(vector<unsigned char> &v, const string &s){
  for(int i=0; i<s.size(); i++){
    v.push_back(s[i]);
  }
}

void (*ppm_pget)(int i, int j, int &r, int &g, int &b) = gx::pget;
int ppmw = 360, ppmh=240;

string itos(int n){
  stringstream a;
  a<<n;
  return a.str();
}

void make_ppm(vector<unsigned char>& v){
  int r,g,b;
  v.clear();
  stobv(v,"P6\n"+itos(ppmw)+"\n"+itos(ppmh)+"\n255\n");
  for(int j=0; j<ppmh; j++){
    for(int i=0; i<ppmw; i++){
      ppm_pget(i,j,r,g,b);
      v.push_back(r);
      v.push_back(g);
      v.push_back(b);
    }
  }
}

void save_ppm(const char* id){
  vector<unsigned char> v;
  gx::make_ppm(v);
  ofstream os;
  os.open(id);
  for(int i=0; i<v.size(); i++){
    os << v[i];
  }
  os.close();
}

}
// namespace

