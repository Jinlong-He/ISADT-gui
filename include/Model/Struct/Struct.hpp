//
//  Struct.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Struct_hpp
#define Model_Struct_hpp
#include <list>
#include <unordered_map>
#include "../Process/Attribute.hpp"
using std::list;
using std::unordered_map;
namespace isadt {
    class Struct {
    public:
        Struct()
            : name_("") {}

        Struct(const string& name) 
            : name_(name) {}

        ~Struct() {
            for (auto attr : attributes_) {
                delete attr;
                attr = nullptr;
            }
        }
        void setName(const string& name);
        const string& getName() const;

        Attribute* mkAttribute(UserType* type, const string& name, int array = 0);
        //Attribute* mkAttribute(const string& name);
        Attribute* getAttributeByName(const string& name);
        bool hasAttribute(const string& name) const;
        const list<Attribute*>& getAttributes() const;
    protected: 
        string name_;
        list<Attribute*> attributes_;
        unordered_map<string, Attribute*> attributeMap_;
    };
}

#endif /* Model_Struct_hpp */
