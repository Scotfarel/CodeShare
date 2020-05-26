/****************************************************************************
** Meta object code from reading C++ file 'myClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../headers/myClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myClient_t {
    QByteArrayData data[33];
    char stringdata0[414];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myClient_t qt_meta_stringdata_myClient = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myClient"
QT_MOC_LITERAL(1, 9, 13), // "statusChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 17), // "formResultSuccess"
QT_MOC_LITERAL(4, 42, 6), // "result"
QT_MOC_LITERAL(5, 49, 17), // "formResultFailure"
QT_MOC_LITERAL(6, 67, 15), // "opResultSuccess"
QT_MOC_LITERAL(7, 83, 15), // "opResultFailure"
QT_MOC_LITERAL(8, 99, 19), // "editorResultSuccess"
QT_MOC_LITERAL(9, 119, 11), // "std::string"
QT_MOC_LITERAL(10, 131, 8), // "filename"
QT_MOC_LITERAL(11, 140, 19), // "editorResultFailure"
QT_MOC_LITERAL(12, 160, 14), // "listFileResult"
QT_MOC_LITERAL(13, 175, 17), // "std::vector<File>"
QT_MOC_LITERAL(14, 193, 5), // "files"
QT_MOC_LITERAL(15, 199, 12), // "insertSymbol"
QT_MOC_LITERAL(16, 212, 22), // "std::pair<int,wchar_t>"
QT_MOC_LITERAL(17, 235, 5), // "tuple"
QT_MOC_LITERAL(18, 241, 13), // "insertSymbols"
QT_MOC_LITERAL(19, 255, 10), // "firstIndex"
QT_MOC_LITERAL(20, 266, 19), // "std::vector<symbol>"
QT_MOC_LITERAL(21, 286, 7), // "symbols"
QT_MOC_LITERAL(22, 294, 12), // "eraseSymbols"
QT_MOC_LITERAL(23, 307, 10), // "startIndex"
QT_MOC_LITERAL(24, 318, 8), // "endIndex"
QT_MOC_LITERAL(25, 327, 14), // "jsonMsgFailure"
QT_MOC_LITERAL(26, 342, 10), // "windowName"
QT_MOC_LITERAL(27, 353, 3), // "msg"
QT_MOC_LITERAL(28, 357, 18), // "removeRemoteCursor"
QT_MOC_LITERAL(29, 376, 8), // "username"
QT_MOC_LITERAL(30, 385, 18), // "changeRemoteCursor"
QT_MOC_LITERAL(31, 404, 5), // "color"
QT_MOC_LITERAL(32, 410, 3) // "pos"

    },
    "myClient\0statusChanged\0\0formResultSuccess\0"
    "result\0formResultFailure\0opResultSuccess\0"
    "opResultFailure\0editorResultSuccess\0"
    "std::string\0filename\0editorResultFailure\0"
    "listFileResult\0std::vector<File>\0files\0"
    "insertSymbol\0std::pair<int,wchar_t>\0"
    "tuple\0insertSymbols\0firstIndex\0"
    "std::vector<symbol>\0symbols\0eraseSymbols\0"
    "startIndex\0endIndex\0jsonMsgFailure\0"
    "windowName\0msg\0removeRemoteCursor\0"
    "username\0changeRemoteCursor\0color\0pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       3,    1,   92,    2, 0x06 /* Public */,
       5,    1,   95,    2, 0x06 /* Public */,
       6,    1,   98,    2, 0x06 /* Public */,
       7,    1,  101,    2, 0x06 /* Public */,
       8,    2,  104,    2, 0x06 /* Public */,
       8,    1,  109,    2, 0x26 /* Public | MethodCloned */,
      11,    1,  112,    2, 0x06 /* Public */,
      12,    1,  115,    2, 0x06 /* Public */,
      15,    1,  118,    2, 0x06 /* Public */,
      18,    2,  121,    2, 0x06 /* Public */,
      22,    2,  126,    2, 0x06 /* Public */,
      25,    2,  131,    2, 0x06 /* Public */,
      28,    1,  136,    2, 0x06 /* Public */,
      30,    3,  139,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 9,    4,   10,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 20,   19,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   26,   27,
    QMetaType::Void, 0x80000000 | 9,   29,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, QMetaType::Int,   29,   31,   32,

       0        // eod
};

void myClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->formResultSuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->formResultFailure((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->opResultSuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->opResultFailure((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->editorResultSuccess((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 6: _t->editorResultSuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->editorResultFailure((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->listFileResult((*reinterpret_cast< std::vector<File>(*)>(_a[1]))); break;
        case 9: _t->insertSymbol((*reinterpret_cast< std::pair<int,wchar_t>(*)>(_a[1]))); break;
        case 10: _t->insertSymbols((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<symbol>(*)>(_a[2]))); break;
        case 11: _t->eraseSymbols((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->jsonMsgFailure((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->removeRemoteCursor((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 14: _t->changeRemoteCursor((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (myClient::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::statusChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (myClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::formResultSuccess)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (myClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::formResultFailure)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (myClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::opResultSuccess)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (myClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::opResultFailure)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (myClient::*)(QString , std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::editorResultSuccess)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (myClient::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::editorResultFailure)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (myClient::*)(std::vector<File> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::listFileResult)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (myClient::*)(std::pair<int,wchar_t> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::insertSymbol)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (myClient::*)(int , std::vector<symbol> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::insertSymbols)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (myClient::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::eraseSymbols)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (myClient::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::jsonMsgFailure)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (myClient::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::removeRemoteCursor)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (myClient::*)(std::string , std::string , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myClient::changeRemoteCursor)) {
                *result = 14;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject myClient::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_myClient.data,
    qt_meta_data_myClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *myClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int myClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void myClient::statusChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myClient::formResultSuccess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void myClient::formResultFailure(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void myClient::opResultSuccess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void myClient::opResultFailure(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void myClient::editorResultSuccess(QString _t1, std::string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 7
void myClient::editorResultFailure(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void myClient::listFileResult(std::vector<File> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void myClient::insertSymbol(std::pair<int,wchar_t> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void myClient::insertSymbols(int _t1, std::vector<symbol> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void myClient::eraseSymbols(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void myClient::jsonMsgFailure(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void myClient::removeRemoteCursor(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void myClient::changeRemoteCursor(std::string _t1, std::string _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
