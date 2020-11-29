#include "Parser/XmlParser/XmlParser.hpp"
#include "Parser/LParser/LParser.hpp"
#include "Manage.hpp"
using std::cout, std::endl;
namespace isadt {
    void XmlParser::parse(const char* fileName, Model* model) {
        XMLDocument doc;
        doc.LoadFile(fileName);
        XMLElement* root = doc.RootElement();
        if (! (root -> NoChildren())) {
            root = root -> FirstChildElement();
            while (root) {
                if (strcmp(root -> Value(), "ClassDiagram") == 0) {
                    parseClassDiagram(root, model);
                } else if (strcmp(root -> Value(), "ProcessToSMs") == 0) {
                    parseProcessToSMs(root, model);
                }
                root = root -> NextSiblingElement();
            }
        }
        for (auto proc : model -> getProcesses()) {
            proc -> mkCompositeStateMachine();
        }
    }

    void XmlParser::parseClassDiagram(XMLElement* root, Model* model) {
        if (! (root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                if (strcmp(element -> Value(), "UserType") == 0) {
                    parseUserType(element, model);
                } else if (strcmp(element -> Value(), "Process") == 0) {
                    parseProcess(element, model);
                } else if (strcmp(element -> Value(), "CommChannel") == 0) {
                    parseCommChannel(element, model);
                } else if (strcmp(element -> Value(), "InitialKnowledge") == 0) {
                    parseInitialKnowledge(element, model);
                } else if (strcmp(element -> Value(), "SafetyProperty") == 0) {
                    parseSafetyProperty(element, model);
                } else if (strcmp(element -> Value(), "SecurityProperty") == 0) {
                    parseSecurityProperty(element, model);
                }
                element = element -> NextSiblingElement();
            }
        }
    }

    void XmlParser::parseCommChannel(XMLElement* root, Model* model) {
        if (! (root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                auto p1 = model -> getProcByName(element -> Attribute("processA"));
                auto p2 = model -> getProcByName(element -> Attribute("processB"));
                auto cm1 = p1 -> getCommMethodByName(element -> Attribute("commMethodA"));
                auto cm2 = p2 -> getCommMethodByName(element -> Attribute("commMethodB"));
                string privacy = element -> Attribute("privacy");
                model -> mkChannel(p1, cm1, p2, cm2, (privacy == "True"));
                element = element -> NextSiblingElement();
            }
        }
    }

    void XmlParser::parseProcessToSMs(XMLElement* root, Model* model) {
        if (! (root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                if (strcmp(element -> Value(), "ProcessToSM") == 0) {
                    auto proc = model -> getProcByName(element -> Attribute("process"));
                    if (! (element -> NoChildren())) {
                        auto node = element -> FirstChildElement();
                        while (node) {
                            parseStateMachine(node, model, proc);
                            node = node -> NextSiblingElement();
                        }
                    }
                }
                element = element -> NextSiblingElement();
            }
        }
    }

    Attribute* XmlParser::parseAttribute(XMLElement* root, Struct* s, Model* model) {
        //cout << root -> Attribute("identifier") << endl;
        return s -> mkAttribute(model -> getUserTypeByName(root -> Attribute("type")),
                                root -> Attribute("identifier"),
                                strcmp(root -> Attribute("isArray"), "False"));
    }

    Method* XmlParser::parseMethod(XMLElement* root, Class* s, Model* model) {
        auto method = s -> mkMethod(root -> Attribute("name"),
                                    model -> getUserTypeByName(root -> Attribute("returnType")), 
                                    root -> Attribute("cryptoSuffix"), "");
        //cout << "method: " + method -> getName() << endl;
        if (!(root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                auto attr = parseAttribute(element, method, model);
                element = element -> NextSiblingElement();
            }
        }
        return method;
    }

    CommMethod* XmlParser::parseCommMethod(XMLElement* root, Process* s, Model* model) {
        auto method = s -> mkCommMethod(root -> Attribute("name"), nullptr,
                                        strcmp(root -> Attribute("inOutSuffix"), "In"),
                                        root -> Attribute("commWay"));
        //cout << "commMethod: " + method -> getName() << endl;
        if (strcmp(root -> Attribute("commWay"), "NativeEthernetFrame") == 0) {
            method -> setType(root -> Attribute("typeId"));
        }
        if (!(root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                auto attr = parseAttribute(element, method, model);
                element = element -> NextSiblingElement();
            }
        }
        return method;
    }

    void XmlParser::parseUserType(XMLElement* root, Model* model) {
        const string& typeStr = root -> Attribute("name");
        auto type = Manage::getType(typeStr);
        if (type) {
            model -> addUserType(type);
            return;
        }
        auto userType = model -> getUserTypeByName(typeStr);
        auto base = root -> Attribute("parent");
        if (base) {
            userType -> setBase(model -> getUserTypeByName(base));
        }
        if (strcmp(base, "Message") == 0) {
            userType -> setMsgType(root -> Attribute("msgType"));
            if (strcmp(root -> Attribute("signLen"), "") != 0) {
                userType -> setSigLen(root -> Attribute("signLen"));
            }
        }
        if (!(root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                if (strcmp(element -> Value(), "Attribute") == 0) {
                    auto attr = parseAttribute(element, userType, model);
                    if (strcmp(base, "Message") == 0) {
                        if (strcmp(element -> Attribute("len"), "") != 0) {
                            attr -> setLength(element -> Attribute("len"));
                        }
                    }
                } else {
                    auto method = parseMethod(element, userType, model);
                }
                element = element -> NextSiblingElement();
            }
        }
    }

