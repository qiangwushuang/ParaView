/*=========================================================================

   Program:   ParaQ
   Module:    pqChartValue.h

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaQ is a free software; you can redistribute it and/or modify it
   under the terms of the ParaQ license version 1.1. 

   See License_v1.1.txt for the full ParaQ license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

/*!
 * \file pqChartValue.h
 *
 * \brief
 *   The pqChartValue class is used to store a number that can be
 *   one of three types: int, float, or double.
 *
 * \author Mark Richardson
 * \date   May 10, 2005
 */

#ifndef _pqChartValue_h
#define _pqChartValue_h

#include "QtChartExport.h"
#include <QString> // Needed for QString return type.

class pqChartValueListData;
class pqChartValueIteratorData;
class pqChartValueConstIteratorData;


/// \class pqChartValue
/// \brief
///   The pqChartValue class is used to store a number that can be
///   one of three types: int, float, or double.
///
/// This union of numeric types allows a chart to handle numeric data
/// of different types without using a template. All the operators
/// make it simple to use values of different types because the
/// conversion is done under the covers. The increment and decrement
/// operators are implemented using the machine floating point epsilon
/// for non-integer types, which is useful when doing boolean operations
/// on selection ranges.
class QTCHART_EXPORT pqChartValue
{
public:
  enum ValueType {
    IntValue,
    FloatValue,
    DoubleValue
  };

public:
  /// \brief
  ///   Creates a chart value object.
  ///
  /// The value created is an integer type with a value of zero.
  pqChartValue();

  /// \brief
  ///   Used to copy another chart value.
  /// \param value The value to store.
  pqChartValue(const pqChartValue &value);

  /// \brief
  ///   Creates a chart value to store an integer.
  /// \param value The value to store.
  pqChartValue(int value);

  /// \brief
  ///   Creates a chart value to store a float.
  /// \param value The value to store.
  pqChartValue(float value);

  /// \brief
  ///   Creates a chart value to store a float.
  /// \param value The value to store.
  pqChartValue(double value);
  ~pqChartValue() {}

  /// \brief
  ///   Gets the type of value stored.
  /// \return
  ///   The type of value stored.
  ValueType getType() const {return this->Type;}

  /// \brief
  ///   Converts the value stored to the specified type.
  /// \param type The type to cast the value to.
  void convertTo(ValueType type);

  /// \brief
  ///   Stores an integer value.
  /// \param value The value to store.
  void setValue(int value);

  /// \brief
  ///   Stores a float value.
  /// \param value The value to store.
  void setValue(float value);

  /// \brief
  ///   Stores a double value.
  /// \param value The value to store.
  void setValue(double value);

  /// \brief
  ///   Gets the value as an integer.
  ///
  /// If the value stored is not an integer, it will be cast
  /// to one.
  ///
  /// \return
  ///   The value as an integer.
  int getIntValue() const;

  /// \brief
  ///   Gets the value as a float.
  ///
  /// If the value stored is not a float, it will be cast
  /// to one.
  ///
  /// \return
  ///   The value as a float.
  float getFloatValue() const;

  /// \brief
  ///   Gets the value as a double.
  ///
  /// If the value stored is not a double, it will be cast
  /// to one.
  ///
  /// \return
  ///   The value as a double.
  double getDoubleValue() const;

  /// \brief
  ///   Gets a string representation of the value.
  ///
  /// If the value is a floating point type, the precision
  /// will determine how many decimal places will be printed.
  /// The number will be printed in exponential notation if
  /// it is shorter.
  ///
  /// \param precision The floating point precision.
  /// \return
  ///   A string representation of the value.
  QString getString(int precision=2) const;

  /// \name Operators
  //@{
  /// Assigns the value from another chart value.
  pqChartValue &operator=(const pqChartValue &value);

  /// Assigns the value from an integer.
  pqChartValue &operator=(int value);

  /// Assigns the value from a float.
  pqChartValue &operator=(float value);

  /// Assigns the value from a double.
  pqChartValue &operator=(double value);

  /// Casts the value to an integer.
  operator int() const {return getIntValue();}

  /// Casts the value to a float.
  operator float() const {return getFloatValue();}

