# CoSeSt2 - Comfortable Settings Structure v2

## Introduction

CoSeSt2 is a wrapper class around [QSettings](https://doc.qt.io/qt-6/qsettings.html), intended to make handling settings both safer and more comfortable.

When values are accessed by string, a small typo in the key will often lead to runtime errors that can be difficult to trace. CoSeSt2 places all settings in a singleton object instead that allows values to be accessed either directly by name or using setter/getter methods. This not only allows typos to be detected at compile-time but also makes it possible to employ the IDE's code-completion features to find and access settings comfortably.

## Usage

Using CoSeSt2 typically only requires a header file to be added to your project.
A simple example may look as follows:

```cpp
#include "CoSeSt2.h"

COSEST_BEGIN(MySettings)
  COSEST_ENTRY(bool, BoolValue, false)
  COSEST_ENTRY(int, IntValue, 42)
  COSEST_ENTRY(double, DoubleValue, 123.4)
  COSEST_ENTRY(QString, StringValue, "Hello world!")
  COSEST_ENTRY(QDateTime, DateTime, QDateTime::currentDateTime())

  COSEST_BEGIN_GROUP(SomeGroup)
    COSEST_ENTRY(bool, BoolValue, true)
    COSEST_ENTRY(int, IntValue, 1234)
  COSEST_END_GROUP(SomeGroup)
COSEST_END
```

Whenever you need to access settings, you can get either a pointer or a const reference to the singleton:

```cpp
MySettings* settings = MySettings::getInstance();
```
```cpp
const MySettings& constSettings = MySettings::getConstInstance();
```

Typically settings should be loaded from disk once at application startup:

```cpp
settings->loadFromDisk();
```

You can then read and/or modify values in either a "struct-like" or object-oriented manner:

```cpp
settings->BoolValue = !settings->BoolValue;
settings->StringValue = "Hello universe!";

MySettings::SomeGroup* group = settings->getSomeGroup();
group->setBoolValue(!group->getBoolValue());
group->setIntValue(group->getIntValue() + 1);
```

Remember to save the settings when finished or on exit:

```cpp
settings->saveToDisk();
```

A more elaborate example is provided along with the library. It demonstrates some advanced features such as using different storage types and creating custom subclasses.


## License

CoSeSt2 is released under the 2-Clause BSD License. See [COPYING](COPYING) for details.


## Contributing

No further development is planned at this point but patches to fix bugs are always welcome and can be submitted by [email](mailto:mahasler@gmail.com).
