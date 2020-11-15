//
//  Property.hpp
//
//  Created by Jinlong He on 2019/11/14.
//  Copyright © 2019 All rights reserved.
//

#ifndef Model_Property_hpp
#define Model_Property_hpp 
#include "../Process/Attribute.hpp"
#include "../StateMachine/Vertex.hpp"

namespace isadt {
    class Process;
    enum PropertyType {CONFIDENTIAL, AUTHENTICITY, INTEGRATY, AVAILABILITY, CTL, INVARIANT};
    class Property {
    public:
        Property() {}
        virtual PropertyType getPropertyType() const = 0;
    };

    class SecurityProperty : public Property {
    public:
        SecurityProperty()
            : Property() {}
        virtual PropertyType getPropertyType() const {};
    };

    class SafetyProperty : public Property{
    public:
        SafetyProperty()
            : Property() {}

        SafetyProperty(const string& str)
            : Property(),
              propertyStr_(str) {}

        const string& getPropertyStr() const {
            return propertyStr_;
        }

        virtual PropertyType getPropertyType() const {};

    private:
        string propertyStr_;
    };

    class ConfidentialProperty : public SecurityProperty {
    public:
        ConfidentialProperty()
            : SecurityProperty(),
              proc_(nullptr),
              attribute_(nullptr) {}
        ConfidentialProperty(Process* proc, Attribute* attribute)
            : SecurityProperty(),
              proc_(proc),
              attribute_(attribute) {}
    public:
        Attribute* getAttribute() {return this->attribute_;}
        PropertyType getPropertyType() const { return CONFIDENTIAL; }
    private:
        Process* proc_;
        Attribute* attribute_;
    };

    class AuthenticityProperty : public SecurityProperty {
    public:
        AuthenticityProperty()
            : SecurityProperty(),
              value1_(nullptr),
              value2_(nullptr) {}
        AuthenticityProperty(Process* proc1, Vertex* vertex1, Attribute* attribute1, Attribute* inner1,
                             Process* proc2, Vertex* vertex2, Attribute* attribute2, Attribute* inner2)
            : SecurityProperty(),
              value1_(new Value(proc1, vertex1, attribute1, inner1)),
              value2_(new Value(proc2, vertex2, attribute2, inner2)) {}
        ~AuthenticityProperty() {
            delete value1_;
            value1_ = nullptr;
            delete value2_;
            value2_ = nullptr;
        }
        PropertyType getPropertyType() const { return AUTHENTICITY; }
        Process* getValue1Proc() { return this->value1_->getProc(); }
        Process* getValue2Proc() { return this->value2_->getProc(); }
        Vertex* getValue1Vertex() { return this->value1_->getVertex(); }
        Vertex* getValue2Vertex() { return this->value2_->getVertex(); }
    private:
        struct Value {
        public:
            Value()
                : proc_(nullptr),
                  vertex_(nullptr),
                  attribute_(nullptr),
                  inner_(nullptr) {}
            Value(Process* proc, Vertex* vertex, Attribute* attribute, Attribute* inner)
                : proc_(proc),
                  vertex_(vertex),
                  attribute_(attribute),
                  inner_(inner) {}
            Process* getProc() { return this->proc_; }
            Vertex* getVertex() { return this->vertex_; }
        private:
            Process* proc_;
            Vertex* vertex_;
            Attribute* attribute_;
            Attribute* inner_;
        };
        Value* value1_;
        Value* value2_;
    };

    class IntegratyProperty : public SecurityProperty {
    public:
        IntegratyProperty()
            : SecurityProperty(),
              value1_(nullptr),
              value2_(nullptr) {}
        IntegratyProperty(Process* proc1, const string& vertex1, Attribute* attribute1,
                          Process* proc2, const string& vertex2, Attribute* attribute2)
            : SecurityProperty(),
              value1_(new Value(proc1, vertex1, attribute1)),
              value2_(new Value(proc2, vertex2, attribute2)) {}
        PropertyType getPropertyType() const { return INTEGRATY; }
    private:
        struct Value {
        public:
            Value()
                : proc_(nullptr),
                  vertex_(nullptr),
                  attribute_(nullptr) {}
            Value(Process* proc, const string& vertex, Attribute* attribute)
                : proc_(proc),
                  vertex_(vertex),
                  attribute_(attribute) {}
        private:
            Process* proc_;
            string vertex_;
            Attribute* attribute_;
        };
        Value* value1_;
        Value* value2_;
    };

    class AvailabilityProperty : public SecurityProperty {
    public:
        AvailabilityProperty()
            : SecurityProperty(),
              value_(nullptr) {}
        AvailabilityProperty(Process* proc, const string& vertex) 
            : SecurityProperty(),
              value_(new Value(proc, vertex)) {}
        PropertyType getPropertyType() const { return AVAILABILITY; }
        Process* getValueProc() { return this->value_->getProc(); }
        string getValueVertex() { return this->value_->getVertex(); }
    private:
        struct Value {
        public:
            Value()
                : proc_(nullptr),
                  vertex_(nullptr) {}
            Value(Process* proc, const string& vertex)
                : proc_(proc),
                  vertex_(vertex) {}
            Process* getProc() { return this->proc_; }
            string getVertex() { return this->vertex_; }
        private:
            Process* proc_;
            string vertex_;
        };
        Value* value_;
    };
    
    class CTLProperty : public SafetyProperty{
    public:
        CTLProperty()
            : SafetyProperty() {}
        CTLProperty(const string& ctlStr)
            : SafetyProperty(),
              ctlStr_(ctlStr) {}
        PropertyType getPropertyType() const { return CTL; }
        string getCtlStr() { return this->ctlStr_; }
        private:
            string ctlStr_;
    };

    class InvariantProperty : public SafetyProperty{
    public:
        InvariantProperty()
            : SafetyProperty() {}
        InvariantProperty(const string invariantStr)
            : SafetyProperty(),
              invariantStr_(invariantStr) {}
        PropertyType getPropertyType() const { return INVARIANT; }
        string getInvariantStr() { return this->invariantStr_; }
        private:
            string invariantStr_;
    };
}

#endif /* Model_Property_hpp */
