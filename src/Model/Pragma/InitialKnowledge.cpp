#include "Model/Pragma/InitialKnowledge.hpp"
namespace isadt {
    bool InitialKnowledge::isKeyPair() {
        return (pkKnowledge_ != nullptr);
    }
}
