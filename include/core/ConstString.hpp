/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <core/namespace.hpp>
#include <core/common.hpp>
#include <core/ConstArray.hpp>
#include <core/String.hpp>

NAMESPACE_CORE_BEGIN

/*! \brief ConstString
 *
 * core::ConstString encapsulates a constant fixed size array of char, commonly known as a string.
 *
 * \warning This implementation is incomplete, and work in progress
 *
 * \tparam S size of the array
 */
template <std::size_t S>
struct ConstString {
    using value_type      = char;  //!< Type of stored objects
    using const_pointer   = const value_type *;  //!< Const Pointer
    using const_reference = const value_type &;  //!< Const Reference
    using const_iterator  = const value_type *;  //!< Const Iterator
    using size_type       = std::size_t;  //!< Type of index and size
    using difference_type = std::ptrdiff_t;

    static const size_type SIZE = S;

    using Traits = ConstArrayTraits<char, S>;
    const_pointer _data;

    ConstString(const_pointer data) {
        _data = data;
    }
        
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
    const ConstString<S>& lhs,
    const ConstString<S>& rhs
)
{
    return strncmp(lhs.data(), rhs.data(), S) == 0;
}

template <std::size_t S1, std::size_t S2>
inline bool
operator==(
    const ConstString<S1>& lhs,
    const String<S2>& rhs
)
{
    return strncmp(lhs.data(), rhs.data(), std::min(S1, S2)) == 0;
}

template <std::size_t S1, std::size_t S2>
inline bool
operator==(
    const String<S1>& lhs,
    const ConstString<S2>& rhs
)
{
    return strncmp(lhs.data(), rhs.data(), std::min(S1, S2)) == 0;
}

template <std::size_t S>
inline bool
operator!=(
    const ConstString<S>& lhs,
    const ConstString<S>& rhs
)
{
    return !(lhs == rhs);
}

template <std::size_t S1, std::size_t S2>
inline bool
operator!=(
    const ConstString<S1>& lhs,
    const String<S2>& rhs
)
{
    return !(lhs == rhs);
}

template <std::size_t S1, std::size_t S2>
inline bool
operator!=(
    const String<S1>& lhs,
    const ConstString<S1>& rhs
)
{
    return !(lhs == rhs);
}

template <std::size_t S>
inline bool
operator==(
    const char*      lhs,
    const ConstString<S>& rhs
)
{
    return strncmp(lhs, rhs.data(), S) == 0;
}

template <std::size_t S>
inline bool
operator==(
        const ConstString<S>& lhs,
        const char*      rhs

)
{
    return strncmp(rhs, lhs.data(), S) == 0;
}

template <std::size_t S>
inline bool
operator!=(
    const char*      lhs,
    const ConstString<S>& rhs
)
{
    return !(lhs == rhs);
}

NAMESPACE_CORE_END
