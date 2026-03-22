#!/bin/bash

# ============================================================
# 🚀 Independent Test Runner (Python & C++)
# ============================================================

C_STATUS=0
CPP_STATUS=0
PYTHON_STATUS=0

# ------------------- Python Setup --------------------------
echo "🐍 Setting up Python virtual environment..."
python3 -m venv venv > /dev/null 2>&1
source ./venv/bin/activate
pip install -r requirements.txt > /dev/null 2>&1

# ------------------- C Build -----------------------------
echo "⚙️  Building C extension..."
cd ./source/c
if python setup.py build_ext --inplace > /dev/null 2>&1; then
    C_STATUS=0
else
    C_STATUS=1
fi
cd ../..

# ------------------- C Tests -----------------------------
echo "🧪 Running C tests..."
if python -m test.c_test -v; then
    C_STATUS=$C_STATUS
else
    C_STATUS=1
fi

# ------------------- C++ Build -----------------------------
echo "⚙️  Building C++ extension..."
cd ./source/cpp
if python setup.py build_ext --inplace > /dev/null 2>&1; then
    CPP_STATUS=0
else
    CPP_STATUS=1
fi
cd ../..

# ------------------- C++ Tests -----------------------------
echo "🧪 Running C++ tests..."
if python -m test.cpp_test -v; then
    CPP_STATUS=$CPP_STATUS
else
    CPP_STATUS=1
fi

# ------------------- Python Tests --------------------------
echo "🧪 Running Python tests..."
if python -m test.py_test -v; then
    PYTHON_STATUS=0
else
    PYTHON_STATUS=1
fi

# ------------------- Cleanup -------------------------------
deactivate > /dev/null 2>&1

# ------------------- Summary -------------------------------
echo ""
echo "================ 🧾 TEST SUMMARY 🧾 ================"
echo "🐍 Python Tests : $([ $PYTHON_STATUS -eq 0 ] && echo "✅ PASSED" || echo "❌ FAILED")"
echo "⚙️  C++ Tests    : $([ $CPP_STATUS -eq 0 ] && echo "✅ PASSED" || echo "❌ FAILED")"
echo "⚙️  C Tests      : $([ $C_STATUS -eq 0 ] && echo "✅ PASSED" || echo "❌ FAILED")"
echo "==================================================="

# ------------------- Exit Code ----------------------------
if [ $PYTHON_STATUS -ne 0 ] || [ $CPP_STATUS -ne 0 ] || [ $C_STATUS -ne 0 ]; then
    exit 1
else
    exit 0
fi