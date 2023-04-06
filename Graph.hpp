#pragma once

#include "Matrix.hpp"
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>

using namespace matrix;
using std::string, std::vector, std::list, std::pair, std::map, std::set;

template <typename TNode>
class Node
{
private:
    TNode nodeData;

public:
    Node() = default;

    Node(const TNode &data)
    {
        nodeData = data;
    }

    ~Node() = default;

    TNode GetData() const
    {
        return nodeData;
    }

    void SetData(const TNode &data)
    {
        nodeData = data;
    }
};

template <typename TNode>
struct NodeCompare
{
    bool operator()(const Node<TNode> &lhs, const Node<TNode> &rhs) const
    {
        return lhs.GetData() < rhs.GetData();
    }
};

template <typename TNode, typename TWeight>
class Graph
{
private:
    map<Node<TNode>, size_t, NodeCompare<TNode>> graphNodes;
    Matrix<TWeight> adjacencyMatrix;

public:
    size_t size() const
    {
        return graphNodes.size();
    }

    size_t Edges() const
    {
        size_t count = 0;
        for (auto i : adjacencyMatrix)
        {
            if (i > 0)
            {
                count++;
            }
        }
        return count;
    }

    set<Node<TNode>, NodeCompare<TNode>> Nodes()
    {
        set<Node<TNode>, NodeCompare<TNode>> s;
        for (auto i : graphNodes)
        {
            s.insert(i.first);
        }
        return s;
    }

    Matrix<TWeight> AdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

    // 3. Основной интрефейс -- начало
    bool empty() const
    {
        return graphNodes.empty();
    }

    void clear()
    {
        graphNodes.clear();
        adjacencyMatrix.Clear();
    }

    void swap(Graph &other)
    {
        Graph tmp = *this;
        *this = other;
        other = tmp;
    }
    // 3. Основной интрефейс -- конец

    // 2. Конструкторы и операторы присваивания класса Graph -- начало
    // Default Constructor
    Graph() = default;

    // Constructor from vector
    Graph(const vector<Node<TNode>> &nodes, const Matrix<TWeight> &matrix)
    {
        if (!matrix.square())
        {
            throw std::invalid_argument("Adjacency matrix has to have equal number of rows and columns.");
        }
        if (nodes.size() != matrix.Rows())
        {
            throw std::invalid_argument(
                "Dimensions of the adjacency matrix should be equal to the number of vertices.");
        }
        size_t index = 0;
        for (auto i : nodes)
        {
            graphNodes[i] = index;
            ++index;
        }
        adjacencyMatrix = matrix;
    }

    // Constructor from list
    Graph(const list<Node<TNode>> &nodes, const Matrix<TWeight> &matrix)
    {
        if (!matrix.square())
        {
            throw std::invalid_argument("Adjacency matrix has to have equal number of rows and columns.");
        }
        if (nodes.size() != matrix.Rows())
        {
            throw std::invalid_argument(
                "Dimensions of the adjacency matrix should be equal to the number of vertices.");
        }
        size_t index = 0;
        for (auto i : nodes)
        {
            graphNodes[i] = index;
            ++index;
        }
        adjacencyMatrix = matrix;
    }

    // Constructor from set
    Graph(const set<Node<TNode>, NodeCompare<TNode>> &nodes, const Matrix<TWeight> &matrix)
    {
        if (!matrix.square())
        {
            throw std::invalid_argument("Adjacency matrix has to have equal number of rows and columns.");
        }
        if (nodes.size() != matrix.Rows())
        {
            throw std::invalid_argument(
                "Dimensions of the adjacency matrix should be equal to the number of vertices.");
        }
        size_t index = 0;
        for (auto i : nodes)
        {
            graphNodes[i] = index;
            ++index;
        }
        adjacencyMatrix = matrix;
    }

    // Destructor
    ~Graph() = default;

    // Copy Constructor
    Graph(Graph<TNode, TWeight> &other)
    {
        if (this != &other)
        {
            graphNodes = other.graphNodes;
            adjacencyMatrix = other.adjacencyMatrix;
        }
    }

    // Move Constructor
    Graph(Graph &&other) noexcept
    {
        if (this != other)
        {
            graphNodes = other.graphNodes;
            adjacencyMatrix = other.adjacencyMatrix;
            other.clear();
        }
    }

    // Copy Assignment Operator
    Graph &operator=(const Graph &other)
    {
        if (this != &other)
        {
            graphNodes = other.graphNodes;
            adjacencyMatrix = other.adjacencyMatrix;
        }
        return *this;
    }

    // Move Assignment Operator
    Graph &operator=(Graph &&other) noexcept
    {
        if (this != &other)
        {
            graphNodes = other.graphNodes;
            adjacencyMatrix = other.adjacencyMatrix;
            other.clear();
        }
        return *this;
    }
    // 2. Конструкторы и операторы присваивания класса Graph -- конец

    // 4. Итерирование по графу -- начало
    auto begin()
    {
        return graphNodes.begin();
    }

    auto end()
    {
        return graphNodes.end();
    }

    auto cbegin() const
    {
        return graphNodes.cbegin();
    }

    auto cend() const
    {
        return graphNodes.cend();
    }
    // 4. Итерирование по графу -- конец

    // 5. Работа с графом через ключ -- начало
    size_t degree_in(const Node<TNode> &node)
    {
        size_t count = 0;
        for (int i = 0; i < size(); ++i)
        {
            if (adjacencyMatrix(graphNodes[node], i) > 0)
            {
                count++;
            }
        }
        return count;
    }

    size_t degree_out(const Node<TNode> &node)
    {
        size_t count = 0;
        for (int i = 0; i < size(); ++i)
        {
            if (adjacencyMatrix(i, graphNodes[node]) > 0)
            {
                count++;
            }
        }
        return count;
    }

