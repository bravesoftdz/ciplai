#ifndef PILA_H
#define PILA_H
struct nodopila
{
     int dato;
     int cuantos;
     nodopila *sig;
};
typedef nodopila *pnodopila;
class pila
{
     private:
     pnodopila pcima;
     public:
     pila();
     ~pila();
     bool estavacia();
     void apilar(int x, int y);
     void apilarmasuno(int x);
     int desapilar();

};
pila::pila()
{
     pcima = NULL;
}
pila::~pila()
{
     pnodopila p,q;
     if ( pcima != NULL )
     {
         p = pcima;
         while ( p != NULL )
         {
             q = (*p).sig;
             delete p;
             p = q;
         }
     }
}
bool pila::estavacia()
{
     if ( pcima == NULL )
          return true;
     else
          return false;
}
void pila::apilar( int x, int y )
{
     pnodopila p;
     p = new nodopila;
     (*p).dato = x;
     (*p).cuantos = y;
     (*p).sig = pcima;
     pcima = p;
}
void pila::apilarmasuno( int x )
{
     pnodopila p;
     p = new nodopila;
     (*p).dato = x;
     (*p).cuantos = (*p).cuantos + 1;
     (*p).sig = pcima;
     pcima = p;
}
int pila::desapilar()
{
     pnodopila p;
     int x;
     p = pcima;
     pcima = (*p).sig;
     x = (*p).dato;
     delete p;
     return x;
}
#endif

