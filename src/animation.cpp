

class animation{
public:
  int px, py;
  int done;
  Img* img;
  animation(int,int);
  ~animation();
  void draw();
  char* data;
  void (*next)(animation* self);
};

animation::animation(int x, int y){
  px=x;
  py=y;
  data=0;
  done=0;
}

animation::~animation(){
  if(data) free(data);
}

void animation::draw(){
  draw_img(img,cpx+px-posx,cpy+py-posy);
}

// void ani1_init(animation* self){
//   int* p = new int;
//   *p=0;
//   self->data = (char*)p;  
// }

void ani1_next(animation* self){
  int* p = (int*) self->data;
  if(*p<4){
    (*p)++;
    self->py+=4;
  }else if(*p<8){
    (*p)++;
    self->py+=2;
    if(*p==7) self->img = btab.enemy1f;
  }else if(*p<10){
    (*p)++;
    self->py-=4;
  }else if(*p<40){
    (*p)++;
    self->py-=8;
  }else{
    self->done=1;
  }
  self->data = (char*) p;
}

animation* ani1(int x, int y){
  animation* a;
  a = new animation(x,y);
  a->img = btab.enemy1;
  a->next=ani1_next;
  int* p = (int*)malloc(sizeof(int));
  *p=0;
  a->data = (char*)p;
  return a;
}

