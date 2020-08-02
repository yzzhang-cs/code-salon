# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info >= (2, 7, 0):
    def swig_import_helper():
        import importlib
        pkg = __name__.rpartition('.')[0]
        mname = '.'.join((pkg, '_cpp_salon')).lstrip('.')
        try:
            return importlib.import_module(mname)
        except ImportError:
            return importlib.import_module('_cpp_salon')
    _cpp_salon = swig_import_helper()
    del swig_import_helper
elif _swig_python_version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_cpp_salon', [dirname(__file__)])
        except ImportError:
            import _cpp_salon
            return _cpp_salon
        try:
            _mod = imp.load_module('_cpp_salon', fp, pathname, description)
        finally:
            if fp is not None:
                fp.close()
        return _mod
    _cpp_salon = swig_import_helper()
    del swig_import_helper
else:
    import _cpp_salon
del _swig_python_version_info

try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr(self, class_type, name):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    raise AttributeError("'%s' object has no attribute '%s'" % (class_type.__name__, name))


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except __builtin__.Exception:
    class _object:
        pass
    _newclass = 0

class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _cpp_salon.delete_SwigPyIterator
    __del__ = lambda self: None

    def value(self):
        return _cpp_salon.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _cpp_salon.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _cpp_salon.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _cpp_salon.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _cpp_salon.SwigPyIterator_equal(self, x)

    def copy(self):
        return _cpp_salon.SwigPyIterator_copy(self)

    def next(self):
        return _cpp_salon.SwigPyIterator_next(self)

    def __next__(self):
        return _cpp_salon.SwigPyIterator___next__(self)

    def previous(self):
        return _cpp_salon.SwigPyIterator_previous(self)

    def advance(self, n):
        return _cpp_salon.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _cpp_salon.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _cpp_salon.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _cpp_salon.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _cpp_salon.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _cpp_salon.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _cpp_salon.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self
SwigPyIterator_swigregister = _cpp_salon.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)

class Stylist(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Stylist, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Stylist, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr

    def style(self, s):
        return _cpp_salon.Stylist_style(self, s)
    __swig_destroy__ = _cpp_salon.delete_Stylist
    __del__ = lambda self: None
Stylist_swigregister = _cpp_salon.Stylist_swigregister
Stylist_swigregister(Stylist)

class CppStylist(Stylist):
    __swig_setmethods__ = {}
    for _s in [Stylist]:
        __swig_setmethods__.update(getattr(_s, '__swig_setmethods__', {}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, CppStylist, name, value)
    __swig_getmethods__ = {}
    for _s in [Stylist]:
        __swig_getmethods__.update(getattr(_s, '__swig_getmethods__', {}))
    __getattr__ = lambda self, name: _swig_getattr(self, CppStylist, name)
    __repr__ = _swig_repr

    def __init__(self, *args):
        this = _cpp_salon.new_CppStylist(*args)
        try:
            self.this.append(this)
        except __builtin__.Exception:
            self.this = this

    def style(self, s):
        return _cpp_salon.CppStylist_style(self, s)
    __swig_destroy__ = _cpp_salon.delete_CppStylist
    __del__ = lambda self: None
CppStylist_swigregister = _cpp_salon.CppStylist_swigregister
CppStylist_swigregister(CppStylist)


def string_to_options(s):
    return _cpp_salon.string_to_options(s)
string_to_options = _cpp_salon.string_to_options
# This file is compatible with both classic and new-style classes.