  /// Casts the value to a double.
  operator double() const {return getDoubleValue();}

  /// \brief
  ///   Increments the value.
  ///
  /// If the value is not an integer type, the value is increased
  /// by the machine epsilon for the type.
  pqChartValue &operator++();

  /// \brief
  ///   Post-increments the value.
  ///
  /// If the value is not an integer type, the value is increased
  /// by the machine epsilon for the type.
  ///
  /// \param post A placeholder to determine the operator.
  pqChartValue operator++(int post);

  /// \brief
  ///   Decrements the value.
  ///
  /// If the value is not an integer type, the value is decreased
  /// by the machine epsilon for the type.
  pqChartValue &operator--();

  /// \brief
  ///   Post-decrements the value.
  ///
  /// If the value is not an integer type, the value is decreased
  /// by the machine epsilon for the type.
  ///
  /// \param post A placeholder to determine the operator.
  pqChartValue operator--(int post);

  /// Adds two chart values.
  pqChartValue operator+(const pqChartValue &value) const;

  /// Adds a chart value and an integer.
  pqChartValue operator+(int value) const;

  /// Adds a chart value and a float.
  pqChartValue operator+(float value) const;

  /// Adds a chart value and a double.
  pqChartValue operator+(double value) const;

  /// Subtracts two chart values.
  pqChartValue operator-(const pqChartValue &value) const;

  /// Subtracts a chart value and an integer.
  pqChartValue operator-(int value) const;

  /// Subtracts a chart value and a float.
  pqChartValue operator-(float value) const;

  /// Subtracts a chart value and a double.
  pqChartValue operator-(double value) const;

  /// Multiplies two chart values.
  pqChartValue operator*(const pqChartValue &value) const;

  /// Multiplies a chart value and an integer.
  pqChartValue operator*(int value) const;

  /// Multiplies a chart value and a float.
  pqChartValue operator*(float value) const;

  /// Multiplies a chart value and a double.
  pqChartValue operator*(double value) const;

  /// Divides two chart values.
  pqChartValue operator/(const pqChartValue &value) const;

  /// Divides a chart value and an integer.
  pqChartValue operator/(int value) const;

  /// Divides a chart value and a float.
  pqChartValue operator/(float value) const;

  /// Divides a chart value and a double.
  pqChartValue operator/(double value) const;

  /// Adds another value to this one and stores the result.
  pqChartValue &operator+=(const pqChartValue &value);

  /// Adds an integer to this value and stores the result.
  pqChartValue &operator+=(int value);

  /// Adds a float to this value and stores the result.
  pqChartValue &operator+=(float value);

  /// Adds a double to this value and stores the result.
  pqChartValue &operator+=(double value);

  /// Subtracts another value from this one and stores the result.
  pqChartValue &operator-=(const pqChartValue &value);

  /// Subtracts an integer from this value and stores the result.
  pqChartValue &operator-=(int value);

  /// Subtracts a float from this value and stores the result.
  pqChartValue &operator-=(float value);

  /// Subtracts a double from this value and stores the result.
  pqChartValue &operator-=(double value);

  /// Multiplies this value by another and stores the result.
  pqChartValue &operator*=(const pqChartValue &value);

  /// Multiplies this value by an integer and stores the result.
  pqChartValue &operator*=(int value);

  /// Multiplies this value by a float and stores the result.
  pqChartValue &operator*=(float value);

  /// Multiplies this value by a double and stores the result.
  pqChartValue &operator*=(double value);

  /// Divides this value by another and stores the result.
  pqChartValue &operator/=(const pqChartValue &value);

  /// Divides this value by an integer and stores the result.
  pqChartValue &operator/=(int value);

  /// Divides this value by a float and stores the result.
  pqChartValue &operator/=(float value);

  /// Divides this value by a double and stores the result.
  pqChartValue &operator/=(double value);

  /// Compares this chart value to another one.
  bool operator==(const pqChartValue &value) const;

  /// Compares this chart value to an integer.
  bool operator==(int value) const;

  /// Compares this chart value to a float.
  bool operator==(float value) const;

  /// Compares this chart value to a double.
  bool operator==(double value) const;

  /// Compares this chart value to another one.
  bool operator!=(const pqChartValue &value) const;

