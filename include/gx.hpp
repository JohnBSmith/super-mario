
#ifndef GX_HPP
#define GX_HPP

#include <string>

namespace gx{

extern int
  gxw, gxh,
  gxwd2, gxhd2, gxwd4, gxhd4,
  gxhm1;

// const int gxdepth = 32, gxbpp=4;

extern bool fullscreen;
extern bool opengl;

void gxexit();
void wait(int);
void flush();
void vgswap();
void mode(int, int);
void init();
void init_buffer();
void pxset(int, int);
void pset(int, int);
void psets(int, int);
void pxsets(int, int);
void pget(int, int, int&, int&, int&);
void pxget(int, int, int&, int&, int&);
void cset(int, int, int);
void cget(int&, int&, int&);
void clear(int, int, int);
void point(float, float, float);
void xpoint(float, float, float);
// int mod;
int quest_event(int&, int&);
int getkey();
void rect(int, int, int, int);
void frect(int, int, int, int);
void spoint(double, double, double);
void psetv(int, int, const char*);

void print(const std::string&);
void uprint(const std::string&);
void setxy(int,int);

}
//namespace


#endif

