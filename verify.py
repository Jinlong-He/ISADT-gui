import os
import sys
xmlPath = "../backxml/current.xml"

os.system("cd build/bin && ./isadt -i ../../" + xmlPath + " -v " + sys.argv[1])
