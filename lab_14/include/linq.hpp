#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <memory>
#include <cassert>

namespace linq {
  namespace impl {
    template<typename T, typename Iter>
    class range_enumerator;
    template<typename T>
    class drop_enumerator;
    template<typename T, typename U, typename F>
    class select_enumerator;
    template<typename T, typename F>
    class until_enumerator;
    template<typename T>
    class take_enumerator;
    template<typename T>
    class until_eq_enumerator;
    template<typename T>
    class where_neq_enumerator;
    template <typename T, typename F>
    class where_enumerator;

    template<typename T>
    class enumerator {
    public:
      virtual const T& operator*() = 0; // Получает текущий элемент
      virtual void operator++() = 0;  // Переход к следующему элементу
      virtual operator bool() = 0;  // Возвращает true, если есть текущий элемент

      auto drop(int count) {
        return drop_enumerator<T>(*this, count);
      }

      auto take(int count) {
        return take_enumerator<T>(*this, count);
      }

      template<typename U = T, typename F>
      auto select(F func) {
        return select_enumerator<U, T, F>(*this, std::move(func));
      }

      template<typename F>
      auto until(F func) {
        return until_enumerator<T, F>(*this, std::move(func));
      }

      template<typename F>
      auto where(F func) {
        return where_enumerator<T, F>(*this, func);
      }

      auto until_eq(T comp) {
        return until_eq_enumerator<T>(*this, std::move(comp));
      }

      auto where_neq(T elem) {
        return where_neq_enumerator<T>(*this, std::move(elem));
      }

      std::vector<T> to_vector() {
        std::vector<T> v;
        while (*this) {
          v.push_back(*(*this));
          ++* this;
        }

        return v;
      }

      template<typename Iter>
      void copy_to(Iter&& it) {
        while (*this) {
          *it = *(*this);
          ++it, ++(*this);
        }
      }
    };

    template<typename T, typename Iter>
    class range_enumerator : public enumerator<T> {
    public:
      range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

      const T& operator*() override {
        return *begin_;
      }

      void operator++() override {
        assert(begin_ != end_);
        ++begin_;
      }

      operator bool() override {
        return begin_ != end_;
      }

    private:
      Iter begin_, end_;
    };

    template<typename T>
    class drop_enumerator : public enumerator<T> {
    public:
      drop_enumerator(enumerator<T>& parent, int count) : count_{ count }, parent_(parent) {
        while (count_ && static_cast<bool>(parent)) {
          ++parent_;
          --count_;
        }

        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      const T& operator*() override {
        return cached;
      }

      void operator++() override {
        ++parent_;

        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      operator bool() override {
        return static_cast<bool>(parent_);
      }

    private:
      int count_;
      enumerator<T>& parent_;
      T cached;
    };

    template<typename T>
    class take_enumerator : public enumerator<T> {
    public:
      take_enumerator(enumerator<T>& parent, int count) : parent_{ parent }, count_{ count } {
        if (count_ && static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      operator bool() override {
        return static_cast<bool>(parent_) && static_cast<bool>(count_);
      }

      void operator++() override {
        --count_;
        ++parent_;
        
        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      const T& operator*() override {
        return cached;
      }

    private:
      enumerator<T>& parent_;
      int count_;
      T cached;
    };

    template<typename T, typename U, typename F>
    class select_enumerator : public enumerator<T> {
    public:
      select_enumerator(enumerator<U>& parent, F func) : parent_{ parent }, func_{ std::move(func) }  {
        if (static_cast<bool>(parent_))
          cached = func_(*parent_);
      }

      const T& operator*() override {
        return cached;
      }

      void operator++() override {
        ++parent_;

        if (static_cast<bool>(parent_))
          cached = func_(*parent_);
      }

      operator bool() override {
        return static_cast<bool>(parent_);
      }

    private:
      enumerator<U>& parent_;
      F func_;
      T cached;
    };

    template<typename T, typename F>
    class until_enumerator : public enumerator<T> {
    public:
      until_enumerator(enumerator<T>& parent, F predicate) : parent_{ parent }, predicate_{ std::move(predicate) } {
        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      const T& operator*() override {
        return cached;
      }

      void operator++() override {
        ++parent_;
        
        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      operator bool() override {
        return static_cast<bool>(parent_) && !predicate_(cached);
      }

    private:
      F predicate_;
      enumerator<T>& parent_;
      T cached;
    };

    template<typename T>
    class until_eq_enumerator : public enumerator<T> {
    public:
      until_eq_enumerator(enumerator<T>& parent, T comp) : parent_{ parent }, comp_{ comp } {
        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      void operator++() override {
        ++parent_;

        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      const T& operator*() override {
        return cached;
      }

      operator bool() override {
        return static_cast<bool>(parent_) && cached != comp_;
      }
    private:
      enumerator<T>& parent_;
      T comp_;
      T cached;
    };

    template<typename T>
    class where_neq_enumerator : public enumerator<T> {
    public:
      where_neq_enumerator(enumerator<T>& parent, T elem) : parent_{ parent }, elem_{ std::move(elem) } {
        while (static_cast<bool>(parent_) && *parent_ == elem_)
          ++parent_;

        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      const T& operator*() override {
        return cached;
      }

      void operator++() override {
        while (static_cast<bool>(parent_)) {
          ++parent_;
          
          if (*parent_ != elem_)
            break; 
        }

        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      operator bool() override {
        return static_cast<bool>(parent_);
      }

      enumerator<T>& parent_;
      T elem_;
      T cached;
    };

    template <typename T, typename F>
    class where_enumerator : public enumerator<T> {
    public:
      where_enumerator(enumerator<T>& parent, F func) : parent_{ parent }, func_{ std::move(func) } {
        while (static_cast<bool>(parent_) && !func_(*parent_))
          ++parent_;

        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      const T& operator*() {
        return cached;
      }

      operator bool() {
        return static_cast<bool>(parent_);
      }

      void operator++() {
        do
          ++parent_;
        while (static_cast<bool>(parent_) && !func_(*parent_));

        if (static_cast<bool>(parent_))
          cached = std::move(*parent_);
      }

      enumerator<T>& parent_;
      F func_;
      T cached;
    };
  } // namespace impl

  template<typename Iter>
  auto from(Iter begin, Iter end) {
    return impl::range_enumerator<typename std::iterator_traits<Iter>::value_type, Iter>(begin, end);
  }

} // namespace linq

#endif