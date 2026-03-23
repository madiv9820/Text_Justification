#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        // 📄 Final result: list of justified lines
        vector<string> justified_Sentences;

        // 🧩 Current line being constructed
        string current_Sentence = "";

        // 📏 Tracks current line length (including tentative spaces)
        int current_Sentence_Length = 0;

        // 🔖 Pointers to track range of words in current line
        int start_Index = 0;
        int end_Index = 0;
        int current_Index = 0;

        // 🚀 Step 1: Greedily pack words into lines
        while(current_Index < words.size()) {
            // ✅ Check if current word can fit in the line
            if(current_Sentence_Length + words[current_Index].length() <= maxWidth) {
                // ➕ Add word length + 1 (for space after it)
                current_Sentence_Length += (words[current_Index].length() + 1);

                // 📍 Update end pointer
                end_Index = current_Index;
                current_Index += 1;
            }
            else {
                // 🎯 Line is full → justify it

                // 🔢 Number of words and gaps
                int no_of_Words_In_Current_Sentence = (end_Index - start_Index) + 1;
                int no_of_Spaces_In_Current_Sentence = (no_of_Words_In_Current_Sentence - 1);

                // 📏 Total spaces to distribute
                int no_of_Characters_Left = maxWidth - (current_Sentence_Length - 1);

                // ⚖️ Case 1: More than one word → distribute spaces evenly
                if(no_of_Spaces_In_Current_Sentence > 0) {

                    // 🔹 Base spaces between each word
                    int no_of_Even_Spaces_Between_Each_Word = (
                        no_of_Characters_Left / no_of_Spaces_In_Current_Sentence
                    ) + 1;

                    // 🔹 Extra spaces go to leftmost gaps
                    int no_of_Left_Aligned_Spaces = (
                        no_of_Characters_Left % no_of_Spaces_In_Current_Sentence
                    );

                    // 🧵 Build the justified sentence
                    for(int i = start_Index; i <= end_Index; ++i) {
                        current_Sentence += words[i];
                        
                        // ⬅️ Add extra spaces to left slots first
                        if(no_of_Left_Aligned_Spaces > 0) {
                            current_Sentence += ' ';
                            no_of_Left_Aligned_Spaces -= 1;
                        }

                        // ➡️ Add evenly distributed spaces
                        if(i < end_Index) {
                            current_Sentence += string(no_of_Even_Spaces_Between_Each_Word, ' ');
                        }
                    }
                }
                // 📌 Case 2: Only one word → left-align
                else {
                    current_Sentence += words[start_Index];
                    current_Sentence += string(no_of_Characters_Left, ' ');
                }

                // ✅ Save justified line
                justified_Sentences.push_back(current_Sentence);

                // 🔄 Reset for next line
                start_Index = current_Index;
                current_Sentence = "";
                current_Sentence_Length = 0;
            }
        }

        // 🧾 Step 2: Handle last line (left-justified)
        current_Sentence_Length = 0;

        for(int i = start_Index; i < words.size(); ++i) {
            current_Sentence += words[i];
            current_Sentence_Length += words[i].length();

            // ➡️ Add single space between words
            if(i < words.size() - 1) {
                current_Sentence += ' ';
                current_Sentence_Length += 1;
            }
        }

        // 📏 Pad remaining spaces at the end
        current_Sentence += string(maxWidth - current_Sentence_Length, ' ');

        // ✅ Add last line
        justified_Sentences.push_back(current_Sentence);

        // ✅ Return final result
        return justified_Sentences;
    }
};