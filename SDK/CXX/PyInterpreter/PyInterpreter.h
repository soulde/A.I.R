//
// Created by lyjly on 2022/12/28.
//

#ifndef CORE_CPP_PYINTERPRETER_H
#define CORE_CPP_PYINTERPRETER_H

#include <Python.h>
#include <map>
#include <type_traits>
#include <string>
#include <iostream>

#define PyFunction PyObject*
#define PyArgList PyObject*
#define PyRetVal PyObject*
#define TYPECHECK(T1, T2) std::is_same<typename std::decay<T1>::type,T2>::value

class PyInterpreter {
public:
    explicit PyInterpreter() {
        Py_Initialize();
    }

    inline void import(const std::string &module) {
        mod = PyImport_ImportModule(module.c_str());
        modMap[module] = mod;
    }

    inline void runCommand(char *cmd) {
        PyRun_SimpleString(cmd);
    }

    inline PyRetVal callFunction(const std::string &module, const std::string &function, PyArgList pList);

    ~PyInterpreter() {
        Py_Finalize();
    }

    inline PyArgList prepareArgs();

    template<typename T>
    T convertFromPy(PyObject *val) {
        T ret;
        if (TYPECHECK(T, int)) {
            PyArg_Parse(val, "i", &ret);
        }
        if (TYPECHECK(T, long)) {
            PyArg_Parse(val, "l", &ret);
        }
        return ret;
    }

    inline PyObject *convertToPy(int val) {

        return nullptr;
    }

private:
    PyObject *mod;
    std::map<std::string, PyObject *> modMap;
};


#endif //CORE_CPP_PYINTERPRETER_H
