import os
import sys
xmlPath = "../backxml/current.xml"

#os.system("rm -rf ~/Desktop/generated")
os.system("cd build/bin && ./isadt -i ../../" + xmlPath + " -k")