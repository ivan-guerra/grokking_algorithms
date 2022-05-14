#pragma once

#include <vector>
#include <forward_list>
#include <functional>
#include <cstddef>

/*!
 * \class Map
 * \brief The Map class implements an associative array with load balancing.
 */
template <typename Key, typename Value>
class Map
{
public:
    /*!
     * \brief Construct a Map with the parameter bucket count.
     *
     * \param table_size Number of buckets the Map will first allocate.
     */
    explicit Map(std::size_t table_size=kDefaultBucketCount);

    ~Map() = default;
    Map(const Map&) = default;
    Map& operator=(const Map&) = default;
    Map(Map&&) = default;
    Map& operator=(Map&&) = default;

    /*!
     * \brief Return the number of elements in the map.
     */
    std::size_t
    Size() const { return size_; }

    /*!
     * \brief Return \c true if the map contains no elements.
     */
    bool
    Empty() const { return (0 == size_); }

    /*!
     * \brief Return the number of buckets (slots).
     */
    std::size_t
    BucketCount() const { return buckets_.size(); }

    /*!
     * \brief Return the load factor.
     */
    float
    LoadFactor() const;

    /*!
     * \brief Insert a key/value pair.
     *
     * Map does not support duplicate keys therefore Insert() can be called
     * to overwrite a previous entry that used the same \a key.
     */
    void
    Insert(const Key& key, const Value& value);

    /*!
     * \brief Return \c true if \a key exists and its entry has been deleted.
     */
    bool
    Erase(const Key& key);

    /*!
     * \brief Return a pointer to the value associated with \a key.
     * \return A pointer to the value associated with \a key. If \a key does
     *         not reference any value in the Map, nullptr is returned.
     */
    const Value*
    Get(const Key& key) const;

    /*!
     * \brief Return a pointer to the value associated with \a key.
     * \return A pointer to the value associated with \a key. If \a key does
     *         not reference any value in the Map, nullptr is returned.
     */
    Value*
    Get(const Key& key);

private:
    using Chain   = std::forward_list<std::pair<Key, Value>>;
    using Buckets = std::vector<Chain>;

    static constexpr float
    kLoadFactorThreshold = 0.7f; /*!< Load factor threshold value. */
    static const std::size_t
    kDefaultBucketCount = 256; /*!< Default bucket count. */

    /*!
     * \brief Return the hash of \a key.
     */
    std::size_t
    Hash(const Key& key) const { return (hasher_(key) % buckets_.size()); }

    /*!
     * \brief Trigger a rehashing of the entire table.
     *
     * A Rehash() implies doubling the number of buckets and then re-inserting
     * all key/value pairs that were present prior to the rehash event.
     */
    void Rehash();

    Buckets        buckets_; /*!< Hash table buckets. */
    std::size_t    size_;    /*!< Number of elements stored in the table. */
    std::hash<Key> hasher_;  /*!< Hash function. */
}; // end Map

template <typename Key, typename Value>
void Map<Key, Value>::Rehash()
{
    /* Temporary copy of the entire map. */
    Buckets tmp = buckets_;

    /* Double the number of buckets. */
    buckets_ = std::vector<Chain>(buckets_.capacity() * 2);
    size_    = 0;

    /* Re-insert all key/value pairs. */
    for (const Chain& chain : tmp) {
        for (const auto& kv : chain)
            Insert(kv.first, kv.second);
    }
}

template <typename Key, typename Value>
Map<Key, Value>::Map(std::size_t table_size) :
    buckets_((table_size > 0) ? table_size : kDefaultBucketCount),
    size_(0)
{

}

template <typename Key, typename Value>
float
Map<Key, Value>::LoadFactor() const
{
    float size        = static_cast<float>(size_);
    float num_buckets = static_cast<float>(buckets_.size());
    return (size / num_buckets);
}

template <typename Key, typename Value>
void
Map<Key, Value>::Insert(const Key& key, const Value& value)
{
    Chain& chain = buckets_[Hash(key)];
    auto curr = chain.begin();
    while (curr != chain.end()) {
        /* The key already exists, overwrite the current value with the
           parameter value. */
        if (curr->first == key) {
            curr->second = value;
            return;
        }
        curr++;
    }

    /* Insert a new key/value pair. */
    buckets_[Hash(key)].push_front({key, value});
    size_++;

    /* Trigger a rehash if the insertion has pushed us over the load factor
       threshold. */
    if (LoadFactor() >= kLoadFactorThreshold)
        Rehash();
}

template <typename Key, typename Value>
bool
Map<Key, Value>::Erase(const Key& key)
{
    Chain& chain = buckets_[Hash(key)];

    auto curr = chain.begin();
    auto prev = chain.before_begin();
    while (curr != chain.end()) {
        if (curr->first == key) {
            chain.erase_after(prev);
            size_--;
            return true;
        }
        prev = curr;
        curr++;
    }
    return false;
}

template <typename Key, typename Value>
const
Value* Map<Key, Value>::Get(const Key& key) const
{
    const Chain& chain = buckets_[Hash(key)];
    auto curr = chain.cbegin();
    while (curr != chain.cend()) {
        if (curr->first == key)
            return &curr->second;
        curr++;
    }
    return nullptr;
}

template <typename Key, typename Value>
Value*
Map<Key, Value>::Get(const Key& key)
{
    Chain& chain = buckets_[Hash(key)];
    auto curr = chain.begin();
    while (curr != chain.end()) {
        if (curr->first == key)
            return &curr->second;
        curr++;
    }
    return nullptr;
}
