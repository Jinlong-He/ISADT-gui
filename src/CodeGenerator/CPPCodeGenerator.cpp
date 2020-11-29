#include "CodeGenerator/CPPCodeGenerator.hpp"
#define INCLUDE_HEADER "#include <stdio.h>\n#include <thread>\n#include <stdlib.h>\n"
#define SIM_INCLUDE ""
#define REAL_INCLUDE "#include \"../CommLib/NetComm/include/EtherReceiver.hpp\"\n\
#include \"../CommLib/NetComm/include/EtherSender.hpp\"\n\
#include \"../CommLib/NetComm/include/UDPSender.hpp\"\n\
#include \"../CommLib/NetComm/include/UDPReceiver.hpp\"\n"
#define CRYPTO_INCLUDE "#include \"../CryptoLib/include/Cryptor.hpp\""
#define SERIALIZATION_INCLUDE "#include <boost/archive/text_oarchive.hpp>\n\
#include <boost/archive/text_iarchive.hpp>\n\
#include <boost/serialization/vector.hpp>\n\
#include <boost/serialization/map.hpp>\n\
#include <boost/serialization/string.hpp>\n"
#define TIMER_INCLUDE ""
#define CR "\n"
#define TAB "\t"
#define DEMO 1
namespace isadt{
        std::list<Plugin*>  CPPCodeGenerator::getPlugins()
        { 
            return this->plugins;
        }
        // methods for generating header file 
        void  CPPCodeGenerator::generateHeaderFile(std::string path, Process* proc)
        {
            std::ofstream outHeadFile;
		    //TODO: make sure here
		    std::string tempFileName = proc->getName() + ".h";
		    std::string outStr = "";
		    // if def
		    outStr += generateHeaderIfDef(proc);
		    // generate includes 
		    outStr += this->generateCommonIncludes();
		    outStr += this->generateCommunicationIncludes();
			outStr += this->generateCryptoIncludes();
		    outStr += this->generateDependIncludes(proc);
			std::cout << "generateStateDef" << std::endl;
			outStr += this->generateStateDef(proc);
			std::cout << "generateStateDefOver" << std::endl;

			std::cout << "generate temp stores" << std::endl;
			outStr += this->generateTempStorage(proc);
			std::cout << "generate temp stores end" << std::endl;
		    // generate attrs and methods declaration
		    // attrs
			outStr += this->generateClassPre(proc);
			outStr += "\tprivate:\n";
		    for (Attribute* attr : proc->getOriginalAttributes()) {
		    	outStr += "\t\t" + this->appendAttrDef(outStr, attr);
		    }
			outStr += "\tpublic: \n";
		    // methods
		    for (Method* m : proc->getMethods()) {
		    	outStr += "\t\t" + this->appendMethodDeclaration(outStr, m);
		    }
			for (CommMethod* m : proc->getCommMethods()){
				outStr += "\t\t" + this->appendCommMethodDeclaration(outStr, m);   
			}
			outStr += "\t\tvoid SMLMain" + proc->getName() + "();\n"; 
			outStr += "};\n";
			
			
			std::cout << "genSrcMain" << std::endl;
		    outStr += this->generateMain(proc);
			
			std::cout << "genSrcMainOver" << std::endl;
		    //endif
		    outStr += "#endif\n";
			std::cout << outStr << std::endl;
		    outHeadFile.open(path + "/generatedHeader" + "/" + tempFileName, std::ofstream::out | std::ostream::out);
		    outHeadFile << outStr << std::endl;
		    outHeadFile.close();
        }

		
		void  CPPCodeGenerator::generateHeaderFileWin(std::string path, Process* proc)
        {
            std::ofstream outHeadFile;
		    //TODO: make sure here
		    std::string tempFileName = proc->getName() + ".h";
		    std::string outStr = "";
		    // if def
		    outStr += generateHeaderIfDef(proc);
		    // generate includes 
		    outStr += this->generateCommonIncludesWin();
		    outStr += this->generateDependIncludes(proc);
			std::cout << "generateStateDef" << std::endl;
			outStr += this->generateStateDef(proc);
			std::cout << "generateStateDefOver" << std::endl;

			std::cout << "generate temp stores" << std::endl;
			std::cout << "generate temp stores end" << std::endl;
		    // generate attrs and methods declaration
		    // attrs
			outStr += this->generateClassPre(proc);
			outStr += "\tprivate:\n";
		    for (Attribute* attr : proc->getOriginalAttributes()) {
		    	outStr += "\t\t" + this->appendAttrDef(outStr, attr);
		    }
			outStr += "\tpublic: \n";
		    // methods
		    for (Method* m : proc->getMethods()) {
		    	outStr += "\t\t" + this->appendMethodDeclaration(outStr, m);
		    }
			for (CommMethod* m : proc->getCommMethods()){
				outStr += "\t\t" + this->appendCommMethodDeclaration(outStr, m);   
			}
			outStr += "\t\tvoid SMLMain" + proc->getName() + "();\n"; 
			outStr += "};\n";
			
			
			std::cout << "genSrcMain" << std::endl;
		    outStr += this->generateMain(proc);
			
			std::cout << "genSrcMainOver" << std::endl;
		    //endif
		    outStr += "#endif\n";
			std::cout << outStr << std::endl;
		    outHeadFile.open(path + "/generatedHeader" + "/" + tempFileName, std::ofstream::out | std::ostream::out);
		    outHeadFile << outStr << std::endl;
		    outHeadFile.close();
        }

