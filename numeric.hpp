// vim: set ft=cpp ts=2 sw=2 et :
#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <iostream>

namespace numeric {

//! expression template class for binary operator
template <typename Lhs, typename BinaryOp, typename Rhs>
class expression {
public:
  //! value type of elements
  using value_type = typename Lhs::value_type;

  //! constructor
  expression(Lhs const& lhs, Rhs const& rhs)
      : lhs_(lhs)
      , rhs_(rhs)
  {
  }

  //! element-wise calculation results
  template <typename Idx>
  value_type operator[](Idx i) const { return BinaryOp()(lhs_[i], rhs_[i]); }

  //! size of expression
  size_t size() const
  {
    return static_cast<size_t>(std::min(lhs_.size(), rhs_.size()));
  }

private:
  Lhs const& lhs_;
  Rhs const& rhs_;
};


#define DEFINE_OPERATOR(opname, op)                                            \
  struct opname {                                                              \
    template <typename Lhs, typename Rhs>                                      \
    auto operator()(Lhs const& lhs, Rhs const& rhs) -> Lhs                     \
    {                                                                          \
      return lhs op rhs;                                                       \
    }                                                                          \
  };                                                                           \
  template <typename Lhs, typename Rhs>                                        \
  expression<Lhs, opname, Rhs> operator op(Lhs const& lhs, Rhs const& rhs)     \
  {                                                                            \
    return expression<Lhs, opname, Rhs>(lhs, rhs);                             \
  }

DEFINE_OPERATOR(plus, +);
DEFINE_OPERATOR(minus, -);
DEFINE_OPERATOR(multiply, *);
DEFINE_OPERATOR(divide, / );

#undef DEFINE_OPERATOR


//! vector class
template <typename T>
class vector {
public:
  //! element value type
  using value_type = T;

  vector() = default;
  vector(vector const&) = default;
  vector& operator=(vector const&) = default;

  vector(std::initializer_list<T> src)
      : body_(src)
  {
  }

  //! initialize from expresion template
  template <typename Lhs, typename Op, typename Rhs>
  vector(expression<Lhs, Op, Rhs> const& e)
  {
    body_.resize(e.size());
    for (size_t i = 0; i < e.size(); ++i) {
      body_[i] = e[i];
    }
  }

  //! asssignment from expression template
  template <typename Lhs, typename Op, typename Rhs>
  vector& operator=(expression<Lhs, Op, Rhs> const& e)
  {
    body_.resize(e.size());
    for (size_t i = 0; i < e.size(); ++i) {
      body_[i] = e[i];
    }
    return *this;
  }

  //! accessor
  T& operator[](size_t i) { return body_[i]; }
  T operator[](size_t i) const { return body_[i]; }

  //! size
  size_t size() const { return body_.size(); }

  //! output
  friend std::ostream& operator<<(std::ostream& os, vector const& vec)
  {
    os << "[";
    if (!vec.body_.empty()) {
      os << vec.body_[0];
      for (size_t i = 1; i < vec.body_.size(); ++i) {
        os << ", " << vec.body_[i];
      }
    }
    os << "]";
    return os;
  }

private:
  std::vector<T> body_;
};


//! matrix class
template <typename T>
class matrix {
public:
  //! element value type
  using value_type = T;

  matrix() = default;
  matrix(matrix const&) = default;
  matrix& operator=(matrix const&) = default;

  matrix(std::initializer_list<T> src, std::pair<std::size_t, std::size_t> size)
      : body_(src)
      , size_(size)
  {
  }

  //! initialize from expresion template
  template <typename Lhs, typename Op, typename Rhs>
  matrix(expression<Lhs, Op, Rhs> const& e)
  {
    body_.resize(e.size());
    for (size_t i = 0; i < e.size(); ++i) {
      body_[i] = e[i];
    }
  }

  //! asssignment from expression template
  template <typename Lhs, typename Op, typename Rhs>
  matrix& operator=(expression<Lhs, Op, Rhs> const& e)
  {
    body_.resize(e.size());
    for (size_t i = 0; i < e.size(); ++i) {
      body_[i] = e[i];
    }
    return *this;
  }

  //! accessor
  T& operator[](size_t i) { return body_[i]; }
  T operator[](size_t i) const { return body_[i]; }
  T operator[](std::pair<size_t, size_t> idx) {
    return body_[idx.first * size_.first + idx.second];
  }

  //! size
  size_t size() const { return body_.size(); }

  //! output
  friend std::ostream& operator<<(std::ostream& os, matrix const& vec)
  {
    os << "[";
    if (!vec.body_.empty()) {
      os << vec.body_[0];
      for (size_t i = 1; i < vec.body_.size(); ++i) {
        os << ", " << vec.body_[i];
      }
    }
    os << "]";
    return os;
  }

private:
  std::vector<T> body_;
  std::pair<std::size_t, std::size_t> size_{0,0};
};


} // namespace numeric
