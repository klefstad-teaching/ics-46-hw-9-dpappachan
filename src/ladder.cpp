#include "ladder.h"

void error(string word1, string word2, string msg) {

    cerr <<"Error: " << msg<< " | "<< word1<<" -> " << word2<<endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    if (abs(len1-len2) >1){
        return false;
    }
    int i =0, j =0, edits = 0;
    while (i< len1 && j <len2) {
        if (str1[i] != str2[j]) {
            if (++edits > d) {
                return false;
            }
            if (len1 > len2) {
                ++i; 
            }else if (len1 < len2) {
                ++j;

            }else { 
                ++i; 
                ++j; 

            }
        } else {
            ++i; 
            ++j;
        }
    }
    return edits+(len1 -i) +(len2 -j)<=d;
}
bool is_adjacent(const string & word1, const string & word2) {
    return edit_distance_within(word1, word2, 1);

}

vector<string> generate_word_ladder(const string& begin_word, const string & end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {}; 

    queue<vector<string>> ladderQ;

    set<string> visited;
    ladderQ.push({begin_word});
    visited.insert(begin_word);
    while (!ladderQ.empty()) {
        vector<string> ladder = ladderQ.front();
        ladderQ.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && !visited.count(word)) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                visited.insert(word);
                
                if (word == end_word) return new_ladder;
                ladderQ.push(new_ladder);
            }
        }
    }
    return {};  
}

void load_words(set<string>& word_list, const string & file_name) {
    ifstream file(file_name);

    if (!file) {
        cerr << "Error opening file: " <<file_name<<endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string> & ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}
