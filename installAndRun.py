import os
import sys

#os.system("rm -rf ~/Desktop/generated")

# not general, used for demonstration
os.system("gnome-terminal -e 'bash -c \"echo PROCESS BOB------ && sudo ../generated/Bob; exec bash\"'")

os.system("gnome-terminal -e 'bash -c \"echo PROCESS ALICE------ && sudo ../generated/Alice; exec bash\"'")
