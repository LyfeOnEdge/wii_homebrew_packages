import os, sys, subprocess, argparse, json, shutil
import xml.etree.ElementTree as ET
from zipfile import ZipFile

BASEICONURL = "wii.apps.fortheusers.org/packages/{}/icon.png"

def create_arg_parser():
	parser = argparse.ArgumentParser(description='folder containing repo scrape')
	parser.add_argument('target',
					help='folder with scraped packages')
	parser.add_argument('output',
					help='folder to output pkgbuild.jsons')
	return parser

arg_parser = create_arg_parser()
parsed_args = arg_parser.parse_args(sys.argv[1:])
target = parsed_args.target
output_target = parsed_args.output
parent_folder = os.path.dirname(target)

#Empty object to populate
def pkgbuildjson():
	struct = {
		"package": None, #Grabbed from folder
		"info" : None,
		"changelog": None, #Ususally grabbed from github changelog I thought
		"assets": []
	}
	return struct

#Gets stuck in pkgbuildjson["info"]
def info_chunk():
	struct = {
		"title": None, #Can also grabbed name in xml
		"author": None, #can be grabbed from coder in xml
		"category": None, 
		"version": None, #version in xml
		"url": None, #usually gbatemp or github
		"license": None,
		"description": None, #can be grabbed from short_description in xml
		"details": None,	 #Can be grabbed from long_description in xml
	}
	return struct

#extracts xml from zip into memory and reads it into bytes
def extract_xml(input_zip, packagename):
	input_zip=ZipFile(input_zip)
	return input_zip.read("apps/{}/meta.xml".format(packagename))

#Gets a list of possible "packages" in target dir
def get_packages(path):
    if os.path.isdir(path):
        packages = []
        #Go through items in packages dir
        for pkg in os.listdir(path):
            if os.path.isdir(os.path.join(path, pkg)):
                packages.append(pkg)

        print("Found {} packages -\n{}".format(len(packages), json.dumps(packages, indent = 4)))
        return packages

#converts and xml object into a dict for easy processing
class xml_to_dict(dict):
    def __init__(self, parent_element):
        if parent_element.items():
            self.update(dict(parent_element.items()))
        for element in parent_element:
            if element:
                if len(element) == 1 or element[0].tag != element[1].tag:
                    aDict = XmlDictConfig(element)
                else:
                    aDict = {element[0].tag: XmlListConfig(element)}
                if element.items():
                    aDict.update(dict(element.items()))
                self.update({element.tag: aDict})
            elif element.items():
                self.update({element.tag: dict(element.items())})
            else:
                self.update({element.tag: element.text})

packages_list = []
for package in get_packages(target):
	# print("\n\nPackage - {}".format(package))
	packagepath = os.path.join(target, package)

	try:
		xml = extract_xml(os.path.join(packagepath,("{}.zip".format(package))), package)
		xml.decode('utf-8').replace('\n','').replace('\r','')
		xmlroot = ET.fromstring(xml)
		xmldict = xml_to_dict(xmlroot)
		# print(json.dumps(xmldict, indent=4))
	except Exception as e:
		print(e)

	pkgbuild = pkgbuildjson()
	info = info_chunk()
	pkgbuild["package"] = package
	info["title"] = xmldict["name"]
	try:
		info["author"] = xmldict["coder"]
	except:
		try:
			info["author"] = xmldict["author"]
		except:
			info["author"] = "Unknown"
	info["version"] = xmldict["version"]
	info["description"] = xmldict["short_description"]
	info["details"] = xmldict["long_description"]
	pkgbuild["info"] = info
	icon = {
				"url": BASEICONURL.format(package),
				"type": "icon",
			}
	pkgbuild["assets"].append(icon)

	outdir = os.path.join(output_target, package)
	if not os.path.isdir(outdir):
		os.mkdir(outdir)
	with open(os.path.join(outdir, "pkgbuild.json"), 'w') as pkgbuild_out:
		json.dump(pkgbuild, pkgbuild_out, indent = 4)
	packages_list.append(package)
	print(json.dumps(pkgbuild, indent = 4))

with open(os.path.join(output_target, "packages.json"), 'w') as packages_json:
	json.dump({"packages" : packages_list}, packages_json, indent = 4)

sys.exit("Done")