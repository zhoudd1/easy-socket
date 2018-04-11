#ifndef _EYS_SOCKET_
#define _EYS_SOCKET_

namespace eys {
    enum connection_type {
        conn_type_udp,
        conn_type_tcp
    };

    class connection {
    private:
        int fd;
    public:
        connection(connection_type type);
        int get() const;
        virtual ~connection();
    };
}

#endif