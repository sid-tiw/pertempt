#include <cassandra.h>
#include "cassandra_operations.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "person.h"

using namespace std;

void connect_to_cassandra()
{
    CassCluster *cluster = cass_cluster_new();
    CassSession *session = cass_session_new();
    cass_cluster_set_contact_points(cluster, "127.0.0.1");
    CassFuture *connection = cass_session_connect(session, cluster);
    if (cass_future_error_code(connection) == CASS_OK)
    {
        /* Run queries here */
        CassFuture *close_future = cass_session_close(session);
        cass_future_wait(close_future);
        cass_future_free(close_future);
    }
    else
    {
        const char *message;
        size_t message_length;
        cass_future_error_message(connection, &message, &message_length);
        fprintf(stderr, "Unable to connect: '%.*s'\n", (int)message_length,
                message);
    }
    cass_future_free(connection);
    cass_cluster_free(cluster);
    cass_session_free(session);
}

bool do_query(CassSession *sess, string query)
{
    CassStatement *stat = cass_statement_new(query.c_str(), 0);
    CassFuture *query_handle = cass_session_execute(sess, stat);
    cass_statement_free(stat);

    // Getting the result and handling begins here

    const CassResult *result = cass_future_get_result(query_handle);
    if (result == NULL)
    {
        cass_future_free(query_handle);
        return false;
    }
    cass_future_free(query_handle);
    const CassRow *row = cass_result_first_row(result);
    set<person> list_of_persons;
    CassIterator *list = cass_iterator_from_collection(cass_row_get_column_by_name(row, "connections"));
    do
    {
        const CassValue *temp_val = cass_iterator_get_value(list);
        CassIterator *temp_iterator = cass_iterator_fields_from_user_type(temp_val);
        string val_arr[4];
        int counter = 0;
        do
        {
            char *t_out;
            size_t *t_size;
            cass_value_get_string(cass_iterator_get_user_type_field_value(temp_iterator), &t_out, t_size);
            val_arr[counter] = "";
            for (int ind = 0; ind < (*t_size); ind++)
                val_arr[counter] += t_out[ind];
            counter++;
        } while (cass_iterator_next(temp_iterator));
        person temp_pers(val_arr[0], val_arr[1], val_arr[2], val_arr[3]);
        list_of_persons.insert(temp_pers);
        cass_iterator_free(temp_iterator);
    } while (cass_iterator_next(list));
    cass_iterator_free(list);
    cass_result_free(result);
}