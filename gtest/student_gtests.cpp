#include <gtest/gtest.h>
#include "../src/ladder.h"
#include "../src/dijkstras.h"
#include <sstream>
#include <fstream>

using namespace std;

set<string> load_test_word_list(const string& filename) {
    set<string> word_list;
    ifstream file(filename);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    return word_list;
}
Graph load_test_graph(const string& filename) {
    Graph G;
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open " << filename << endl;
        exit(1);
    }
    file >> G;
    return G;
}


TEST(WordLadderTest, SameStartEndWord) {
    set<string> word_list = load_test_word_list("words.txt");
    EXPECT_EQ(generate_word_ladder("were", "were", word_list).size(), 0);
}


TEST(WordLadderTest, NoLadderExists) {
    set<string> word_list = load_test_word_list("words.txt");
    vector<string> result = generate_word_ladder("abcdef", "sleep", word_list);
    EXPECT_TRUE(result.empty());
}


TEST(DijkstraTest, SmallGraph) {
    Graph G = load_test_graph("small.txt");

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    vector<int> expected_distances = {0, 3, 6, 1};
    EXPECT_EQ(distances, expected_distances);
}
