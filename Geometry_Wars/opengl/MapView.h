#pragma once

#include <map>



/// MapView: Class that is only used internally, to create read only view of a map.
/**
 * Allows the owner to let external users access a std::map through
 * operator[] without letting the external users change the map itself.
 * Used by ShaderState to grant access to the uniform and attribute variables.
 */
template <typename KEY_TYPE, typename VALUE_TYPE>
class MapView
{

public:

    /// Only allow the construction of MapView through the dedicated constructor.
    MapView() = delete;

    /// Construct the MapView with a reference to the map you wish to expose.
    MapView(std::map<KEY_TYPE, VALUE_TYPE>& map_reference)
        : mapped_data(map_reference)
    { }

    /// Access to the underlying std::map
    VALUE_TYPE& operator[](const KEY_TYPE& key)
    {
        return mapped_data.at(key);
    }

private:

    std::map<KEY_TYPE, VALUE_TYPE>& mapped_data;

};
