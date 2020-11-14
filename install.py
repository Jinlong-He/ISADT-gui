import os
import sys

os.system("sudo apt-get install git")
os.system("sudo apt-get install g++")
os.system("sudo apt-get install libpcap-dev")
os.system("sudo apt-get install libboost-dev libboost-all-dev")
os.system("sudo apt-get install openssl libssl-dev")

#os.system("rm -rf ~/Desktop/generated")
os.system("mkdir ../generated")
os.system("mkdir ../generated/CommLib")
os.system("mkdir ../generated/CryptoLib")
os.system("git clone https://github.com/SpencerL-Y/CryptoLib ../generated/CryptoLib")
os.system("git clone https://github.com/SpencerL-Y/CommLib ../generated/CommLib")

os.system("rm -rf ../generated/generatedSrc")
os.system("rm -rf ../generated/generatedHeader")
os.system("mkdir ../generated/generatedSrc")
os.system("mkdir ../generated/generatedHeader")
#os.system("cd build && cmake .. && make && cd bin && ./isadt -i ../../needham_without_key_0.xml -g")
#os.system("cd ~/Desktop/generated/ && python3 compile.py")