		std::string CPPCodeGenerator::generateClassPre(Process* proc){
			std::string result = "class " + proc->getName() + " {" + CR;
			result += "\tprivate: \n";
			return result;
		}

        std::string  CPPCodeGenerator::generateCommonIncludes()
        {
            std::string commonIncludes =
			"#include <iostream>\n#include <string>\n#include <vector>\n#include <stdlib.h>\n#include <thread>\n#include <stdlib.h>\n#include <sstream>\n#include <arpa/inet.h>\n";
		    commonIncludes += INCLUDE_HEADER;
		    commonIncludes += SERIALIZATION_INCLUDE;
			return commonIncludes;
        }

		std::string  CPPCodeGenerator::generateCommonIncludesWin()
        {
            std::string commonIncludes =
			"#include <iostream>\n#include <string>\n#include <vector>\n#include <stdlib.h>\n#include <thread>\n#include <stdlib.h>\n#include <sstream>\n";
		    commonIncludes += INCLUDE_HEADER;
			return commonIncludes;
        }

        std::string  CPPCodeGenerator::generateCommunicationIncludes()
        {
			// for real world we use libcap or libnet for the ethernet comm
			// use linux socket for the udp transmission
            std::string communicationIncludes = SIM_INCLUDE;
			communicationIncludes += REAL_INCLUDE;
		    return communicationIncludes;
        }

		std::string CPPCodeGenerator::generateCryptoIncludes()
		{
			std::string cryptoIncludes = CRYPTO_INCLUDE;
			return cryptoIncludes;
		}

        std::string  CPPCodeGenerator::generateDependIncludes(Process* currentProc)
        {
            //TODO: make sure here
            std::string dependHeaders = CR;
            /*
		    std::string dependHeaders = CR;
		    for (Process* p : currentProc->getDependProcs()) {
		    	//TODO: add path for process here
		    	std::string headerPath;
		    	dependHeaders += "#include \"" + headerPath + "\\" + p->getName() + ".h\" \n";
		    }
            */
            dependHeaders += "#include \"../UserType.hpp\" \n";
		    return dependHeaders;
        }

        std::string  CPPCodeGenerator::appendAttrDef(std::string inStr, Attribute* attr)
        {
            std::string result = "";
		    result += attr->getType()->getName() + " " + attr->getIdentifier() + ";\n";
		    return result;
        }

        std::string CPPCodeGenerator::appendMethodDeclaration(std::string inStr, Method* method)
        {
			std::cout << "appendMethod Declare" << std::endl;
            std::string result = "";
		    std::string attrStr;
		    int i = 1;
		    for (Attribute* a : method->getAttributes()) 
			{
		    	attrStr += a->getType()->getName() + " " + a->getIdentifier();
		    	if (i < method->getAttributes().size()) 
				{
		    		attrStr += ", ";
		    	}
		    	i++;
		    }
		    result += method->getReturnType()->getName() + " " + method->getName() + "(" + attrStr + ");\n";
			std::cout << "appendMethod Declare End" << std::endl;
		    return result;
        }

