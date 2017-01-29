// Porter.H

/* 

   translated from Java to C++ by Al Popescul, and modified to
   detect stop words (the list of stop words is given in the
   constructor definition); 

   popescul@unagi.cis.upenn.edu
   
   date: March 1999.


   
Java version :
(http://ftp.dcs.glasgow.ac.uk/idom/ir_resources/linguistic_utils/porter.java) 
by:
Fotis Lazarinis (translated from C to Java) June 1997
address:  Psilovraxou 12, Agrinio, 30100



comments: Compile Porter.C, inlcude the Porter class into you program and
create an instance.  Then use the stripAffixes method which takes a
string as input and returns the stem of this string again as a string.
It returns an empty string if the input is a stop word.

*/

#include <iostream.h>
#include <string>
#include <ctype.h>
#include <cctype>
#include <set>


/*
  class stringSet {
private:
    char* stringArray[];
    int num;

public:
    stringSet() { };
    stringSet(char* sA[], int n) {
	stringArray = sA;
	num = n;
    }
    find(char* s);
    find(string s);
}

*/

class Porter {
private: 
  // data member for stop words
    set<string> stopWordList;
  
  string Clean(string);
  int hasSuffix(string, string, string&);
  int vowel(char , char);
  int measure(string);
  int containsVowel(string);
  int cvc(string);
  string step1(string);
  string step2(string);
  string step3(string);
  string step4(string);
  string step5(string);
  string stripPrefixes (string);
  string stripSuffixes(string);
  
  // stop word check
  bool isStopWord(string);

public:
  // constructor initializes the stop word list
  Porter();
  string stripAffixes( string);
};



