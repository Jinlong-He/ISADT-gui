#include "Model/Struct/Struct.hpp"
namespace isadt {
    void Struct::setName(const string& name) {
        name_ = name;
    }

    const string& Struct::getName() const {
        return name_;
    }

    Attribute* Struct::mkAttribute(UserType* type, const string& name, int array) {
        Attribute* attr = new Attribute(type, name, array);
        attributes_.push_back(attr);
        attributeMap_[name] = attr;
        attributeIdMap_[name] = attributes_.size() - 1;
        return attr;
    }

    //Attribute* Struct::mkAttribute(const string& name) {
    //    return mkAttribute(nullptr, name);
    //}

    Attribute* Struct::getAttributeByName(const string& name) {
        if (attributeMap_.count(name) == 0) return nullptr;
        return attributeMap_[name];
    }

    bool Struct::hasAttribute(const string& name) const {
        return attributeMap_.count(name);
    }

    const list<Attribute*>& Struct::getAttributes() const {
        return attributes_;
    }

    size_t Struct::getID(const string& name) const {
        if (attributeIdMap_.count(name) == 0) return -1;
        return attributeIdMap_.at(name);
    }
}
