#include <bits/stdc++.h>
using namespace std;
#define fast_io {\
                ios_base::sync_with_stdio(false);\
                cin.tie(0);\
                cout.tie(0);}
#define rep(i,a,b) for(int i=a ; i<(b) ; ++i )
#define pb push_back
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
class Trie {
    public:
    /** data structure Initialized here. */
    struct trie{
        bool flag=false;
        // vector<trie*> next(26);// Wrong // use more explit statement
        vector<trie*> next = vector<trie*>(26,nullptr);
    };
    trie* my_trie;
    Trie(){
        my_trie= new trie;  
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        
        trie* ptr=my_trie; 
        if(word=="")ptr->flag= true;

        
        for(int i=0;i<word.length();++i){
            if( ptr->next[ word[i]-'a' ]==nullptr ){
                ptr->next[ word[i]-'a' ] = new trie;            
                ptr = ptr->next[word[i]- 'a'];
            }else{
                ptr= ptr->next[ word[i]-'a' ];
            }
            if(i==word.length()-1){
                ptr->flag = true;
            }   
        }
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        trie* ptr=my_trie; 
        if(word=="" ){
            if( ptr->flag==true)
            return true;
            else
                return false;
        }
        
        for(int i=0;i<word.length();++i){
            if( ptr->next[ word[i]-'a' ]==nullptr ){
                return false;
            }else{
                ptr= ptr->next[ word[i]-'a' ];
            }
            
            if(i==word.length()-1){
                if(ptr->flag == true)
                return true;
                else
                    return false;
            }
        }
        return false;
    }
    

    bool startsWith(string word) {
         trie* ptr=my_trie; 
        if(word=="" ){
            if( ptr->flag==true)
            return true;
            else
                return false;
        }

        for(int i=0;i<word.length();++i){
            if( ptr->next[ word[i]-'a' ]==nullptr ){
                return false;
            }else{
                ptr= ptr->next[ word[i]-'a' ];
            }
            //POE
            if(i==word.length()-1){
                return true;
            }
        }
        return false;
    }
    
    
    //Method return the number of bad words in the sentence //
    int getBadWordCnt(string sentence){
        
        //break our sentence into words//
        //i.e "you are a bad person" -> "you", "are", "a", "bad", "person"
        // vector<string> words_in_comment = getWords(new_comment);
        vector<string> res;
        
        string current_word="";
        for(int i=0;i<sentence.length();++i){
            
            if(sentence[i]==' '){// " " is the delimiter // break when a space encountered//
                res.pb(current_word);
                current_word="";
            }
            else
                current_word+=sentence[i];
                
            if(i==sentence.length()-1)
                res.pb(current_word);
        }
         
        int cnt=0;// count of bad words in this comment
        for(auto x: res){
            if(search(x))
                ++cnt;
        }
        return cnt;
    }
    float profanity_score(int cnt, int tot){
        float ans = (0.1* cnt)/ tot;
        return (ans);
    }
};

/// ENTRY POINT to Program///
void solve(){
    
    Trie badWords;
    
    //Lets suppose these are the collection of bad words//
    vector<string> my_bad_words={"bad", "stupid", "dumb", "aggresive "};
    int totalBadWords = my_bad_words.size();// total 4 bad words in our collection currently//
    
    //Inssert these words in our trie data structure//
    for(auto word: my_bad_words )
        badWords.insert(word);
    
    
    //Lets assess this how bad this new_comment is?
    string new_comment="abc is a bad person";
    
    //break our sentence into words//
    //i.e "you are a bad person" -> "you", "are", "a", "bad", "person"
    // vector<string> words_in_comment = getWords(new_comment);
    
    int cnt  = badWords.getBadWordCnt(new_comment);
    
    float sc = badWords.profanity_score(cnt, totalBadWords);

    cout<<"profanity score for the comment:\""<< new_comment<<"\" : "<<sc<<"\n";
    
    string another_comment="xyz is a bad and dumb person and stupid";
    
    cnt  = badWords.getBadWordCnt(another_comment);
    sc = badWords.profanity_score(cnt, totalBadWords);
    
    cout<<"profanity score for the comment:\""<< another_comment<<"\" : "<<sc<<"\n";
    
    
}
int main() {
	fast_io;
	int t=1;
// 	cin>>t;
	while(t--)
	{
	    solve();
	}
	return 0;
}

//OUTPUT//
// profanity score for the comment:"abc is a bad person" : 0.025
// profanity score for the comment:"xyz is a bad and dumb person and stupid" : 0.075
