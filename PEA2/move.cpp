#include "move.h"

Move::Move()
{
   //ctor
}

Move::~Move()
{
   //dtor
}

bool Move::reduceFrequency()
{
   this->frequency--;
   if(this->frequency!= 0)
   {
      return false;  /* nie mozemy usunac z zakazanych */
   }
   return true;   /* mozna usunac z zakazanych */
}
