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
	parser.add_argument('-gemc',  action='store_true',   help='write goption help with physics list modules, maps and constructors')
	parser.add_argument('-html',  action='store_true',   help='write html help with physics list modules, maps and constructors')

	args = parser.parse_args()


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
		
	print('\tphysicsListHelp += "\\n" + string(HELPFILLSPACE) + "The default e.m. physics can be replaced by appending one of these string to the module above:\\n\\n";')
	for repTicket, repItem in rmap.items():
		print(f'\tphysicsListHelp += string(HELPFILLSPACE) + " - _{repTicket} to use {repItem}\\n" ;')
	print('\tphysicsListHelp += "\\n" + string(HELPFILLSPACE) + "For example, FTFP_BERT_LIV would replace the default e.m. physics with the Livermode model \\n\\n";')
	print('\tphysicsListHelp += "\\n" + string(HELPFILLSPACE) + "Additional physics can be loaded by adding its constructor name to the list using the \"+\" sign\\n";')
	print('\tphysicsListHelp += "\\n" + string(HELPFILLSPACE) + "For example: FTFP_BERT + G4OpticalPhysics. The available constructors are: \\n\\n";')
	for m in ctors:
		print(f'\tphysicsListHelp += string(HELPFILLSPACE) + " - {m}\\n";')

	print("\n\n")

	

if __name__ == "__main__":
	main()





