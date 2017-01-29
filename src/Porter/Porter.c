// Porter.C



/* 

   translated from Java to C++ by Al Popescul, and modified to
   detect stop words (the list of stop words is given in the
   constructor definition); 

   popescul@unagi.cis.upenn.edu
   
   date: March 1999.

   
Java version 
(http://ftp.dcs.glasgow.ac.uk/idom/ir_resources/linguistic_utils/porter.java) 
by:
Fotis Lazarinis (translated from C to Java) June 1997
address:  Psilovraxou 12, Agrinio, 30100



comments: Compile Porter.C, inlcude the Porter class into you program and
create an instance.  Then use the stripAffixes method which takes a
string as input and returns the stem of this string again as a string.
It returns an empty string if the input is a stop word.

*/


#include "Porter.H"
#include "strings.h"

/*
stringSet::find(char* s)
{
    int pos = num / 2;
    int dir;
    while (pos >= 0 && pos < num && !(dir = strcmp(s,stringArray[pos])))
	{
	    if (dir > 0)
		{
		    pos = (pos + num) / 2;
		}
	    else
		{
		    pos = pos / 2;
		}
	}
    if (!dir)
	{
	    return 1;
	}
    else
	{
	    return 0;
	}
}

*/



Porter::Porter() {

const int numberStopWords = 319;


// using the stop word list found at
// http://ftp.dcs.glasgow.ac.uk/idom/ir_resources/linguistic_utils/stop_words

const char* stopWordsLocal[numberStopWords] = {"a", "about", "above",
"across", "after", "afterwards", "again", "against", "all", "almost",
"alone", "along", "already", "also", "although", "always", "am",
"among", "amongst", "amoungst", "amount", "an", "and", "another",
"any", "anyhow", "anyone", "anything", "anyway", "anywhere", "are",
"around", "as", "at", "back", "be", "became", "because", "become",
"becomes", "becoming", "been", "before", "beforehand", "behind",
"being", "below", "beside", "besides", "between", "beyond", "bill",
"both", "bottom", "but", "by", "call", "can", "cannot", "cant", "co",
"computer", "con", "could", "couldnt", "cry", "de", "describe",
"detail", "do", "done", "down", "due", "during", "each", "eg",
"eight", "either", "eleven", "else", "elsewhere", "empty", "enough",
"etc", "even", "ever", "every", "everyone", "everything",
"everywhere", "except", "few", "fifteen", "fify", "fill", "find",
"fire", "first", "five", "for", "former", "formerly", "forty",
"found", "four", "from", "front", "full", "further", "get", "give",
"go", "had", "has", "hasnt", "have", "he", "hence", "her", "here",
"hereafter", "hereby", "herein", "hereupon", "hers", "herself", "him",
"himself", "his", "how", "however", "hundred", "i", "ie", "if", "in",
"inc", "indeed", "interest", "into", "is", "it", "its", "itself",
"keep", "last", "latter", "latterly", "least", "less", "ltd", "made",
"many", "may", "me", "meanwhile", "might", "mill", "mine", "more",
"moreover", "most", "mostly", "move", "much", "must", "my", "myself",
"name", "namely", "neither", "never", "nevertheless", "next", "nine",
"no", "nobody", "none", "noone", "nor", "not", "nothing", "now",
"nowhere", "of", "off", "often", "on", "once", "one", "only", "onto",
"or", "other", "others", "otherwise", "our", "ours", "ourselves",
"out", "over", "own", "part", "per", "perhaps", "please", "put",
"rather", "re", "same", "see", "seem", "seemed", "seeming", "seems",
"serious", "several", "she", "should", "show", "side", "since",
"sincere", "six", "sixty", "so", "some", "somehow", "someone",
"something", "sometime", "sometimes", "somewhere", "still", "such",
"system", "take", "ten", "than", "that", "the", "their", "them",
"themselves", "then", "thence", "there", "thereafter", "thereby",
"therefore", "therein", "thereupon", "these", "they", "thick", "thin",
"third", "this", "those", "though", "three", "through", "throughout",
"thru", "thus", "to", "together", "too", "top", "toward", "towards",
"twelve", "twenty", "two", "un", "under", "until", "up", "upon", "us",
"very", "via", "was", "we", "well", "were", "what", "whatever",
"when", "whence", "whenever", "where", "whereafter", "whereas",
"whereby", "wherein", "whereupon", "wherever", "whether", "which",
"while", "whither", "who", "whoever", "whole", "whom", "whose", "why",
"will", "with", "within", "without", "would", "yet", "you", "your",
"yours", "yourself", "yourselves"};
 
 set<string> temp(stopWordsLocal, stopWordsLocal + numberStopWords);
 
 stopWordList = temp;
 
}

string
Porter::Clean(string str) {
  int last = str.length();
  
  char ch = str[0];
  string temp = "";
  
  for ( int i=0; i < last; i++ ) {
    if ( isalnum(str[i]))
      temp += str[i];
  }
  
  return temp;
} //clean