		std::string CPPCodeGenerator::appendCommMethodDeclaration(std::string inStr, CommMethod* method){
			
			std::cout << "appendCommMethod Declare" << std::endl;
			std::string result = "";
		    std::string attrStr;
		    int i = 1;
		    for (Attribute* a : method->getAttributes()) 
			{
				std::cout << "here" << std::endl;
		    	attrStr += a->getType()->getName() + " " + a->getIdentifier();
		    	if (i < method->getAttributes().size()) 
				{
		    		attrStr += ", ";
		    	}
		    	i++;
		    }
		    result +="int " + method->getName() + "(" + attrStr + ");\n";
			
			std::cout << "appendMethod Declare End" << std::endl;
		    return result;
		} 

        std::string CPPCodeGenerator::generateHeaderIfDef(Process* proc)
        {
            std::string result = "#ifndef " + proc->getName() + "_" + "h" + CR;
		    result += "#define " + proc->getName() + "_" + "h" + CR;
            return result;
        }

        // methods for generating src file
        void  CPPCodeGenerator::generateSrcFile(std::string path, Process* proc)
        {
            //TODO: imple later
            std::string outStr = "";
		    std::ofstream outSrcFile;
		    std::string tempFileName = proc->getName() + ".cpp";
			std::cout << "genSrcInclude" << std::endl;
		    outStr += this->generateSrcIncludes(proc);
			std::cout << "genSrcInclude Over" << std::endl;
			std::cout << "genSrcMethod" << std::endl;
		    outStr += this->generateSrcMethods(proc);
			
			std::cout << "genSrcMethodOver" << std::endl;
			std::cout << outStr << std::endl;
		    outSrcFile.open(path + "/generatedSrc" + "/" + tempFileName, std::ofstream::out | std::ostream::out);
		    outSrcFile << outStr << std::endl;
		    outSrcFile.close();
        }

        std::string  CPPCodeGenerator::generateStateDef(Process* proc)
        {
            std::string defs = "";
		    //defs += "#define STATE__START__STATE 0\n";
		    int i = 0;
			int loop_count = 0;
			for(StateMachine* sm : proc->getStateMachines()){
				for (Vertex* v : sm->getVertices()) 
				{
		    		//TODO: refine the state definition later
		    		defs += "#define STATE__" + v->getName() + " " + std::to_string(i) + "\n";
		    		i++;
		   	 	}
				loop_count++;
			}
		    
		    //defs += "#define STATE__STOP__STATE " + std::to_string(i) + "\n";
		    return defs;
        }
        
        std::string CPPCodeGenerator::generateTempStorage(Process* proc){
			std::string outStr = "";
			outStr += "static pcap_t* dev" + proc->getName() + ";\n";
			outStr += "static char* tempData" + proc->getName() + "\n;";
			outStr += "static std::string tempData" + proc->getName() + "Str;\n";
			return outStr;
		}

		std::string  CPPCodeGenerator::generateSrcIncludes(Process* proc)
		{
			//TODO: add path latter
			std::string headerPath;
			std::string srcIncludeStr = "#include \"../generatedHeader/" + proc->getName() + ".h\"\n";
			return srcIncludeStr;
		}

        std::string generateAttrs(const list<Attribute*>& attrs)
        {
            std::string attrStr = "(";
            int i = 1;
            for (Attribute* a : attrs) {
                attrStr += a->getType()->getName() + " "
                             + a->getIdentifier();
                if (i < attrs.size()) {
                    attrStr += ", ";
                }
                i++;
            }
            attrStr += ")";
            return attrStr;
        }

        std::string generateMethodSignature(const std::string& rttStr, const std::string& nameSpace,
                                            const std::string& methodName, const list<Attribute*>& attrs)
        {
            if (nameSpace == "") {
                return rttStr + " " + methodName + generateAttrs(attrs);
            }
            return  rttStr + " " + nameSpace + "::" + methodName + generateAttrs(attrs);
        }

