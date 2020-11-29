/**
 * 
 */
#include "Facade.hpp"
#include<unordered_map>

namespace isadt {
    class FacadeImp: public Facade {
    private:
        bool macEqualToBroad(u_char mac[6]){
            for(int i = 0; i < 6; i ++){
                if(mac[i] != 0xff){
                    return false;
                }
            }
            return true;
        }

        bool macEqualToSelf(u_char mac[6]){
            for(int i = 0; i < 6; i ++){
                if(mac[i] != (u_char)client_mac[i]){  
                    return false;
                }
            }
            return true;
        }
        void dataHandlerHostReceive(u_char* param, const struct pcap_pkthdr* header, const u_char* packetData);
    public:
        static unordered_map<char*, MQ*> mq_map;
        static unsigned short eh_type;
        int Sign(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const char* key, const string& id);
        int Verify(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const char* key, const string& id);
        int Verify(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const char* key, unsigned int verify_id, const string& id);
        int SymEnc(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id);
        int SymDec(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id);
        int AsymEnc(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id);
        int AsymDec(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id);
        int EhRecv();
        int UDPRecv(MQ& mq, const char* ip, unsigned short port);
        void dataHandlerHostReceive(u_char* param, const struct pcap_pkthdr* header, const u_char* packetData);
    };
}