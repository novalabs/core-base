/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <core/namespace.hpp>
#include <core/common.hpp>
#include <memory>

NAMESPACE_CORE_BEGIN

template <typename T, std::size_t S>
struct ArrayTraits {
   using Type      = T[S];
   using ConstType = const T[S];

   static constexpr T&
   ref(
      const Type& t,
      std::size_t n
   )
   {
      return const_cast<T&>(t[n]);
   }
};

template <typename T>
struct ArrayTraits<T, 0>{
   using Type = struct {};

   using ConstType = struct {};

   static constexpr T&
   ref(
      const Type&,
      std::size_t
   )
   {
      return *static_cast<T*>(nullptr);
   }
};

/*! \brief Array
 *
 * core::Array encapsulates a fixed size array.
 * It offers the performance of a C-style array with all the features of a stdlib container (it knows its own size, offers random access iterators, supports assignment and comparison ops, and so on).
 *
 * It is a stripped down std::array
 *
 * \tparam T type of the objects to be stored by the array
 * \tparam S size of the array
 */
template <typename T, std::size_t S>
struct Array {
   using value_type      = T; //!< Type of stored objects
   using pointer         = value_type *; //!< Pointer
   using const_pointer   = const value_type *; //!< Const Pointer
   using reference       = value_type &; //!< Reference
   using const_reference = const value_type &; //!< Const Reference
   using iterator        = value_type *; //!< Iterator
   using const_iterator  = const value_type *; //!< Const Iterator
   using size_type       = std::size_t; //!< Type of index and size
   using difference_type = std::ptrdiff_t;

   using Traits = ArrayTraits<T, S>;
   typename Traits::Type _data;

   // Iterators.
   /*! \brief Iterator
    *
    * \return iterator to the first element of the array
    */
   iterator
   begin()
   {
      return iterator(data());
   }

   /*! \brief Iterator
    *
    * \return const iterator to the first element of the array
    */
   const_iterator
   begin() const
   {
      return const_iterator(data());
   }

   /*! \brief Iterator
    *
    * \return iterator to the last element of the array
    */
   iterator
   end()
   {
      return iterator(data() + S);
   }

   /*! \brief Iterator
    *
    * \return const iterator to the last element of the array
    */
   const_iterator
   end() const
   {
      return const_iterator(data() + S);
   }

   /*! \brief Iterator
    *
    * \return const iterator to the first element of the array
    */
   const_iterator
   cbegin() const
   {
      return const_iterator(data());
   }

   /*! \brief Iterator
    *
    * \return const iterator to the last element of the array
    */
   const_iterator
   cend() const
   {
      return const_iterator(data() + S);
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

   constexpr size_type
   max_size() const
   {
      return S;
   }

   constexpr bool
   empty() const
   {
      return size() == 0;
   }

   // Element access.
   /*! \brief Element access
    *
    * \return a reference to element at index \c __n
    */
   reference
   operator[](
      size_type __n //!< [in] index
   )
   {
      return Traits::ref(_data, __n);
   }

   /*! \brief Element access
    *
    * \return a const reference to element at index \c __n
    */
   constexpr const_reference
   operator[](
      size_type __n //!< [in] index
   ) const
   {
      return Traits::ref(_data, __n);
   }

   /*! \brief Element access (with range check)
    *
    * \pre \c __n must index a valid object
    *
    * \return a reference to element at index \c __n
    */
   reference
   at(
      size_type __n //!< [in] index
   )
   {
      CORE_ASSERT(__n < S);

      return Traits::ref(_data, __n);
   }

   /*! \brief Element access (with range check)
    *
    * \pre \c __n must index a valid object
    *
    * \return a const reference to element at index \c __n
    */
   const_reference
   at(
      size_type __n //!< [in] index
   ) const
   {
      CORE_ASSERT(__n < S);

      return Traits::ref(_data, __n);
   }

   /*! \brief Access the first element
    *
    * \return reference to the first element
    */
   reference
   front()
   {
      return *begin();
   }

   /*! \brief Access the first element
    *
    * \return const reference to the first element
    */
   constexpr const_reference
   front() const
   {
      return Traits::ref(_data, 0);
   }

   /*! \brief Access the last element
    *
    * \return reference to the last element
    */
   reference
   back()
   {
      return S ? *(end() - 1) : *end();
   }

   /*! \brief Access the last element
    *
    * \return const reference to the last element
    */
   constexpr const_reference
   back() const
   {
      return S ? Traits::ref(_data, S - 1) : Traits::ref(_data, 0);
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

   /*! \brief Cast operator
    *
    * \return pointer to the underlying element storage
    */
   explicit
   operator pointer()
   {
      return data();
   }

   /*! \brief Cast operator
    *
    * \return const pointer to the underlying element storage
    */
   explicit
   operator const_pointer()
   {
      return data();
   }

   void
   copyFrom(
      typename Traits::ConstType from
   )
   {
      for (std::size_t i = 0; i < S; i++) {
         _data[i] = from[i];
      }
   }

   void
   copyTo(
      typename Traits::Type to
   ) const
   {
      for (std::size_t i = 0; i < S; i++) {
         to[i] = _data[i];
      }
   }
};


template <typename T, std::size_t S>
inline bool
operator==(
   const Array<T, S>& lhs,
   const Array<T, S>& rhs
)
{
   for (std::size_t i = 0; i < S; i++) {
      if (lhs[i] != rhs[i]) {
         return false;
      }
   }

   return true;
}

template <typename T, std::size_t S>
inline bool
operator==(
   const typename ArrayTraits<T, S>::Type& lhs,
   const Array<T, S>& rhs
)
{
   for (std::size_t i = 0; i < S; i++) {
      if (lhs[i] != rhs[i]) {
         return false;
      }
   }

   return true;
}

template <typename T, std::size_t S>
inline bool
operator!=(
   const typename ArrayTraits<T, S>::Type& lhs,
   const Array<T, S>& rhs
)
{
   return !(lhs == rhs);
}

NAMESPACE_CORE_END
