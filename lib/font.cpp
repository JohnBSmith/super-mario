
namespace gx{

int posy=9, posx=9;
int posxn=9;

void setxy(int x, int y){
  posx=x; posy=y;
  posxn=x;
}

void (*fpset)(int,int) = pset;

void setv(const char* p){
  int x=posx, y=posy;
  while(*p!='\0'){
    if(*p=='x'){
      fpset(x,y);
      x++;
    }else if(*p=='\n'){
      y++; x=posx;
    }else{
      x++;
    }
    p++;
  }
}

void setemp(){
setv(
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
);
}

void set0(){
setv(
  ".xxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".xxx.\n"
);
}

void set1(){
setv(
  "..x..\n"
  ".xx..\n"
  "x.x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "xxxxx\n"
);
}

void set2(){
setv(
  ".xxx.\n"
  "x...x\n"
  "....x\n"
  "...x.\n"
  "..x..\n"
  ".x...\n"
  "xxxxx\n"
);
}

void set3(){
setv(
  ".xxx.\n"
  "....x\n"
  "....x\n"
  ".xxx.\n"
  "....x\n"
  "....x\n"
  ".xxx.\n"
);
}

void set4(){
setv(
  "x..x\n"
  "x..x.\n"
  "x..x.\n"
  "xxxxx\n"
  "...x.\n"
  "...x.\n"
  "...x.\n"
);
}

void set5(){
setv(
  "xxxxx\n"
  "x....\n"
  "x....\n"
  "xxxx.\n"
  "....x\n"
  "....x\n"
  "xxxx.\n"
);
}

void set6(){
setv(
  ".xxx.\n"
  "x....\n"
  "x....\n"
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  ".xxx.\n"
);
}

void set7(){
setv(
  "xxxxx\n"
  "....x\n"
  "...x.\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
);
}

void set8(){
setv(
  ".xxx.\n"
  "x...x\n"
  "x...x\n"
  ".xxx.\n"
  "x...x\n"
  "x...x\n"
  ".xxx.\n"
);
}

void set9(){
setv(
  ".xxx.\n"
  "x...x\n"
  "x...x\n"
  ".xxxx\n"
  "....x\n"
  "....x\n"
  ".xxx.\n"
);
}

void setcomma(){
setv(
  "\n\n"
  ".....\n"
  ".....\n"
  ".....\n"
  "..x..\n"
  "..x..\n"
  ".x...\n"
);
}

void setsc(){
setv(
  "\n\n"
  "..x..\n"
  "..x..\n"
  ".....\n"
  "..x..\n"
  "..x..\n"
  ".x...\n"
);
}

void setpoint(){
setv(
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".xx..\n"
  ".xx..\n"
);
}

void setdpoint(){
setv(
  ".....\n"
  ".....\n"
  ".xx..\n"
  ".xx..\n"
  ".....\n"
  ".xx..\n"
  ".xx..\n"
);
}

void setpp(){
setv(
  "x.x.x\n"
  ".x.x.\n"
  "x.x.x\n"
  ".x.x.\n"
  "x.x.x\n"
  ".x.x.\n"
  "x.x.x\n"
);
}

void setA(){
setv(
  ".xxx.\n"
  "x...x\n"
  "x...x\n"
  "xxxxx\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
);
}


void setB(){
setv(
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "xxxx.\n"
);
}


void setC(){
setv(
  ".xxxx\n"
  "x....\n"
  "x....\n"
  "x....\n"
  "x....\n"
  "x....\n"
  ".xxxx\n"
);
}


void setD(){
setv(
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "xxxx.\n"
);
}


void setE(){
setv(
  "xxxxx\n"
  "x....\n"
  "x....\n"
  "xxxxx\n"
  "x....\n"
  "x....\n"
  "xxxxx\n"
);
}

void setF(){
setv(
  "xxxxx\n"
  "x....\n"
  "x....\n"
  "xxxxx\n"
  "x....\n"
  "x....\n"
  "x....\n"
);
}

void setG(){
setv(
  ".xxxx\n"
  "x....\n"
  "x....\n"
  "x..xx\n"
  "x...x\n"
  "x...x\n"
  ".xxxx\n"
);
}

void setH(){
setv(
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "xxxxx\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
);
}

void setI(){
setv(
  "xxxxx\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "xxxxx\n"
);
}

void setJ(){
setv(
  "xxxxx\n"
  "...x.\n"
  "...x.\n"
  "...x.\n"
  "...x.\n"
  "x..x.\n"
  ".xx..\n"
);
}

void setK(){
setv(
  "x...x\n"
  "x..x.\n"
  "x.x..\n"
  "xxx..\n"
  "x..x.\n"
  "x...x\n"
  "x...x\n"
);
}

void setL(){
setv(
  "x....\n"
  "x....\n"
  "x....\n"
  "x....\n"
  "x....\n"
  "x....\n"
  "xxxxx\n"
);
}

void setM(){
setv(
  "x...x\n"
  "xx.xx\n"
  "x.x.x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
);
}

void setN(){
setv(
  "x...x\n"
  "x...x\n"
  "xx..x\n"
  "x.x.x\n"
  "x..xx\n"
  "x...x\n"
  "x...x\n"
);
}

void setO(){
setv(
  ".xxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".xxx.\n"
);
}

void setP(){
setv(
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "xxxx.\n"
  "x....\n"
  "x....\n"
  "x....\n"
);
}

void setQ(){
setv(
  ".xxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x.x.x\n"
  "x..xx\n"
  "xxxxx\n"
);
}

void setR(){
setv(
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
);
}

void setS(){
setv(
  ".xxx.\n"
  "x....\n"
  "x....\n"
  ".xxx.\n"
  "....x\n"
  "....x\n"
  "xxxx.\n"
);
}

void setT(){
setv(
  "xxxxx\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
);
}

void setU(){
setv(
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".xxx.\n"
);
}

void setV(){
setv(
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".x.x.\n"
  ".x.x.\n"
  "..x..\n"
);
}

void setW(){
setv(
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x.x.x\n"
  "xx.xx\n"
  "x...x\n"
);
}

void setX(){
setv(
  "x...x\n"
  "x...x\n"
  ".x.x.\n"
  "..x..\n"
  ".x.x.\n"
  "x...x\n"
  "x...x\n"
);
}

void setY(){
setv(
  "x...x\n"
  "x...x\n"
  ".x.x.\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
);
}

void setZ(){
setv(
  "xxxxx\n"
  "....x\n"
  "...x.\n"
  "..x..\n"
  ".x...\n"
  "x....\n"
  "xxxxx\n"
);
}

void seta(){
setv(
  "\n\n"
  ".xxx.\n"
  "....x\n"
  ".xxxx\n"
  "x...x\n"
  ".xxxx\n"
);
}

void setb(){
setv(
  "x....\n"
  "x....\n"
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "xxxx.\n"
);
}

void setc(){
setv(
  "\n\n"
  ".xxx.\n"
  "x....\n"
  "x....\n"
  "x....\n"
  ".xxx.\n"
);
}

void setd(){
setv(
  "....x\n"
  "....x\n"
  ".xxxx\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".xxxx\n"
);
}

void sete(){
setv(
  "\n\n"
  ".xxx.\n"
  "x...x\n"
  "xxxxx\n"
  "x....\n"
  ".xxxx\n"
);
}

void setf(){
setv(
  "...xx\n"
  "..x..\n"
  ".xxxx.\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
);
}

void setg(){
setv(
  "\n\n"
  ".xxxx\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".xxxx\n"
  "....x\n"
  "xxxx.\n"
);
}

void seth(){
setv(
  "x....\n"
  "x....\n"
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
);
}

void seti(){
setv(
  "..x..\n"
  ".....\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  ".xxx.\n"
);
}

void setj(){
setv(
  "...x.\n"
  ".....\n"
  "...x.\n"
  "...x.\n"
  "...x.\n"
  "...x.\n"
  ".xx..\n"
);
}

void setk(){
setv(
  "x....\n"
  "x....\n"
  "x.xx.\n"
  "xxx..\n"
  "x..x.\n"
  "x...x\n"
  "x...x\n"
);
}

void setl(){
setv(
  ".xx..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  ".xxx.\n"
);
}

void setm(){
setv(
  "\n\n"
  "xxxx.\n"
  "x.x.x\n"
  "x.x.x\n"
  "x.x.x\n"
  "x.x.x\n"
);
}

void setn(){
setv(
  "\n\n"
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
);
}

void seto(){
setv(
  "\n\n"
  ".xxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".xxx.\n"
);
}

void setp(){
setv(
  "\n\n"
  "xxxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "xxxx.\n"
  "x....\n"
  "x....\n"
);
}

void setq(){
setv(
  "\n\n"
  ".xxx.\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".xxxx\n"
  "....x\n"
  "....x\n"
);
}

void setr(){
setv(
  "\n\n"
  "x.xx.\n"
  "xx...\n"
  "x....\n"
  "x....\n"
  "x....\n"
);
}

void sets(){
setv(
  "\n\n"
  ".xxx.\n"
  "x....\n"
  ".xxx.\n"
  "....x\n"
  "xxxx.\n"
);
}

void sett(){
setv(
  "..x..\n"
  "..x..\n"
  "xxxxx\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "...xx\n"
);
}

void setu(){
setv(
  "\n\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".xxx.\n"
);
}

void setv(){
setv(
  "\n\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".x.x.\n"
  "..x..\n"
);
}

void setw(){
setv(
  "\n\n"
  "x...x\n"
  "x...x\n"
  "x.x.x\n"
  "xx.xx\n"
  "x...x\n"
);
}

void setx(){
setv(
  "\n\n"
  "x...x\n"
  ".x.x.\n"
  "..x..\n"
  ".x.x.\n"
  "x...x\n"
);
}

void sety(){
setv(
  "\n\n"
  "x...x\n"
  "x...x\n"
  "x...x\n"
  ".xxxx\n"
  "....x\n"
  "....x\n"
  ".xxx.\n"
);
}

void setz(){
setv(
  "\n\n"
  "xxxxx\n"
  "...x.\n"
  "..x..\n"
  ".x...\n"
  "xxxxx\n"
);
}

void seteq(){
setv(
  "\n\n"
  "xxxxx\n"
  ".....\n"
  "xxxxx"
);
}

void setpa(){
setv(
  "...x.\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "...x.\n"
);
}

void setpb(){
setv(
  ".x...\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  ".x...\n"
);
}

void setba(){
setv(
  "..xx.\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..xx.\n"
);
}

void setbb(){
setv(
  ".xx..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  ".xx..\n"
);
}

void setca(){
setv(
  "...xx\n"
  "..x..\n"
  "..x..\n"
  ".x...\n"
  "..x..\n"
  "..x..\n"
  "...xx\n"
);
}

void setcb(){
setv(
  "xx...\n"
  "..x..\n"
  "..x..\n"
  "...x.\n"
  "..x..\n"
  "..x..\n"
  "xx...\n"
  ".....\n"
);
}

void setadd(){
setv(
  ".....\n"
  ".....\n"
  "..x..\n"
  "..x..\n"
  "xxxxx\n"
  "..x..\n"
  "..x..\n"
);
}

void setsub(){
setv(
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
  "xxxxx\n"
  ".....\n"
  ".....\n"
);
}

void setmpy(){
setv(
  ".....\n"
  ".....\n"
  ".x.x.\n"
  "..x..\n"
  ".x.x.\n"
  ".....\n"
  ".....\n"
);
}

void setdiv(){
setv(
  "...x.\n"
  "...x.\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  ".x...\n"
  ".x...\n"
);
}

void setqm(){
setv(
  ".xx..\n"
  "...x.\n"
  "...x.\n"
  "..x..\n"
  "..x..\n"
  ".....\n"
  "..x..\n"
);
}

void setbang(){
setv(
  "..x..\n"
  "..x..\n"
  "..x.\n"
  "..x..\n"
  "..x..\n"
  ".....\n"
  "..x..\n"
);
}

void setpercent(){
setv(
  "\n\n"
  "xx..x\n"
  "xx.x.\n"
  "..x..\n"
  ".x.xx\n"
  "x..xx\n"
);
}

void setbs(){
setv(
  ".x...\n"
  ".x...\n"
  "..x.\n"
  "..x..\n"
  "..x..\n"
  "...x.\n"
  "...x.\n"
);
}

void setcaret(){
setv(
  "..x..\n"
  ".x.x.\n"
  "x...x\n"
  ".....\n"
);
}

void setvline(){
setv(
  "..x..\n"
  "..x..\n"
  "..x.\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
  "..x..\n"
);
}

void setamp(){
setv(
  ".xxx.\n"
  "x...x\n"
  "x..x\n"
  ".xx..\n"
  "x..x\n"
  "x..x.\n"
  ".xx.x\n"
);
}

void setLT(){
setv(
  "\n\n"
  "...xx\n"
  ".xx..\n"
  "x....\n"
  ".xx..\n"
  "...xx\n"
);
}

void setGT(){
setv(
  "\n\n"
  "xx...\n"
  "..xx.\n"
  "....x\n"
  "..xx.\n"
  "xx...\n"
);
}

void setqt(){
setv(
  "..x..\n"
  "..x..\n"
  "..x..\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
);
}

void setqq(){
setv(
  ".x.x.\n"
  ".x.x.\n"
  ".x.x.\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
);
}

void settd(){
setv(
  ".....\n"
  ".....\n"
  ".....\n"
  ".x...\n"
  "x.x.x\n"
  "...x.\n"
  ".....\n"
);
}

void setuline(){
setv(
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
  "xxxxx\n"
);
}

void setgrave(){
setv(
  ".x...\n"
  "..x..\n"
  "...x.\n"
  ".....\n"
  ".....\n"
  ".....\n"
  ".....\n"
);
}

void putchar(int n){
  switch(n){
  case '0': set0(); break;
  case '1': set1(); break;
  case '2': set2(); break;
  case '3': set3(); break;
  case '4': set4(); break;
  case '5': set5(); break;
  case '6': set6(); break;
  case '7': set7(); break;
  case '8': set8(); break;
  case '9': set9(); break;

  case 'A': setA(); break;
  case 'B': setB(); break;
  case 'C': setC(); break;
  case 'D': setD(); break;
  case 'E': setE(); break;
  case 'F': setF(); break;
  case 'G': setG(); break;
  case 'H': setH(); break;
  case 'I': setI(); break;
  case 'J': setJ(); break;
  case 'K': setK(); break;
  case 'L': setL(); break;
  case 'M': setM(); break;
  case 'N': setN(); break;
  case 'O': setO(); break;
  case 'P': setP(); break;
  case 'Q': setQ(); break;
  case 'R': setR(); break;
  case 'S': setS(); break;
  case 'T': setT(); break;
  case 'U': setU(); break;
  case 'V': setV(); break;
  case 'W': setW(); break;
  case 'X': setX(); break;
  case 'Y': setY(); break;
  case 'Z': setZ(); break;

  case 'a': seta(); break;
  case 'b': setb(); break;
  case 'c': setc(); break;
  case 'd': setd(); break;
  case 'e': sete(); break;
  case 'f': setf(); break;
  case 'g': setg(); break;
  case 'h': seth(); break;
  case 'i': seti(); break;
  case 'j': setj(); break;
  case 'k': setk(); break;
  case 'l': setl(); break;
  case 'm': setm(); break;
  case 'n': setn(); break;
  case 'o': seto(); break;
  case 'p': setp(); break;
  case 'q': setq(); break;
  case 'r': setr(); break;
  case 's': sets(); break;
  case 't': sett(); break;
  case 'u': setu(); break;
  case 'v': setv(); break;
  case 'w': setw(); break;
  case 'x': setx(); break;
  case 'y': sety(); break;
  case 'z': setz(); break;

  case ' ': break;
  case ',': setcomma(); break;
  case '.': setpoint(); break;
  case ';': setsc(); break;
  case ':': setdpoint(); break;
  case '\n': break; 
  case '+': setadd(); break;
  case '-': setsub(); break;
  case '*': setmpy(); break;
  case '/': setdiv(); break;
  case '=': seteq(); break;
  case '(': setpa(); break;
  case ')': setpb(); break;
  case '[': setba(); break;
  case ']': setbb(); break;
  case '{': setca(); break;
  case '}': setcb(); break;
  case '?': setqm(); break;
  case '!': setbang(); break;
  case '%': setpercent(); break;
  case '\\': setbs(); break;
  case '^': setcaret(); break;
  case '&': setamp(); break;
  case '|': setvline(); break;
  case '<': setLT(); break;
  case '>': setGT(); break;
  case '\'': setqt(); break;
  case '"': setqq(); break;
  case '~': settd(); break;
  case '_': setuline(); break;
  case '`': setgrave(); break;
  default: break;
  }
}

int underline=0;

void putuchar(char c){
  setv("\n\n\n\n\n\n\n\nxxxxxx");
  putchar(c);
}

void print(const string &s){
  int x=posx, y=posy;
  for(int i=0; i<s.size(); i++){
    if(s[i]=='\n'){posx=posxn; x=posxn; posy+=10;}
    else{
      if(underline>0)putuchar(s[i]);
      else putchar(s[i]);
      posx+=6;
    }
  }
}

void printu(const string &s){
  int x=underline;
  underline=1;
  print(s);
  underline=x;
}

}
//namespace


