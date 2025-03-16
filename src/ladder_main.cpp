#include "ladder.h"

int main() {

    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;
    set<string> word_list;
    load_words(word_list, "words.txt");

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);
    return 0;
}
