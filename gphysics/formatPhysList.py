#!/usr/bin/python3 -B   # -B prevents writing .pyc compiled versions of each module

# - Read geant4 physics modules, mapping and constructors
# - Output c++ code for the help table
# - Output html code for the documentation table


import sys, os, argparse, subprocess


moduleStringCatcher       = 'Base G4VModularPhysicsLists in G4PhysListRegistry are:'
replaceMapStringCatcher   = 'Replacement mappings in G4PhysListRegistry are:'
constructorsStringCatcher = 'G4VPhysicsConstructors in G4PhysicsConstructorRegistry are:'
resetStringCatcher        = 'Use these mapping to extend physics list; append with _EXT or +EXT'

modules = []
uniqueReplacements = []
rmap = dict()
ctors = []

def main():
	
	# Provides the -h, --help message
	desc_str = "   Geant4 Physics List Help / HTML creator\n"
	parser = argparse.ArgumentParser(description=desc_str)
	

	# code snippets loggers: volume
	parser.add_argument('-gemc', action='store_true',   help='write goption help with physics list modules, maps and constructors')
	parser.add_argument('-web',  action='store_true',   help='write jekyll file in gemc home with physics list modules, maps and constructors')

	args = parser.parse_args()

	# need to run the example to print out the modules, maps and
	d = dict(os.environ)   # Make a copy of the current environment
	d['DYLD_LIBRARY_PATH'] = d['LD_LIBRARY_PATH']
	example = subprocess.run(['./example', '-showAvailablePhysicsX'], env=d, capture_output=True, text=True)
	lines = example.stdout.split('\n')
	logType = 'none'

	for l in lines:
		if l == moduleStringCatcher:
			logType = 'module'
		elif l == replaceMapStringCatcher:
			logType = 'rmap'
		elif l == constructorsStringCatcher:
			logType = 'ctor'
		elif l == resetStringCatcher:
			logType = 'none'
		
		if l != '':
			addModule(l, logType)
	


	print("\nModules:")
	print(modules)

	print("\n\nReplacement Map:")
	print(rmap)
	
	print("\n\nConstructor:")
	print(ctors)
	print("\n")

	if args.gemc:
		printGemcHelp()

	if args.web:
		printGemcMD()

def addModule(module, type):

	if type == 'module':
		if module != moduleStringCatcher:
			modules.append(module.split(' ')[-1].replace('"', ''))
	elif type == 'rmap':
		if module != replaceMapStringCatcher:
			repTicket = module.split('=>')[0].replace(' ', '')
			repItem   = module.split('=>')[-1].replace(' ', '')
			if repItem not in uniqueReplacements:
				uniqueReplacements.append(repItem)
				rmap[repTicket] = repItem
	elif type == 'ctor':
		if module != constructorsStringCatcher:
			ctors.append(module.split(' ')[-1].replace('"', ''))



def printGemcHelp():

	print("\n\n")
	print('\tphysicsListHelp += string(HELPFILLSPACE) + "The available geant4 modules are:\\n\\n";')
	
	for m in modules:
		print(f'\tphysicsListHelp += string(HELPFILLSPACE) + " - {m}\\n";')
		
	print('\tphysicsListHelp += "\\n" + string(HELPFILLSPACE) + "The default e.m. physics can be replaced by appending one of these strings to the module above:\\n\\n";')
	
	for repTicket, repItem in rmap.items():
		print(f'\tphysicsListHelp += string(HELPFILLSPACE) + " - _{repTicket} to use {repItem}\\n" ;')
	
	print('\tphysicsListHelp += "\\n" + string(HELPFILLSPACE) + "For example, FTFP_BERT_LIV would replace the default e.m. physics with the Livermode model \\n\\n";')
	print('\tphysicsListHelp += "\\n" + string(HELPFILLSPACE) + "Additional physics can be loaded by adding its constructor name to the list using the \"+\" sign\\n";')
	print('\tphysicsListHelp += "\\n" + string(HELPFILLSPACE) + "For example: FTFP_BERT + G4OpticalPhysics. The available constructors are: \\n\\n";')
	
	for m in ctors:
		print(f'\tphysicsListHelp += string(HELPFILLSPACE) + " - {m}\\n";')

	print("\n\n")


# prints jekyll output
# notice we print directly on ../../home/_documentation
def printGemcMD():
		
	jekyllFileName='../../home/_documentation/physistExtList.md'
	with open(jekyllFileName, 'w') as dn:
		lstr = '---\n'
		lstr += 'layout: documentation\n'
		lstr += 'title: Geant4 Physics\n'
		lstr += 'order: 2\n'
		lstr += '---\n'
		lstr += '\n'
		lstr += 'The Geant4 Physics is determined with the option **physicsList**. If the option is not used, gemc will use **FTFP_BERT** as default.\n'
		lstr += '\n<br/>\n'
		lstr += '#### Usage:\n'
		lstr += '\n<br/>\n'
		lstr += 'The **physicsList** option is used to specify a physic list by compounding codes (see below for the complete list)\n\n'
		lstr += 'In the jcard, add the line:\n'
		lstr += ' ```\n"physicsList": "your choice of physics"\n```  \n'
		lstr += ' to select the geant4 physics. The choice is a string composed by: \n'
		lstr += '\n'
		lstr += ' - The main geant4 module. For example: **QGSP_BIC** (mandatory)\n'
		lstr += ' - Optional: a replacement for the default electro-magnetic physics list, specified by adding the string "_CODE" to the module\n'
		lstr += ' - Optional: one or more geant4 physics constructors can be added using the **+** sign\n'
		lstr += '\n<br/>\n'
		lstr += '#### Examples:\n'
		lstr += '<br/>\n'
		lstr += ' - "**QGSP_BIC_EMX**" will use the **QGSP_BIC** module but replace its e.m. physics with the **G4EmStandardPhysics_option2**\n'
		lstr += ' - "**FTFP_BERT_HP + G4OpticalPhysics**" will use the **FTFP_BERT_HP** module and add **G4OpticalPhysics** on top of it\n'
		lstr += ' - "**QGSP_BIC_PEN + G4OpticalPhysics + G4RadioactiveDecayPhysics**" will use the **QGSP_BIC** module,'
		lstr += '    replace its e.m. physics with the **G4EmPenelopePhysics**, and add the G4OpticalPhysics and G4RadioactiveDecayPhysics\n'
		lstr += '\n<br/>\n'
		lstr += '#### Geant4 Modules:\n'
		for m in modules:
			lstr += f' - {m}\n'
		lstr += '\n<br/>\n'
		lstr += '#### Geant4 e.m. replacement codes:\n'
		for repTicket, repItem in rmap.items():
			lstr += f' - _{repTicket}: {repItem}\n'
		lstr += '\n<br/><br/>\n'
		lstr += '#### Geant4 Physics Constructors:\n'
		for m in ctors:
			lstr += f' - {m}\n'

		lstr += '\n'
		dn.write(lstr)


if __name__ == "__main__":
	main()





