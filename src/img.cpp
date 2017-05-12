
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

Img* copy_img(Img* img){
  Img* img2 = new Img;
  img2->w = img->w;
  img2->h = img->h;
  int n = img->h*img->w*3;
  img2->p = new unsigned char[n];
  memcpy(img2->p,img->p,n);
  return img2;
}

void swap_char(unsigned char &c1, unsigned char &c2){
  char c;
  c=c1; c1=c2; c2=c;
}

void swap_mem(unsigned char* p1, unsigned char* p2, int n){
  unsigned char c;
  for(int i=0; i<n; i++){
    swap_char(p1[i],p2[i]);
  }
}

void flip(Img* img){
  if(img==NULL) return;
  int m = img->w*3;
  int h = img->h;
  int n=h/2;
  unsigned char* p = img->p;
  for(int i=0; i<n; i++){
    swap_mem(p+i*m,p+(h-1-i)*m,m);
  }
}

void mirror_img(Img* img){
  if(img==NULL) return;
  unsigned char* p = img->p;
  int m = img->h;
  int n = img->w;
  int dn2=n/2;
  int k1,k2,i1;
  for(int i=0; i<m; i++){
    i1=i*n*3;
    for(int j=0; j<dn2; j++){
      k1=i1+j*3;
      k2=i1+(n-1-j)*3;
      swap_char(p[k1],p[k2]);
      swap_char(p[k1+1],p[k2+1]);
      swap_char(p[k1+2],p[k2+2]);
    }
  }
}

