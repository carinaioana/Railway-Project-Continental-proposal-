#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <fstream>
#include<mysql/mysql.h>
using namespace std;
//#include <jsoncpp/json/json.h>

struct connection_details{
    const char *server, *user, *password, *database;
};
MYSQL*  mysql_connection_setup(struct connection_details mysql_details){
    MYSQL *connection = mysql_init(NULL);
    if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database,0,NULL,0) ) {
        cout<< "Connection Error:"<< mysql_error(connection)<<endl;
        exit(1);
    }
    return connection;
}
MYSQL_RES* mysql_execute_query(MYSQL *connection, const char *sql_query){
    if (mysql_query(connection, sql_query)){
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
    return mysql_use_result(connection);
}
int main(int argc, char *argv[])
{

    MYSQL *con;
    MYSQL_RES *res;
    MYSQL_ROW row;

    struct connection_details mysqlD;
    mysqlD.server = "localhost";
    mysqlD.user = "carina";
    mysqlD.password = "password";
    mysqlD.database = "STUDENT";

    con = mysql_connection_setup(mysqlD);
    res = mysql_execute_query(con, "select * from MersulTrenurilor;");

    cout << "Displaying output:\n "<< endl;

    while ( ( row = mysql_fetch_row(res) ) != NULL){
        cout << row[0] << " | " << row[1] << " | "<< row[2] << " | " << row[3] << " | "<<row[4] << " | " << row[5] << " | "<< row[6] <<endl<<endl;
    }
    mysql_free_result(res);
    mysql_close(con);


    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "ERROR opening socket" << std::endl;
        return 1;
    }

    // Bind the socket to a port
    int portno = 5001;
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "ERROR binding socket to port" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 5);

    // Accept an incoming connection
    sockaddr_in cli_addr;
    socklen_t client = sizeof(cli_addr);
    int newsockfd = accept(sockfd, (sockaddr*)&cli_addr, &client);
    if (newsockfd < 0)
    {
        std::cerr << "ERROR accepting connection" << std::endl;
        return 1;
    }

    // Read data from the client
    char buffer[256];
    int n = read(newsockfd, buffer, 255);
    if (n < 0)
    {
        std::cerr << "ERROR reading from socket" << std::endl;
        return 1;
    }
    std::cout << "Received message from client: " << buffer << std::endl;

    // Write data to the client
    std::string message = "Hello from the server!";
    n = write(newsockfd, message.c_str(), message.size());
    if (n < 0)
    {
        std::cerr << "ERROR writing to socket" << std::endl;
        return 1;
    }

    // Close the socket
    close(newsockfd);
    close(sockfd);


    return 0;
}
