"""Production-only comparison identities must not become game hooks."""
from types import SimpleNamespace
import unittest
import hybrid

class ComparisonOnlyEntries(unittest.TestCase):
    def context(self):
        return SimpleNamespace(functions={
            '0x100': {'address':'0x100','names':['first','alias'],'kind':'function','demangled':'first()'},
            '0x200': {'address':'0x200','names':['compiler'],'kind':'compiler','demangled':'compiler()'},
            '0x300': {'address':'0x300','names':['testOnly'],'kind':'function','demangled':'testOnly()'},
        }, image=SimpleNamespace(read=lambda a,n:bytes(range(n))))
    def test_only_actual_production_definitions_are_registered(self):
        hooks=[{'original':0x100,'symbol':'first'}]
        result=hybrid.comparison_entries(self.context(),{'first','alias','compiler','unknown'},hooks)
        self.assertEqual([('alias',0x100)],[(x['symbol'],x['original']) for x in result])
        self.assertEqual(list(range(8)),result[0]['expected'])
        self.assertEqual([{'original':0x100,'symbol':'first'}],hooks)
    def test_no_production_definition_means_no_comparison(self):
        self.assertEqual([],hybrid.comparison_entries(self.context(),set(),[]))
    def test_separate_sections_have_disjoint_generated_labels(self):
        row={'original':0x100,'symbol':'first','demangled':'first()','expected':[0]*8}
        hook=hybrid.hooks_assembly([row])
        comparison=hybrid.hooks_assembly([row],'.tlhybrid.comparisons','comparison')
        self.assertIn('.tlhybrid.hooks',hook)
        self.assertIn('.tlhybrid.comparisons',comparison)
        self.assertIn('.Ltlhybrid_hook_name_0:',hook)
        self.assertIn('.Ltlhybrid_comparison_name_0:',comparison)
