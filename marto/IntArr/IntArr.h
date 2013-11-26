#ifndef IntArr_H
#define IntArr_H

class IntArr
{
      public:
          IntArr(int);
          IntArr(const IntArr&);
          ~IntArr();
          void operator=(IntArr);
          int& operator[](int);
          bool operator==(IntArr);
          int Size();
          void Print();
          
          static int HowMany();
      private:
          int* arr;
          int size;
          static int counter;
          void Error(int);
};

#endif
