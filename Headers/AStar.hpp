#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <functional>
#include <set>
#include <math.h>
namespace AStar
{
    //Struttura che contiene le coordinate
    struct Vec2i
    {
        int x, y;

        bool operator == (const Vec2i& coordinates_);
    };

    //Typedef (buonanima) per rendere più snelle le firme dei metodi 
    using HeuristicFunction = std::function<unsigned(Vec2i, Vec2i)>;
    using CoordinateList = std::vector<Vec2i>;
    //struttura che rappresenta un nodo del grafo
    struct Node
    {
        //i due punteggi che fanno da valutatori per il nodo all'interno dell'algoritmo A*
        unsigned G, H;
        Vec2i coordinates;
        //Nodo del quale è figlio, nullptr per il root
        Node *parent;

        Node(const Vec2i& coord_, Node *parent_ = nullptr);
        unsigned getScore();
    };
    //Facendo alcuni test si è riscontrato che con vector l'algoritmo è più efficiente che con list
    using NodeSet = std::vector<Node *>;

    //Generatore di percorsi
    class Generator
    {
        //Controlla se il prossimo nodo è una collisione
        bool detectCollision(const Vec2i& coordinates_);
        //Trova un nodo nella lista
        Node* findNodeOnList(const NodeSet& nodes_, const Vec2i& coordinates_);
        //Concella dei nodi dalla lista
        void releaseNodes(NodeSet& nodes_);

    public:
        Generator();
        //set delle dimensioni del mondo
        void setWorldSize(const Vec2i& worldSize_);
        //accetta anche movimenti diagonali
        void setDiagonalMovement(const bool& enable_);
        //set della funzione euristica con il quale valutare il parametro H di un nodo
        void setHeuristic(HeuristicFunction heuristic_);
        //metodo che genera il percorso
        CoordinateList findPath(const Vec2i& source_, const Vec2i& target_);
        void addCollision(const Vec2i& coordinates_);
        void removeCollision(const Vec2i& coordinates_);
        void clearCollisions();

    private:
        //funzione euristica
        HeuristicFunction heuristic;
        //le direzioni in cui si può andare e le collisioni
        CoordinateList direction, walls;
        Vec2i worldSize;
        unsigned directions;
    };

    class Heuristic
    {
        //restituisce il vettore con componenti le rispettive differenze tra le componenti dei nodi source e target
        static Vec2i getDelta(const Vec2i& source_, const Vec2i& target_);

    public:
        //Distanza di manhattan o geometria del taxi, |x1-x2|+|y1+y2|
        static unsigned manhattan(const Vec2i& source_, const Vec2i& target_);
        //Distanza euclidea o metrica pitagorica, sqrt(pow(x1-x2,2)+pow(y1-y2,2))
        static unsigned euclidean(const Vec2i& source_, const Vec2i& target_);
    };
}

#endif
