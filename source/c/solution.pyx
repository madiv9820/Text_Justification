from libc.stdlib cimport malloc, free
from libc.string cimport strcpy

# 🔗 Import C function from header file
cdef extern from 'solution.h':
    char** fullJustify(
        char** words, 
        int wordSize, 
        int maxWidth, 
        int* returnSize
    )

# 🧩 Cython wrapper class to interface Python ↔ C
cdef class cSolution:
    def c_fullJustify(self, words, maxWidth):
        """
        📌 Wrapper for C implementation of fullJustify

        Parameters:
        - words (List[str]): Input words from Python
        - maxWidth (int): Maximum width of each line

        Returns:
        - List[str]: Justified text returned from C implementation
        """

        cdef int cpp_wordSize = len(words)                  # 🔢 Number of words
        cdef int cpp_maxWidth = maxWidth                    # 🔢 Line width

        # 📦 Allocate memory for return size (C will write number of lines here)
        cdef int* cpp_returnSize = <int*> malloc(sizeof(int))

        # 📦 Allocate array of C string pointers (char**)
        cdef char** cpp_words = <char**> malloc(cpp_wordSize * sizeof(char*))
        
        # 🔄 Convert Python list[str] → C char** (array of C-style strings)
        for i in range(cpp_wordSize):
            temp = words[i].encode("utf-8")                 # 🐍 Python str → bytes
            cpp_words[i] = <char*> malloc((len(temp) + 1) * sizeof(char))  # 📦 allocate C string (+1 for '\0')
            strcpy(cpp_words[i], temp)                      # 📋 copy content into C memory

        # ⚙️ Call C function
        cdef char** cpp_result = fullJustify(
            cpp_words, 
            cpp_wordSize, 
            cpp_maxWidth, 
            cpp_returnSize                                 # 📏 Output parameter (number of lines)
        )

        result = []                                         # 🐍 Python list for final output

        # 🔄 Convert C result → Python list[str]
        if cpp_result is not NULL:
            for i in range(cpp_returnSize[0]):              # 📏 iterate over returned lines
                result.append(cpp_result[i].decode("utf-8"))  # 🐍 bytes → Python str

            # 🧹 Free memory allocated by C for result strings
            # ⚠️ Assumes C used malloc for each string
            for i in range(cpp_returnSize[0]):
                free(cpp_result[i])
            
            free(cpp_result)                               # 🧹 Free outer array (char**)

        # 🧹 Free input memory (words passed to C)
        for i in range(cpp_wordSize):
            free(cpp_words[i])
        
        free(cpp_words)

        # 🧹 Free return size pointer
        free(cpp_returnSize)
        
        return result