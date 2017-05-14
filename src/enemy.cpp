
class Enemy{
public:
  int px,py;
  int direction;
  int active;
  Img* img;
  Enemy(int x, int y);
  void draw();
  void move();
private:
  void collision();
  int ctest(int,int);
};

Enemy::Enemy(int x, int y){
  px=x; py=y;
  img=0;
  direction=1;
  active=1;
}

void Enemy::draw(){
  if(active){
    draw_img(img,cpx+px-posx,cpy+py-posy);
    // draw_cross(cpx+px-posx,cpy+py-posy);
  }
}

int Enemy::ctest(int x1, int y1){
  int x=x1/24, y=y1/24;
  int n=map.w;
  int a = map.p[y*n+x].solid;
  return a;
}

void Enemy::collision(){
  int p1x, p2x;
  int cleft, cright;
  p1x=px; p2x=px+24;
  cleft = ctest(p1x-2,py);
  cright = ctest(p2x+1,py);
  if(cleft>1 or cright>1){
    direction = -direction;
  }
}

void Enemy::move(){
  if(active){
    if(abs(posx-px)>400){
      active=0;
    }else{
      px+=direction;
      collision();
    }
  }else{
    if(abs(posx-px)<400) active=1;
  }
}