        std::string  CPPCodeGenerator::generateSrcMethods(Process* proc)
		{		
			std::string outStr = "";
            std::unordered_set<std::string> keyMethods {"Sign", "Verify",
                                                        "SymEnc", "SymDec",
                                                        "AsymEnc", "AsymDec"};
            std::unordered_set<std::string> filterMethods {"htonl", "ntohl",
                                                        "ntohs", "htons"};

			/*code generation for base methods*/ 
			std::cout << "generate Methods" << std::endl;
            
			for (Method* m : proc->getMethods())
			{
                if (keyMethods.find(m->getName()) != keyMethods.end()) {
                    // Key Methods
                    // m->getAlgorithmId(): None -> IBE
                    // Sign, Verfiy
                    
                    // SymEnc, SymDec
                    // AsymEnc, AsymDec

                    std::cout << "Key Method: " << m->getName() << std::endl;
                    std::string rttStr =  m->getReturnType()->getName();
                    std::string methodSig = generateMethodSignature(rttStr, proc->getName(),
                                                                m->getName(), m->getAttributes());
					std::string returnVal = "\t" + rttStr + " result;" + CR;
                    // sign(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const string& id)
                    auto& alId = m->getAlgorithmId();

                    auto attrsIt = m->getAttributes().cbegin();
                    auto msgId = (*attrsIt)->getIdentifier();
                    attrsIt++;
                    auto keyId = (*attrsIt)->getIdentifier();
                    
                    std::string algId = alId == "None" ? "IBE" : alId;
                    // sign((char*)msg, msg.getLen(), msg.getSig(), msg.getSigLen(), (char*)key, "IBE");
                    std::string callAdaptor = "\tresult = " + m->getName() + "((char*)" + msgId + ", " +
                        msgId + ".getLen(), " +
                        msgId + ".getSig(), " +
                        msgId + ".getSigLend(), " +
                        "(char*)" + keyId + ", \"" +
                        algId + "\");\n";
					std::string ret = "\treturn result;\n";
					std::string methodBody = "{\n" + returnVal + callAdaptor + ret + "\n}\n";
					outStr += (methodSig + methodBody);
                } else {
                    if (filterMethods.find(m->getName()) != filterMethods.end()) {
                        continue;
                    }
                    // Simple Methods
                    std::string rttStr =  m->getReturnType()->getName();
					std::string methodSig = generateMethodSignature(rttStr, proc->getName(),
                                                                m->getName(), m->getAttributes());
					std::string returnVal = "\t" + rttStr + " result;" + CR;
					std::string ret = "\treturn result;\n";
					std::string methodBody = "{\n" + returnVal + ret + "\n}\n";
					outStr += (methodSig + methodBody);
                }
			}
			std::cout << "generate Methods Over" << std::endl;

			/*code generation for communication methods*/
			std::cout << "generate Communication Methods" << std::endl;
			for (CommMethod* m : proc->getCommMethods()){
				std::string commStr = "";
				std::string commHandlerStr = "";
                commStr += "\t// commID: " + m->getCommId() + CR;
                // commID: NativeEthernetFrame, UDP
                // Generate Handler?

				// Method Head
				std::string rttStr = "int";
                std::string methodSig = generateMethodSignature(rttStr, proc->getName(),
                                                                m->getName(), m->getAttributes());
				std::string returnVal = '\t' + rttStr + " result;" + CR;
				std::string ret = "\treturn result;";
				
				std::string methodBody = "";
				if(!m->getCommId().compare("NativeEthernetFrame")){
					if(!m->getInOut()){
						// IN
					} else {
						// OUT
					}
					methodBody = "{\n" + commStr + returnVal + ret + "\n}\n";
				} else if(!m->getCommId().compare("UDP")){
					if(!m->getInOut()){
						// IN

					} else {
                        // OUT
					}
					methodBody = "{\n" + commStr +"\n}\n";
				} else {
					std::cout << "Invalid commway num." << std::endl;
				}
				outStr += (commHandlerStr + methodSig + methodBody);
			}
			std::cout << "generate Communication Methods Over" << std::endl;

			std::cout << "generate SML Main loop method" << std::endl;
			outStr += ("void " + proc->getName() + "::SMLMain" + proc->getName() + "(){\n");
			outStr += this->generateSMLoop(proc);
			outStr += "}\n";
			std::cout << "generate SML Main loop method end" << std::endl;
			return outStr;
		}

        std::string CPPCodeGenerator::generateMain(Process* proc)
		{
			std::string outStr = "";
			// current state 
			outStr += "static int __currentState = STATE__" + proc->getStateMachines().front()->getStartVertex()->getName()+ ";\n";
			
			outStr += "int main(int argc, char** argv) {\n";
			outStr += "\t" + this->generateInstObject(proc);
			outStr += ("\tobj.SMLMain" + proc->getName() + "();\n");
			outStr += "}\n";
			return outStr;
		}

