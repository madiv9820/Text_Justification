from libcpp.vector cimport vector
from libcpp.string cimport string

# 🔗 Import C++ class and method from header file
cdef extern from 'solution.hpp':
    cdef cppclass Solution:
        Solution() except +                                  # Constructor (handles C++ exceptions)
        vector[string] fullJustify(
            vector[string]& words, 
            int maxWidth
        )

# 🧩 Cython wrapper class to interface Python ↔ C++
cdef class cppSolution:
    cdef Solution *ptr                                       # Pointer to C++ Solution object
    
    def __init__(self) -> None:
        # 🚀 Allocate C++ object
        self.ptr = new Solution()

    def __dealloc__(self) -> None:
        # 🧹 Free allocated C++ object to avoid memory leaks
        del self.ptr
    
    def cpp_fullJustify(self, words, maxWidth):
        """
        📌 Wrapper function for C++ fullJustify

        Parameters:
        - words (List[str]): Python list of words
        - maxWidth (int): Maximum width of each line

        Returns:
        - List[str]: Justified text returned from C++ implementation
        """

        cdef vector[string] cpp_words                        # 📦 C++ vector to store input words
        cdef int cpp_maxWidth = maxWidth                     # 🔢 Convert Python int → C++ int

        # 🔄 Convert Python list[str] → C++ vector<string>
        for i in range(len(words)):
            # ⚠️ Explicit encoding required (Python str → bytes → C++ string)
            cpp_words.push_back(words[i].encode('utf-8'))
        
        # ⚙️ Call C++ function
        cdef vector[string] cpp_result = \
            self.ptr.fullJustify(
                cpp_words, 
                cpp_maxWidth
            )
        
        cdef int cpp_resultSize = cpp_result.size()          # 📏 Size of result vector
        result = []                                          # 🐍 Python list for final output

        # 🔄 Convert C++ vector<string> → Python list[str]
        for i in range(cpp_resultSize):
            # ⚠️ Decode bytes → Python string
            result.append(cpp_result[i].decode('utf-8'))
        
        # ✅ Return final formatted result
        return result