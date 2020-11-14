import os
import sys
xmlPath = "../backxml/current.xml"

#os.system("rm -rf ~/Desktop/generated")

os.system("rm -rf ../generated/generatedSrc")
os.system("rm -rf ../generated/generatedHeader")
os.system("rm ../generated/UserType.hpp")
os.system("rm ../generated/UserType.java")
os.system("mkdir ../generated/generatedSrc")
os.system("mkdir ../generated/generatedHeader")
os.system("cd build/bin && ./isadt -i ../../" + xmlPath + " -g " + sys.argv[1] + " " + sys.argv[2])
print( sys.argv[2])