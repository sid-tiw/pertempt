/**
 * @file cassandra_operations.h
 * @author Siddhartha Tiwari (201851127@iiitvadodara.ac.in)
 * @brief This is the file defining all the operations related to Cassandra.
 * @version 0.1
 * @date 2020-06-03
 */

#ifndef __CASSANDRA_OPERATIONS__
#define __CASSANDRA_OPERATIONS__
#include <set>
#include <string>

#include "person.h"

#define ATTRIBUTES(i)             \
	((i == 0) ? "username"        \
			  : (i == 1) ? "name" \
						 : (i == 2) ? "image" : (i == 3) ? "loc_univ" : "")

#define CREATE_KEYSPACE \
	"CREATE KEYSPACE IF NOT EXISTS GITHUB WITH replication \
= {'class': 'SimpleStrategy', 'replication_factor': 3};"

#define USE_KEYSPACE "USE GITHUB;"

#define CREATE_TYPE \
	"CREATE TYPE IF NOT EXISTS person (\
	username text,\
	name text,\
	image text,\
	loc_univ text,\
	level smallint\
);"

#define CREATE_TABLE \
	"CREATE TABLE IF NOT EXISTS tree (\
	username text PRIMARY KEY,\
	connections list<frozen<person>>,\
	scannedon timestamp\
);"

/**
 * @brief This function calculates the query string to insert a set of persons into the tree table
 * 
 * @param username :::: the username of the root of a particular tree
 * @param connections :::: a set containing the details of the descendants of the root and the depth of each descendant
 * @return std::string :::: the processed query string
 */
std::string insert_into_table(std::string username, set<pair<person, int>> connections);

/**
 * @brief It is a helping function of insert_into_table. It generates the UDT query of Cassandra.
 * 
 * @param prs the person for which to generate the query
 * @param lev person's depth from the root
 * @return std::string the UDT query string
 */

std::string person_queries(person prs, int lev);

/**
 * @brief Tells whether the person's details and its connection tree is
 * available in Cassandra or not.
 *
 * @param root :::: The person to search for.
 * @return true :::: if the person's connection tree is available in Cassandra's
 * Cluster.
 * @return false :::: otherwise
 */

bool isAvailable(person root);

/**
 * @brief Return the list of all the persons related to the person.
 *
 * @param root :::: The person who is the root of the connection tree that is
 * seeked.
 * @return set<pair<person, int>> :::: The list of all the connections of the
 * person with their respective depths.
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