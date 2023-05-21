
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

using namespace std;

class Synonyms {
public:
    // The function adds both words as synonyms
    void Add(const string& first_word, const string& second_word)
    {
        synonyms_[first_word].insert(second_word);
        synonyms_[second_word].insert(first_word);
        cout << first_word << " and " << second_word << " were added as synonyms." << endl;
        cout << endl;
    }
    // Returns the number of synonyms for the given word  
    size_t GetSynonymCount(const string& word) const
    {
        if (synonyms_.count(word) != 0) { return synonyms_.at(word).size(); }
        return 0;
    }
    // Checks if two given words are synonyms
    bool AreSynonyms(const string& first_word, const string& second_word) const
    {
        if (synonyms_.count(first_word) != 0)
        {
            return synonyms_.at(first_word).count(second_word) != 0;
        }
        return false;
    }
    // Prints all the words and synonyms
    void PrintAll()
    {
        size_t Count = 0;
        if (!synonyms_.empty())
        {
            cout << "These are the words and their synonyms: " << endl;
            for (const auto iter : synonyms_)
            {
                cout << iter.first << ": ";
                for (const auto syn : iter.second)
                {
                    if (Count >= iter.second.size())
                    {
                        cout << syn;
                    }
                    else
                    {
                        cout << syn << ", "s;
                        ++Count;
                    }
                }
                cout << ";" << endl;
            }
        }
    }


private:
    map<string, set<string>> synonyms_;

public:
    // Output function for map
    friend ostream& operator <<(ostream& Mos, const Synonyms& s)
    {
        for (const auto iter : s.synonyms_)
        {
            Mos << iter.first << ": "s << endl;
            for (const auto word : iter.second)
            {
                Mos << word << " " << endl;
            }
        }
        return Mos;
    }
    map<string, set<string>> GetAllWords()
    {
        return synonyms_;
    }
};
// Template function for macros to check synonyms for word
template <typename U, typename T>
void TestForSyn(const T& t, const U& u, const string& t_str, const string& hint)
{
    if (t == u)
    {
        cout << "Apparently the word " << t_str << " has no synonyms.";
        cout << endl;
        cout << hint << endl;
    }
    else
    {
        if (t > 1)
        {
            cout << "Apparently the word " << t_str << " has " << t << " synonyms." << endl;
        }
        else
        {
            cout << "Apparently the word " << t_str << " has " << t << " synonym." << endl;
        }
    }
    cout << endl;
}

// Template function for macros to check if words are synonyms
template <typename U, typename T>
void TestIfSyn(const T& t, const U& u, const string& t_str, const string& u_str, const string& hint)
{
    if (t == u)
    {
        cout << "Sorry, " << t_str << " and " << u_str << " aren't synonyms." << endl;
    }
    else
    {
        cout << "You were right, " << t_str << " and " << u_str << " are synonyms" << endl;
    }
    cout << endl;
}

// Macros for testing functionality
#define TEST_FOR_SYN(a, b, c) TestForSyn((a), (b), (c), ""s)
#define TEST_IF_SYN(a, b, c, e) TestIfSyn((a), (b), (c), (e), ""s)
#define TEST_PRINT_ALL synonyms.PrintAll()

// Function to run tests
void TestAreSynonyms() {
    Synonyms synonyms;
    TEST_IF_SYN(synonyms.AreSynonyms("winner"s, "champion"s), 0, "winner"s, "champion"s, ""s);

    synonyms.Add("winner"s, "champion"s);
    synonyms.Add("good"s, "nice"s);
    synonyms.Add("automobile"s, "sedan"s);
    synonyms.Add("automobile"s, "bus"s);
    synonyms.Add("good"s, "amazing"s);
    synonyms.Add("melody"s, "music"s);
    synonyms.Add("music"s, "tune"s);
    synonyms.Add("music"s, "melody"s);
    synonyms.Add("house"s, "home"s);
    synonyms.Add("car"s, "automobile"s);

    TEST_FOR_SYN(synonyms.GetSynonymCount("winner"s), 0, "winner"s, ""s);
    TEST_FOR_SYN(synonyms.GetSynonymCount("melody"s), 0, "melody"s, ""s);
    TEST_FOR_SYN(synonyms.GetSynonymCount("melody"s), 0, "melody"s, ""s);
    TEST_FOR_SYN(synonyms.GetSynonymCount("melody"s), 0, "melody"s, ""s);
    TEST_FOR_SYN(synonyms.GetSynonymCount("music"s), 0, "music"s, ""s);
    TEST_FOR_SYN(synonyms.GetSynonymCount("music"s), 0, "music"s, ""s);

    TEST_IF_SYN(synonyms.AreSynonyms("winner"s, "champion"s), 0, "winner"s, "champion"s, ""s);
    TEST_IF_SYN(synonyms.AreSynonyms("good"s, "nice"s), 0, "good"s, "nice"s, ""s);
    TEST_IF_SYN(synonyms.AreSynonyms("champion"s, "winner"s), 0, "champion"s, "winner"s, ""s);

    TEST_PRINT_ALL;
}

int main() {

    Synonyms synonyms;
    TestAreSynonyms();
    string line;
    while (getline(cin, line)) {
        istringstream command(line);
        string action;
        command >> action;

        if (action == "ADD"s)
        {
            string first_word, second_word;
            command >> first_word >> second_word;
            synonyms.Add(first_word, second_word);
        }
        else if (action == "COUNT"s)
        {
            string word;
            command >> word;
            cout << synonyms.GetSynonymCount(word) << endl;
        }
        else if (action == "CHECK"s)
        {
            string first_word, second_word;
            command >> first_word >> second_word;
            if (synonyms.AreSynonyms(first_word, second_word))
            {
                cout << "YES"s << endl;
            }
            else { cout << "NO"s << endl; }
        }
        else if (action == "EXIT") { break; }
    }
}
