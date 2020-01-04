#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <bits/cpp_type_traits.h>
#include <ext/type_traits.h>
#include <bits/move.h>
#include <bits/ptr_traits.h>
#include <iterator>
#include <iostream>

namespace String{
    using std::iterator_traits;

    template<typename Iterator_>
    class Reverse_Iterator{
        
    };

    
    //TODO: It is unclear what the second parameter means.
    template<typename Iterator_, typename Container_>
    class Base_Iterator{
            //using std::iterator_traits; //can't set there.
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
            template<typename _Iter>
            Base_Iterator(const Base_Iterator<_Iter, 
                    typename std::enable_if<
                    (std::__are_same<_Iter, typename Container_::pointer>::__value),
                    Container_>::__type>& __i) noexcept
            : Value_(__i.base()) {
                int x;
                std::cin >> x ;
                std::cout << "in there.\n";
            }

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

  // Following is library notes. 

  // Note: In what follows, the left- and right-hand-side iterators are
  // allowed to vary in types (conceptually in cv-qualification) so that
  // comparison between cv-qualified and non-cv-qualified iterators be
  // valid.  However, the greedy and unfriendly operators in std::rel_ops
  // will make overload resolution ambiguous (when in scope) if we don't
  // provide overloads whose operands are of the same type.  Can someone
  // remind me what generic programming is about? -- Gaby

  /**
   * In my optional, it's so cool!
   * Reproduction method:
   * delete one para operator, using std::rel_ops and using operator!=.
  */
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

    //My opinion: for distance function. Make it type like a pointer.
    template<typename _IteratorLhs, typename _IteratorRhs, typename _Container>
      inline auto 
      operator-(const Base_Iterator<_IteratorLhs,  _Container>& lhs,
        const Base_Iterator<_IteratorRhs,_Container>& rhs) noexcept
        ->decltype(lhs.base() - rhs.base()){
            return lhs.base() <= rhs.base();
        }

    template<typename _Iterator, typename _Container>
      inline typename Base_Iterator<_Iterator, _Container>::difference_type
      operator-(const Base_Iterator<_Iterator,  _Container>& lhs,
        const Base_Iterator<_Iterator,_Container>& rhs){
            return lhs.base() - rhs.base();
        }
    
    template<typename _Iterator, typename _Container>
      inline Base_Iterator<_Iterator, _Container>
      operator+(const Base_Iterator<_Iterator,  _Container>& para,
      typename Base_Iterator<_Iterator,  _Container>::difference_type n){
          return para.base() + n;
      }

}

#endif