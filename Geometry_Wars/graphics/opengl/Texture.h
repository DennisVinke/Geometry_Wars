#pragma once

#include <utility>

#include "glad/glad.h"





/// Texture class, holds a texture in OpenGL
/**
 *  Texture can be allocated empty or with data from the memory, in case of empty
 *  The texture is useful ass a frameBuffer.
 *  
 *  All Query functions both update the data stored client side, and return it.
 *  When you do not use get_handle() to change the opengl state of the texture,
 *  It is never necessary to query the state, from opengl, the state in this class
 *  is should always be up to date, if you only use it's member functions to change 
 *  the state
 */
class Texture
{

public:


    /// enum class Texture::Type
    /**
     *  Enum that has all different texture tyeps that are possible, much cleaner than
     *  having seperate values for normalizedness, mipmap, and msaa, when most 
     *  combinations of those are invalid state.
     */
    enum class Type : GLsizei
    {
        MULTI_SAMPLED_2 = 2,
        MULTI_SAMPLED_4 = 4,
        MULTI_SAMPLED_8 = 8,
        MULTI_SAMPLED_16 = 16,
        NORMALIZED_MIPMAP = 17,
        NORMALIZED_NO_MIPMAP = 18,
        NON_NORMALIZED = 19
    };


    /// default constructor is deleted.
    Texture() = delete;


    /// It is possible to construct Textures when a type and a pixel_format is provided.
    Texture(Type type, GLenum pixel_format);


    /// Copying is disabled because it is ambiguous who retains ownership of the gpu data.
    Texture(const Texture&) = delete;


    /// Move constructor is allowed becuase only one instance stays responsible for the gpu memory
    Texture(Texture&& other);


    /// destructor.
    ~Texture();


    /// allocates the memory on the gpu, without filling it to a certain color.
    void allocate_empty(unsigned int width, unsigned int height);


    /// allocate with data from client side memory, this is useful when showing images on the screen.
    void allocate_filled(unsigned int width, unsigned int height, const unsigned char* data);
    

    /// resizes the texture to size width/ height, undefined what happens with the old data
    void set_size(unsigned int width, unsigned int height);


    /// returns the current allocated size of the texture
    std::pair<int, int> get_size() const;



    /// returns the allocated size of the texture, but instead of returning the cached value, queries the value from opengl
    std::pair<int, int> query_size();

    /// returns the width of the texture
    int get_width() const;

    /// returns the height of the texture
    int get_height() const;

    /// returns the width of the texture, but instead of returning the cached value, queries the value from opengl
    int query_width();

    /// returns the height of the texture, but instead of returning the cached value, queries the value from opengl
    int query_height();
    

    /// sets the filter that is used when sampling this texture, and this texture is magnified
    void set_mag_filter(GLenum mag_filter);

    /// sets the filter that is used when sampling this texture, and this texture is minified
    void set_min_filter(GLenum min_filter);

    /// returns the filter that is used when sampling this texture, and this texture is minified
    GLenum get_mag_filter() const;

    /// returns the filter that is used when sampling this texture, and this texture is minified
    GLenum get_min_filter() const;


    /// returns the filter that is used when sampling this texture, and this texture is magnified
    /// unlike the get variant of this version (returning the cached value ) it is queried from opengl
    GLenum query_mag_filter();

    /// returns the filter that is used when sampling this texture, and this texture is minified
    /// unlike the get variant of this version (returning the cached value ) it is queried from opengl
    GLenum query_min_filter();

 
    /// Sets the wrap mode used when the texture is sampled outside of its boundaries.
    void set_wrap_x(GLenum wrap_mode);

    /// Sets the wrap mode used when the texture is sampled outside of its boundaries.
    void set_wrap_y(GLenum wrap_mode);

    /// Returns the wrap mode used when the texture is sampled outside of its boundaries.
    GLenum get_wrap_x() const;

    /// Returns the wrap mode used when the texture is sampled outside of its boundaries.
    GLenum get_wrap_y() const;

    /// Returns the wrap mode used when the texture is sampled outside of its boundaries.
    /// unlike the get variant of this version (returning the cached value ) it is queried from opengl
    GLenum query_wrap_x();

    /// Returns the wrap mode used when the texture is sampled outside of its boundaries.
    /// unlike the get variant of this version (returning the cached value ) it is queried from opengl
    GLenum query_wrap_y();

    
    /// Returns the amount of samples (MSAA samples) that this texture is configured to use 
    /// This is only necessary when the texture is being used as a render target.
    int get_num_samples() const;

    /// sets the amount of samples (MSAA samples) that this texture is configured to use 
    /// This is only necessary when the texture is being used as a render target.
    int query_num_samples();

    
    /// Binds this texture to its OpenGL binding target.
    void bind() const;

    /// returns the handle that points to the texture object in opengl
    GLuint get_handle() const;

    

    const GLenum binding_target;

    const GLenum pixel_format;

    const Type   type;


private:

    
    // Not const becuase OpenGL is not gauranteed to give the amount of samples asked for.
    int num_samples = 1;

    // Size is allowed to be changed dynamically.
    int texture_width = 0, texture_height = 0;

    // These properties are allowed to be changed dynamically.
    GLenum mag_filter, min_filter, texture_wrap_x, texture_wrap_y;


    GLuint texture_handle;

    bool cleanup_responsible = true;


    static constexpr GLenum binding_target_of(const Type& type);


};