		std::string CPPCodeGenerator::generateInstObject(Process* proc){
			std::string outStr = "";
			outStr += proc->getName() + " obj;\n";
			outStr += "/*Initialize the object by user*/\n";
			return outStr;
		}

        //std::string  CPPCodeGenerator::generateGuardVarsDef(Process* proc);
        std::string  CPPCodeGenerator::generateSMLoop(Process* proc)
		{
			std::string outStr = "";
			std::cout << "generateSMLoopMain" << std::endl;
			outStr += "\twhile(__currentState != -100) {\n";
			outStr += "\t\tswitch(__currentState){\n";
			//make sure that start state is included
			//TODO
			outStr += this->generateStateBehavior((StateMachine *)proc->getStateMachines().front());
			outStr += "\t\t\tdefault: break;\n";
			outStr += "\t\t}\n";
			outStr += "\t}\n";
			std::cout << "generateSMLoopMain Over" << std::endl;
			
			std::cout << "generateSMLoopOther" << std::endl;
			std::cout << "SM size: " << proc->getStateMachines().size() << std::endl;
			if(proc->getStateMachines().size() > 1){
				int stateMachineId = 1;
				std::list<StateMachine*> sms = proc->getStateMachines();
				for(std::list<StateMachine*>::iterator it = (++sms.begin()); it != sms.end(); ++it){
					std::string stateMachineFunctionStr = "void stateMachine" + std::to_string(stateMachineId) + "Behavior(){\n";
					stateMachineFunctionStr += "int __sm" + std::to_string(stateMachineId) + "State = " + "STATE__"+(*it)->getStartVertex()->getName() + ";\n";
					stateMachineFunctionStr += "while(__sm" + std::to_string(stateMachineId) + "State != " + (*it)->getEndVertex()->getName() + "){\n";
					stateMachineFunctionStr += "\tswitch(__sm" + std::to_string(stateMachineId) + "State){\n";
					std::cout << "HERE"<< stateMachineId << std::endl;
					stateMachineFunctionStr += this->generateStateBehavior((*it));
					std::cout << "HERE" << std::endl;
					stateMachineFunctionStr += "\t}\n";
					stateMachineFunctionStr += "\t\tdefault: break;\n";
					stateMachineFunctionStr += "\t}\n";
					stateMachineFunctionStr += "}\n";
					outStr += stateMachineFunctionStr + "\n";
					stateMachineId ++;
				}
			}
			std::cout << "generateSMLoopOther Over" << std::endl;
			return outStr;
		}

		std::string CPPCodeGenerator::generateStateBehavior(StateMachine* sm)
		{
			std::string casesBody;
			std::string caseTab = "\t\t\t";
			std::string caseBodyTab = "\t\t\t\t";
			
			std::cout << "GenStateBehave" << std::endl;
			for(Vertex* v : sm->getVertices()){
				
				std::cout << "vertex " + v->getName() << std::endl;
				casesBody += (caseTab + "case STATE__" + v->getName() + ":{") + CR;
				casesBody += (caseBodyTab + "std::cout << \"--------------------STATE__" + v->getName() + "\" << std::endl;\n");
				bool elseIf = false;
				bool elseGen = false;
				bool hasCondition = false;
				for(Edge* e : sm->getEdges()){
					std::cout << "edge loop" << std::endl;
					if(!e->getFromVertex()->getName().compare(v->getName())){
						// if the edge starts from v
						// makesure Make sure guard to string method
						std::cout << e->getFromVertex()->getName() << v->getName() << std::endl;
						
						std::cout << "caseBody"<< std::endl;
						if(!e->isGuardNull()){
							hasCondition = true;
							std::cout << "generate If branch: " << e->getGuard()->to_string() << std::endl;
							casesBody += (caseBodyTab + (elseIf ? "else if(" : "if(") + e->getGuard()->to_string() + "){") + CR;
							for(Action* a : e->getActions()){
								if(!a->hasNext()){
									casesBody += TAB + (caseBodyTab + a->to_string() + ";") + CR;
								}
							}
							casesBody += ("\t\t\t\t__currentState = STATE__" + e->getToVertex()->getName()) + ";\n";
							std::cout << "generate If branch end" << std::endl;
							casesBody += (caseBodyTab + "}") + CR;
							elseIf = true;
						} else {
							elseGen = true;
							casesBody += (caseBodyTab + (elseIf ? "else {"  : "") + CR);
							for(Action* a : e->getActions()){
								casesBody += TAB + (caseBodyTab + a->to_string() + ";") + CR;
							}
							casesBody += ("\t\t\t\t__currentState = STATE__" + e->getToVertex()->getName()) + ";\n";
							casesBody += (caseBodyTab + (elseIf ? "}"  : "") + CR);
							
						}
					}
					
					
					std::cout << "edge loop end" << std::endl;
				}
				if(!elseGen && hasCondition){
						casesBody += (caseBodyTab + "else {" + CR);
						if(DEMO){
							casesBody += (caseBodyTab + "__currentState = STATE___final;\n");
						} else {
							casesBody += (caseBodyTab + "__currentState = -100;\n");
						}	
						casesBody += (caseBodyTab + "}\n");
				}
				if(!v->getName().compare("_final")){
					casesBody += (caseBodyTab + "\t__currentState = -100;\n");
				}
				casesBody += "\t\t\t\tbreak;\n";
				
				casesBody += "\t\t\t}\n";
			}
			std::cout << "GenStateBehave Over" << std::endl;
			return casesBody;
		}

