#include "Model/Struct/Class.hpp"
namespace isadt {
    Method* Class::mkMethod(const string& name, UserType* returnType,
                            const string& algorithmId, const string& userCode) {
        Method* m = new Method(name, returnType, algorithmId, userCode);
        methods_.push_back(m);
        methodMap_[name] = m;
        return m;
    }

    Method* Class::mkMethod(const string& name) {
        return mkMethod(name, nullptr, "", "");
    }

    Method* Class::getMethodByName(const string& name) {
        if (methodMap_.count(name) == 0) return nullptr;
        return methodMap_[name];
    }

    bool Class::hasMethod(const string& name) const {
        return methodMap_.count(name);
    }

    const list<Method*>& Class::getMethods() const {
        return methods_;
    }
}
