#include "Verifier/ProverifTranslator.hpp"
#include "Verifier/mkInitialKnowledge.hpp"
#include "Verifier/mkProcesses.hpp"
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>

namespace isadt {
    void ProverifTranslator::proverifTranslate(Model* model) {
        //std::cout << "It's OK!" << std::endl;
        std::string dstFile = "proverifModel.pv";
        std::ofstream out;
        out.open(dstFile, std::ios::trunc);

        out << "free c : channel .\n";
        for (auto type : model->getUserTypes()) {
            if (type->getName() != "host" &&
                type->getName() != "nonce" &&
                type->getName() != "pk" &&
                type->getName() != "sk" &&
                type->getName() != "spk" &&
                type->getName() != "ssk" &&
                type->getName() != "msg")
                out << "type " << type->getName() << ".\n";
        }
        out << "type msg.\n"
               "type host.\n"
               "type int.\n"
               "type nonce.\n"
               "type pk.\n"
               "type sk.\n"
               "type spk.\n"
               "type ssk.\n"
               "\n"
               "fun nonce_to_bitstring(nonce): bitstring [data,typeConverter].\n"
               "\n"
               "(* Public key encryption *)\n"
               "\n"
               "fun pk1(sk): pk.\n"
               "fun encrypt(bitstring, pk): bitstring.\n"
               "reduc forall x: bitstring, y: sk; decrypt(encrypt(x,pk1(y)),y) = x.\n"
               "\n"
               "(* Signatures *)\n"
               "\n"
               "fun spk1(ssk): spk.\n"
               "fun sign(bitstring, ssk): bitstring.\n"
               "reduc forall m: bitstring, k: ssk; getmess(sign(m,k)) = m.\n"
               "reduc forall m: bitstring, k: ssk; checksign(sign(m,k), spk1(k)) = m.\n"
               "\n"
               "(* Shared key encryption *)\n"
               "\n"
               "fun sencrypt(bitstring,nonce): bitstring.\n"
               "reduc forall x: bitstring, y: nonce; sdecrypt(sencrypt(x,y),y) = x.\n"
               "\n"
               "fun SymEnc(ByteVec, ByteVec):ByteVec.\n"
               "reduc forall m:ByteVec, k:ByteVec;SymDec(SymEnc(m,k),k)=m.\n"
               "\n"
               "fun pkByte(ByteVec):ByteVec.\n"
               "fun AsymEnc(ByteVec, ByteVec):ByteVec.\n"
               "reduc forall m:ByteVec, k:ByteVec;AsymDec(AsymEnc(m,pkByte(k)),k)=m." << std::endl;

        //out << "free Na,Nb: bitstring [private].\n"
        //       "query secret nonceA;\n"
        //       "      secret nonceB.\n";
        // Add event
        unordered_map<string, Vertex*> vms;
        for (auto process : model->getProcesses()) {
            out << "event " << process->getName() << "__init().\n";
            out << "event " << process->getName() << "__final().\n";
            auto vertexMap = process->getVertexMap();
            for (auto event : vertexMap) {
                //out << "event " << (string)event.first << "().\n";
                string eventName = process->getName() + "_" + event.first;
                Vertex* vertex = event.second;
                vms[eventName] = vertex;
            }
        }

        for (auto vm : vms) {
            out << "event " << (string)vm.first << "().\n";
        }
        // Add queries in proverif file
        for (auto property : model->getProps())
        {
            //std::cout << ((ConfidentialProperty*)property)->getAttribute()->getIdentifier() << std::endl;
            switch(property->getPropertyType()) {
                case CONFIDENTIAL: {
                    string queryParam = ((ConfidentialProperty *) property)->getAttribute()->getIdentifier();
                    out << "query secret " << queryParam << ".\n";
                    break;
                }
                case AUTHENTICITY: {
                    auto authenticityProperty = ((AuthenticityProperty *) property);
                    string queryParam1 = authenticityProperty->getValue1Proc()->getName()+"_"+authenticityProperty->getValue1Vertex()->getName();
                    string queryParam2 = authenticityProperty->getValue2Proc()->getName()+"_"+authenticityProperty->getValue2Vertex()->getName();
                    out << "query event(" << queryParam1 << "()) ==> event(" << queryParam2 << "()).\n";
                    break;
                }
                case AVAILABILITY: {
                    auto availabilityProperty = ((AvailabilityProperty*) property);
                    string queryParam1 = availabilityProperty->getValueProc()->getName()+"_"+availabilityProperty->getValueVertex();
                    string queryParam2 = availabilityProperty->getValueProc()->getName()+"__init";
                    out << "query event(" << queryParam1 << "()) ==> event(" << queryParam2 << "()).\n";
                    break;
                }
                default:
                    break;
            }
        }
//        out << "event beginBparam(pkey).\n"
//               "event endBparam(pkey).\n"
//               "event beginAparam(pkey).\n"
//               "event endAparam(pkey).\n\n";
        // Add processes
        out << mkProcesses(model);
        // Add starting process
        out << "process \n";
        out << mkInitialKnowledge(model);
        out << mkInitialProcess(model);
        out.close();
    }
}