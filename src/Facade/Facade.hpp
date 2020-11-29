/**
 * 
 */

#include<string>
#include "MQ.h"
using namespace std;

namespace isadt {
    class Facade {
    public:
        virtual int Sign(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const char* key, const string& id) = 0;
        virtual int Verify(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const char* key, const string& id) = 0;
        virtual int Verify(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const char* key, unsigned int verify_id, const string& id) = 0;
        virtual int SymEnc(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id) = 0;
        virtual int SymDec(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id) = 0;
        virtual int AsymEnc(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id) = 0;
        virtual int AsymDec(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id) = 0;
        virtual int EhRecv() = 0;
        virtual int UDPRecv(ConcurrentQueue& mq, const char* ip, unsigned short port) = 0;

    };
}
