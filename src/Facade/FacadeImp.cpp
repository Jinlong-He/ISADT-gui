/**
 * 
 */

#include "FacadeImp.hpp"
#include "Cryptor.hpp"
#include "EtherReceiver.hpp"
#include "UDPReceiver.hpp"
extern int digital_sign(const char* msg, size_t msgLen, const char* key, const string& id);
extern int digital_verify(const char* sig, const char* msg, size_t msgLen, unsigned int verify_id, const char* key);

namespace isadt {
    //IBE, SHA1
    int FacadeImp::Sign(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const char* key, const string& id) {
        int result = 0;
        if ("IBE" == id) {
            if (digital_sign(msg, msgLen, key, sig) == -1) {
                printf("ERROR: IBE sign failed\n");
                result = -1;
            }
        } else if ("SHA1" == id) {
            if (Cryptor::sha1_encrypt(msg, key, sig) == -1) {
                printf("ERROR: SHA1 sign failed\n");
                result = -1;
            }
        }

        if (result >= 0) {
            printf("INFO: Sign over\n");
        }

        return result;
    }

    int FacadeImp::Verify(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const char* key, const string& id) {
        int result = 0;
        if ("SHA1" == id) {
            if (Cryptor::sha1_encrypt(msg, key, sig) == -1) {
                printf("ERROR: SHA1 verify failed\n");
                result = -1;
            }
        }

        if (result >= 0) {
            printf("INFO: Verify over\n");
        }
        return result;
    }

    /**
     * just for ibe
     */
    int FacadeImp::Verify(const char* msg, size_t msgLen, const char* sig, size_t sigLen, const char* key, unsigned int verify_id, const string& id) {
        int result = 0;
        if ("IBE" == id) {
            if (digital_verify(sig, msg, msgLen, verify_id, key) == -1) {
                printf("ERROR: Verify failed\n");
                result = -1;
            }
        } else {
            printf("ERROR: Verify parameter Error\n");
            result = -1;
        }

        if (result >= 0) {
            printf("INFO: Verify over\n");
        }
        return result;
    }

    int FacadeImp::SymEnc(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id) {
        int result = 0;
        if ("AES" == id) {
            if(Cryptor::aes_encrypt(msg, key, new_msg) == -1) {
                printf("ERROR: AES encrypt failed\n");
                result = -1;
            }
        } else if ("DES" == id) {
            if(Cryptor::des_cbc_encrypt(msg, key, new_msg) == -1) {
                printf("ERROR: DES encrypt failed\n");
                result = -1;
            }
        }

        if (result >= 0) {
            printf("INFO: Encrypt over\n");
        }
        return result;
    }

    int FacadeImp::SymDec(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id) {
        int result = 0;
        if ("AES" == id) {
            if(Cryptor::aes_decrypt(msg, key, new_msg) == -1) {
                printf("ERROR: AES decrypt failed\n");
                result = -1;
            }
        } else if ("DES" == id) {
            if(Cryptor::des_cbc_decrypt(msg, key, new_msg) == -1) {
                printf("ERROR: DES decrypt failed\n");
                result = -1;
            }
        }

        if (result >= 0) {
            printf("INFO: Decrypt over\n");
        }
        return result;

    }

    int FacadeImp::AsymEnc(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id) {
        int result = 0;
        if ("RSA" == id) {
            if(Cryptor::rsa_pubkey_encrypt(msg, key, new_msg) == -1) {
                printf("ERROR: RSA encrypt failed\n");
                result = -1;
            }
        }

        if (result >= 0) {
            printf("INFO: encrypt over\n");
        }
        return result;
    }

    int FacadeImp::AsymDec(const char* msg, size_t msgLen, const char* new_msg, size_t sigLen, const char* key, const string& id) {
        int result = 0;
        if ("RSA" == id) {
            if(Cryptor::rsa_prikey_decrypt(msg, key, new_msg) == -1) {
                printf("ERROR: RSA decrypt failed\n");
                result = -1;
            }
        }

        if (result >= 0) {
            printf("INFO: decrypt over\n");
        }
        return result;
    }

    void dataHandlerHostReceive(u_char* param, const struct pcap_pkthdr* header, const u_char* packetData) {
        ether_header* eh;
        eh = (ether_header*)packetData;
        /*Configure your own prootcol number of ethernet frame*/
        if(ntohs(eh->type) == 0x888f && (macEqualToBroad(eh->h_dest) || macEqualToSelf(eh->h_dest))){
            printf("INFO: ETHER RECEIVED\n");
            const char* mac = eh->h_dest;
            if (mq_map.find(mac) != mq_map.end()) {
                mq_map[mac].Push(packetData);
            } else {
                printf("INFO: Can not find mac\n");
            }   
        }
    }

    int EhRecv() {
        /*Configure your own implementation of length_*/
        int length_ = 0;
        u_char* data_ = (u_char*)malloc(length_*sizeof(u_char));
        u_char* dst_;	/*Add MAC Address here*/
        u_char mac[6];
        EtherReceiver er;
        pcap_if_t* dev = er.getDevice();
        char errbuf[500];
        pcap_t* selectedAdp = pcap_open_live(dev->name, 65536, 1, 1000, errbuf);
        devHost = selectedAdp;
        std::cout << dev->name << std::endl;
        /*Add self defined dataHandler to handle data received*/
        /*parameters: u_char* param, const struct pcap_pkthdr* header, const u_char* packetData*/
        er.listenWithHandler(devHost, dataHandlerHostReceive, data_);
        /*Add your own data processing logic here*/
        free(data_);
        int result;
        return result;
    }

    int UDPRecv(MQ& mq, const char* ip, unsigned short port) {
        /*Add IP Str and portNUm here*/
        bool breakListen = true;
        UDPReceiver  er;
        /*allocation for dst_ here*/
        while(breakListen){
            char* item = (char*)malloc(1000*sizeof(char));
            
            std::cout << "INFO: recving info: IP: " << ip << " port: " << port << std::endl;
            int result = er.receivePacket((u_char*)item, ip, port);

            std::cout << "INFO: recv item: " << static_cast<const void *>(item) << std::endl;
            if(result == 0 || result == -1 || result == -2) {
                std::cout << "ERROR: receivePacket Error: " << std::dec <<result << std::endl;
                breakListen = false;
            }
            mq.Push(item);
        }
        return 0;
    }

}