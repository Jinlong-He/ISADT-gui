#ifndef Model_Channel_hpp
#define Model_Channel_hpp
#include "../Process/CommMethod.hpp"
namespace isadt {
    class Process;
    class Channel  {
        public: 
            Channel()
                : srcPair_(nullptr),
                  dstPair_(nullptr) {}
            Channel(Process* proc1, CommMethod* commMethod1,
                    Process* proc2, CommMethod* commMethod2,
                    bool privacy = true)
                : srcPair_(new ProcMethodPair(proc1, commMethod1)),
                  dstPair_(new ProcMethodPair(proc2, commMethod2)),
                  privacy_(privacy) {}
            ~Channel() {
                delete srcPair_;
                srcPair_ = nullptr;
                delete dstPair_;
                dstPair_ = nullptr;
            }

            bool equal(Process* proc1, MethodBase* m1,
                       Process* proc2, MethodBase* m2) const {
                return (srcPair_ -> proc_ == proc1) && (srcPair_ -> commMethod_ == m1) &&
                       (dstPair_ -> proc_ == proc2) && (dstPair_ -> commMethod_ == m2) ||
                       (srcPair_ -> proc_ == proc2) && (srcPair_ -> commMethod_ == m2) &&
                       (dstPair_ -> proc_ == proc1) && (dstPair_ -> commMethod_ == m1);
            }

        private:
            struct ProcMethodPair {
            public:
                ProcMethodPair()
                    : proc_(nullptr),
                      commMethod_(nullptr) {}
                ProcMethodPair(Process* proc, CommMethod* commMethod)
                    : proc_(proc),
                      commMethod_(commMethod) {}
                Process* proc_;
                CommMethod* commMethod_;
            };
            ProcMethodPair* srcPair_;
            ProcMethodPair* dstPair_;
            bool privacy_;
    };
}


#endif
