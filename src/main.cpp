#include "md5.h"
#include "RSA.h"

int main(int argc, const char* argv[]) {
    if (!strcmp(argv[1], "-md5")) {
        string s;
        md5 encypher;
        while (1) {
            std::getline(std::cin, s);
            if (s == "q")
                exit(0);
            encypher.setMsg(s);
            encypher.encypher();
            std::cout << s + "->" << encypher.to_string() << std::endl;
        }
    }
    else {
        RSA encypher;
        std::cout << "public key, private key -> " << encypher.to_string() << std::endl;
        ull s;
        while (1) {
            std::cin >> s;
            if (s == -1)
                exit(0);
            ull c = encypher.encypher(s);
            std::cout << "ciphertext is -> " << c << std::endl;
            std::cout << "Bob decrypts -> " << encypher.decypher(c) << std::endl;
        }

    }
    return 0;
}