  /// Compares this chart value to an integer.
  bool operator!=(int value) const;

  /// Compares this chart value to a float.
  bool operator!=(float value) const;

  /// Compares this chart value to a double.
  bool operator!=(double value) const;

  /// Compares this chart value to another one.
  bool operator>(const pqChartValue &value) const;

  /// Compares this chart value to an integer.
  bool operator>(int value) const;

  /// Compares this chart value to a float.
  bool operator>(float value) const;

  /// Compares this chart value to a double.
  bool operator>(double value) const;

  /// Compares this chart value to another one.
  bool operator<(const pqChartValue &value) const;

  /// Compares this chart value to an integer.
  bool operator<(int value) const;

  /// Compares this chart value to a float.
  bool operator<(float value) const;

  /// Compares this chart value to a double.
  bool operator<(double value) const;

  /// Compares this chart value to another one.
  bool operator>=(const pqChartValue &value) const;

  /// Compares this chart value to an integer.
  bool operator>=(int value) const;

  /// Compares this chart value to a float.
  bool operator>=(float value) const;

  /// Compares this chart value to a double.
  bool operator>=(double value) const;

  /// Compares this chart value to another one.
  bool operator<=(const pqChartValue &value) const;

  /// Compares this chart value to an integer.
  bool operator<=(int value) const;

  /// Compares this chart value to a float.
  bool operator<=(float value) const;

  /// Compares this chart value to a double.
  bool operator<=(double value) const;
  //@}

private:
  ValueType Type; ///< Stores the value type.
  union {
    int Int;
    float Float;
    double Double;
  } Value; ///< Stores the value as an int, float, or double.
};


class pqChartValueConstIterator;

/// \class pqChartValueIterator
/// \brief
///   The pqChartValueIterator class is used to iterate through
///   a pqChartValueList.
class QTCHART_EXPORT pqChartValueIterator
{
  friend class pqChartValueList;
  friend class pqChartValueConstIterator;

public:
  pqChartValueIterator();
  pqChartValueIterator(const pqChartValueIterator &iter);
  ~pqChartValueIterator();

  bool operator==(const pqChartValueIterator &iter) const;
  bool operator!=(const pqChartValueIterator &iter) const;
  bool operator==(const pqChartValueConstIterator &iter) const;
  bool operator!=(const pqChartValueConstIterator &iter) const;

  const pqChartValue &operator*() const;
  pqChartValue &operator*();
  pqChartValue *operator->();

  pqChartValueIterator &operator++();
  pqChartValueIterator operator++(int post);

  pqChartValueIterator &operator=(const pqChartValueIterator &iter);

private:
  pqChartValueIteratorData *Data;
};


/// \class pqChartValueConstIterator
/// \brief
///   The pqChartValueConstIterator class is used to iterate
///   through a pqChartValueList.
class QTCHART_EXPORT pqChartValueConstIterator
{
  friend class pqChartValueList;
  friend class pqChartValueIterator;

public:
  pqChartValueConstIterator();
  pqChartValueConstIterator(const pqChartValueIterator &iter);
  pqChartValueConstIterator(const pqChartValueConstIterator &iter);
  ~pqChartValueConstIterator();

  bool operator==(const pqChartValueConstIterator &iter) const;
  bool operator!=(const pqChartValueConstIterator &iter) const;
  bool operator==(const pqChartValueIterator &iter) const;
  bool operator!=(const pqChartValueIterator &iter) const;

  const pqChartValue &operator*() const;
  const pqChartValue *operator->() const;

  pqChartValueConstIterator &operator++();
  pqChartValueConstIterator operator++(int post);

  pqChartValueConstIterator &operator=(const pqChartValueConstIterator &iter);
  pqChartValueConstIterator &operator=(const pqChartValueIterator &iter);

private:
  pqChartValueConstIteratorData *Data;
};

/*!
 *  \class pqChartValueList
 *  \brief
 *    The pqChartValueList class contains a list of pqChartValue
 *    objects.
 * 
 *  The list can be navigated using a value list iterator. There
 *  are iterators available for mutable and immutable lists. The
 *  following example shows how to iterate through the list:
 * 
 *  \code
 *  pqChartValueList::Iterator iter = list.begin();
 *  for( ; iter != list.end(); ++iter)
 *  {
 *     ...
 *  }
 *  \endcode
 */