int
Porter::hasSuffix(string word, string suffix, string& stem) {
  
  string tmp = "";
  
  if (word.length() <= suffix.length())
        return 0;
  if (suffix.length() > 1) 
    if (word[word.length()-2] != suffix[suffix.length()-2])
      return 0;
  
  stem = "";
  
  for ( int i=0; i<word.length()-suffix.length(); i++)
    stem += word[i];
     tmp = stem;
     
     for ( int i=0; i<suffix.length(); i++ )
       tmp += suffix[i];
     
     if ( tmp.compare(word) == 0)
       return 1;
     else
       return 0;
}

int
Porter::vowel( char ch, char prev ) {
    switch ( ch ) {
    case 'a': 
    case 'e': 
    case 'i': 
    case 'o': 
    case 'u': 
      {return 1; break;}
    case 'y': {
      
      switch ( prev ) {
    case 'a': 
    case 'e': 
    case 'i': 
    case 'o': 
    case 'u': 
      { return 0; break; }
    default: 
      return 1;
    }
  }
  default : 
    return 0;
  }
}

int
Porter::measure(string stem) {
    
    int i=0;
    int count = 0;
    int length = stem.length();

    while ( i < length ) {
       for ( ; i < length ; i++ ) {
           if ( i > 0 ) {
              if ( vowel(stem[i],stem[i-1]) )
                 break;
           }
           else {  
              if ( vowel(stem[i],'a') )
                break; 
           }
       }

       for ( i++ ; i < length ; i++ ) {
           if ( i > 0 ) {
              if ( !vowel(stem[i],stem[i-1]) )
                  break;
              }
           else {  
              if ( !vowel(stem[i],'?') )
                 break;
           }
       } 
      if ( i < length ) {
         count++;
         i++;
      }
    } //while
    
    return count;
  }

int
Porter::containsVowel(string word) {
    
    for (int i=0 ; i < word.length(); i++ )
      if ( i > 0 ) {
	if ( vowel(word[i],word[i-1]) )
	  return 1;
         }
      else {  
	if ( vowel(word[0],'a') )
	  return 1;
      }
    
    return 0;
  }


int
Porter::cvc( string str ) {
  int length=str.length();
  
  if ( length < 3 )
    return 0;
  
  if ( (!vowel(str[length-1],str[length-2]) )
       && (str[length-1] != 'w') && (str[length-1] != 'x') && (str[length-1] != 'y')
       && (vowel(str[length-2],str[length-3])) ) {
    
    if (length == 3) {
      if (!vowel(str[0],'?')) 
	return 1;
      else
	return 0;
    }
    else {
      if (!vowel(str[length-3],str[length-4]) ) 
	return 1; 
      else
	return 0;
    } 
  }   
  
  return 0;
}

string
Porter::step1(string str) {

  string stem;
  
  if ( str[str.length()-1] == 's' ) {
    if ( (hasSuffix( str, "sses", stem )) || (hasSuffix( str, "ies", stem)) ){
      string tmp = "";
      for (int i=0; i<(str.length()-2); i++)
	tmp += str[i];
      str = tmp;
    }
    else {
	  if ( ( str.length() == 1 ) && ( str[str.length()-1] == 's' ) ) {
	    str = "";
	    return str;
	  }
	  if ( str[str.length()-2] != 's' ) {
	    string tmp = "";
	    for (int i=0; i<str.length()-1; i++)
	      tmp += str[i];
	    str = tmp;
	  }
    }  
  }
  
     if ( hasSuffix( str,"eed",stem ) ) {
       if ( measure( stem ) > 0 ) {
	 string tmp = "";
	 for (int i=0; i<str.length()-1; i++)
	   tmp += str[i];
	 str = tmp;
       }
     }
     else {  
       if (  (hasSuffix( str,"ed",stem )) || (hasSuffix( str,"ing",stem )) ) { 
	 if (containsVowel( stem ))  {
	   
	   string tmp = "";
	   for ( int i = 0; i < stem.length(); i++)
                  tmp += str[i];
              str = tmp;
              if ( str.length() == 1 )
                 return str;
	      
              if ( ( hasSuffix( str,"at",stem) ) || ( hasSuffix( str,"bl",stem ) ) || ( hasSuffix( str,"iz",stem) ) ) {
		str += "e";
		
              }
              else {   
		int length = str.length(); 
		if ( (str[length-1] == str[length-2]) 
		     && (str[length-1] != 'l') && (str[length-1] != 's') && (str[length-1] != 'z') ) {
		  
                    tmp = "";
                    for (int i=0; i<str.length()-1; i++)
		      tmp += str[i];
                    str = tmp;
		}
                 else
		   if ( measure( str ) == 1 ) {
                       if ( cvc(str) ) 
			 str += "e";
		   }
              }
	 }
       }
     }
     
     if ( hasSuffix(str,"y",stem) ) 
       if ( containsVowel( stem) ) {
	 string tmp = "";
	 for (int i=0; i<str.length()-1; i++ )
               tmp += str[i];
	 str = tmp + "i";
       }
     return str;  
  }



