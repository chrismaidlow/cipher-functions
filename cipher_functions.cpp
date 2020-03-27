// Example program
#include <iostream>
using std::cout; using std::cin; using std::endl;
#include <string>
using std::string;
#include "proj05_functions.h"

/* 
   iterate through string and for every character
   that is a letter (excluding q) lowercase and 
   append to new string.
*/

string clean_string(string s)
{
    string new_str = "";
    
    //iterate
    for(char character : s)
    {
        //check if letter
        if(isalpha(character))
        {
            //exclude Q
            if(character != 'q' and character != 'Q')
            {
               new_str.push_back(tolower(character));
            }        
                
        }
    }
    return new_str;
}

/* 
   Part 1: iterate through string key - search if char in encoded string
   if not, append it. This gets rid of duplicates.
   
   Part 2: iterate through string alphabet and any char not 
   already included in encoded string gets appended.
*/

string create_encoding(string key)
{
    //initialize variables - ignore is to remove q's
    string encoded = "";
    string alphabet = "abcdefghijklmnoprstuvwxyz";
    char ignore = 'q';
    
    //iterate through string key
    for(char character : key)
    {
        
        if(isalpha(character))
        {
            //if char not found in encoded 
            if(encoded.find(character) == string::npos)
            {
               // if char not Q or q
               if(character != ignore and character != 'Q')
               {
                //append it to encoded
                encoded.push_back(tolower(character));
               }
            } 
        }
    }
    // iterate through alphabet
    for(char alphachara : alphabet)
    {
        //if letter not in encoded append to encoded
        if(encoded.find(alphachara) == string::npos)
        {
            encoded.push_back(alphachara);
        }
    }
    return encoded;
}

/* 
    iterate through dg pulling two char substrings at a time
    using algo provided for the corresponding keywords encode 
    the characters and append them to encoded.
*/

string encode_digraph(string dg, string block1, string block2)
{
    string encoded = "";
    string alphabet = "abcdefghijklmnoprstuvwxyz";
    
    //create encoded strings for each block
    string block1_code = create_encoding(block1);
    string block2_code = create_encoding(block2);
    
    //iterate through string dg evaluating 2 chars at time
    for(int limit = 0; limit < dg.size(); limit +=2)
    {
        //allows us to evaluate 2 char substrings 
        string sub = dg.substr(limit, 2);
        
        //Algo to find encoded letter for first char
        long index_letter1 = alphabet.find(sub[0]);
        long index_letter2 = alphabet.find(sub[1]);
        long row_let1 = index_letter1/5;
        long col_let1 = index_letter2 % 5;
        long new_index1 = row_let1*5 + col_let1;
        char new_letter1 = block1_code[new_index1];
        encoded.push_back(new_letter1);
        
        //Algo to find encoded letter for second char
        long row_let2 = index_letter2/5;
        long col_let2 = index_letter1%5;
        long new_index2 = row_let2*5 + col_let2;
        char new_letter2 = block2_code[new_index2];
        encoded.push_back(new_letter2);
    }

    return encoded;
}

/*
    Very similar to encode_digraph except the intial index 
    is found in the blocks instead of in the alphabet
*/

string decode_digraph(string dg, string block1, string block2)
{
    string encoded = "";
    string alphabet = "abcdefghijklmnoprstuvwxyz";
    
    //create encoding 
    string block1_code = create_encoding(block1);
    string block2_code = create_encoding(block2);
    
    for(int limit = 0; limit < dg.size(); limit +=2)
    {
        //similar algo for encode_digraph 
        //indexing is reversed through
        string sub = dg.substr(limit, 2);
        long index_letter1 = block1_code.find(sub[0]);
        long index_letter2 = block2_code.find(sub[1]);
        long row_let1 = index_letter1/5;
        long col_let1 = index_letter2 % 5;
        long reindex1 = row_let1*5 + col_let1;
        char output = alphabet[reindex1];
        encoded.push_back(output);
        
        long row_let2 = index_letter2/5;
        long col_let2 = index_letter1%5;
        long reindex2 = row_let2*5 + col_let2;
        char output2 = alphabet[reindex2];
        encoded.push_back(output2);
    }
    return encoded;
}

string encode(string msg, string key1, string key2)
{
    string encoded = "";
    string alphabet = "abcdefghijklmnoprstuvwxyz";
    long cnt = 0;
    
    //get count of all letters in string before clean string
    for(char charas : msg)
    {
        if(isalpha(charas))
        {
            cnt += 1;
        }
    }
    
    //clean string
    string new_msg = clean_string(msg);
    
    //create keys from encoding
    string block1_code = create_encoding(key1);
    string block2_code = create_encoding(key2);
    
    //if odd amount of letters append x to clean string 
    if(cnt % 2)
    {
        new_msg.push_back('x');
    }
    
    //SEE: encode_digraph()
    for(int limit = 0; limit < new_msg.size(); limit +=2)
    {
        string sub = new_msg.substr(limit, 2);
        long index_letter1 = alphabet.find(sub[0]);
        long index_letter2 = alphabet.find(sub[1]);
        long row_let1 = index_letter1/5;
        long col_let1 = index_letter2 % 5;
        long reindex1 = row_let1*5 + col_let1;
        char output = block1_code[reindex1];
        encoded.push_back(output);
        
        long row_let2 = index_letter2/5;
        long col_let2 = index_letter1%5;
        long reindex2 = row_let2*5 + col_let2;
        char output2 = block2_code[reindex2];
        encoded.push_back(output2);
    }

    return encoded;
}

/* 
    same as decode_digraph except allows for full messages
*/

string decode(string msg, string key1, string key2)
{
    string encoded = "";
    string alphabet = "abcdefghijklmnoprstuvwxyz";
    
    string new_msg = clean_string(msg);
    
    string block1_code = create_encoding(key1);
    string block2_code = create_encoding(key2);
    
    // SEE: decode_digraph()
    for(int limit = 0; limit < new_msg.size(); limit +=2)
    {
        string sub = new_msg.substr(limit, 2);
        long index_letter1 = block1_code.find(sub[0]);
        long index_letter2 = block2_code.find(sub[1]);
        long row_let1 = index_letter1/5;
        long col_let1 = index_letter2 % 5;
        long reindex1 = row_let1*5 + col_let1;
        char output = alphabet[reindex1];
        encoded.push_back(output);
        
        long row_let2 = index_letter2/5;
        long col_let2 = index_letter1%5;
        long reindex2 = row_let2*5 + col_let2;
        char output2 = alphabet[reindex2];
        encoded.push_back(output2);
    }

    return encoded;
}