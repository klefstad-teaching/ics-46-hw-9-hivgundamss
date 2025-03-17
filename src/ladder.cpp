#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include <cctype>
using namespace std;

void error(string word1, string word2, string msg){
    cout << word1 << ',' << word2 << ',' << msg;
}


string to_lowercase(string str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c){ return tolower(c); });
    return str;
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(to_lowercase(word));
    }

    file.close();
}
bool edit_distance_within(const string& str1, const string& str2, int d) {
    const int m = str1.length();
    const int n = str2.length();
    
    if (abs(m - n) > d) return false;
    
    vector<int> prev(n + 1, 0), current(n + 1, 0);
    
    for (int j = 0; j <= n; ++j) prev[j] = j;
    
    for (int i = 1; i <= m; ++i) {
        current[0] = i; 
        
        for (int j = 1; j <= n; ++j) {
            if (str1[i-1] == str2[j-1]) {
                current[j] = prev[j-1];
            } else {
                current[j] = 1 + min({ prev[j],current[j-1],prev[j-1] }); 
            }
        }
        
        if (*min_element(current.begin(), current.end()) > d) {
            return false;
        }
        
        swap(prev, current);
    }
    
    return prev[n] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {

    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if(begin_word == end_word){
        error(begin_word,end_word,"Two words are the same.");
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    unordered_set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void print_word_ladder(const vector<string>& ladder){
    if(ladder.empty())
        cout << "No word ladder found.";
    else{
        cout << "Word ladder found: ";
        for(auto s : ladder)
            cout << s << ' ';
    }
    cout << endl;

}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "./src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

 
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}