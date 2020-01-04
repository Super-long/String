#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <bits/cpp_type_traits.h>
#include <ext/type_traits.h>
#include <bits/move.h>
#include <bits/ptr_traits.h>
#include <iterator>

namespace String{
    using std::iterator_traits;
    template<typename Iterator_, typename Container_>
    class Base_Iterator{
            //using std::iterator_traits; //不能放在这里
        protected: //will write a reverse iterator.
            Iterator_ Value_;
            using Iterator_traits = iterator_traits<Iterator_>;

        public:
            //This is only for strings.
            //using iterator_category = random_access_itreator_tag;

            using Iterator_type = Iterator_;
            using iterator_category = typename Iterator_traits::iterator_category;
            using value_type = typename Iterator_traits::value_type;
            using difference_type = typename Iterator_traits::difference_type;
            using reference = typename Iterator_traits::reference;
            using pointer = typename Iterator_traits::pointer;

            //Following is construct function.
            //字面值类型包括算数类型，引用和指针,还有一些类
            //证明迭代其是一个字面值常量类
            /**
             *  数据成员必须都必须是字面值类型。

                类必须至少含有一个constexpr构造函数。

                如果一个数据成员含有类内初始值，则初始值必须是常量表达式；如果成员属于某种类，初始值必须使用该类的constexpr构造函数。

                类必须使用析构函数的默认定义。
            */
            constexpr Base_Iterator() noexcept
                :Value_(Iterator_()) {}

            explicit Base_Iterator(const Iterator_& para) noexcept
                :Value_(para) {}

            //Allow iterator to const_iterator conversion.
            //TODO : 还是没搞明白为什么可以转换 
            /*template<typename _Iter>
            Base_Iterator(const Base_Iterator<_Iter, 
                    typename __enable_if<
                    (std::__are_same<_Iter, typename _Container::pointer>::__value),
                    _Container>::type>& __i) noexcept
            : Value_(__i.base()) {}*/

            //Following is Functional function.

            reference
            operator*() const noexcept{
                return *Value_;
            }

            pointer
            operator->() const noexcept{
                return Value_;
            }

            Base_Iterator&
            operator++() noexcept{
                ++Value_;
                return *this;
            }

            Base_Iterator
            operator++(int) noexcept{
                return Base_Iterator(Value_++);
            }

            Base_Iterator&
            operator--() noexcept{
                --Value_;
                return *this;
            }

            Base_Iterator
            operator--(int) noexcept{
                return Base_Iterator(Value_--);
            }

            //difference - ptrdiff_t - long int(my device)
            //pridiff_t : Alias of one of the fundamental signed integer types.
            reference
            operator[](difference_type n) const noexcept{
                return Value_[n];
            }

            Base_Iterator&
            operator-(difference_type n) const noexcept{
                return Base_Iterator(Value_ - n);
            }

            Base_Iterator& //没有用RVO 下去再学习学习
            operator+(difference_type n) const noexcept{
                return Base_Iterator(Value_ + n);
            }

            Base_Iterator&
            operator-=(difference_type n) noexcept{
                Value_ -= n; return *this;
            }

            Base_Iterator&
            operator+=(difference_type n) noexcept{
                Value_ += n; return *this;
            }

            const Iterator_& 
            base() const noexcept{
                return Value_;
            }
    };

    //Forward iterator requirements.
    template<typename _IteratorLhs, typename _IteratorRhs, typename _Container>
      inline bool 
      operator==(const Base_Iterator<_IteratorLhs,  _Container>& lhs,
        const Base_Iterator<_IteratorRhs,_Container>& rhs) noexcept {
            return lhs.base() == rhs.base();
        }

    template<typename _Iterator, typename _Container>
      inline bool
      operator==(const Base_Iterator<_Iterator,  _Container>& lhs,
        const Base_Iterator<_Iterator,_Container>& rhs) noexcept {
            return lhs.base() == rhs.base();
        }

    template<typename _IteratorLhs, typename _IteratorRhs, typename _Container>
      inline bool 
      operator!=(const Base_Iterator<_IteratorLhs,  _Container>& lhs,
        const Base_Iterator<_IteratorRhs,_Container>& rhs) noexcept {
            return lhs.base() != rhs.base();
        }

    template<typename _Iterator, typename _Container>
      inline bool
      operator!=(const Base_Iterator<_Iterator,  _Container>& lhs,
        const Base_Iterator<_Iterator,_Container>& rhs) noexcept {
            return lhs.base() != rhs.base();
        }

    //Random access iterator requirements.
    template<typename _IteratorLhs, typename _IteratorRhs, typename _Container>
      inline bool 
      operator>(const Base_Iterator<_IteratorLhs,  _Container>& lhs,
        const Base_Iterator<_IteratorRhs,_Container>& rhs) noexcept {
            return lhs.base() > rhs.base();
        }

    template<typename _Iterator, typename _Container>
      inline bool
      operator>(const Base_Iterator<_Iterator,  _Container>& lhs,
        const Base_Iterator<_Iterator,_Container>& rhs) noexcept {
            return lhs.base() > rhs.base();
        }

    template<typename _IteratorLhs, typename _IteratorRhs, typename _Container>
      inline bool 
      operator<(const Base_Iterator<_IteratorLhs,  _Container>& lhs,
        const Base_Iterator<_IteratorRhs,_Container>& rhs) noexcept {
            return lhs.base() < rhs.base();
        }

    template<typename _Iterator, typename _Container>
      inline bool
      operator<(const Base_Iterator<_Iterator,  _Container>& lhs,
        const Base_Iterator<_Iterator,_Container>& rhs) noexcept {
            return lhs.base() < rhs.base();
        }

    template<typename _IteratorLhs, typename _IteratorRhs, typename _Container>
      inline bool 
      operator>=(const Base_Iterator<_IteratorLhs,  _Container>& lhs,
        const Base_Iterator<_IteratorRhs,_Container>& rhs) noexcept {
            return lhs.base() >= rhs.base();
        }

    template<typename _Iterator, typename _Container>
      inline bool
      operator>=(const Base_Iterator<_Iterator,  _Container>& lhs,
        const Base_Iterator<_Iterator,_Container>& rhs) noexcept {
            return lhs.base() >= rhs.base();
        }

    template<typename _IteratorLhs, typename _IteratorRhs, typename _Container>
      inline bool 
      operator<=(const Base_Iterator<_IteratorLhs,  _Container>& lhs,
        const Base_Iterator<_IteratorRhs,_Container>& rhs) noexcept {
            return lhs.base() <= rhs.base();
        }

    template<typename _Iterator, typename _Container>
      inline bool
      operator<=(const Base_Iterator<_Iterator,  _Container>& lhs,
        const Base_Iterator<_Iterator,_Container>& rhs) noexcept {
            return lhs.base() <= rhs.base();
        }

}

#endif