/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <core/namespace.hpp>
#include <core/common.hpp>
#include <core/Array.hpp>
#include <core/String.hpp>
#include <core/os/Time.hpp>

NAMESPACE_CORE_BEGIN

enum class CoreType {
    VOID, CHAR, INT8, UINT8, INT16, UINT16, INT32, UINT32, INT64, UINT64, FLOAT32, FLOAT64, TIMESTAMP, VARIANT
};

template <CoreType T>
struct CoreTypeTraitsHelperF;

template <>
struct CoreTypeTraitsHelperF<CoreType::VOID>{
    typedef void Type;
    static const std::size_t sizeOfType = 0;
};

template <>
struct CoreTypeTraitsHelperF<CoreType::CHAR>{
    typedef char Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::INT8>{
    typedef int8_t Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::UINT8>{
    typedef uint8_t Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::INT16>{
    typedef int16_t Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::UINT16>{
    typedef uint16_t Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::INT32>{
    typedef int32_t Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::UINT32>{
    typedef uint32_t Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::INT64>{
    typedef int64_t Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::UINT64>{
    typedef uint64_t Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::TIMESTAMP>{
    typedef struct {
        uint32_t sec;
        uint32_t nsec;
    } Type;
//		typedef core::mwcore::os::Time Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::FLOAT32>{
    typedef float Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::FLOAT64>{
    typedef double Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <>
struct CoreTypeTraitsHelperF<CoreType::VARIANT>{
    typedef struct {
        union {
            CoreTypeTraitsHelperF<core::CoreType::TIMESTAMP>::Type timestamp;
            CoreTypeTraitsHelperF<core::CoreType::FLOAT64>::Type f64;
            CoreTypeTraitsHelperF<core::CoreType::INT64>::Type i64;
            CoreTypeTraitsHelperF<core::CoreType::UINT64>::Type u64;
            CoreTypeTraitsHelperF<core::CoreType::FLOAT32>::Type f32;
            CoreTypeTraitsHelperF<core::CoreType::INT32>::Type i32;
            CoreTypeTraitsHelperF<core::CoreType::UINT32>::Type u32;
            CoreTypeTraitsHelperF<core::CoreType::INT16>::Type i16;
            CoreTypeTraitsHelperF<core::CoreType::UINT16>::Type u16;
            CoreTypeTraitsHelperF<core::CoreType::INT8>::Type i8;
            CoreTypeTraitsHelperF<core::CoreType::UINT8>::Type u8;
            CoreTypeTraitsHelperF<core::CoreType::CHAR>::Type c;
        };

        CoreType type;
    } Type;
    static const std::size_t sizeOfType = sizeof(Type);
};

template <typename T>
struct CoreTypeTraitsHelperB;

template <>
struct CoreTypeTraitsHelperB<char>{
    static const CoreType types = CoreType::CHAR;
};

template <>
struct CoreTypeTraitsHelperB<int8_t>{
    static const CoreType types = CoreType::INT8;
};

template <>
struct CoreTypeTraitsHelperB<uint8_t>{
    static const CoreType types = CoreType::UINT8;
};

template <>
struct CoreTypeTraitsHelperB<int16_t>{
    static const CoreType types = CoreType::INT16;
};

template <>
struct CoreTypeTraitsHelperB<uint16_t>{
    static const CoreType types = CoreType::UINT16;
};

template <>
struct CoreTypeTraitsHelperB<int>{
    static const CoreType types = CoreType::INT32;
};

template <>
struct CoreTypeTraitsHelperB<int32_t>{
    static const CoreType types = CoreType::INT32;
};

template <>
struct CoreTypeTraitsHelperB<uint32_t>{
    static const CoreType types = CoreType::UINT32;
};

template <>
struct CoreTypeTraitsHelperB<int64_t>{
    static const CoreType types = CoreType::INT64;
};

template <>
struct CoreTypeTraitsHelperB<uint64_t>{
    static const CoreType types = CoreType::UINT64;
};

template <>
struct CoreTypeTraitsHelperB<float>{
    static const CoreType types = CoreType::FLOAT32;
};

template <>
struct CoreTypeTraitsHelperB<double>{
    static const CoreType types = CoreType::FLOAT64;
};

template <>
struct CoreTypeTraitsHelperB<CoreTypeTraitsHelperF<CoreType::TIMESTAMP> >{
    static const CoreType types = CoreType::TIMESTAMP;
};

template <>
struct CoreTypeTraitsHelperB<CoreTypeTraitsHelperF<CoreType::VARIANT> >{
    static const CoreType types = CoreType::VARIANT;
};

template <CoreType T, std::size_t S>
struct CoreTypeTraits {
    static const CoreType    types       = T;
    static const std::size_t sizeOfTypes = CoreTypeTraitsHelperF<T>::sizeOfType;
    static const std::size_t size = S;

    using BaseType = typename CoreTypeTraitsHelperF<T>::Type;
    using Type     = core::Array<BaseType, S>;
};

template <std::size_t S>
struct CoreTypeTraits<CoreType::CHAR, S> {
    static const CoreType    types       = CoreType::CHAR;
    static const std::size_t sizeOfTypes = CoreTypeTraitsHelperF<CoreType::CHAR>::sizeOfType;
    static const std::size_t size = S;

    using BaseType = typename CoreTypeTraitsHelperF<CoreType::CHAR>::Type;
    using Type     = core::String<S>;
};

template <>
struct CoreTypeTraits<CoreType::CHAR, 1> {
    static const CoreType    types       = CoreType::CHAR;
    static const std::size_t sizeOfTypes = CoreTypeTraitsHelperF<CoreType::CHAR>::sizeOfType;
    static const std::size_t size = 1;

    using BaseType = typename CoreTypeTraitsHelperF<CoreType::CHAR>::Type;
    using Type     = BaseType;
};

template <CoreType T>
struct CoreTypeTraits<T, 1>{
    static const CoreType    types       = T;
    static const std::size_t sizeOfTypes = CoreTypeTraitsHelperF<T>::sizeOfType;
    static const std::size_t size = 1;

    using BaseType = typename CoreTypeTraitsHelperF<T>::Type;
    using Type     = BaseType;
};

template <CoreType T>
struct CoreTypeTraits<T, 0>{
    static const CoreType    types       = CoreType::VOID;
    static const std::size_t sizeOfTypes = CoreTypeTraitsHelperF<T>::sizeOfType;
    static const std::size_t size = 0;

    using BaseType = typename CoreTypeTraitsHelperF<T>::Type;
    using Type     = BaseType;
};

namespace CoreTypeUtils {
template <typename T, std::size_t S>
inline std::size_t
size(
    const T(&v)[S]
)
{
    return S;
}

template <typename T, std::size_t S>
inline std::size_t
size(
    const ::core::Array<T, S> (&v)
)
{
    return S;
}

template <typename T>
inline std::size_t
size(
    const T(&v)
)
{
    return 1;
}

template <typename T, std::size_t S>
inline CoreType
coreType(
    const T(&v)[S]
)
{
    return CoreTypeTraitsHelperB<T>::types;
}

template <typename T, std::size_t S>
inline CoreType
coreType(
    const ::core::Array<T, S> (&v)
)
{
    return CoreTypeTraitsHelperB<T>::types;
}

template <typename T>
inline CoreType
coreType(
    const T(&v)
)
{
    return CoreTypeTraitsHelperB<T>::types;
}

#define SIZE_OF_CASE(__x__) case CoreType::__x__: \
      return CoreTypeTraitsHelperF<CoreType::__x__>::sizeOfType; break
inline std::size_t
coreTypeSize(
    CoreType type
)
{
    // For run-time...
    switch (type) {
        SIZE_OF_CASE(VOID);
        SIZE_OF_CASE(CHAR);
        SIZE_OF_CASE(INT8);
        SIZE_OF_CASE(UINT8);
        SIZE_OF_CASE(INT16);
        SIZE_OF_CASE(UINT16);
        SIZE_OF_CASE(INT32);
        SIZE_OF_CASE(UINT32);
        SIZE_OF_CASE(INT64);
        SIZE_OF_CASE(UINT64);
        SIZE_OF_CASE(FLOAT32);
        SIZE_OF_CASE(FLOAT64);
        SIZE_OF_CASE(TIMESTAMP);
        SIZE_OF_CASE(VARIANT);
      default:
          CORE_ASSERT(!"Undefined CoreType");
          return 0; // unreachable
    } // switch
} // coreTypeSize

#undef SIZE_OF_CASE

template <typename T>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    T& x
);


template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    double& x
)
{
    x = value.f64;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    int64_t& x
)
{
    x = value.i64;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    uint64_t& x
)
{
    x = value.u64;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    float& x
)
{
    x = value.f32;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    int32_t& x
)
{
    x = value.i32;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    uint32_t& x
)
{
    x = value.u32;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    int16_t& x
)
{
    x = value.i16;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    uint16_t& x
)
{
    x = value.u16;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    int8_t& x
)
{
    x = value.i8;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    uint8_t& x
)
{
    x = value.u8;
}

template <>
inline void
variantGet(
    const core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value,
    char& x
)
{
    x = value.c;
}

template <typename T>
inline void
variantSet(
    T x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
);


template <>
inline void
variantSet(
    double x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.f64 = x;
}

template <>
inline void
variantSet(
    int64_t x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.i64 = x;
}

template <>
inline void
variantSet(
    uint64_t x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.u64 = x;
}

template <>
inline void
variantSet(
    float x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.f32 = x;
}

template <>
inline void
variantSet(
    int32_t x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.i32 = x;
}

template <>
inline void
variantSet(
    uint32_t x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.u32 = x;
}

template <>
inline void
variantSet(
    int16_t x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.i16 = x;
}

template <>
inline void
variantSet(
    uint16_t x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.u16 = x;
}

template <>
inline void
variantSet(
    int8_t x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.i8 = x;
}

template <>
inline void
variantSet(
    uint8_t x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.u8 = x;
}

template <>
inline void
variantSet(
    char x,
    core::CoreTypeTraits<core::CoreType::VARIANT, 1>::Type& value
)
{
    value.c = x;
}
}


NAMESPACE_CORE_END

#define CORETYPE_UDL_INT(__s__, __t__) constexpr core::CoreTypeTraits<core::CoreType::__t__, 1>::Type operator"" _ ## __s__(unsigned long long x) { \
        return static_cast<core::CoreTypeTraits<core::CoreType::__t__, 1>::Type>(x); \
}
#define CORETYPE_UDL_FLOAT(__s__, __t__) constexpr core::CoreTypeTraits<core::CoreType::__t__, 1>::Type operator"" _ ## __s__(long double x) { \
        return static_cast<core::CoreTypeTraits<core::CoreType::__t__, 1>::Type>(x); \
}

CORETYPE_UDL_INT(s8, INT8);
CORETYPE_UDL_INT(u8, UINT8);
CORETYPE_UDL_INT(s16, INT16);
CORETYPE_UDL_INT(u16, UINT16);
CORETYPE_UDL_INT(s32, INT32);
CORETYPE_UDL_INT(u32, UINT32);
CORETYPE_UDL_INT(s64, INT64);
CORETYPE_UDL_INT(u64, UINT64);
CORETYPE_UDL_FLOAT(f32, FLOAT32);
CORETYPE_UDL_FLOAT(f64, FLOAT64);
