/* COPYRIGHT (c) 2016-2017 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <core/namespace.hpp>
#include <core/common.hpp>
#include <core/String.hpp>

#include <cstdarg>
#include <cstdio>

NAMESPACE_CORE_BEGIN

/*! \brief Function that can printf something
 *
 * \param buffer [in] destination buffer
 * \param length [in] length of the destination buffer
 * \param data   [in] the "something"
 *
 * \return number of bytes written (not including the \0)
 * \retval -1 the buffer was not large enough
 */
using FormatterFunction = int(char* buffer, std::size_t length, const void* data);

/*! \brief StringBuffer
 *
 * core::StringBuffer makes it easy to build up a string
 *
 * \warning This implementation is rather incomplete, and work in progress
 *
 * \tparam S size of the buffer
 */
template <std::size_t SIZE>
class StringBuffer:
    public core::String<SIZE>
{
public:
    StringBuffer()
    {
        reset();
    }

    inline bool
    appendString(
        const char* s
    )
    {
        return appendString(s, strlen(s));
    }

    inline bool
    appendString(
        const char* s,
        size_t      n
    )
    {
        size_t m = n;

        if (m > (size_t)(_top - _curr)) {
            m = (size_t)(_top - _curr);
        }

        while (m > 0) {
            if (*s == 0) {
                *_curr = 0;
                return true;
            }

            *_curr++ = *s++;
            m--;
        }

        *_curr = 0;

        return true;
    } // append

    bool
    appendFormat(
        const char* format,
        ...
    )
    {
        va_list ap;

        va_start(ap, format);
        auto n = vsnprintf(_curr, (_top - _curr), format, ap);
        va_end(ap);

        if ((n >= 0) && (n < (_top - _curr))) {
            _curr += n;
            *_curr = 0;
            return true;
        }

        return false;
    }

    bool
    appendFrmttr(
        FormatterFunction* function,
        const void*        data
    )
    {
        return appendFormatter(function, data);
    }

    bool
    appendFormatter(
        FormatterFunction* function,
        const void*        data
    )
    {
        auto n = function(_curr, (_top - _curr), data);

        if ((n >= 0) && (n < (_top - _curr))) {
            _curr += n;
            *_curr = 0;
            return true;
        }

        return false;
    }

    void
    reset()
    {
        _curr  = this->data();
        _top   = _curr + SIZE - 1;
        *_curr = 0;
    }

    std::size_t
    length() const
    {
        return _curr - this->data();
    }

private:
    typename core::String<SIZE>::pointer _curr = nullptr;
    typename core::String<SIZE>::pointer _top  = nullptr;
};

NAMESPACE_CORE_END
