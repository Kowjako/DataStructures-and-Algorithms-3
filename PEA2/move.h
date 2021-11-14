#ifndef MOVE_H
#define MOVE_H


class Move
{
   public:
      Move();
      virtual ~Move();
      int startNode;
      int finishNode;
      int frequency; /* czestotliwosc wystepowania wierzcholka w ruchach zakazanych */
      bool reduceFrequency(); /* sprawdzenie czy mozemy usunac wierzcholek z zakazanych */

   protected:

   private:
};

#endif // MOVE_H
