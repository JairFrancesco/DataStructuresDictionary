#ifndef FHEAP_H
#define FHEAP_H
#include "NodoF.h"
#include <math.h>
#include <algorithm>
#include <vector>


template <class T>
void imprimir_vector(std::vector<NodoF<T>* > l)
{
    std::cout<<"{ ";
    for (typename std::vector<NodoF<T>* >::iterator it=l.begin();it!=l.end();it++)
    {
        if (*it)
            std::cout<<(*it)->valor<<" -> ";
        else
            std::cout<<"vacio"<<" -> ";
    }
    std::cout<<" }"<<std::endl;

}

template <class T>
void imprimir_lista(std::list<NodoF<T>* > l)
{
    std::cout<<"{ ";
    for (typename std::list<NodoF<T>* >::iterator it=l.begin();it!=l.end();it++)
        std::cout<< (*it)->valor<<","<<(*it)->get_grado()<<" -> ";
    std::cout<< "}"<<std::endl;
}

template <class T>
class Fheap
{
    typedef NodoF<T>* Fnodo;
    typedef std::list<Fnodo> Flista;
    typedef typename Flista::iterator Fiterator;

    public:
        Fheap()
        {

        }
        void insertar(T);
        void insertarpalabra(Palabra );
        void unir_raices(Fnodo&, Fnodo&);
        void actualizar_min();
        void borrar(NodoF<T>*&);
        void unir(Fheap<T>);
        Flista getRaices()
        {
            return this->raices;
        }
        void ver_raices()
        {
            std::cout<<"raices: ";
            imprimir_lista(this->raices);
        }
        T getmin()
        {
            return (*minimo)->valor;
        }
        void mostrar();
        void decrease_key(Fnodo&, T);
        void compactar();
        void split(Fiterator,int);
        void eliminar_min();
        virtual ~Fheap(){}
    protected:
    public:
        Flista raices;
        Fiterator minimo;

};

template<class T>
void Fheap<T>::insertarpalabra(Palabra pal)
{
    string a=pal.idioma1;
    int i,res;
    i=res=0;
    while (a[i]!='\0')
    {
        int c=a[i];
        res=res+c;
        i++;
    }
    int reso=res;
    insertar(reso);
    /*
    for (std::vector<string>::iterator it=pal.idioma2.begin();it!=pal.idioma2.end();it++)
    {

        while (a[i]!='\0')
        {
            int c=a[i];
            res=res+c;
            i++;
        }
        insertar(res);
        res=reso;
    }
    */
}

template <class T>
void Fheap<T>::split(Fiterator it, int n)
{
    if (!(*it) ) return;
    for (int i=0;i<n;i++)
        std::cout<<"  ";
    std::cout<<"la raiz es: "<<(*it)->valor<<std::endl;
    for (int i=0;i<n;i++)
        std::cout<<"  ";
    std::cout<<"los hijos de: "<<(*it)->valor<<" son :  ";
    imprimir_lista((*it)->hijos);
    Fiterator it2=(*it)->hijos.begin();
    split(it2,n+1);
    split(++it2,n+1);
}

template <class T>
void Fheap<T>::mostrar()
{
    Fiterator it=raices.begin();
    while (it!=raices.end())
    {
        split(it,0);
        it++;
        std::cout<<"--------------------------------"<<std::endl;
    }

}

template <class T>
void Fheap<T>::unir(Fheap<T> otro)
{
    if ((*otro.minimo)->valor < (*minimo)->valor)
    {
        this->minimo=otro.minimo;
    }
    this->raices.merge(otro.raices);
}

template <class T>
void Fheap<T>::borrar(NodoF<T>*& a)
{
    decrease_key(a,-12321);
    eliminar_min();

}


template <class T>
void Fheap<T>::actualizar_min()
{
    Fiterator vmini=raices.begin();
    for (Fiterator mini=raices.begin();mini!=raices.end();mini++)
    {
        if ((*vmini)->valor>(*mini)->valor)
            vmini=mini;
        (*mini)->marcado=false;
    }
    this->minimo=vmini;
}

