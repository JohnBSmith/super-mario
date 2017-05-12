

struct node{
  void *data;
  node *next, *prev;
};

class list{
public:
  node *first, *last;
  list();
  void append(void*);
  void remove(node*);
  void insert(node*,void*);
  void pop();
  void pop_front();
};

list::list(){
  first=0;
  last=0;
}

void list::append(void* data){
  node* b;
  if(this==0){
    std::cout << "error in append\n";
  }else if(last==0){
    last = new node;
    first = last;
    last->data = data;
    last->prev = 0;
    last->next = 0;
  }else{
    b=last;
    last->next = new node;
    last = last->next;
    last->prev = b;
    last->next = 0;
    last->data=data;
  }
}

void list::remove(node* p){
  node* b;
  if(last==0){
    std::cout << "error in list remove: list is empty\n";
  }else if(p==last and last == first){
    first=0;
    last=0;
    delete p;
  }else if(p==first){
    b=p->next;
    b->prev=0;
    first=b;
    delete p;
  }else if(p==last){
    b=p->prev;
    b->next=0;
    last=b;
    delete p;
  }else{
    b=p->prev;
    p->next->prev = b;
    b->next = p->next;
    delete p;
  }
}

void list::insert(node* p, void* data){
  node* b;
  if(p==first){
    b = new node;
    b->data = data;
    b->prev=0;
    b->next=p;
    first=b;
  }else{
    b = new node;
    b->data=data;
    b->prev=p->prev;
    b->next=p;
    p->prev->next=b;
  }
}

void list::pop(){
  remove(last);
}

void list::pop_front(){
  remove(first);
}

/*
void print(list &a){
  node* p;
  cout << "[";
  for(p=a.first; p!=0; p=p->next){
    cout << "(" << *static_cast<int*>(p->data) << ")";
  }
  cout << "]\n";
}

int main(){
  list a;
  for(int i=0; i<20; i++){
    a.append(new int(i));
    print(a);
  }
}
*/
