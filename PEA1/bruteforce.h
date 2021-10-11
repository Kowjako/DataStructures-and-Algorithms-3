#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H


class BruteForce
{
   public:
      BruteForce();
      virtual ~BruteForce();
      bool ReadFromFile(string filename);

   protected:

   private:
      int** macierz;  /* macierz sasiedztwa */
      void SetValueForMatrix(int i, int j, int value);
};

#endif // BRUTEFORCE_H