string
Porter::step2( string str ) {

     string suffixes[22][2] = { { "ational", "ate" },
                                    { "tional",  "tion" },
                                    { "enci",    "ence" },
                                    { "anci",    "ance" },
                                    { "izer",    "ize" },
                                    { "iser",    "ize" },
                                    { "abli",    "able" },
                                    { "alli",    "al" },
                                    { "entli",   "ent" },
                                    { "eli",     "e" },
                                    { "ousli",   "ous" },
                                    { "ization", "ize" },
                                    { "isation", "ize" },
                                    { "ation",   "ate" },
                                    { "ator",    "ate" },
                                    { "alism",   "al" },
                                    { "iveness", "ive" },
                                    { "fulness", "ful" },
                                    { "ousness", "ous" },
                                    { "aliti",   "al" },
                                    { "iviti",   "ive" },
                                    { "biliti",  "ble" }};
     string stem;


     

     
     for ( int index = 0 ; index < 22; index++ ) {
         if ( hasSuffix ( str, suffixes[index][0], stem ) ) {
            if ( measure ( stem ) > 0 ) {
               str = stem + suffixes[index][1];
               return str;
            }
         }
     }

     return str;
  }




string
Porter::step3( string str ) {

        string suffixes[8][2] = { { "icate", "ic" },
                                       { "ative", "" },
                                       { "alize", "al" },
                                       { "alise", "al" },
                                       { "iciti", "ic" },
                                       { "ical",  "ic" },
                                       { "ful",   "" },
                                       { "ness",  "" }};
        string stem;

        for ( int index = 0 ; index<8; index++ ) {
            if ( hasSuffix ( str, suffixes[index][0], stem ))
               if ( measure ( stem ) > 0 ) {
                  str = stem + (suffixes[index][1]);
                  return str;
               }
        }
        return str;
  }



string
Porter::step4( string str ) {
        
     string suffixes[21] = { "al", "ance", "ence", "er", "ic", "able", "ible", "ant", "ement", "ment", "ent", "sion", "tion", "ou", "ism", "ate", "iti", "ous", "ive", "ize", "ise"};
     
     string stem;
        
     for ( int index = 0 ; index<21; index++ ) {
         if ( hasSuffix ( str, suffixes[index], stem ) ) {
           
            if ( measure ( stem ) > 1 ) {
               str = stem;
               return str;
            }
         }
     }
     return str;
  }



string
Porter::step5( string str ) {

    if ( str[str.length()-1] == 'e' ) { 
      if ( measure(str) > 1 ) {/* measure(str)==measure(stem) if ends in vowel */
	string tmp = "";
	for ( int i=0; i<str.length()-1; i++ ) 
	  tmp += str[i];
	str = tmp;
      }
      else
	if ( measure(str) == 1 ) {
	  string stem = "";
	  for ( int i=0; i<str.length()-1; i++ ) 
	    stem += str[i];
	  
	  if ( !cvc(stem) )
	    str = stem;
	}
    }
    
    if (str.length() == 1)
      return str;
    if ( (str[str.length()-1] == 'l') && (str[str.length()-2] == 'l') && (measure(str) > 1) )
      if ( measure(str) > 1 ) {/* measure(str)==measure(stem) if ends in vowel */
	string tmp = "";
           for ( int i=0; i<(str.length()-1); i++ ) 
               tmp += str[i];
           str = tmp;
        } 
     return str;
  }
  

string
Porter::stripPrefixes ( string str) {
    
    string prefixes[9] = { "kilo", "micro", "milli", "intra", "ultra", "mega", "nano", "pico", "pseudo"};
    int pos;
    int last = 9;
    for ( int i=0 ; i<last; i++ ) {
      pos = str.find(prefixes[i]);
      if (pos == 0) {
	string temp = "";
	for ( int j=0 ; j<(str.length()-prefixes[i].length()); j++ )
	  temp += str[j+ (prefixes[i].length()) ];
	return temp;
      }
    }
    
    return str;
  }
  
  

string
Porter::stripSuffixes(string str) {
    str = step1( str );
    if ( str.length() >= 1 )
      str = step2( str );
    if ( str.length() >= 1 )
      str = step3( str );
    if ( str.length() >= 1 )
      str = step4( str );
    if ( str.length() >= 1 )
      str = step5( str );
    return str; 
  }
  

string
Porter::stripAffixes( string str ) {


for(int i=0; i<str.length(); ++i)
      str[i] = tolower(str[i]);

    str = Clean(str);

  if(stopWordList.find(str)!=stopWordList.end())
    return "";
  else {
        
    if (( str != "" ) && (str.length() > 2)) {
      str = stripPrefixes(str);
      
      if (str != "" ) 
	str = stripSuffixes(str);
    }   
    
    return str;
  }
} //stripAffixes
