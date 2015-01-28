#ifndef MON_MATH_H
#define MON_MATH_H


typedef struct MonMathHandle_t
    {
    /** reference to the flex lexer */
    void* scanner;
    long retval;
    }MonMathHandle,*MonMathHandlePtr;

#endif

