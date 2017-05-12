
#ifndef TK_HPP
#define TK_HPP

#include <string>
#include <vector>
#include <fstream>

namespace tk{

void input(std::string&);
void itos(std::string&,int);
int stoi(const std::string&);
void lstrip(std::string&, bool test(char));
void rstrip(std::string&, bool test(char));
void strip(std::string&, bool test(char));
void load(std::string&, const char*);
void save(const std::string&, const char*);
void read(std::ifstream &is, std::string &s);
void read(std::ifstream &is, std::vector<unsigned char> &v);

}
//namespace


#endif
