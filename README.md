# [📝 Text Justification](https://leetcode.com/problems/text-justification/description/?envType=study-plan-v2&envId=top-interview-150)
You are given:
- An array of strings **`words`**, where each element represents a word 📚
- An integer **`maxWidth`**, representing the maximum number of characters allowed per line 📏

Your task is to format the given words into multiple lines such that:
- Each line contains **exactly `maxWidth` characters**
- Each line is **fully justified**, meaning text is aligned evenly on both the left and right sides ⚖️

### 📌 Examples

#### 🔹 Example 1
#### Input:
```
words = ["This", "is", "an", "example", "of", "text", "justification."]
maxWidth = 16
```
#### Output:
```
[
  "This    is    an",
  "example  of text",
  "justification.  "
]
```

#### 🔹 Example 2
#### Input:
```
words = ["What","must","be","acknowledgment","shall","be"]
maxWidth = 16
```

#### Output:
```
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
```

#### 🔹 Example 3
#### Input:
```
words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"]
maxWidth = 20
```

#### Output:
```
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
```

#### Explanation 🧾:
- The last line is left-justified → **`"shall be "`**
- The second line contains only one word, so it is also left-aligned

### 📏 Formatting Rules
- Words must be arranged in order and grouped into lines 🧩
- Each line should contain as many words as possible without exceeding **`maxWidth`**
- Extra spaces **`' '`** should be added so that the total length of each line becomes exactly **`maxWidth`**

### 📊 Constraints
- **`1 <= words.length <= 300`**
- **`1 <= words[i].length <= 20`**
- **`words[i]`** consists of only English letters and symbols 🔡
- **`1 <= maxWidth <= 100`**
- **`words[i].length <= maxWidth`**

### ⚖️ Space Distribution
- Spaces are inserted **between words** to achieve the required line width
- These spaces should be distributed as evenly as possible
- If the spaces cannot be evenly divided:
    - The **leftmost gaps receive more spaces** than the right ones ⬅️

### 📌 Additional Notes
- A word is defined as a sequence of non-space characters 🔤
- Each word has a length between **`1`** and **`maxWidth`**
- The input array **`words`** contains at least one word

### 🎯 Output
Return a list of strings where:
- Each string represents a justified line 📄
- Each line has exactly **`maxWidth`** characters
- All formatting rules are strictly followed ✅
---