        int getAttrsLen(const list<Attribute*>& attrs)
        {
            int len = 0;
            for (auto& attr : attrs) {
                len += attr->getLength();
            }
            return len;
        }

        std::string generateAttr(const std::string& typeName, const std::string& id, bool isArray, int len)
        {
            if (typeName == "int" && isArray) {
                return "u_int " + id + "[" + std::to_string(len) + "];\n";
            } else if (typeName == "int" && len == 4) {
                return "u_int " + id + ";\n";
            } else if (typeName == "int" && len == 2) {
                return "u_short " + id + ";\n";
            } else if (typeName == "byte" && isArray) {
                return "u_char " + id + "[" + std::to_string(len) + "];\n";
            } else if (typeName == "byte") {
                return "u_char " + id + ";\n";
            } else if (typeName == "ByteVec") {
                return "u_char* " + id + ";\n";
            }
            if (typeName == "byte") {
                std::cout << "isArray: " << isArray <<  ", len: " << len << std::endl;
            }
            return typeName + " " + id + ";\n";
        }

        /*-------------Generate UserTypes-------------*/
		void CPPCodeGenerator::generateUserTypes(std::string path, Model* model)
		{
			std::ofstream outUserTypeFile;
		    //TODO: make sure here
		    std::string fileName = "UserType.hpp";
		    std::string outStr = "";
			std::cout << "generate Usertype" << std::endl;
			outStr += this->generateCommonIncludes();
			// outStr += this->generateTimer();
			for(UserType* u : model->getUserTypes())
			{
				//make sure 
				if(u->getName() == ""){
					continue;
				}
                outStr += ("#pragma pack(1)\n");
				if(u->getBase()){
					outStr += ("struct " + u->getName() + " : public " + u->getBase()->getName() + "{") + CR;
                    if (u->getBase()->getName() == "Message") {
                        // outStr += "\tpublic:\n";
                        auto len = getAttrsLen(u->getAttributes());
                        outStr += "\t\tu_int getLen() {return " + std::to_string(len) + ";}\n";
                        if (u->getSigLen() != 0) {
                            outStr += "\t\tu_char* getSig() {return " + u->getAttributes().back()->getIdentifier() + ";}\n";
                            outStr += "\t\tu_int getSigLen() {return " + std::to_string(u->getSigLen()) + ";}\n";
                        }
                        outStr += "\n\n";
                    }
				} else {
					outStr += ("struct " + u->getName() + "{") + CR;
				}
                
                if (u->getName() == "ByteVec") {
                    // ByteVec
                    // outStr += "\tpublic:\n";
                    outStr += "\t\tvirtual u_int getLen() {return 0;}\n";
                    outStr += "\t\tvirtual u_char* getSig() {return NULL;}\n";
                    outStr += "\t\tvirtual u_int getSigLen() {return 0;}\n";
                } else {
                    // if (u->getAttributes().size() > 0) {
                    //     outStr += "\tpublic:\n";
                    // }
                    for(Attribute* a : u->getAttributes())
                    {
                        outStr += "\t\t" + generateAttr(a->getType()->getName(), a->getIdentifier(), a->getArray(), a->getLength());
                        // outStr += "\t\t" + (a->getType()->getName() + " " + a->getIdentifier()) + ";\n";
                    }
                    for(Method* m : u->getMethods()){
                        auto& rttStr = m->getReturnType()->getName();
                        m->getAttributes().size();
                        auto methodSig = generateMethodSignature(rttStr, "", m->getName(), m->getAttributes());
                        outStr += methodSig + "\t\t\t" + m->getReturnType()->getName() + " " + "result;\n";
                        outStr += "\t\t}\n";
                    }
                }

				outStr += "};\n";
                outStr += ("#pragma pack()\n");
			}
			
			// outStr += this->generateSerializeBinding(model);
			std::cout << "end usertypes" << std::endl;
			outUserTypeFile.open(path  + "/" + fileName, std::ofstream::out | std::ostream::out);
			outUserTypeFile << outStr << std::endl;
			outUserTypeFile.close();
		}

