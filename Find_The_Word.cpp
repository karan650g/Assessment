// Import all the necessary libraries for the problem
#include <bits/stdc++.h> 
#include<fstream>
using namespace std; 

// Create a global vector to store all the words with their frequencies
vector<pair<string,int>> S;

// Trie data structure
struct Trie { 
    bool Last; 
    unordered_map<char, Trie*> m; 
    int frequency; 
}; 
  
// Function to create a new Trie node 
Trie* NewNode() 
{ 
    Trie* node = new Trie; 
    node->Last = false; 
    node->frequency =0;  // stores the frequency of each word
    return node; 
} 

// Function to insert Words in the Trie data structure
void insert(Trie*& root, const string& str) 
{ 
  
    // If root is null make a new Trie Node 
    if (root == NULL) 
        root = NewNode(); 
  
    Trie* t = root; 
    for (int i = 0; i < str.length(); i++) { 
        char x = str[i]; 
  
        // Make a new map if there is none for present iteration
        if (t->m.find(x) == t->m.end()) 
            t->m[x] = NewNode(); 
  
        t = t->m[x]; 
    } 
  
    // Mark end of word and increment frequency at last node. 
    t->Last = true; 
    t->frequency+=1; 
} 
  

// Function to search a word in the Trie and return its frequency if the word exists 
int ifPresent(Trie* root, const string& word) 
{ 
  
    // If root is null i.e. the dictionary is empty 
    if (root == NULL) 
        return 0; 
  
    Trie* t = root; 
  
    // Search a word in the Trie 
    for (int i = 0; i < word.length(); i++) { 
        t = t->m[word[i]]; 
        if (t == NULL) 
            return 0; 
    } 
  
    // If it is the end of a valid word stored then return its frequency 
    if (t->Last) 
        return t->frequency; 
    return 0; 
} 

// Function to get current Word
string getWord(char* str, int n)
{

    string s;
   for(int i=0; i<n; i++)
   {
      s+=str[i];
   }
   //return word
   return s;
}
// Function to iterate over the Trie recursively and store words with their frequency.
void getSerializedWords(Trie* root, char* words, int pos = 0)
{
   if(root == NULL)
      return;
   if(root->Last)
   {
     //store the word in global vector
      S.push_back(make_pair(getWord(words, pos),root->frequency));
   }
   for(int i=0; i<26; i++)
   {
      if(root->m.find(char(i+97)) != root->m.end())
      {
         words[pos] = i+'a';
         getSerializedWords(root->m[char(i+97)], words, pos+1);
      }
   }
}

  

int main() 
{ 
    //Start with root Node as NULL

    Trie* root = NULL; 
    ifstream fin; 
  
    // Read Input data from the Dictionary|||||| -------------------------------------------
    fin.open("EnglishDictionary.csv");  //|||||| This files contains only unique word
    vector<string> row;                 //|||||| correctness can be verified using demo below 
    string line, word;                  //|||||| --------------------------------------------
  
    while (!fin.eof()) 
    { 
        //read each line one by one
        getline(fin, line); 
  
        // break words and store them in a vector 
        stringstream s(line);  
        while (getline(s, word, ',')) { 
            row.push_back(word); 
        } 
  
            insert(root,row[0]); 
            row.clear();
        
    } 

    //|||||||||||||||||||||||||||||||||||||||||||||||||||
    /*insert(root,"zoo");
    insert(root,"zoo");
    // check if the Trie is implemented correctly  ------------------------------------------------
    string str = "zoo";                         //| Demo to check if trie is implemented correctly |
    int freq = ifPresent(root,str);                ------------------------------------------------
    if(freq>0);
    cout<<"YES ,"<<freq<<endl;*/
    //|||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Store the Serialized words with frequencies in a new CSV file
    char words[1000001];
    // call function to iterate over Trie 
    getSerializedWords(root, words);
    for(int i=0;i<S.size();i++)
    cout<<S[i].first<<" , "<<S[i].second<<"\n";
    ofstream OP;
    OP.open("Serialized_Dictionary.csv");
    for(int i=0;i<S.size();i++)
    OP<<S[i].first<<" , "<<S[i].second<<"\n";
    
    return 0; 
} 