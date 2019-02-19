#include "../Headers/AStar.hpp"
#include <algorithm>

using namespace std::placeholders;

bool AStar::Vec2i::operator==(const Vec2i &coordinates_)
{
    return (x == coordinates_.x && y == coordinates_.y);
}

AStar::Vec2i operator+(const AStar::Vec2i &left_, const AStar::Vec2i &right_)
{
    return {left_.x + right_.x, left_.y + right_.y};
}

AStar::Node::Node(const Vec2i& coordinates_, Node *parent_)
{
    parent = parent_;
    coordinates = coordinates_;
    G = H = 0;
}

unsigned AStar::Node::getScore()
{
    return G + H;
}

AStar::Generator::Generator()
{
    setDiagonalMovement(false);
    setHeuristic(&Heuristic::manhattan);
    direction = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
}

void AStar::Generator::setWorldSize(const Vec2i& worldSize_)
{
    worldSize = worldSize_;
}

void AStar::Generator::setDiagonalMovement(const bool& enable_)
{
    directions = (enable_ ? 8 : 4);
}

void AStar::Generator::setHeuristic(HeuristicFunction heuristic_)
{
    heuristic = std::bind(heuristic_, _1, _2);
}

void AStar::Generator::addCollision(const Vec2i& coordinates_)
{
    walls.push_back(coordinates_);
}

void AStar::Generator::removeCollision(const Vec2i& coordinates_)
{
    auto it = std::find(walls.begin(), walls.end(), coordinates_);
    if (it != walls.end())
    {
        walls.erase(it);
    }
}

void AStar::Generator::clearCollisions()
{
    walls.clear();
}

AStar::CoordinateList AStar::Generator::findPath(const Vec2i& source_, const Vec2i& target_)
{
    //il nodo corrente
    Node *current = nullptr;
    //nodi da visitare e già visitati
    NodeSet openSet, closedSet;
    openSet.reserve(100);
    closedSet.reserve(100);
    //Il primo nodo entra in lista
    openSet.push_back(new Node(source_));

    while (!openSet.empty()) // se la lista è vuota non esiste nessun percorso
    {
        auto current_it = openSet.begin();
        current = *current_it;

        for (auto it = openSet.begin(); it != openSet.end(); it++)
        {
            auto node = *it;
            if (node->getScore() <= current->getScore()) //se un nodo nella lista ha punteggio migliore del precedente, questo nodo diventa il corrente
            {
                current = node;
                current_it = it;
            }
        }

        if (current->coordinates == target_) // se il nodo corrente è il nodo d'arrivo, l'algoritmo termina
        {
            break;
        }

        closedSet.push_back(current); // metto il corrente nei nodi già visitati
        openSet.erase(current_it);    // lo elimino da quelli da visitare

        for (unsigned i = 0; i < directions; ++i) //trovo i prossmi nodi da mettere in lista
        {
            Vec2i newCoordinates(current->coordinates + direction[i]);
            if (!detectCollision(newCoordinates) && !findNodeOnList(closedSet, newCoordinates)) //se il nuovo nodo è nei nodi da visitare e non è un muro
            {
                unsigned totalCost = current->G + ((i < 4) ? 10 : 14);     // calcolo il nuovo costo totale per quel arco
                Node *successor = findNodeOnList(openSet, newCoordinates); // ne prendo il riferimento dai nodi da visitare
                if (successor == nullptr)                                  //se non esiste lo creo
                {
                    successor = new Node(newCoordinates, current);
                    successor->G = totalCost;
                    successor->H = heuristic(successor->coordinates, target_);
                    openSet.push_back(successor);
                }
                else if (totalCost < successor->G) //altrimenti lo aggiorno se necessario
                {
                    successor->parent = current;
                    successor->G = totalCost;
                }
            }
        }
    }

    CoordinateList path;
    while (current != nullptr) //genero il path
    {
        path.push_back(current->coordinates);
        current = current->parent;
    }

    releaseNodes(openSet);
    releaseNodes(closedSet);

    return path;
}

AStar::Node *AStar::Generator::findNodeOnList(const NodeSet &nodes_, const Vec2i& coordinates_)
{
    for (auto node : nodes_)
    {
        if (node->coordinates == coordinates_)
        {
            return node;
        }
    }
    return nullptr;
}

void AStar::Generator::releaseNodes(NodeSet &nodes_)
{
    for (auto it = nodes_.begin(); it != nodes_.end();)
    {
        delete *it;
        it = nodes_.erase(it);
    }
}

bool AStar::Generator::detectCollision(const Vec2i& coordinates_)
{
    if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
        coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
        std::find(walls.begin(), walls.end(), coordinates_) != walls.end())
    {
        return true;
    }
    return false;
}

AStar::Vec2i AStar::Heuristic::getDelta(const Vec2i& source_, const Vec2i& target_)
{
    return {abs(source_.x - target_.x), abs(source_.y - target_.y)};
}

unsigned AStar::Heuristic::manhattan(const Vec2i& source_, const Vec2i& target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<unsigned>(10 * (delta.x + delta.y));
}

unsigned AStar::Heuristic::euclidean(const Vec2i& source_, const Vec2i& target_)
{
    auto delta = std::move(getDelta(source_, target_));
    return static_cast<unsigned>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}