		void CPPCodeGenerator::generateUserTypesWin(std::string path, Model* model)
		{
			std::ofstream outUserTypeFile;
		    //TODO: make sure here
		    std::string fileName = "UserType.hpp";
		    std::string outStr = "";
			std::cout << "generate Usertype" << std::endl;
			outStr += this->generateCommonIncludesWin();
			outStr += this->generateTimer();
			for(UserType* u : model->getUserTypes())
			{
				//make sure 
				if(!u->getName().compare("")){
					continue;
				}
				if(u->getBase()){
					outStr += ("class " + u->getName() + " : public " + u->getBase()->getName() + "{") + CR;
				} else {
					outStr += ("class " + u->getName() + "{") + CR;
				}
				outStr += "\tpublic:\n";
				if(!u->getName().compare("ByteVec")){
					outStr += "\t\tstd::string str;\n";
				}
				for(Attribute* a : u->getAttributes())
				{
					outStr += "\t\t" + (a->getType()->getName() + " " + a->getIdentifier()) + ";\n";
				}
				if(!u->getName().compare("ByteVec")){
					outStr += "\t\tstd::string getStr();\n";
				}
				for(Method* m : u->getMethods()){
					outStr += "\t\t" + (m->getReturnType()->getName() + " " + m->getName() + "(");
					int i = 1;
					if(m->getAttributes().size() > 0){
						for(Attribute* a : m->getAttributes()){
							if(i < m->getAttributes().size()){	
								outStr += a->getType()->getName() + " " + a->getIdentifier() + ", ";
							} else {
								outStr += a->getType()->getName() + " " + a->getIdentifier() + "){\n";
							}
						}
					} else {
						outStr += "){\n";
					}
					
					outStr += "\t\t\t" + m->getReturnType()->getName() + " " + "result;\n";
					outStr += 
				//outStr += this->generateByteVecAndTimer();"\t\t\treturn result;\n"; 
					outStr += "\t\t}\n";
				}
				outStr += "};\n";
				std::cout << outStr << std::endl;
			}
			
			std::cout << "end usertypes" << std::endl;
			outUserTypeFile.open(path  + "/" + fileName, std::ofstream::out | std::ostream::out);
			outUserTypeFile << outStr << std::endl;
			outUserTypeFile.close();
		}

		std::string CPPCodeGenerator::generateSerializeBinding(Model* model){
			std::string outStr = "namespace boost{\n";
			outStr += "\tnamespace serialization{\n";
			
			for(UserType* ut : model->getUserTypes()){
				outStr += "\t\ttemplate<class Archive>\n";
				outStr += "\t\tvoid serialize(Archive & ar, " + ut->getName() + " & d, const unsigned int version){\n";
				if(!ut->getName().compare("ByteVec")){
					outStr += "\t\t\tar& d.str;\n";
				}
				for(Attribute* a : ut->getAttributes()){
					outStr += "\t\t\tar& d." + a->getIdentifier() + ";\n";
				}
				outStr += "\t\t}\n";
			}
			outStr += "\t}\n";
			outStr += "}\n";
			return outStr;
		}


