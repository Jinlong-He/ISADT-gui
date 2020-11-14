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
        std::string dstFile = "verify.pv";
        std::ofstream out;
        out.open(dstFile, std::ios::trunc);

        out << "free c : channel .\n";
        for (auto type : model->getUserTypes()) {
            if (type->getName() != "host" &&
                type->getName() != "nonce" &&
                type->getName() != "pkey" &&
                type->getName() != "skey" &&
                type->getName() != "spkey" &&
                type->getName() != "sskey" &&
                type->getName() != "pk" &&
                type->getName() != "sk")
                out << "type " << type->getName() << ".\n";
        }
        out << "type host.\n"
               "type nonce.\n"
               "type pkey.\n"
               "type skey.\n"
               "type spkey.\n"
               "type sskey.\n"
               "\n"
               "fun nonce_to_bitstring(nonce): bitstring [data,typeConverter].\n"
               "\n"
               "(* Public key encryption *)\n"
               "\n"
               "fun pk(skey): pkey.\n"
               "fun encrypt(bitstring, pkey): bitstring.\n"
               "reduc forall x: bitstring, y: skey; decrypt(encrypt(x,pk(y)),y) = x.\n"
               "\n"
               "(* Signatures *)\n"
               "\n"
               "fun spk(sskey): spkey.\n"
               "fun sign(bitstring, sskey): bitstring.\n"
               "reduc forall m: bitstring, k: sskey; getmess(sign(m,k)) = m.\n"
               "reduc forall m: bitstring, k: sskey; checksign(sign(m,k), spk(k)) = m.\n"
               "\n"
               "(* Shared key encryption *)\n"
               "\n"
               "fun sencrypt(bitstring,nonce): bitstring.\n"
               "reduc forall x: bitstring, y: nonce; sdecrypt(sencrypt(x,y),y) = x.\n"
               "\n"
               "fun aenc(bitstring,pkey):bitstring.\n"
               "reduc forall x:bitstring,y:skey;adec(aenc(x,pk(y)),y)=x.\n"<< std::endl;

        // Add queries in proverif file
        for (auto property : model->getProcesses())
        {
            if (typeid(property).name()==typeid(ConfidentialProperty).name())
            {
                string queryParam = ((ConfidentialProperty*)property)->getAttribute()->getIdentifier();
                out << "query attacker(" << queryParam << ").\n";
            }
        }
        out << "free Na,Nb: bitstring [private].\n"
               "query secret nonceA;\n"
               "      secret nonceB.\n";
        // Add event
        unordered_map<string, Vertex*> vms;
        for (auto process : model->getProcesses()) {
            auto vertexMap = process->getVertexMap();
            for (auto event : vertexMap) {
                //out << "event " << (string)event.first << "().\n";
                vms.insert(event);
            }
        }

        for (auto vm : vms) {
            out << "event " << (string)vm.first << "().\n";
        }

        out << "event beginBparam(pkey).\n"
               "event endBparam(pkey).\n"
               "event beginAparam(pkey).\n"
               "event endAparam(pkey).\n\n";
        // Add processes
        out << mkProcesses(model);
        // Add starting process
        out << "process \n"
               "\t";
        out << mkInitialKnowledge(model);
        out << mkInitialProcess(model);
        out.close();
    }
}