// Porter.test.C


#include "Porter.H"
#include <fstream.h>
#include <strstream.h>
#include <cstdlib> 

void error(const char* p, const char* p2 = "")
{
  cerr << p << ' '<<p2 << endl;
  std::exit(1);
}


// and output file name
// output will contain stemmed input file words in 
// that order, with the stop words removed 

main(int argc, char* argv[])
{
  Porter p;
  string str;
  
  char buffer[1000000];

  if(argc != 3) error("wrong number of arguments");


  std::ifstream fcin(argv[1]);
  if(!fcin) error("cannot open input file", argv[1]);
  std::ofstream fcout(argv[2]);
  if(!fcout) error("cannot open output file", argv[2]);
     
  fcin.getline(buffer, 1000000, '\n');

  while(!fcin.eof()) {
    istrstream ist(buffer);
    while(!ist.eof()){
    ist >> str;
    str = p.stripAffixes(str);
    if(str.compare("")!=0)
      fcout << str << " ";
    str = "";
    }
    fcout << endl;
    fcin.getline(buffer, 10000, '\n'); 
  }

  // in case the input file doesn't end with new line character

  istrstream ist(buffer);
    while(!ist.eof()){
    ist >> str;
    str = p.stripAffixes(str);
    if(str.compare("")!=0)
      fcout << str << " ";
    str = "";
    }
    fcout << endl;
    fcin.getline(buffer, 10000, '\n'); 


  fcin.close();
  fcout.close(); 
}


