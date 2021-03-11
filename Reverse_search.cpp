// Import all the necessary libraries for the problem
#include <bits/stdc++.h> 
#include<fstream>
using namespace std; 

// Create a global variable that assigns label to each word
int Node = 0;

// Trie data structure
struct Trie { 
    bool Last; 
    unordered_map<char, Trie*> m; 
    int num; 
}; 
  
// Function to create a new Trie node 
Trie* NewNode() 
{ 
    Trie* node = new Trie; 
    node->Last = false; 
    node->num =0;  // stores the label of each word
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
  
        // Make a new map if there is none for present letter of the word.
        if (t->m.find(x) == t->m.end()) 
            t->m[x] = NewNode(); 
  
        t = t->m[x]; 
    } 
  
    // Mark end of word
    t->Last = true; 
} 
  


// Function to Label every word with corresponding number in lexicographical order
void Labelling(Trie* root)
{
   if(root == NULL)
      return ;
   if(root->Last)
   {
      //Store the label as this is the last node of the word
      root->num = Node;
      Node+=1;
   }
   // Keep iterating untill the word ends
   for(int i=0; i<26; i++)
   {
      if(root->m.find(char(i+97)) != root->m.end())
      {
         Labelling(root->m[char(i+97)]);
      }
   }
   return ;
}

// Function to print the word if it is found.
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

// Function to Find the word from it's corresponding label
// Keep storing temporary words untill we find our match
void Findword(Trie* root, char* words,int N, int pos = 0)
{
   if(root == NULL)
      return;

   if(root->Last && root->num == N)
   {
        cout<<getWord(words, pos);
        return ;
   }

   for(int i=0; i<26; i++)
   {
      if(root->m.find(char(i+97)) != root->m.end())
      {
         words[pos] = i+'a';
         Findword(root->m[char(i+97)], words,N, pos+1);
      }
   }
}

  

int main() 
{ 
    //Start with root Node as NULL

    Trie* root = NULL; 

    insert(root,"zoo");        //     |  0 -> arr
    insert(root,"yum");        //     |  1 -> har
    insert(root,"kar");        //     |  2 -> kar
    insert(root,"arr");        //     |  3 -> yamuna
    insert(root,"yamuna");     //     |  4 -> yum
    insert(root,"har");        //     |  5 -> zoo
    insert(root,"zxy");        //     |  6 -> zxy
    char words[100];
    // Start labelling each word
    Labelling(root); 

    // Find the word with corresponding input label.
    Findword(root,words,4);
    cout<<endl;
    
    
    return 0; 
} 