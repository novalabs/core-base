/* COPYRIGHT (c) 2016-2017 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <core/namespace.hpp>
#include <core/common.hpp>
#include <core/Array.hpp>

NAMESPACE_CORE_BEGIN

/*! \brief String
 *
 * core::String encapsulates a fixed size array of char, commonly known as a string.
 *
 * \warning This implementation is incomplete, and work in progress
 *
 * \tparam S size of the array
 */
template <std::size_t S>
struct String {
    using value_type      = char;  //!< Type of stored objects
    using pointer         = value_type *;  //!< Pointer
    using const_pointer   = const value_type *;  //!< Const Pointer
    using reference       = value_type &;  //!< Reference
    using const_reference = const value_type &;  //!< Const Reference
    using iterator        = value_type *;  //!< Iterator
    using const_iterator  = const value_type *;  //!< Const Iterator
    using size_type       = std::size_t;  //!< Type of index and size
    using difference_type = std::ptrdiff_t;

    static const size_type SIZE = S;

    using Traits = ArrayTraits<char, S>;
    typename Traits::Type _data;

    // Capacity.
    /*! \brief Get the size of the array
     *
     * \return the size of the array
     */
    constexpr size_type
    size() const
    {
        return S;
    }

    /*! \brief Direct access to the underlying array
     *
     * \return pointer to the underlying element storage
     */
    pointer
    data()
    {
        return std::__addressof(Traits::ref(_data, 0));
    }

    /*! \brief Direct access to the underlying array
     *
     * \return const pointer to the underlying element storage
     */
    const_pointer
    data() const
    {
        return std::__addressof(Traits::ref(_data, 0));
    }

    const char*
    c_str() const
    {
        return data();
    }

    void
    clear()
    {
        _data[0] = 0;
    }

    std::size_t
    length() const
    {
        for (std::size_t i = 0; i < S; i++) {
            if (_data[i] == 0) {
                return i;
            }
        }

        return S;
    }

    void
    operator=(
        const char* x
    )
    {
        std::size_t l = strlen(x);

        CORE_ASSERT(l <= S);

        for (std::size_t i = 0; i <= l; i++) {
            _data[i] = *x++;
        }
    }

    template <std::size_t S2>
    void
    operator=(
        const Array<char, S2>& x
    )
    {
        static_assert(S2 <= S, "The size of the source array must be less than or equal to the size of this string");

        for (std::size_t i = 0; i <= S; i++) {
            _data[i] = x[i];
        }
    }

    void
    operator=(
        const Array<char, S>& x
    )
    {
        for (std::size_t i = 0; i <= S; i++) {
            _data[i] = x[i];
        }
    }

    /*! \brief Cast operator
     *
     * \return pointer to the underlying element storage
     */
    operator char*() {
        return data();
    }

    /*! \brief Cast operator
     *
     * \return const pointer to the underlying element storage
     */
    operator const char*() const {
        return data();
    }
};

template <std::size_t S>
inline bool
operator==(
    const String<S>& lhs,
    const String<S>& rhs
)
{
    return strncmp(lhs.data(), rhs.data(), S) == 0;
}

template <std::size_t S>
inline bool
operator!=(
    const String<S>& lhs,
    const String<S>& rhs
)
{
    return !(lhs == rhs);
}

template <std::size_t S>
inline bool
operator==(
    const char*      lhs,
    const String<S>& rhs
)
{
    return strncmp(lhs, rhs.data(), S) == 0;
}

template <std::size_t S>
inline bool
operator==(
        const String<S>& lhs,
        const char*      rhs

)
{
    return strncmp(rhs, lhs.data(), S) == 0;
}

template <std::size_t S>
inline bool
operator!=(
    const char*      lhs,
    const String<S>& rhs
)
{
    return !(lhs == rhs);
}

NAMESPACE_CORE_END
