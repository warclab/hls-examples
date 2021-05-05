import sys
from shutil import copyfile
from glob import glob
import xml.etree.ElementTree as ET
from json import dump

proj_name = sys.argv[1].split('.prj')[0]
try:
    xml_info = glob(f'{sys.argv[1]}/{sys.argv[2]}/impl/ip/*_info.xml')[0]
except:
    return ValueError("Cannot find *_info.xml")
    exit(1)

with open(xml_info) as fp:
    tree = ET.parse(fp)
    root = tree.getroot()

    config_json = {}
    for kernel in root[0]:
        config_json[kernel.attrib['name']] = {}
        for child in kernel:
            if (child.tag == 'port'):
                config_json[kernel.attrib['name']][child.attrib['name']] = {}
            try:
                config_json[kernel.attrib['name']][child.attrib['port']][child.attrib['name']] = child.attrib
                del config_json[kernel.attrib['name']][child.attrib['port']][child.attrib['name']]['port']
            except:
                pass

    with open('config.json', 'w') as config:
        dump(config_json, config, indent=4, sort_keys=True)

    copyfile('config.json', f'{sys.argv[1]}/{sys.argv[2]}/syn/verilog/config.json')
