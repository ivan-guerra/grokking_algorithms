#pragma once

#include <utility>
#include <algorithm>
#include <forward_list>
#include <unordered_map>
#include <initializer_list>
#include <cstddef>

/*!
 * \class Graph
 * \brief The Graph class implements an unweighted, directed graph.
 */
template <typename T>
class Graph
{
public:
    using EdgeSet = std::pair<T, std::forward_list<T>>;

    /*!
     * \brief Construct the graph from a set of EdgeSet objects.
     */
    explicit Graph(const std::initializer_list<EdgeSet>& il={});

    ~Graph() = default;
    Graph(const Graph&) = default;
    Graph& operator=(const Graph&) = default;
    Graph(Graph&&) = default;
    Graph& operator=(Graph&&) = default;

    /*!
     * \brief Return the number of nodes in the Graph.
     */
    std::size_t
    Size() const { return size_; }

    /*!
     * \brief Return \c true if the Graph contains no nodes.
     */
    bool
    Empty() const { return (0 == size_); }

    /*!
     * \brief Insert a node.
     *
     * Duplicate nodes are not allowed.
     */
    bool
    InsertNode(const T& node);

    /*!
     * \brief Delete a node.
     *
     * EraseNode() does not delete the node's neighbors.
     *
     * \return \c true if the node exists and is deleted.
     */
    bool
    EraseNode(const T& node);

    /*!
     * \brief Return \c true if \a node exists in the graph.
     */
    bool
    HasNode(const T& node) const
        { return (adj_list_.find(node) != adj_list_.end()); }

    /*!
     * \brief Insert an edge from \a src to \dst.
     * \return \c true if the edge was inserted. \c false is returned
     *         if \a src or \a dst do not exist or the edge already
     *         exists.
     */
    bool
    InsertEdge(const T& src, const T& dst);

    /*!
     * \brief Return \c true if the edge \a src to \a dst is deleted.
     */
    bool
    EraseEdge(const T& src, const T& dst);

    /*!
     * \brief Return \c true if the edge \a src to \a dst exists.
     */
    bool
    HasEdge(const T& src, const T& dst) const;

    /*!
     * \brief Return \a node's list of neighbors.
     *
     * Calling GetNeighbors() on a nonexistent node triggers
     * undefined behavior.
     */
    const std::forward_list<T>&
    GetNeighbors(const T& node) const
        { return adj_list_.find(node)->second; }

    /*!
     * \brief Return \a node's list of neighbors.
     *
     * Calling GetNeighbors() on a nonexistent node triggers
     * undefined behavior.
     */
    std::forward_list<T>&
    GetNeighbors(const T& node)
        { return adj_list_.find(node)->second; }

private:
    using EdgeList = std::forward_list<T>;
    using AdjMatrix = std::unordered_map<T, EdgeList>;

    AdjMatrix   adj_list_; /*!< Adjacency list representation. */
    std::size_t size_;     /*!< Number of nodes in the graph. */
}; // end Graph

template <typename T>
Graph<T>::Graph(const std::initializer_list<EdgeSet>& il) :
    size_(0)
{
    for (const EdgeSet& es : il) {
        InsertNode(es.first);
        for (const T& neighbor : es.second) {
            InsertNode(neighbor);
            InsertEdge(es.first, neighbor);
        }
    }
}

template <typename T>
bool
Graph<T>::InsertNode(const T& node)
{
    /* Disallow the duplication of nodes. */
    if (HasNode(node))
        return false;

    /* Insert the a node with an empty edge list. */
    adj_list_[node] = {};
    size_++;

    return true;
}

template <typename T>
bool
Graph<T>::EraseNode(const T& node)
{
    /* Return false if the node to be erased does not exist. */
    if (!HasNode(node))
        return false;

    /* Erase the node. */
    adj_list_.erase(node);
    size_--;

    return true;
}

template <typename T>
bool
Graph<T>::InsertEdge(const T& src, const T& dst)
{
    /* Avoid duplication of edges. */
    if (HasEdge(src, dst))
        return false;

    adj_list_[src].push_front(dst);
    return true;
}

template <typename T>
bool
Graph<T>::EraseEdge(const T& src, const T& dst)
{
    /* Guard against deleting an edge that does not exist. */
    if (!HasEdge(src, dst))
        return false;

    /* Search the neighbors list for the target node. */
    EdgeList& edges = adj_list_[src];
    auto curr = edges.begin();
    auto prev = edges.before_begin();
    while (curr != edges.end()) {
        if (dst == *curr)
            break;

        prev = curr;
        curr++;
    }

    edges.erase_after(prev);

    return true;
}

template <typename T>
bool
Graph<T>::HasEdge(const T& src, const T& dst) const
{
    /* Cannot have an edge with nodes that do not already
       exist in the graph. */
    if (!HasNode(src) || !HasNode(dst))
        return false;

    const EdgeList& edges = adj_list_.find(src)->second;
    auto search_result =
        std::find(edges.cbegin(), edges.cend(), dst);

    return (search_result != edges.cend());
}
