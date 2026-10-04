#!/usr/bin/env python3
import unittest
import mutate

class Overloads(unittest.TestCase):
    source = '''
void Unit::add(Theme* theme) { if (theme != 0) consume(theme); }
void Unit::add(const std::wstring& name) { consume(name); }
void Unit::add(long long guid) { consume(guid); }
'''
    def body(self, params, source=None):
        source = source or self.source
        f = dict(demangled='Unit::add('+params+')', params=params)
        span=mutate.definition(source,mutate.mask(source),f)
        return None if span is None else source[span[0]:span[1]+1]
    def test_same_arity(self):
        self.assertIn('consume(theme)',self.body('Theme*'))
        self.assertIn('consume(name)',self.body(mutate.autotest.WSTRING+' const&'))
        self.assertIn('consume(guid)',self.body('long long'))
    def test_unknown_stays_unresolved(self):
        self.assertIsNone(self.body('Other*'))
    def test_duplicate_stays_unresolved(self):
        self.assertIsNone(self.body('Theme*',self.source+self.source))
    def test_unique_arity_keeps_existing_alias_behavior(self):
        self.assertIn('consume(x)',self.body('Alias','void Unit::add(Actual x) { consume(x); }'))
    def test_unnamed_parameters(self):
        self.assertIn('one()',self.body('Theme*','void Unit::add(Theme*) { one(); }\nvoid Unit::add(long long) { two(); }'))

if __name__=='__main__':unittest.main()