class QTCHART_EXPORT pqChartValueList
{
public:
  typedef pqChartValueIterator Iterator;
  typedef pqChartValueConstIterator ConstIterator;

public:
  pqChartValueList();
  ~pqChartValueList();

  /// \name List Navigation Methods
  //@{
  /// \brief
  ///   Gets an iterator to the beginning of the list.
  /// \return
  ///   An iterator to the beginning of the list.
  Iterator begin();

  /// \brief
  ///   Gets an iterator to the end of the list.
  /// \return
  ///   An iterator to the end of the list.
  Iterator end();

  /// \brief
  ///   Gets an iterator to the beginning of an immutable list.
  /// \return
  ///   An iterator to the beginning of an immutable list.
  ConstIterator begin() const;

  /// \brief
  ///   Gets an iterator to the end of an immutable list.
  /// \return
  ///   An iterator to the end of an immutable list.
  ConstIterator end() const;

  /// \brief
  ///   Gets an iterator to the beginning of an immutable list.
  /// \return
  ///   An iterator to the beginning of an immutable list.
  ConstIterator constBegin() const;

  /// \brief
  ///   Gets an iterator to the end of an immutable list.
  /// \return
  ///   An iterator to the end of an immutable list.
  ConstIterator constEnd() const;

  /// \return
  ///   True if the list is empty.
  bool isEmpty() const;

  /// \return
  ///   The number of items in the list.
  int getSize() const;
  //@}

  /// \name List Modification Methods
  //@{
  /// \brief
  ///   Clears all the chart value items from the list.
  void clear();

  /// \brief
  ///   Appends a new chart value item to the end of the list.
  /// \param value The new chart value to append.
  void pushBack(const pqChartValue &value);
  //@}

  /// \name Operators
  //@{
  /// \brief
  ///   Makes a copy of another list.
  /// \param list The list of chart value items to copy.
  /// \return
  ///   A reference to the value list.
  pqChartValueList &operator=(const pqChartValueList &list);

  /// \brief
  ///   Appends a list of chart value items to this list.
  /// \param list The list of value items to add.
  /// \return
  ///   A reference to the value list.
  pqChartValueList &operator+=(const pqChartValueList &list);
  //@}

private:
  pqChartValueListData *Data; ///< Stores the list of values.
};


/// \relates pqChartValue
/// \brief
///   Adds an integer and a chart value object.
int operator+(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Adds a float and a chart value object.
float operator+(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Adds a double and a chart value object.
double operator+(double value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Subtracts an integer and a chart value object.
int operator-(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Subtracts a float and a chart value object.
float operator-(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Subtracts a double and a chart value object.
double operator-(double value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Multiplies an integer and a chart value object.
int operator*(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Multiplies a float and a chart value object.
float operator*(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Multiplies a double and a chart value object.
double operator*(double value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Divides an integer and a chart value object.
int operator/(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Divides a float and a chart value object.
float operator/(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Divides a double and a chart value object.
double operator/(double value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares an integer and a chart value object.
bool operator==(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a float and a chart value object.
bool operator==(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a double and a chart value object.
bool operator==(double value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares an integer and a chart value object.
bool operator!=(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a float and a chart value object.
bool operator!=(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a double and a chart value object.
bool operator!=(double value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares an integer and a chart value object.
bool operator>(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a float and a chart value object.
bool operator>(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a double and a chart value object.
bool operator>(double value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares an integer and a chart value object.
bool operator<(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a float and a chart value object.
bool operator<(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a double and a chart value object.
bool operator<(double value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares an integer and a chart value object.
bool operator>=(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a float and a chart value object.
bool operator>=(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a double and a chart value object.
bool operator>=(double value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares an integer and a chart value object.
bool operator<=(int value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a float and a chart value object.
bool operator<=(float value1, const pqChartValue &value2);

/// \relates pqChartValue
/// \brief
///   Compares a double and a chart value object.
bool operator<=(double value1, const pqChartValue &value2);

#endif
