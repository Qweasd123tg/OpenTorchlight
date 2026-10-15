import unittest
from llm_context import Declaration, _callback_aliases, _declares_callee

class CallbackAliasTests(unittest.TestCase):
    def declaration(self, parameters):
        return Declaration('CDescriptor::add', 'function', 'unsigned int add('+parameters+');', ())
    def callee(self, parameters):
        return {'method':'add', 'qualified':'CDescriptor::add', 'params':parameters, 'cv':''}
    def aliases(self, text):
        return _callback_aliases({'Callbacks.h':text})
    def test_named_callback_alias_expands_and_preserves_const_reference(self):
        aliases=self.aliases('typedef unsigned int (*Callback)(CScene*, const std::wstring&, void*);')
        self.assertTrue(_declares_callee(self.declaration('Callback callback, int count'), self.callee('unsigned int (*)(CScene*, std::wstring const&, void*), int'), aliases))
    def test_different_callback_argument_is_rejected(self):
        aliases=self.aliases('typedef unsigned int (*Callback)(CScene*, const std::wstring&, void*);')
        self.assertFalse(_declares_callee(self.declaration('Callback callback'), self.callee('unsigned int (*)(CScene*, std::wstring&, void*)'), aliases))
    def test_different_return_type_is_rejected(self):
        aliases=self.aliases('typedef unsigned int (*Callback)(int);')
        self.assertFalse(_declares_callee(self.declaration('Callback callback'), self.callee('int (*)(int)'), aliases))
    def test_unknown_alias_stays_gap(self):
        self.assertFalse(_declares_callee(self.declaration('Callback callback'), self.callee('unsigned int (*)(int)'), {}))
    def test_conflicting_aliases_are_not_expanded(self):
        aliases=_callback_aliases({'A.h':'typedef int (*Callback)(int);','B.h':'typedef int (*Callback)(float);'})
        self.assertEqual(aliases,{})
    def test_scoped_aliases_are_not_expanded(self):
        self.assertEqual(self.aliases('namespace N { typedef int (*Callback)(int); }'),{})
    def test_scoped_callback_shadows_global_alias(self):
        aliases=self.aliases('typedef int (*Callback)(int); class C { typedef float (*Callback)(int); void add(Callback callback); };')
        self.assertEqual(aliases,{})
        self.assertFalse(_declares_callee(self.declaration('Callback callback'), self.callee('int (*)(int)'), aliases))
    def test_scoped_noncallback_typedef_also_blocks_global_alias(self):
        self.assertEqual(self.aliases('typedef int (*Callback)(int); class C { typedef float Callback; };'),{})
    def test_pointer_to_alias_is_not_callback(self):
        aliases=self.aliases('typedef int (*Callback)(int);')
        self.assertFalse(_declares_callee(self.declaration('Callback* callback'), self.callee('int (*)(int)'), aliases))
    def test_nested_named_callback_is_not_guessed(self):
        self.assertEqual(self.aliases('typedef int (*Callback)(int (*nested)(int));'),{})
