// ============================================================================================== //
//                                                                                                //
//   This file is part of the CoSeSt2 project.                                                    //
//                                                                                                //
//   Author:                                                                                      //
//   Marcel Hasler <mahasler@gmail.com>                                                           //
//                                                                                                //
//   Original concept by Sebastian Sporrer                                                        //
//                                                                                                //
//   Copyright (c) 2019 - 2023                                                                    //
//   Bonn-Rhein-Sieg University of Applied Sciences                                               //
//                                                                                                //
//   Redistribution and use in source and binary forms, with or without modification,             //
//   are permitted provided that the following conditions are met:                                //
//                                                                                                //
//   1. Redistributions of source code must retain the above copyright notice,                    //
//      this list of conditions and the following disclaimer.                                     //
//                                                                                                //
//   2. Redistributions in binary form must reproduce the above copyright notice,                 //
//      this list of conditions and the following disclaimer in the documentation                 //
//      and/or other materials provided with the distribution.                                    //
//                                                                                                //
//   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"                  //
//   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED            //
//   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.           //
//   IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,             //
//   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT           //
//   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR           //
//   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,            //
//   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)           //
//   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE                   //
//   POSSIBILITY OF SUCH DAMAGE.                                                                  //
//                                                                                                //
// ============================================================================================== //

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include "CoSeSt2.h"

#include <QDateTime>

/*
 *  If set to CoSeSt::StorageType::Global (corresponding to standard QSettings behavior),
 *  QCoreApplication::setOrganizationName() and QCoreApplication::setApplicationName()
 *  must be called before using loadFromDisk() or saveToDisk().
 */
constexpr CoSeSt::StorageType StorageType = CoSeSt::StorageType::Local;

/*
 *  If COSEST_BEGIN is used without the second parameter,
 *  CoSeSt::StorageType::Local is assumed by default
 */
COSEST_BEGIN(Settings, StorageType)
  COSEST_ENTRY(bool, BoolValue, false)
  COSEST_ENTRY(QString, StringValue, "")
  COSEST_ENTRY(int, IntValue, 0)
  COSEST_ENTRY(double, DoubleValue, 1.0)
  COSEST_ENTRY(QDateTime, DateTime, QDateTime::currentDateTime())

  COSEST_BEGIN_GROUP(Test)
    COSEST_ENTRY(bool, BoolValue, false)
    COSEST_ENTRY(int, IntValue, 0)
  COSEST_END_GROUP(Test)
COSEST_END

/*
 *  Third argument to COSEST_ENTRY is optional, if none is given,
 *  the default value for the given type is used
 */
COSEST_BEGIN(MoreSettings)
  COSEST_ENTRY(bool, BoolValue)
  COSEST_ENTRY(int, IntValue)
COSEST_END

/*
 *  Use COSEST_BEGIN_BASE to create an abstract base class,
 *  use COSEST_GET_INSTANCE(classname) to define an instance
 *  access method in your custom class
 */
COSEST_BEGIN_BASE(BaseSettings)
  COSEST_ENTRY(bool, BoolValue, false)
  COSEST_ENTRY(unsigned int, EnumIndex, 1)
COSEST_END_BASE

class CustomSettings : public BaseSettings
{
    COSEST_GET_INSTANCE(CustomSettings)

public:
    enum class Enum
    {
        Value0,
        Value1,
        Value2,
        Value3
    };

    static constexpr size_t EnumCount = 4;

    auto getEnum() const -> Enum
    {
        unsigned int index = getEnumIndex();

        if (index >= EnumCount)
            throw std::runtime_error("Invalid Enum index in settings file.");

        return static_cast<Enum>(index);
    }

private:
    /*
     *  Optional: Set name to save the settings under.
     *  You could also call loadFromDisk() in the constructor
     *  and validate the values stored in the settings file
     */
    CustomSettings() : BaseSettings("CustomSettings") {}
};

#endif // EXAMPLE_H
