#ifndef NODE_H
#define NODE_H


class Node
{
   public:
      Node();
      virtual ~Node();

      Node* next;
      int ograniczenie = 0;
      int value = 0;

   protected:

   private:
};

#endif // NODE_H
