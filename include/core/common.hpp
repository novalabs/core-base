/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <limits>

#include <core/Uncopyable.hpp>

#include <core/mw/Utils.hpp>
#include <core/os/SysLock.hpp>
#include <core/os/OS.hpp>

# if __GNUC_PREREQ(4, 6)
#  define CORE_WARNINGS_NO_CAST_ALIGN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wcast-align\"")

#  define CORE_WARNINGS_RESET \
    _Pragma ("GCC diagnostic pop")
# else
#  define CORE_WARNINGS_NO_CAST_ALIGN
#  define CORE_WARNINGS_RESET
# endif

#ifdef USE_CORE_ASSERT
#define CORE_ASSERT(expr) {chDbgCheck(expr); }
#else
#define CORE_ASSERT(expr) {}
#endif

#define CORE_ENSURE_THAT(expr) do {      \
    if(!(expr)) {                        \
        core::os::OS::halt(__func__);    \
    }                                    \
} while(false)

#ifndef CORE_MEMORY_ALIGNED
#define CORE_MEMORY_ALIGNED  __attribute__((aligned(sizeof(unsigned))))
#endif

#define CORE_PACKED          __attribute__((packed))
#define CORE_PACKED_ALIGNED  __attribute__((aligned(4), packed))

#define CORE_FORCE_INLINE    inline __attribute__((always_inline))

#define UNREACHABLE          __builtin_unreachable();

#define CORE_NORESET         __attribute__((section(".noreset")))

#define CORE_APP_CONFIG      __attribute__((section("app_config")))

#if !defined(CORE_USE_BRIDGE_MODE) || defined(__DOXYGEN__)
#define CORE_USE_BRIDGE_MODE 0
#endif


template <typename Test, typename Base>
CORE_FORCE_INLINE
void
static_cast_check()
{
    register const Test* const pd = NULL;
    register const Base* const pb = pd;

    (void)pd;
    (void)pb;
}

inline
size_t
bit_mask(
    size_t num_bits
)
{
    return (static_cast<size_t>(1) << num_bits) - 1;
}

inline
size_t
byte_mask(
    size_t num_bytes
)
{
    return bit_mask(num_bytes << 3);
}

template <typename T>
inline
size_t
type_mask()
{
    return byte_mask(sizeof(T));
}

template <typename T>
inline
size_t
compute_chunk_size(
    const T* startp,
    const T* endxp
)
{
    return static_cast<size_t>(
        reinterpret_cast<ptrdiff_t>(endxp) - reinterpret_cast<ptrdiff_t>(startp)
    );
}

inline
bool
check_bounds(
    const void* valuep,
    size_t      valuelen,
    const void* slotp,
    size_t      slotlen
)
{
    register const uint8_t* const vp = reinterpret_cast<const uint8_t*>(valuep);
    register const uint8_t* const sp = reinterpret_cast<const uint8_t*>(slotp);

    return vp >= sp && (vp + valuelen) <= (sp + slotlen);
}

inline
size_t
compute_segment(
    const void* ptr,
    size_t      segment_size
)
{
    return reinterpret_cast<size_t>(ptr) & ~(segment_size - 1);
}

inline
size_t
compute_offset(
    const void* ptr,
    size_t      segment_size
)
{
    return reinterpret_cast<size_t>(ptr) & (segment_size - 1);
}

#define MANAGEMENT_TOPIC_NAME "R2P"
#define MANAGEMENT_TOPIC_ID ((uint8_t)0x00)

#define RPC_TOPIC_NAME "CORERPC"
#define RPC_TOPIC_ID ((uint8_t)0xFB)

#define BOOTLOADER_MASTER_TOPIC_NAME "BOOTLOADERMSTR"
#define BOOTLOADER_MASTER_TOPIC_ID ((uint8_t)0xFC)

#define BOOTLOADER_TOPIC_NAME "BOOTLOADER"
#define BOOTLOADER_TOPIC_ID ((uint8_t)0xFD)

#define TEST_TOPIC_NAME "test"
#define TEST_TOPIC_ID ((uint8_t)0xFE)