		std::string CPPCodeGenerator::generateTimer(){
			std::string outStr = "";
			outStr += "class Timer {\n";
			outStr += "\tpublic: \n";
			outStr += "\t\t int reset();\n";
			outStr += "\t\t int time;\n";
			outStr += "};\n";
			return outStr;
		}

		/*---------Generate Compile Auxiliary--------*/
		void CPPCodeGenerator::generateCompileFile(std::string path, Model* model)
		{
			std::ofstream outCompileFile;
			std::cout << "generate compile auxiliary" << std::endl;
			std::string outStr = "import os\n";
			outStr += "import sys\n";
			outStr += "os.system(\"g++ -g -c CommLib/NetComm/src/*.cpp\")\n";
			outStr += "os.system(\"ar cqs libnetcomm.a ./*.o\")\n";
			outStr += "os.system(\"mv *.o CommLib/NetComm/src/\")\n";
			outStr += "os.system(\"mv *.a CommLib/NetComm/src/\")\n";
			outStr += "os.system(\"g++ -g -c CryptoLib/src/*.cpp\")\n";
			outStr += "os.system(\"ar cqs libcryptorlib.a ./*.o\")\n";
			outStr += "os.system(\"mv *.o CryptoLib/src/\")\n";
			outStr += "os.system(\"mv *.a CryptoLib/src/\")\n";
			for(Process* proc : model->getProcesses())
			{
				outStr += "os.system(\"g++ -g -o " + proc->getName() + " ./generatedSrc/" + proc->getName() +  
				".cpp -L./CommLib/NetComm/src/ -lnetcomm -L./CryptoLib/src/ -lcryptorlib -lssl -lcrypto -lpcap -lboost_serialization\")\n";
			}
			outCompileFile.open(path  + "/compile.py", std::ofstream::out | std::ostream::out);
			outCompileFile << outStr << std::endl;
			std::cout << outStr << std::endl;
			outCompileFile.close();
		}

		
		void CPPCodeGenerator::generateCompileFileWin(std::string path, Model* model)
		{
			std::ofstream outCompileFile;
			std::cout << "generate compile auxiliary" << std::endl;
			std::string outStr = "import os\n";
			outStr += "import sys\n";
			for(Process* proc : model->getProcesses())
			{
				outStr += "os.system(\"g++ -g -o " + proc->getName() + " ./generatedSrc/" + proc->getName() +  ".cpp\")\n";
				outStr += "t = os.path.isfile(\"./" + proc->getName() + "\")\n";
				outStr += "if t:\n";
				outStr += "\tos.system(\"echo #false#\")\n";
			}
			outCompileFile.open(path  + "/compile.py", std::ofstream::out | std::ostream::out);
			outCompileFile << outStr << std::endl;
			std::cout << outStr << std::endl;
			outCompileFile.close();
		}

		/*---------Gen---------*/
        void  CPPCodeGenerator::generateCodeProc(std::string path, Process* proc)
		{
			this->generateHeaderFile(path, proc);
			this->generateSrcFile(path, proc);
		}
		

		void CPPCodeGenerator::generateCodeProcWin(std::string path, Process* proc){
			this->generateHeaderFileWin(path, proc);
			this->generateSrcFile(path, proc);
		}

        void CPPCodeGenerator::generateAll(std::string path, Model* model)
		{
			this->generateUserTypes(path, model);
			for(Process* proc : model->getProcesses())
			{
				this->generateCodeProc(path, proc);
			}
			this->generateCompileFile(path, model);
		}

		void CPPCodeGenerator::generateAllWin(std::string path, Model* model){
			this->generateUserTypesWin(path, model);
			for(Process* proc : model->getProcesses()){
				this->generateCodeProcWin(path, proc);
			}
			this->generateCompileFileWin(path, model);
		}

		void CPPCodeGenerator::generateRefine(std::string path, Model* model){
			this->generateUserTypes(path, model);
			for(Process* proc : model->getProcesses())
			{
				this->generateSrcFile(path, proc);
			}
			this->generateCompileFile(path, model);
		}


        //constructors
         CPPCodeGenerator::CPPCodeGenerator(/*args*/)
         {

         }

         CPPCodeGenerator::~CPPCodeGenerator()
         {

         }
    
}