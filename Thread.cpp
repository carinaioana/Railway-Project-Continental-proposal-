//
// Created by carina on 02.01.2023.
//

#include "Thread.h"

Thread::Thread(int sock, Server *pServer)  : clientSocket (sock), pServer (pServer){
}

void * Thread::threadLaunch(void * argument) {
    auto * pThread = (Thread * )( argument );//pointer la obiectul Thread
    pThread->run ();
    delete pThread;
    return nullptr;
}
void * function(void *);

struct Thread::connection_details{
    const char *server, *user, *password, *database;
};
MYSQL* Thread:: mysql_connection_setup(struct connection_details mysql_details){
    MYSQL *connection = mysql_init(NULL);
    if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database,0,NULL,0) ) {
        cout<< "Connection Error:"<< mysql_error(connection)<<endl;
        exit(1);
    }
    return connection;
}
MYSQL_RES* Thread:: mysql_execute_query(MYSQL *connection, const char *sql_query){
    if (mysql_query(connection, sql_query)){
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
    return mysql_use_result(connection);
}

string Thread::trainsAllDay() {
    MYSQL *con;
    MYSQL_RES *res1;
    MYSQL_ROW row;

    struct connection_details mysqlD;
    mysqlD.server = "localhost";
    mysqlD.user = "carina";
    mysqlD.password = "password";
    mysqlD.database = "STUDENT";

    con = mysql_connection_setup(mysqlD);

    res1 = mysql_execute_query(con, "select id_tren, plecare, sosire, data_plecare, ora_plecare, intarzieri_plecare,estimare_plecare, data_sosire, ora_sosire, intarziere_sosire,estimare_sosire from MersulTrenurilor where date(data_plecare) = curdate();");

    cout << "Displaying output:\n "<< endl;
    string s;
    while ( ( row = mysql_fetch_row(res1) ) != NULL) {
        s.append(row[0]); //id_tren
        s.append(". ");
        s.append(row[1]); //plecare
        s.append(" - ");
        s.append(row[2]); //sosire
        s.append(", data plecarii: ");
        s.append(row[3]); //data_plecare
        s.append(" | ");
        s.append(row[4]); //ora_plecare
        s.append(", intarzieri: ");
        s.append(row[5]); //intarzieri_plecare
        s.append(" minute, estimare plecare: ");
        s.append(row[6]); //estimare_plecare
        s.append(", data sosirii: ");
        s.append(row[7]); // data_sosire
        s.append(" | ");
        s.append(row[8]); //ora_sosire
        s.append(", intarzieri: ");
        s.append(row[9]); //intarziere_sosire
        s.append(" minute, estimare sosire: ");
        s.append(row[10]); //estimare_sosire
        s.append("\n");
    }
    mysql_free_result(res1);
    mysql_close(con);
    return s;

}
string Thread::trainsLeaveNextHour() {
    MYSQL *con;
    MYSQL_RES *res2;
    MYSQL_ROW row;

    struct connection_details mysqlD;
    mysqlD.server = "localhost";
    mysqlD.user = "carina";
    mysqlD.password = "password";
    mysqlD.database = "STUDENT";

    con = mysql_connection_setup(mysqlD);
    res2 = mysql_execute_query(con, "SELECT id_tren, plecare,  ora_plecare, sosire, ora_sosire, intarzieri_plecare, estimare_plecare FROM MersulTrenurilor WHERE data_plecare = CURDATE() AND ora_plecare BETWEEN CURTIME() AND DATE_ADD(CURTIME(), INTERVAL 1 HOUR);");

    cout << "Displaying output:\n "<< endl;
    string s;
    while ( ( row = mysql_fetch_row(res2) ) != NULL) {
        s.append(row[0]);
        s.append(". ");
        s.append(row[1]);
        s.append(" - ");
        s.append(row[2]);
        s.append(", ");
        s.append(row[3]);
        s.append(" - ");
        s.append(row[4]);
        s.append(", intarziere: ");
        s.append(row[5]);
        s.append(" minute, estimare plecare: ");
        s.append(row[6]);
        s.append("\n");
    }
    mysql_free_result(res2);
    mysql_close(con);
    if (s.length() == 0){
        s = "No trains departing in the next hour";
    }
    return s;
}
string Thread::trainsArriveNextHour() {
    MYSQL *con;
    MYSQL_RES *res3;
    MYSQL_ROW row;

    struct connection_details mysqlD;
    mysqlD.server = "localhost";
    mysqlD.user = "carina";
    mysqlD.password = "password";
    mysqlD.database = "STUDENT";

    con = mysql_connection_setup(mysqlD);
    res3 = mysql_execute_query(con, "SELECT id_tren, plecare, ora_plecare, sosire, ora_sosire, intarziere_sosire, estimare_sosire FROM MersulTrenurilor WHERE data_sosire = CURDATE() AND ora_sosire BETWEEN CURTIME() AND DATE_ADD(CURTIME(), INTERVAL 1 HOUR);");

    cout << "Displaying output:\n"<< endl;

    string s;
    while ( ( row = mysql_fetch_row(res3) ) != NULL) {
        s.append(row[0]);
        s.append(". ");
        s.append(row[1]);
        s.append(" - ");
        s.append(row[2]);
        s.append(", ");
        s.append(row[3]);
        s.append(" - ");
        s.append(row[4]);
        s.append(", intarziere: ");
        s.append(row[5]);
        s.append(" minute, estimare sosire: ");
        s.append(row[6]);
        s.append("\n");
    }

    mysql_free_result(res3);
    mysql_close(con);

    if (s.length() == 0){
        s = "No trains departing in the next hour";
    }
    return s;
}

string Thread::updateDelay(int id, int intarziereINT, std::string command) {
    MYSQL *con;
    MYSQL_RES *res4,res5;
    MYSQL_ROW row;

    struct connection_details mysqlD;
    mysqlD.server = "localhost";
    mysqlD.user = "carina";
    mysqlD.password = "password";
    mysqlD.database = "STUDENT";

    std::string query;

    if(command == "1") {

         query = " UPDATE MersulTrenurilor SET intarzieri_plecare = ' " + to_string(intarziereINT) +
                            " ' WHERE id_tren = '" +
                            to_string(id) + "';";

    }
    else if(command == "2") {
        query = " UPDATE MersulTrenurilor SET intarziere_sosire = ' " + to_string(intarziereINT) +
                            " ' WHERE id_tren = '" +
                            to_string(id) + "';";
    }

    con = mysql_connection_setup(mysqlD);
    res4 = mysql_execute_query(con, query.c_str());
    mysql_free_result(res4);
    mysql_close(con);
    return trainsAllDay();
}
void Thread :: run () {

    char buffer[1024];

    //afisez implicit trenurile din ziua respectiva

    std::string allDay = trainsAllDay();

    read ( this->clientSocket,&buffer, sizeof (buffer));
    cout<<buffer;
    write ( this->clientSocket, allDay.c_str(), allDay.length() );

    memset(buffer,0,sizeof(buffer)); //pune null in buffer

    //dupa ce primesc comanda, afisez trenurile care pleaca/vin in urm ora

    read ( this->clientSocket,&buffer, sizeof (buffer));

    cout<< "Comanda primita: " << buffer<<endl;


    if( buffer[0] == '2' ){
        std::string arrive = trainsArriveNextHour();
        write ( this->clientSocket, arrive.c_str(), arrive.length() );
    }
    else if( buffer[0] == '1' ){
        std::string leave = trainsLeaveNextHour();
        write ( this->clientSocket, leave.c_str(), leave.length() );
    }
    std::string command(buffer);

    memset(buffer,0,sizeof(buffer)); //pune null in buffer

    //clientul trimite intarzierile la plecare

    cout<< "Raspuns actualizare"<< buffer<<endl;
    read(this->clientSocket, &buffer, sizeof buffer);
    int id_tren;
    id_tren = atoi(buffer);
    cout<<"id: "<< id_tren<<endl;

    read(this->clientSocket, &buffer, sizeof buffer);
    int intarziere;
    intarziere = atoi(buffer);
    cout<<"intarzieri: "<<intarziere<<endl;

    if(id_tren != 0 && intarziere != 0) {
       std::string update = updateDelay(id_tren, intarziere, command);

       write(this->clientSocket, update.c_str(), update.length());

       std::cout<<update;
    }


}

