#pragma once

#include <vector>
#include <string>
#include <Graph.h>

using namespace std;

/**
 * justifies the given text.
 *
 * @param text      the text
 * @param pageWidth the page width
 * @param indent    the indention
 */
void justifyText(const string &text, int pageWidth, int indent);

/**
 * Extracts all values corresponding to a given option.
 *
 * e.g. we have a command line like "-a foo1 foo2 foo3 -b ffoo"
 * and call getOptionValues("a", "-a foo1 foo2 foo3 -b ffoo")
 * ==> returns an array with {"foo1", "foo2", "foo3"}
 *
 * <b>checks only short names of options!</b>
 *
 * @param option    an option
 * @param args      all arguments (from main **argv)
 * @return an array with all values of the given option
 */
vector<string> getValues(string option, vector<string> args);

/**
 * Returns the extension of a filename.
 *
 * @param filename  the filename
 * @return the file ext.
 */
string getFileExtension(string filename);

/**
 * Replace all long name options with their corresponding short name
 *
 * @param args  array with arguments
 * @return array with shorten options
 */
vector<string> replaceLongWithShortNames(vector<string> args);

/**
 * Extracts als used options in arguments.
 *
 * @param allArgs   all program arguments
 * @return  an array of all options
 */
vector<string> getUsedOptionsFromArg(const vector<string> &allArgs);

/**
 * Printf wrapper for verbose mode. Prints a formatted string and the corresponding number of values.
 * @param str   formatted string
 */
void printv(const char *fstr, ...);

/**
 * prints out the help page.
 */
void showHelp(void);

/**
 * checks whether there are enough arguments for a certain option.
 *
 * @param option        the option
 * @param optionValues  its values
 */
void checkNumberOfRequiredArguments(string option, vector<string> optionValues);

/**
 * checks whether a string contains only digits
 * @param s the string
 * @return true, if string only contains digits
 */
bool hasOnlyDigits(const string s);

/**
 * converts the program arguments to one arry
 *
 * @param argc  argument count
 * @param argv  arguments
 * @return  array with all arguments
 */
vector<string> getAllArgs(int argc, char **argv);

/**
 * Converts a string to a int
 * @param number string with a number ([0-9]*)
 * @return string as int
 */
int str2int(string number);

void call_getInDeg(const vector<string> &allArgs, Graph *currentGraph);

void call_getNumberOfNodes(const vector<string> &allArgs, Graph *currentGraph);

void call_getNumberOfEdges(const vector<string> &allArgs, Graph *currentGraph);

void call_hasCycle(const vector<string> &allArgs, Graph *currentGraph);

void call_isComplete(const vector<string> &allArgs, Graph *currentGraph);

void call_isDirected(const vector<string> &allArgs, Graph *currentGraph);

void call_isFreeOfLoops(const vector<string> &allArgs, Graph *currentGraph);

void call_isMultigraph(const vector<string> &allArgs, Graph *currentGraph);

void call_isRegular(const vector<string> &allArgs, Graph *currentGraph);

void call_isSimple(const vector<string> &allArgs, Graph *currentGraph);

void call_getOutDeg(const vector<string> &allArgs, Graph *currentGraph);

void call_areNeighbours(const vector<string> &allArgs, Graph *currentGraph) ;

void call_hasConnectivity(const vector<string> &allArgs, Graph *currentGraph) ;

void call_hasEdge(const vector<string> &allArgs, Graph *currentGraph) ;

void call_hasPath(const vector<string> &allArgs, Graph *currentGraph) ;
