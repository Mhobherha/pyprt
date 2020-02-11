import sys
import os

import pyprt
from pyprt.pyprt_utils import visualize_prt_results

CS_FOLDER = os.path.dirname(os.path.realpath(__file__))

def asset_file(filename):
    return os.path.join(os.path.dirname(CS_FOLDER), 'data', filename)

print('\nInitializing PRT.')
pyprt.initialize_prt()

if not pyprt.is_prt_initialized():
    raise Exception('PRT is not initialized')


### DATA
rpk1 = asset_file('candler.rpk')
attrs1 = {'ruleFile': 'bin/candler.cgb', 'startRule': 'Default$Footprint'}


### INITIAL SHAPES
shape_geometry_1 = pyprt.InitialShape([0, 0, 0,  0, 0, 100,  100, 0, 100,  100, 0, 0])
shape_geometry_2 = pyprt.InitialShape([0, 0, 0,  0, 0, -10,  -10, 0, -10,  -10, 0, 0, -5, 0, -5])


### PRT GENERATION
m1 = pyprt.ModelGenerator([shape_geometry_2, shape_geometry_1])

encoderOptions = {'outputPath': '/tmp/pyprt_output'}
os.makedirs(encoderOptions['outputPath'], exist_ok=True)

mo = m1.generate_model([attrs1], rpk1, 'com.esri.prt.codecs.OBJEncoder', encoderOptions)
visualize_prt_results(mo)


### PRT END
pyprt.shutdown_prt()
print('\nShutdown PRT.')