    bool loop(const Node<TNode> &node)
    {
        return adjacencyMatrix(graphNodes[node], graphNodes[node]) > 0;
    }
    // 5. Работа с графом через ключ -- конец

    // 6. Вставка узлов и рёбер в граф -- начало
    auto insert_node(const Node<TNode> &node)
    {
        //        if (&node == nullptr) {
        //            throw std::invalid_argument("Node does not exist.");
        //        }
        if (graphNodes.find(node) != graphNodes.end())
        {
            return std::make_pair(graphNodes.end(), false);
        }
        Matrix<TWeight> matrix(size() + 1, size() + 1, 0);
        for (size_t i = 0; i < size(); ++i)
        {
            for (size_t j = 0; j < size(); ++j)
            {
                matrix(i, j) = adjacencyMatrix(i, j);
            }
        }
        graphNodes[node] = size();
        adjacencyMatrix = matrix;
        return std::make_pair(graphNodes.find(node), true);
    }

    auto insert_or_assign_node(const Node<TNode> &node)
    {
        if (&node == nullptr)
        {
            throw std::invalid_argument("Node does not exist.");
        }
        auto it = graphNodes.find(node);
        if (it != graphNodes.end())
        {
            return std::make_pair(it, true);
        }
        Matrix<TWeight> matrix(size() + 1, size() + 1, 0);
        for (size_t i = 0; i < size(); ++i)
        {
            for (size_t j = 0; j < size(); ++j)
            {
                matrix(i, j) = adjacencyMatrix(i, j);
            }
        }
        graphNodes[node] = size();
        adjacencyMatrix = matrix;
        return std::make_pair(graphNodes.find(node), true);
    }

    auto insert_edge(const pair<const Node<TNode> &, const Node<TNode> &> &nodes, const TWeight &weight)
    {
        auto fromNode = nodes.first;
        auto toNode = nodes.second;
        if (graphNodes.find(fromNode) == graphNodes.end() || graphNodes.find(toNode) == graphNodes.end())
        {
            throw std::invalid_argument("Node does not exist within the graph.");
        }
        if (adjacencyMatrix(graphNodes[toNode], graphNodes[fromNode]) > 0)
        {
            return std::make_pair(graphNodes.end(), false);
        }
        adjacencyMatrix(graphNodes[toNode], graphNodes[fromNode]) = weight;
        return std::make_pair(graphNodes.find(fromNode), true);
    }

    auto insert_or_assign_edge(const pair<const Node<TNode> &, const Node<TNode> &> &nodes, const TWeight &weight)
    {
        auto fromNode = nodes.first;
        auto toNode = nodes.second;
        if (graphNodes.find(fromNode) == graphNodes.end() || graphNodes.find(toNode) == graphNodes.end())
        {
            throw std::invalid_argument("Node does not exist within the graph.");
        }
        adjacencyMatrix(graphNodes[toNode], graphNodes[fromNode]) = weight;
        return std::make_pair(graphNodes.find(fromNode), true);
    }
    // 6. Вставка узлов и рёбер в граф -- конец

    // 7. Удаление узлов и рёбер из Graph -- начало
    void clear_edges()
    {
        adjacencyMatrix = Matrix<TWeight>(size(), size(), 0);
    }

    bool erase_edges_go_from(const Node<TNode> &node)
    {
        if (graphNodes.find(node) == graphNodes.end())
        {
            return false;
        }
        for (int i = 0; i < size(); ++i)
        {
            adjacencyMatrix(i, graphNodes[node]) = 0;
        }
        return true;
    }

    bool erase_edges_go_to(const Node<TNode> &node)
    {
        if (graphNodes.find(node) == graphNodes.end())
        {
            return false;
        }
        for (int i = 0; i < size(); ++i)
        {
            adjacencyMatrix(graphNodes[node], i) = 0;
        }
        return true;
    }

    bool erase_node(const Node<TNode> &node)
    {
        if (graphNodes.find(node) == graphNodes.end())
        {
            return false;
        }
        adjacencyMatrix = adjacencyMatrix.Minor(graphNodes[node], graphNodes[node]);
        for (auto it = graphNodes.find(node); it != graphNodes.end(); it++)
        {
            it->second = it->second - 1;
        }
        graphNodes.erase(node);
        return true;
    }
    // 7. Удаление узлов и рёбер из Graph -- конец

    // 8. Считывание и запись в файл -- начало
    bool load_from_file(const string &path)
    {
        std::ifstream ifstream;
        ifstream.open(path);

        if (!ifstream)
        {
            return false;
        }

        size_t n;
        ifstream >> n;
        for (size_t i = 0; i < n; ++i)
        {
            TNode tmp;
            ifstream >> tmp;
            insert_node(tmp);
        }
        ifstream >> adjacencyMatrix;
        ifstream.close();
        return true;
    }

    bool save_to_file(const string &path)
    {
        std::ofstream ofstream;
        ofstream.open(path);

        if (!ofstream)
        {
            return false;
        }

        ofstream << "Nodes contents:\n";
        for (auto i : graphNodes)
        {
            ofstream << i.first.GetData() << "\n";
        }
        ofstream << "\nAdjacency matrix:\n";
        ofstream << adjacencyMatrix;
        ofstream.close();
        return true;
    }
    // 8. Считывание и запись в файл -- конец
};

template <typename TNode, typename TWeight>
void swap(Graph<TNode, TWeight> &graph1, Graph<TNode, TWeight> &graph2)
{
    Graph<TNode, TWeight> tmp = graph1;
    graph1 = graph2;
    graph2 = tmp;
}
