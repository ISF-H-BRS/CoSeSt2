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

#include "example.h"

#include <QCoreApplication>
#include <QDebug>

// ---------------------------------------------------------------------------------------------- //

static void example1() // Demonstrates direct "struct-like" access syntax
{
    Settings* settings = Settings::getInstance();

    auto printValues = [settings]()
    {
        qDebug() << "settings->BoolValue      =" << settings->BoolValue;
        qDebug() << "settings->StringValue    =" << settings->StringValue;
        qDebug() << "settings->IntValue       =" << settings->IntValue;
        qDebug() << "settings->DoubleValue    =" << settings->DoubleValue;
        qDebug() << "settings->DateTime       =" << settings->DateTime;
        qDebug() << "settings->Test.BoolValue =" << settings->Test.BoolValue;
        qDebug() << "settings->Test.IntValue  =" << settings->Test.IntValue;
        qDebug() << "";
    };

    qDebug() << "Example 1 (struct-like)";
    qDebug() << "-----------------------";

    qDebug() << "Initial values:";
    printValues();

    settings->loadFromDisk();

    qDebug() << "Loaded from disk:";
    printValues();

    settings->BoolValue = !settings->BoolValue;
    settings->StringValue = "Hello world!";
    settings->IntValue = settings->IntValue + 1;
    settings->DoubleValue = settings->DoubleValue * 1.01;
    settings->DateTime = settings->DateTime.get().addDays(1);

    settings->Test.BoolValue = !settings->Test.BoolValue;
    settings->Test.IntValue = settings->Test.IntValue + 2;

    qDebug() << "Updated values:";
    printValues();

    settings->saveToDisk();
    qDebug() << "Values saved to disk.";
}

// ---------------------------------------------------------------------------------------------- //

static void example2() // Demonstrates object-oriented access syntax using setter/getter methods
{
    Settings* settings = Settings::getInstance();

    auto printValues = [settings]()
    {
        qDebug() << "settings->getBoolValue()                 =" << settings->getBoolValue();
        qDebug() << "settings->getStringValue()               =" << settings->getStringValue();
        qDebug() << "settings->getIntValue()                  =" << settings->getIntValue();
        qDebug() << "settings->getDoubleValue()               =" << settings->getDoubleValue();
        qDebug() << "settings->getDateTime()                  =" << settings->getDateTime();
        qDebug() << "settings->getTestGroup()->getBoolValue() ="
                 <<  settings->getTestGroup()->getBoolValue();
        qDebug() << "settings->getTestGroup()->getIntValue()  ="
                 <<  settings->getTestGroup()->getIntValue();
        qDebug() << "";
    };

    qDebug() << "Example 2 (object-oriented)";
    qDebug() << "---------------------------";

    qDebug() << "Initial values:";
    printValues();

    settings->loadFromDisk();

    qDebug() << "Loaded from disk:";
    printValues();

    settings->setBoolValue(!settings->getBoolValue());
    settings->setStringValue("Hello world!");
    settings->setIntValue(settings->getIntValue() + 1);
    settings->setDoubleValue(settings->getDoubleValue() * 1.01);
    settings->setDateTime(settings->getDateTime().addDays(1));

    Settings::TestGroup* test = settings->getTestGroup();
    test->setBoolValue(!test->getBoolValue());
    test->setIntValue(test->getIntValue() + 2);

    qDebug() << "Updated values:";
    printValues();

    settings->saveToDisk();
    qDebug() << "Values saved to disk.";
}

// ---------------------------------------------------------------------------------------------- //

auto main(int argc, char* argv[]) -> int
{
    QCoreApplication::setOrganizationName("Bonn-Rhein-Sieg University of Applied Sciences");
    QCoreApplication::setApplicationName("CoSeSt2 Example");

    if (argc != 2)
    {
        qDebug() << "Usage:" << argv[0] << "<1 or 2>";
        return -1;
    }

    QString index(argv[1]);

    if (index == "1")
        example1();
    else if (index == "2")
        example2();
    else
    {
        qDebug() << "Invalid argument, only 1 and 2 are allowed.";
        return -1;
    }

    // CoSeSt2 supports more than one settings class
    MoreSettings* settings = MoreSettings::getInstance();
    settings->loadFromDisk();

    settings->BoolValue = !settings->BoolValue;
    settings->IntValue = settings->IntValue - 1;

    settings->saveToDisk();

    // Read settings from a custom class
    CustomSettings* custom = CustomSettings::getInstance();
    custom->loadFromDisk();

    CustomSettings::Enum e = custom->getEnum();
    qDebug() << "";
    qDebug() << QString("Custom enum value is%1CustomSettings::Enum::Value2.")
                .arg(e == CustomSettings::Enum::Value2 ? " " : " not ").toStdString().c_str();

    custom->saveToDisk();

    return 0;
}

// ---------------------------------------------------------------------------------------------- //
