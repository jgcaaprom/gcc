// { dg-do run }
// { dg-options "-g -O0 -std=gnu++14" }

// Copyright (C) 2014-2016 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// Type printers only recognize the old std::string for now.
#define _GLIBCXX_USE_CXX11_ABI 0

#include <experimental/any>
#include <experimental/optional>
#include <experimental/string_view>
#include <string>
#include <map>

using std::experimental::any;
using std::experimental::optional;
using std::experimental::string_view;

int
main()
{
  string_view str = "string";
// { dg-final { note-test str "\"string\"" } }

  optional<int> o;
// { dg-final { note-test o {std::experimental::optional<int> [no contained value]} } }
  optional<bool> ob{false};
// { dg-final { note-test ob {std::experimental::optional<bool> = {[contained value] = false}} } }
  optional<int> oi{5};
// { dg-final { note-test oi {std::experimental::optional<int> = {[contained value] = 5}} } }
  optional<void*> op{nullptr};
// { dg-final { note-test op {std::experimental::optional<void *> = {[contained value] = 0x0}} } }
  optional<std::map<int, double>> om;
  om = std::map<int, double>{ {1, 2.}, {3, 4.}, {5, 6.} };
// { dg-final { note-test om {std::experimental::optional<std::map<int, double>> containing std::map with 3 elements = {[1] = 2, [3] = 4, [5] = 6}} } }
  optional<std::string> os{ "stringy" };
// { dg-final { note-test os {std::experimental::optional<std::string> = {[contained value] = "stringy"}} } }

  any a;
// { dg-final { note-test a {std::experimental::any [no contained value]} } }
  any ab(false);
// { dg-final { note-test ab {std::experimental::any containing bool = {[contained value] = false}} } }
  any ai(6);
// { dg-final { note-test ai {std::experimental::any containing int = {[contained value] = 6}} } }
  any ap = (void*)nullptr;
// { dg-final { note-test ap {std::experimental::any containing void * = {[contained value] = 0x0}} } }
  any as = *os;
// { dg-final { note-test as {std::experimental::any containing std::string = {[contained value] = "stringy"}} } }
  any as2("stringiest");
// { dg-final { regexp-test as2 {std::experimental::any containing const char \* = {\[contained value\] = 0x[[:xdigit:]]+ "stringiest"}} } }
  any am = *om;
// { dg-final { note-test am {std::experimental::any containing std::map with 3 elements = {[1] = 2, [3] = 4, [5] = 6}} } }

  return 0;			// Mark SPOT
}

// { dg-final { gdb-test SPOT } }
