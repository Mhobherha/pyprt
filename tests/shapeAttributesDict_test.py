import os
import unittest

import pyprt

CS_FOLDER = os.path.dirname(os.path.realpath(__file__))


def asset_file(filename):
    return os.path.join(os.path.dirname(CS_FOLDER), 'data', filename)


class ShapeAttributesTest(unittest.TestCase):
    def test_correctExecution(self):
        rpk = asset_file('test_rule.rpk')
        attrs_1 = {'ruleFile': 'bin/test_rule.cgb', 'startRule': 'Default$Footprint'}
        attrs_2 = {'ruleFile': 'bin/test_rule.cgb', 'startRule': 'Default$Footprint', 'minBuildingHeight': 30.0}
        attrs_3 = {'ruleFile': 'bin/test_rule.cgb', 'startRule': 'Default$Footprint', 'text': 'hello'}
        shape_geometry_1 = pyprt.InitialShape(
            [0, 0, 0, 0, 0, 100, 100, 0, 100, 100, 0, 0])
        shape_geometry_2 = pyprt.InitialShape(
            [0, 0, 0, 0, 0, -10, -10, 0, -10, -10, 0, 0, -5, 0, -5])
        shape_geometry_3 = pyprt.InitialShape(
            [0, 0, 0, 0, 0, -10, 10, 0, -10, 10, 0, 0, -5, 0, -5])
        m = pyprt.ModelGenerator([shape_geometry_1, shape_geometry_2, shape_geometry_3])
        model = m.generate_model([attrs_1, attrs_2, attrs_3], rpk, 'com.esri.pyprt.PyEncoder',
                                 {'emitReport': False, 'emitGeometry': True})
        self.assertEqual(len(model), 3)

    def test_oneDictForAll(self):
        rpk = asset_file('test_rule.rpk')
        attrs = {'ruleFile': 'bin/test_rule.cgb', 'startRule': 'Default$Footprint', 'text': 'hello'}
        shape_geometry_1 = pyprt.InitialShape(
            [0, 0, 0, 0, 0, 100, 100, 0, 100, 100, 0, 0])
        shape_geometry_2 = pyprt.InitialShape(
            [0, 0, 0, 0, 0, -10, -10, 0, -10, -10, 0, 0, -5, 0, -5])
        shape_geometry_3 = pyprt.InitialShape(
            [0, 0, 0, 0, 0, -10, 10, 0, -10, 10, 0, 0, -5, 0, -5])
        m = pyprt.ModelGenerator([shape_geometry_1, shape_geometry_2, shape_geometry_3])
        model = m.generate_model([attrs], rpk, 'com.esri.pyprt.PyEncoder',
                                 {'emitReport': False, 'emitGeometry': True})
        self.assertEqual(len(model), 3)

    def test_wrongNumberOfDict(self):
        rpk = asset_file('test_rule.rpk')
        attrs_1 = {'ruleFile': 'bin/test_rule.cgb', 'startRule': 'Default$Footprint'}
        attrs_2 = {'ruleFile': 'bin/test_rule.cgb', 'startRule': 'Default$Footprint', 'minBuildingHeight': 30.0}
        shape_geometry_1 = pyprt.InitialShape(
            [0, 0, 0, 0, 0, 100, 100, 0, 100, 100, 0, 0])
        shape_geometry_2 = pyprt.InitialShape(
            [0, 0, 0, 0, 0, -10, -10, 0, -10, -10, 0, 0, -5, 0, -5])
        shape_geometry_3 = pyprt.InitialShape(
            [0, 0, 0, 0, 0, -10, 10, 0, -10, 10, 0, 0, -5, 0, -5])
        m = pyprt.ModelGenerator([shape_geometry_1, shape_geometry_2, shape_geometry_3])
        model = m.generate_model([attrs_1, attrs_2], rpk, 'com.esri.pyprt.PyEncoder',
                                 {'emitReport': False, 'emitGeometry': True})
        self.assertEqual(len(model), 0)

    def test_oneDictPerInitialShapeType(self):
        rpk = asset_file('test_rule.rpk')
        attrs_1 = {'ruleFile': 'bin/test_rule.cgb', 'startRule': 'Default$Footprint'}
        attrs_2 = {'ruleFile': 'bin/test_rule.cgb', 'startRule': 'Default$Footprint', 'minBuildingHeight': 30.0}
        shape_geometry_1 = pyprt.InitialShape(
            [-50.447, 0, 89.886, -50.447, 0, 39.523, 34.368, 0, 39.523, 34.368, 0, 89.886])
        shape_geometry_2 = pyprt.InitialShape(asset_file('bigFootprint_0.obj'))
        m = pyprt.ModelGenerator([shape_geometry_1, shape_geometry_2])
        model = m.generate_model([attrs_1, attrs_2], rpk, 'com.esri.pyprt.PyEncoder', {})
        self.assertNotEqual(model[0].get_report()['Min Height.0_avg'], model[1].get_report()['Min Height.0_avg'])