/**
 * @file cassandra_operations.h
 * @author Siddhartha Tiwari (201851127@iiitvadodara.ac.in)
 * @brief This is the file defining all the operations related to Cassandra.
 * @version 0.1
 * @date 2020-06-03
 */

#ifndef __CASSANDRA_OPERATIONS__
#define __CASSANDRA_OPERATIONS__
#include "person.h"
#include <set>

#define ATTRIBUTES(i) ((i == 0) ? "username" \
: (i == 1) ? "name" : (i == 2) ? "image" \
: (i == 3) ? "loc_univ" : "")

#define CREATE_KEYSPACE "CREATE KEYSPACE IF NOT EXISTS GITHUB WITH replication \
= {'class': 'SimpleStrategy', 'replication_factor': 3};"

#define USE_KEYSPACE "USE GITHUB;"

#define CREATE_TYPE "CREATE TYPE IF NOT EXISTS person (\
	username text,\
	name text,\
	image text,\
	loc_univ text\
);"

#define CREATE_TABLE "CREATE TABLE IF NOT EXISTS test (\
	username text PRIMARY KEY,\
	connections list<frozen<person>>\
);"

#define INSERT_INTO_TABLE()

/**
 * @brief Tells whether the person's details and its connection tree is available in Cassandra or not.
 * 
 * @param root :::: The person to search for.
 * @return true :::: if the person's connection tree is available in Cassandra's Cluster.
 * @return false :::: otherwise
 */

bool isAvailable(person root);

/**
 * @brief Return the list of all the persons related to the person.
 * 
 * @param root :::: The person who is the root of the connection tree that is seeked.
 * @return set<pair<person, int>> :::: The list of all the connections of the person with their respective depths.
 */

set<pair<person, int>> listAll(person root);

/**
 * @brief does a query
 * 
 * @param sess 
 * @param query 
 * @return true 
 * @return false 
 */
bool do_query(CassSession *sess, string query);

#endif