template <class T>
void Fheap<T>::decrease_key(NodoF<T>*& a, T d)
{
    a->valor=d;

    if (a->valor<a->padre->valor)
    {
        if (!a->padre->marcado)
        {
            a->padre->marcado=true;
            a->padre=0;
            a->padre->hijos.remove(a);
            a->marcado=false;
            raices.push_front(a);
        }
        else
        {
            while (a->padre || a->padre->marcado)
            {
                a->marcado=false;
                a->padre=0;
                a->padre.hijos.remove(a);
                raices.push_front(a);
                a=a->padre;
            }
        }

    }
    actualizar_min();
}


template <class T>
void Fheap<T>::compactar()
{
    int a=raices.size();
    std::vector<NodoF<T>*> v;
    for (int i=0;i<10;i++)
    {
        v.push_back(0);
    }
    Fiterator it=raices.begin();
    NodoF<T>* aux=*it;
    while (it!=raices.end())
    {
        //std::cout<<"el nodo entrante es: "<<(*it)->valor<<" *  ";
        int grado=(*it)->get_grado();
        if (!v.at(grado))
        {
          //  std::cout<<"En este grado puede llenarse: "<<(*it)->valor<<std::endl;
            v.at(grado)=*it;
            it++;
        }
        else
        {
            //std::cout<<"En este grado no puede llenarse: "<<(*it)->valor<<std::endl;
            Fiterator itaux=it;
            if ((v.at(grado))->valor<(*it)->valor)
            {
              //  std::cout<<"el del vector padre (vector) "<<(v.at(grado))->valor<<"       ";
                Fiterator itaux=find(raices.begin(),raices.end(),v.at(grado));
                unir_raices(v.at(grado),*it);
                it=itaux;
                int ngrado= (*it)->get_grado();
                if (!v.at(ngrado))
                {
                    v.at(grado)=0;
                    v.at(ngrado)=(*it);
                    it++;
                }
                else
                {
                    v.at(grado)=0;
                }


            }
            else
            {

                //std::cout<<"el del vector padre (iterador) "<<(*it)->valor<<"       ";
//                int agrado=(*it)->
                unir_raices(*it,v.at(grado));

                int ngrado=(*it)->get_grado();
                if (!v.at(ngrado))
                {
                    v.at(grado)=0;
                    v.at(ngrado)=(*it);
                    it++;
                }



            }
            //unir_raices(v.at(grado),*it);


        }
        /*std::cout<<"raices: ";
        imprimir_lista(raices);
        std::cout<<"vec: ";
        imprimir_vector(v);
        std::cout<<"------------------------------"<<std::endl;*/
//        it++;

    }
    //std::cout<<"vec: ";
    //imprimir_vector(v);


}


template <class T>
void Fheap<T>::eliminar_min()
{
    Fnodo aux=*minimo;
    raices.remove(aux);
    if (!aux->hijos.empty())
    {
        for (auto i: aux->hijos)
        {
            raices.push_back(i);
            aux->hijos.remove(i);
            i->padre=0;
        }
    }
    actualizar_min();
    compactar();
}



template <class T>
void Fheap<T>::unir_raices(NodoF<T>*& a, NodoF<T>*& b)
{
    if ((a->valor)<(b->valor))
    {
        raices.remove(b);
        a->hijos.push_front(b);
        //std::cout<<"va: "<<b->valor<<std::endl;
        b->padre=a;
        //std::cout<<"prueba: ";
        //imprimir_lista(a->hijos);

    }


}

template <class T>
void Fheap<T>::insertar(T d)
{
    Fnodo nuevo=new NodoF<T>(d);
    if (raices.empty())
    {
        raices.push_back(nuevo);
        minimo=raices.begin();
    }
    else
    {
        raices.insert(minimo,nuevo);
        if ((*minimo)->valor>=d) minimo--;
    }
    compactar();
    //ver_raices();
    //std::cout<<"Por ahora el minimo es: "<<(*minimo)->valor<<std::endl;
}




#endif // FHEAP_H
