# 📝 Text Justification — Greedy Approach
### 📌 Overview

This problem focuses on formatting a list of words such that each line has exactly **`maxWidth`** characters and is **fully justified** (aligned both left and right).

The approach follows a **greedy strategy**:
- Pack as many words as possible into each line 📦
- Distribute spaces evenly between words ⚖️
- Assign extra spaces to the left slots when needed ⬅️

### 📝 Explanation
#### 🧩 Step 1: Pack Words Greedily
- Iterate through the list of words
- Keep adding words to the current line until adding another word would exceed **`maxWidth`**

#### ⚖️ Step 2: Distribute Spaces
Once a line is finalized:
- Calculate total extra spaces required
- Distribute spaces evenly between words
- If spaces don’t divide evenly:
  - Extra spaces go to the **leftmost gaps first** ⬅️

#### 📏 Step 3: Handle Edge Cases
- **Single word in a line** → Left-justify and pad spaces at the end
- **Last line**:
  - Words are separated by a single space
  - Remaining spaces are added at the end

### 🧠 Pseudocode
```
FUNCTION fullJustify(words, maxWidth):
    result = []
    
    start = 0
    currentLength = 0

    FOR current FROM 0 → len(words) - 1:

        IF currentLength + length(words[current]) <= maxWidth:
            currentLength += length(words[current]) + 1
        ELSE:
            # 🚧 Line is full → justify it

            end = current - 1
            numberOfWords = end - start + 1
            numberOfGaps = numberOfWords - 1

            totalChars = currentLength - 1
            spacesNeeded = maxWidth - totalChars

            line = ""

            IF numberOfGaps > 0:
                evenSpaces = spacesNeeded DIV numberOfGaps
                extraSpaces = spacesNeeded MOD numberOfGaps

                FOR i FROM start → end:
                    line += words[i]

                    IF i < end:
                        # Add evenly distributed spaces
                        line += " " * evenSpaces

                        # Add extra space to left gaps
                        IF extraSpaces > 0:
                            line += " "
                            extraSpaces -= 1
            ELSE:
                # Single word case
                line += words[start]
                line += " " * spacesNeeded

            ADD line TO result

            # 🔄 Reset for next line
            start = current
            currentLength = length(words[current]) + 1

    # 🧾 Handle last line (left-justified)
    line = ""

    FOR i FROM start → len(words) - 1:
        line += words[i]

        IF i < len(words) - 1:
            line += " "

    remainingSpaces = maxWidth - length(line)
    line += " " * remainingSpaces

    ADD line TO result

    RETURN result
```

### 🌍 Multi-Language Implementation
This approach is implemented consistently across:
- 🐍 Python — clean and readable
- ⚙️ C++ — efficient STL-based implementation
- 🔧 C — low-level implementation with manual memory management

### ⏱️ Complexity Analysis
| **Type**             | **Complexity** |
| ---------------- | ---------- |
| Time Complexity  | **⏱️ `O(n)`**    |
| Space Complexity | **📦 `O(n)`**    |


### 💡 Key Insights
- The problem is not about complex algorithms, but **careful simulation 🧩**
- Handling **spaces correctly** is the core challenge ⚖️
- A structured greedy approach keeps the implementation clean and efficient 🚀

### 🎯 Summary
- Greedy packing ensures optimal line usage
- Even space distribution achieves proper justification
- Special handling of edge cases ensures correctness
---