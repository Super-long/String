#ifndef _ITERATOR_H_
#define _ITERATOR_H_

namespace String{
    template<typename Iterator_, typename Container_>
    class Base_Iterator{
        protected: //will write a reverse iterator.
            Iterator_ Value_;
        
            using Iterator_traits = iterator_traits<_Iterator>;

        public:
            //This is only for strings.
            //using iterator_category = random_access_itreator_tag;

            using Iterator_					iterator_type;
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
            
            
    };
}

#endif