#ifndef LISTAS_H
#define LISTAS_H
struct nodo
{
 	int dato;
        int cuantos;
	nodo *sig;
};
typedef nodo *pnodo;
class lista
{
     	private:
     	pnodo pL;
     	public:
     	lista();
     	~lista();
     	void insertar_comienzo(int x, int y);
     	void insertar_final(int x, int y);
        void eliminar(int x);
     	pnodo buscar(int x);
     	pnodo buscar_anterior(int x);

};
lista::lista()
{
	 pL = NULL;
}
lista::~lista()
{
     	pnodo p,q;
     	if ( pL != NULL )
     	{
         		p = pL;
         		while ( p != NULL )
         		{
             		q = (*p).sig;
             		delete p;
             		p = q;
         		}
     	}
}
void lista::insertar_comienzo(int x,int y)
{
	 pnodo p;
	 p = new nodo;
	 (*p).dato = x;
         (*p).cuantos = y;
	 (*p).sig = pL;
	 pL = p;
}
void lista::insertar_final(int x,int y)
{
	 pnodo p,q;
	 p = new nodo;
	 (*p).dato = x;
         (*p).cuantos = y;
         (*p).sig = NULL;
	 if ( pL == NULL )
		pL = p;
	 else
	 {
		 q = pL;
		 while ( (*q).sig != NULL )
			 q = (*q).sig;
		 (*q).sig = p;
	 }
}
pnodo lista::buscar(int x)
{
	 pnodo p;
	 if ( pL == NULL )
		 return NULL;
	 else
	 {
		 p = pL;
		 while ( p != NULL && (*p).dato != x )
			 p = (*p).sig;
		 return p;
	 }
}
pnodo lista::buscar_anterior(int x)
{
	 pnodo a,p;
	 a = NULL;
	 p = pL;
	 while ( (*p).dato != x )
	 {
		 a = p;
		 p = (*p).sig;
	 }
	 return a;
}
void lista::eliminar( int x )
{
	 pnodo a,p;
	 p = buscar( x );
	 if ( p == NULL )
                  int noesta;
		 //cout<<"El elemento no esta en la lista"<<endl;
	 else
	 {
		 a = buscar_anterior(x);
		 if ( a == NULL )
			 pL = (*p).sig;
		 else
			 (*a).sig = (*p).sig;
		 delete p;
	 }
}
#endif

