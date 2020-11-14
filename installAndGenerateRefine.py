import os
import sys
xmlPath = "../backxml/current.xml"

#os.system("rm -rf ~/Desktop/generated")

os.system("rm -rf ../generated/generatedSrc")
os.system("mkdir ../generated/generatedSrc")
os.system("cd build/bin && ./isadt -i ../../" + xmlPath + " -g --refine " + sys.argv[1] + " " + sys.argv[2])
print( sys.argv[2])