# String
**因为std::string中有一些地方为了保证空间与时间的平衡从而采用了在时间上较为保守的方式 所以我在此基础上略微的打破了这个平衡 使得更追求时间效率.**

## 做了什么
 1. char_traits<_CharT>中的比较方法较为低效 为逐字符比较 导致basic_string中find系方法较为低效 为O(n2), 遂改为内部使用strstr()函数,也可改为kmp,两者效率差不多,以此提升字符串比较的效率.
 2. 在string的动态扩容中同样对应着容量动态减小,标准库中的做法是遇到容量减小时直接使用alloctor销毁原来大块内存,然后分配小块内存,这样会涉及多余的内存分配,在我的实现中,为了保证时间,取消的容量减小
 3. 在移动构造函数中同样存在着上述问题 即减小容量的问题 在我的移动构造函数的实现中我取消了容量减小这一步 以追求更少的时间
 4. 标准库中的shrink_to_fi实现几乎是没有意义的 仅有一种情况有意义 即length小于初始容量(短字符串优化)时会释放alloctor中分配的内存, 但对于其他情况就没有任何意义了 所以我简单的对这个函数做了功能上的完善 即在length大于初始容量时这个函数可以做它该做的事情 即减少容量至length.(还在修改)
 5. 项目中实现了迭代器板块(base_iterator, reverse_iterator),实现参考标准库中实现,可把本项目中的迭代器操作直接放在标准库中的泛型算法中进行使用.


## 需要改进之处

 1. 前期因为懒,在扩容中没有使用移动,使得拷贝效率较低,这是改进的一个方向
 2. 不能兼容string_view 那部分的元编程最近没有时间深究
 3. 对于wstring,u16string, u32string还未编写char_traits部分
 4. 中间有一阵脑子比较乱,对于_Return_pointer()这个操作在一些函数中分成了两部写 但这是没有一点必要的,因为初始化时静态数组的值已经赋给了_True_value,这是一个重大的败笔,大概有几十处的使用错误,还未修改
 5. 未编写输入部分

## 结论

 1. 大致看了一遍string的源码后我的感觉就是标准库中的string操作大都是十分简单的,但有一点不好实现,即输入部分,标准库中的实现是把所有的值放到输入流中 然后从流中取出数据append到string中 再去动态扩容, 这个操作对于我们来说是不好实现的,所以string的一大左右就是**无限制的输入**
 2. std::string没有网上说的那么不堪,至少实现的功能绝对是很好的,虽然功能很少,效率不高,可以的情况下使用string_view.
 3. 搞清楚了迭代器到底是什么,那句**广义上的指针**一点也没错,
 4. 善用标准库.
