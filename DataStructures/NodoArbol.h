#ifndef NODOARBOL_H
#define NODOARBOL_H

template <class T>
class NodoA
{
    public:
        NodoA(T d)
        {
            this->valor=d;
            this->altura=0;
            mpson[0]=mpson[1]=0;
        }
        virtual ~NodoA(){}
    protected:
    public:
        T valor;
        int altura;
        NodoA<T>* mpson[2];

};

#endif // NODOARBOL_H
