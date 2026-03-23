from typing import List

class pySolution:
    def py_fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        # 📄 Final result: list of justified lines
        justified_Sentences: List[str] = []
        
        # 🧩 Current line being built
        current_Sentence: str = ''
        
        # 📏 Tracks length of current line (including tentative spaces)
        current_Sentence_Length: int = 0
        
        # 🔖 Pointers to track word range for current line
        start_Index: int = 0
        end_Index: int = 0
        current_Index: int = 0

        # 🚀 Step 1: Build lines greedily
        while current_Index < len(words):
            # ✅ Check if current word can fit in the line
            if current_Sentence_Length + len(words[current_Index]) <= maxWidth:
                # ➕ Add word length + 1 space (tentative)
                current_Sentence_Length += (len(words[current_Index]) + 1)
                
                # 📍 Update end pointer
                end_Index = current_Index
                current_Index += 1
            else:
                # 🎯 Line is full → time to justify it

                # 🔢 Count words and spaces
                no_of_Words_In_Current_Sentence: int = (end_Index - start_Index) + 1
                no_of_Spaces_In_Current_Sentence: int = no_of_Words_In_Current_Sentence - 1
                
                # 📏 Remaining spaces to distribute
                no_of_Characters_Left: int = maxWidth - (current_Sentence_Length - 1)
                
                # ⚖️ Case 1: More than one word → distribute spaces
                if no_of_Spaces_In_Current_Sentence > 0:
                    # 🔹 Even spaces between words
                    no_of_Even_Spaces_Between_Each_Word: int = (
                        no_of_Characters_Left // no_of_Spaces_In_Current_Sentence
                    ) + 1

                    # 🔹 Extra spaces go to left slots
                    no_of_Left_Aligned_Spaces: int = (
                        no_of_Characters_Left % no_of_Spaces_In_Current_Sentence
                    )

                    # 🧵 Build the justified sentence
                    for i in range(start_Index, end_Index + 1):
                        current_Sentence += words[i]

                        # ⬅️ Add extra space to left gaps first
                        if no_of_Left_Aligned_Spaces > 0:
                            current_Sentence += ' '
                            no_of_Left_Aligned_Spaces -= 1

                        # ➡️ Add evenly distributed spaces
                        if i < end_Index:
                            current_Sentence += (' ' * no_of_Even_Spaces_Between_Each_Word)

                # 📌 Case 2: Only one word → left-align
                else:
                    current_Sentence += (
                        words[start_Index] + ' ' * no_of_Characters_Left
                    )
                
                # ✅ Save justified line
                justified_Sentences.append(current_Sentence)

                # 🔄 Reset for next line
                start_Index = current_Index
                current_Sentence = ''
                current_Sentence_Length = 0
        
        # 🧾 Step 2: Handle last line (left-justified)
        current_Sentence_Length = 0

        for i in range(start_Index, len(words)):
            current_Sentence += words[i]
            current_Sentence_Length += len(words[i])

            # ➡️ Add single space between words
            if i < len(words) - 1:
                current_Sentence += ' '
                current_Sentence_Length += 1
        
        # 📏 Pad remaining spaces at the end
        current_Sentence += (' ' * (maxWidth - current_Sentence_Length))

        # ✅ Add last line
        justified_Sentences.append(current_Sentence)

        # ✅ Return final result
        return justified_Sentences