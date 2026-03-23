#include <stdlib.h>
#include <string.h>

char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    // 📄 Allocate result array (max possible lines = wordsSize)
    char** justified_Sentences = (char**) malloc(wordsSize * sizeof(char*));

    // 🔢 Initialize number of lines returned
    returnSize[0] = 0;

    // 🧩 Temporary buffer to build each line
    char* current_Sentence = (char*) malloc((maxWidth + 1) * sizeof(char));
    current_Sentence[maxWidth] = '\0';   // 🛑 Null terminate

    // 📏 Tracks current line length (including tentative spaces)
    int current_Sentence_Length = 0;

    // 🔖 Pointers to track word range for current line
    int start_Index = 0;
    int end_Index = 0;
    int current_Index = 0;

    // 🚀 Step 1: Greedily pack words into lines
    while(current_Index < wordsSize) {

        // ✅ Check if current word can fit in the current line
        if(current_Sentence_Length + strlen(words[current_Index]) <= maxWidth) {
            current_Sentence_Length += (strlen(words[current_Index]) + 1); // ➕ include space
            end_Index = current_Index;
            current_Index += 1;
        }
        else {
            // 🎯 Line is full → justify it

            int no_of_Words_In_Current_Sentence = (end_Index - start_Index) + 1;
            int no_of_Spaces_In_Current_Sentence = no_of_Words_In_Current_Sentence - 1;

            // 📏 Total spaces to distribute
            int no_of_Characters_Left = maxWidth - (current_Sentence_Length - 1);

            // 🧵 Pointer to fill characters in current_Sentence
            int current_Sentence_Index = 0;

            // ⚖️ Case 1: Multiple words → distribute spaces evenly
            if(no_of_Spaces_In_Current_Sentence > 0) {

                // 🔹 Base spaces between each word
                int no_of_Spaces_In_Each_Word = (
                    no_of_Characters_Left / no_of_Spaces_In_Current_Sentence
                ) + 1;

                // 🔹 Extra spaces go to leftmost gaps
                int no_of_Left_Aligned_Spaces = (
                    no_of_Characters_Left % no_of_Spaces_In_Current_Sentence
                );

                // 🔄 Build the justified sentence
                for(int i = start_Index; i <= end_Index; ++i) {

                    // 📥 Copy word character by character
                    for(int j = 0; words[i][j] != '\0'; ++j) {
                        current_Sentence[current_Sentence_Index++] = words[i][j];
                    }

                    // ⬅️ Add extra spaces to left gaps first
                    if(no_of_Left_Aligned_Spaces > 0) {
                        current_Sentence[current_Sentence_Index++] = ' ';
                        no_of_Left_Aligned_Spaces -= 1;
                    }

                    // ➡️ Add evenly distributed spaces
                    if(i < end_Index) {
                        for(int j = 0; j < no_of_Spaces_In_Each_Word; ++j) {
                            current_Sentence[current_Sentence_Index++] = ' ';
                        }
                    }
                }
            }
            // 📌 Case 2: Only one word → left-aligned
            else {
                // 📥 Copy the word
                for(int j = 0; words[start_Index][j] != '\0'; ++j) {
                    current_Sentence[current_Sentence_Index++] = words[start_Index][j];
                }

                // ➡️ Fill remaining spaces
                for(int j = 0; j < no_of_Characters_Left; ++j) {
                    current_Sentence[current_Sentence_Index++] = ' ';
                }
            }

            // 📦 Allocate memory for this justified line
            justified_Sentences[returnSize[0]] = (char*) malloc((maxWidth + 1) * sizeof(char));

            // 📋 Copy constructed line
            strcpy(justified_Sentences[returnSize[0]], current_Sentence);

            // 🔄 Move to next line
            start_Index = current_Index;
            returnSize[0] += 1;

            // 🧹 Reset buffer for next line
            free(current_Sentence);
            current_Sentence_Length = 0;

            current_Sentence = (char*) malloc((maxWidth + 1) * sizeof(char));
            current_Sentence[maxWidth] = '\0';
        }
    }

    // 🧾 Step 2: Handle last line (left-justified)
    current_Sentence_Length = 0;

    for(int i = start_Index; i < wordsSize; ++i) {

        // 📥 Copy word
        for(int j = 0; words[i][j] != '\0'; ++j) {
            current_Sentence[current_Sentence_Length++] = words[i][j];
        }

        // ➡️ Add single space between words
        if(i < wordsSize - 1) {
            current_Sentence[current_Sentence_Length++] = ' ';
        }
    }

    // 📏 Pad remaining spaces at the end
    int characters_Left = maxWidth - current_Sentence_Length;
    for(int j = 0; j < characters_Left; ++j) {
        current_Sentence[current_Sentence_Length++] = ' ';
    }

    // 📦 Save last line
    justified_Sentences[returnSize[0]] = (char*) malloc((maxWidth + 1) * sizeof(char));
    strcpy(justified_Sentences[returnSize[0]], current_Sentence);

    returnSize[0] += 1;

    // 🧹 Free temporary buffer
    free(current_Sentence);
    
    // ✅ Return final result
    return justified_Sentences;
}