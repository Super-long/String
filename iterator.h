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
        protected:
            Iterator_ Value_;
            using Iterator_traits = iterator_traits<Iterator_>;

        public:
            using Iterator_type = Iterator_;
            using iterator_category = typename Iterator_traits::iterator_category;
            using value_type = typename Iterator_traits::value_type;
            using difference_type = typename Iterator_traits::difference_type;
            using reference = typename Iterator_traits::reference;
            using pointer = typename Iterator_traits::pointer;

            constexpr Reverse_Iterator() :
                Value_(){}
            

            explicit constexpr Reverse_Iterator(Iterator_ para) :
                Value_(para){}

            constexpr Reverse_Iterator(const Reverse_Iterator& para) :
                Value_(para.Value_){}

            template<typename Iter>
            constexpr Reverse_Iterator(const Reverse_Iterator<Iter>& para) :
                Value_(para.base()){}

            constexpr Iterator_type
            base() const {
                return Value_;
            }

            constexpr reference
            operator*() const {
                Iterator_ Temp = Value_;
                return *--Temp;
            }

            constexpr reference
            operator->() const {
                return &(operator*());//For convenience.
            }

            constexpr Reverse_Iterator&
            operator++(){
                --Value_;
                return *this;
            }

            constexpr Reverse_Iterator&
            operator++(int){
                Reverse_Iterator Temp = *this;
                --Value_;
                return Temp;
            }

            constexpr Reverse_Iterator&
            operator--(){
                ++Value_;
                return *this;
            }

            constexpr Reverse_Iterator&
            operator--(int){
                Reverse_Iterator Temp = *this;
                ++Value_;
                return Temp;
            }

            constexpr Reverse_Iterator
            operator+(difference_type n) const {
                return Reverse_Iterator(Value_ - n);
            }

            constexpr Reverse_Iterator
            operator-(difference_type n) const {
                return Reverse_Iterator(Value_ + n);
            }

            constexpr Reverse_Iterator
            operator+=(difference_type n){
                Value_ -= n;
                return *this;
            }

            constexpr Reverse_Iterator
            operator-=(difference_type n){
                Value_ += n;
                return *this;
            }

            constexpr reference
            operator[](difference_type n) const{
                return *(*this + n);
            }
    };

    template<typename Iterator_>
      inline constexpr bool
      operator==(const Reverse_Iterator<Iterator_>& lhs,
        const Reverse_Iterator<Iterator_>& rhs){
            return lhs.base() == rhs.base();
        }

    template<typename Iterator_>
      inline constexpr bool
      operator!=(const Reverse_Iterator<Iterator_>& lhs,
        const Reverse_Iterator<Iterator_>& rhs){
            return lhs.base() != rhs.base();
        }

    template<typename Iterator_>
      inline constexpr bool
      operator<(const Reverse_Iterator<Iterator_>& lhs,
        const Reverse_Iterator<Iterator_>& rhs){
            return lhs.base() > rhs.base();
        }

    template<typename Iterator_>
      inline constexpr bool
      operator<=(const Reverse_Iterator<Iterator_>& lhs,
        const Reverse_Iterator<Iterator_>& rhs){
            return !(lhs > rhs);
        }

    template<typename Iterator_>
      inline constexpr bool
      operator>(const Reverse_Iterator<Iterator_>& lhs,
        const Reverse_Iterator<Iterator_>& rhs){
            return lhs.base() < rhs.base();
        }

    template<typename Iterator_>
      inline constexpr bool
      operator>=(const Reverse_Iterator<Iterator_>& lhs,
        const Reverse_Iterator<Iterator_>& rhs){
            return !(lhs < rhs);
        }

    //Comparison of no-const and const.
    template<typename IteratorLhs_, typename IteratorRhs_>
      inline constexpr bool
      operator==(const Reverse_Iterator<IteratorLhs_>& lhs,
        const Reverse_Iterator<IteratorRhs_>& rhs){
            return lhs.base() == rhs.base();
        }
    
    template<typename IteratorLhs_, typename IteratorRhs_>
      inline constexpr bool
      operator!=(const Reverse_Iterator<IteratorLhs_>& lhs,
        const Reverse_Iterator<IteratorRhs_>& rhs){
            return lhs.base() != rhs.base();
        }

    template<typename IteratorLhs_, typename IteratorRhs_>
      inline constexpr bool
      operator<(const Reverse_Iterator<IteratorLhs_>& lhs,
        const Reverse_Iterator<IteratorRhs_>& rhs){
            return lhs.base() > rhs.base();
        }
    
    template<typename IteratorLhs_, typename IteratorRhs_>
      inline constexpr bool
      operator>(const Reverse_Iterator<IteratorLhs_>& lhs,
        const Reverse_Iterator<IteratorRhs_>& rhs){
            return lhs.base() < rhs.base();
        }
    
    template<typename IteratorLhs_, typename IteratorRhs_>
      inline constexpr bool
      operator<=(const Reverse_Iterator<IteratorLhs_>& lhs,
        const Reverse_Iterator<IteratorRhs_>& rhs){
            return !(lhs > rhs);
        }

    template<typename IteratorLhs_, typename IteratorRhs_>
      inline constexpr bool
      operator>=(const Reverse_Iterator<IteratorLhs_>& lhs,
        const Reverse_Iterator<IteratorRhs_>& rhs){
            return !(lhs < rhs);
        }

    template<typename IteratorLhs_, typename IteratorRhs_>
      inline constexpr auto
      operator-(const Reverse_Iterator<IteratorLhs_>& lhs,
        const Reverse_Iterator<IteratorRhs_>& rhs)
        -> decltype(rhs.base() - rhs.base()) {
            return rhs.base() - rhs.base();
        }

    template<typename Iterator_>
    inline constexpr Reverse_Iterator<Iterator_>
    operator+(typename Reverse_Iterator<Iterator_>::difference_type n,
        const Reverse_Iterator<Iterator_>& para){
            return Reverse_Iterator<Iterator_>(para.base() - n);
        }

#if __cplusplus >= 201103L

    template<typename Iterator_>
      inline constexpr Reverse_Iterator<Iterator_>
      make_reverse_iterator(Iterator_ para){
          return Reverse_Iterator<Iterator_>(para);
      }

#endif 

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