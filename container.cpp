#include "container.hpp"

#include<string>

int main(void){
  size_t size = 3;
  Container<std::string>* c = new Container<std::string>(size);
  //int i = 1;
  std::string s1("s1");
  std::string s2("s2");
  std::string s3("s3");
  std::string s4("s4");
  c->insertNew(s1);
  c->insertNew(s2);
  c->insertNew(s3);
  // (s1,0) (s2,0) (s3,0)
  std::cout << "Initially = " << *c << std::endl;

  c->getValue(2); // (s1,0) (s2,0) (s3,1)
  c->getValue(1); // (s1,0) (s2,1) (s3,1)
  std::string s5("s5"); 
  c->modifyExisting(2, s5); // (s1,0) (s2,1) (s5,2)
  // (s1,0) (s2,1) (s5,2)
  std::cout << "After several accessing = " << *c << std::endl;

  c->insertNew(s4); // (s4,0) (s2,1) (s5,2)
  // (s4,0) (s2,1) (s5,2)
  std::cout << "After inserting = " << *c << std::endl;
  std::vector<std::pair<std::string, int> >::iterator iter = c->getIterator();
  ++iter;
  c->removeExisting(iter); // (s4,0) (s5,2)
  // (s4,0) (s5,2)
  std::cout << "Final states = " << *c << std::endl;
  
  // copy the container -> c1
  Container<std::string>* c1(c);
  // (s4,0) (s5,2)
  std::cout << "newly copied c1 = " << *c1 << std::endl;

  // a new container -> c2
  Container<std::string>* c2(c);
  // (s4,0) (s5,2)
  std::cout << "newly copied c2 = " << *c2 << std::endl;
  c2->insertNew(s1); // (s4,0) (s5,2) (s1,0)
  c2->getValue(0); // (s4,1) (s5,2) (s1,0)
  std::cout << "a new container c2 = " << *c2 << std::endl;

  // use assignment operator
  c1 = c2; // (s4,1) (s5,2) (s1,0)
  std::cout << "c1 now equals to c2 = " << *c1 << std::endl;
  c1->insertNew(s3); // (s4,1) (s5,2) (s3,0)
  std::cout << "c1 = " << *c1 << std::endl;
  
  return EXIT_SUCCESS;
}
