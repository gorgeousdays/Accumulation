#pragma once
#ifndef _MYEXCEPT_H_
#define _MYEXCEPT_H_
class MyExcept {
    public:
        virtual const char* getWhat() = 0;
};
class MyFormatError :public MyExcept {
   public:
       const char* getWhat() {
           return "Format Error.";
       }
};
class MyIllegal :public MyExcept {
    public:
       const  char* getWhat() {
            return "Illegal.";
        }
};
#endif