    void XmlParser::parseProcess(XMLElement* root, Model* model) {
        auto proc = model -> getProcByName(root -> Attribute("name"));
        //cout << "proc: " + proc -> getName() << endl;
        if (!(root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                if (strcmp(element -> Value(), "Attribute") == 0) {
                    auto attr = parseAttribute(element, proc, model);
                } else if (strcmp(element -> Value(), "Method") == 0) {
                    auto method = parseMethod(element, proc, model);
                } else if (strcmp(element -> Value(), "CommMethod") == 0) {
                    auto method = parseCommMethod(element, proc, model);
                }
                element = element -> NextSiblingElement();
            }
        }
        proc -> setOriginalAttributes();
    }

    Edge* XmlParser::parseEdge(XMLElement* root, Model* model, Process* proc, StateMachine* sm) {
        auto s = sm -> getVertexByName1(root -> Attribute("source"));
        auto t = sm -> getVertexByName1(root -> Attribute("dest"));
        auto e = sm -> mkEdge(s, t);
        auto guardStr = root -> Attribute("guard");
        if (guardStr != nullptr && strcmp(guardStr, "") != 0) {
            LParser::parseGuard(guardStr, model, proc, e);
        }
        if (!(root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                if (strcmp(element -> Value(), "Action") == 0) {
                    LParser::parseAction(element -> Attribute("content"), model, proc, e);
                }
                element = element -> NextSiblingElement();
            }
        }
        return e;
    }

    StateMachine* XmlParser::parseStateMachine(XMLElement* root, Model* model, Process* proc) {
        auto sm = proc -> mkStateMachine(proc -> getVertexByName(root -> Attribute("refine_state")));
        sm -> mkStartVertex("_init");
        sm -> mkEndVertex("_final");
        if (!(root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                if (strcmp(element -> Value(), "Transition") == 0) {
                    auto e = parseEdge(element, model, proc, sm);
                } else if (strcmp(element -> Value(), "State") == 0) {
                    auto s = sm -> getVertexByName1(element -> Attribute("name"));
                    proc -> addVertex(s);
                }
                element = element -> NextSiblingElement();
            }
        }
        return sm;
    }

    void XmlParser::parseInitialKnowledge(XMLElement* root, Model* model) {
        if (!(root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                if (strcmp(element -> Value(), "Knowledge") == 0) {
                    parseK(element, model);
                } else if (strcmp(element -> Value(), "KeyPair") == 0) {
                    parseKP(element, model);
                }
                element = element -> NextSiblingElement();
            }
        }
    }

    void XmlParser::parseK(XMLElement* root, Model* model) {
        auto proc = model -> getProcByName(root -> Attribute("process"));
        model -> mkInitialKnowledge(proc, proc -> getAttributeByName(root -> Attribute("attribute")));
    }

    void XmlParser::parseKP(XMLElement* root, Model* model) {
        auto proc1 = model -> getProcByName(root -> Attribute("pubProcess"));
        auto proc2 = model -> getProcByName(root -> Attribute("secProcess"));
        model -> mkInitialKnowledge(proc1, proc1 -> getAttributeByName(root -> Attribute("pubKey")),
                                    proc2, proc2 -> getAttributeByName(root -> Attribute("secKey")));
    }

    void XmlParser::parseSafetyProperty(XMLElement* root, Model* model) {
        if (!(root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                if (strcmp(element -> Value(), "CTL") == 0) {
                    parseCTL(element, model);
                } else if (strcmp(element -> Value(), "Invariant") == 0) {
                    parseInv(element, model);
                }
                element = element -> NextSiblingElement();
            }
        }
    }

    void XmlParser::parseCTL(XMLElement* root, Model* model) {
        model -> mkSafetyProperty(root -> Attribute("formula"));
    }

    void XmlParser::parseInv(XMLElement* root, Model* model) {
        model -> mkSafetyProperty(root -> Attribute("content"));
    }

    void XmlParser::parseSecurityProperty(XMLElement* root, Model* model) {
        if (!(root -> NoChildren())) {
            auto element = root -> FirstChildElement();
            while (element) {
                if (strcmp(element -> Value(), "Confidential") == 0) {
                    parseConfidential(element, model);
                } else if (strcmp(element -> Value(), "Authenticity") == 0) {
                } else if (strcmp(element -> Value(), "Integrity") == 0) {
                    parseIntegrity(element, model);
                } else if (strcmp(element -> Value(), "Availability") == 0) {
                    parseAvailability(element, model);
                }
                element = element -> NextSiblingElement();
            }
        }
    }

    void XmlParser::parseConfidential(XMLElement* root, Model* model) {
        auto proc = model -> getProcByName(root -> Attribute("process"));
        model -> mkConfidentialProperty(proc, proc -> getAttributeByName(root -> Attribute("attribute")));
    }

    void XmlParser::parseIntegrity(XMLElement* root, Model* model) {
        auto proc1 = model -> getProcByName(root -> Attribute("processA"));
        auto proc2 = model -> getProcByName(root -> Attribute("processB"));
        model -> mkIntegratyProperty(proc1, root -> Attribute("stateA"), proc1 -> getAttributeByName(root -> Attribute("attributeA")),
                                     proc2, root -> Attribute("stateB"), proc2 -> getAttributeByName(root -> Attribute("attributeB")));
    }

    void XmlParser::parseAvailability(XMLElement* root, Model* model) {
        auto proc = model -> getProcByName(root -> Attribute("process"));
        model -> mkAvailabilityProperty(proc, root -> Attribute("state"));
    }
}
