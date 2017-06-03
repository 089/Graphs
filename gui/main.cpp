#include "main.h"
#include <iostream>
#include <Graph.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <iomanip>
#include <cstdarg>

using namespace std;

/**
 * switch for verbose mode
 */
bool verbose = false;

/**
 * number of columns for indention
 */
int indention = 22;

/**
 * One option item.
 */
struct optionItem {
    string shortName;
    string longName;
    int requiredArguments;
    string description;
};

/**
 * All possible option items. Must be handled in the main functions if-else if-else block!
 */
static struct optionItem options[] =
        {
                // input
                {"i",    "input-csv",           1, ""}, // ->
                {"iml",  "input-matlab",        1, ""}, // -> Ctor (string matlabMatrix)
                {"ima",  "input-mathematica",   1, ""}, // ->
                {"ivn",  "input-vertices-name", 1, ""}, // -> TODO: Die Knotennamen werden eingelesen, auf Anzahl überprüft und bei der Ausgabe übergeben

                // output
                {"o",    "",                    0, ""}, // ->
                {"v",    "verbose",             0, ""}, // -> activates verbose mode in main function

                // functions
                {"a",    "no-args",             1, "Ruft alle Funktionen, die keine Argumente benötigen auf und gibt die Ergebnisse aus. "},
                {"ideg", "indegree",            1, ""}, // -> getInDeg()
                {"odeg", "outdegree",           1, ""}, // -> getOutDeg()
                {"n",    "nodes-count",         0, ""}, // -> getNumberOfNodes()
        };

void call_getInDeg(const vector <string> &allArgs, Graph *currentGraph);

void call_getNumberOfNodes(const vector <string> &allArgs, Graph *currentGraph);

void call_getNumberOfEdges(const vector <string> &allArgs, Graph *currentGraph);

void call_hasCycle(const vector <string> &allArgs, Graph *currentGraph);

void call_isComplete(const vector <string> &allArgs, Graph *currentGraph);

void call_isDirected(const vector <string> &allArgs, Graph *currentGraph);

void call_isFreeOfLoops(const vector <string> &allArgs, Graph *currentGraph);

void call_isMultigraph(const vector <string> &allArgs, Graph *currentGraph);

void call_isRegular(const vector <string> &allArgs, Graph *currentGraph);

void call_isSimple(const vector <string> &allArgs, Graph *currentGraph);

/*                     __            __ ___    __
 * |\/|  /\  | |\ |   |_  /  \ |\ | /    |  | /  \ |\ |
 * |  | /--\ | | \|   |   \__/ | \| \__  |  | \__/ | \|
 */
int main(int argc, char **argv) {

    // get all args as an array
    const vector <string> allArgs = getAllArgs(argc, argv);

    // extract only options from **argv
    const vector <string> optionArgs = getUsedOptionsFromArg(allArgs);

    // (de)activates verbose mode in main
    verbose = boost::algorithm::any_of_equal(optionArgs, "-v")
              || boost::algorithm::any_of_equal(optionArgs, "--verbose");
    printv("Entered verbose mode.");

    // argv[0] = program call
    if (argc <= 1) {
        showHelp();
    } else {
        vector < Graph * > graphs;

        /*         __       ___
         * | |\ | |__) /  \  |
         * | | \| |    \__/  |
         */

        // Get input from csv file
        // TODO @ForrestFalcon issue #10

        // Get input from matlab string
        vector <string> inputMatlab = getValues("iml", allArgs);
        for (int i = 0; i < inputMatlab.size(); i++) {
            Graph *g = new Graph(inputMatlab[i]);
            graphs.push_back(g);
        }
        printv("Found %d matlab input strings.", inputMatlab.size());

        // Get input from mathematica string
        // TODO: issue #42

        /*   __            __ ___    __        __
         *  |_  /  \ |\ | /    |  | /  \ |\ | (_
         *  |   \__/ | \| \__  |  | \__/ | \| __)
         */

        // do actions for every single graph
        printv("Apply %d selected functions to %d graphs.", optionArgs.size(), graphs.size());
        for (int gIndex = 0; gIndex < graphs.size(); gIndex++) {
            Graph *currentGraph = graphs[gIndex];
            printf("Select Graph %d.\n", gIndex);
            cout << "========================================" << endl;

            // call all selected functions on the single graph
            for (int argIndex = 0; argIndex < optionArgs.size(); argIndex++) {
                string currentOption = string(optionArgs[argIndex]);

                // check which options (only short names!) are selected
                if (currentOption == "-a") {
                    call_getNumberOfNodes(allArgs, currentGraph);
                    call_getNumberOfEdges(allArgs, currentGraph);
                    call_isDirected(allArgs, currentGraph);
                    call_isComplete(allArgs, currentGraph);
                    call_isMultigraph(allArgs, currentGraph);
                    call_isRegular(allArgs, currentGraph);
                    call_isSimple(allArgs, currentGraph);
                    call_hasCycle(allArgs, currentGraph);
                    call_isFreeOfLoops(allArgs, currentGraph);

                } else if (currentOption == "-") {
                } else if (currentOption == "-n") {
                    call_getNumberOfNodes(allArgs, currentGraph);

                } else if (currentOption == "-ideg") {
                    call_getInDeg(allArgs, currentGraph);

                } else if (currentOption == "-odeg") {

                } else if (currentOption == "ex") {

                }

            }
        }
        printv("done functions");

        /*   __       ___  __       ___
         *  /  \ /  \  |  |__) /  \  |
         *  \__/ \__/  |  |    \__/  |
         */

        vector <string> outputFiles;
/*
        string ext = getFileExtension(inputMatlab[i]);
        if (ext == ".") {
        } else if (ext == ".") {
        } else {
        }
*/

    }

    showHelp();
    exit(0);
}

void print_result(string key, int value) {
    cout << left << key << ": " << setw(indention) << " " << value << endl;
}

void print_result(string key, string value) {
    cout << left << key << ": " << setw(indention) << " " << value << endl;
}

void print_result(string key, bool value) {
    cout << left << key << ": " << setw(indention) << " " << (value ? "ja" : "nein") << endl;
}

void call_getNumberOfNodes(const vector <string> &allArgs, Graph *currentGraph) {
    print_result("Anzahl Knoten", currentGraph->getNumberOfNodes());
}

void call_getNumberOfEdges(const vector <string> &allArgs, Graph *currentGraph) {
    print_result("Anzahl Kanten", currentGraph->getNumberOfEdges());
}

void call_hasCycle(const vector <string> &allArgs, Graph *currentGraph) {
    print_result("Hat einen Kreis", currentGraph->hasCycle());
}

void call_isComplete(const vector <string> &allArgs, Graph *currentGraph) {
    print_result("Ist vollständig", currentGraph->isComplete());
}

void call_isDirected(const vector <string> &allArgs, Graph *currentGraph) {
    print_result("Ist gerichtet", currentGraph->isDirected());
}

void call_isFreeOfLoops(const vector <string> &allArgs, Graph *currentGraph) {
    print_result("Ist kreisfrei", currentGraph->isFreeOfLoops());
}

void call_isMultigraph(const vector <string> &allArgs, Graph *currentGraph) {
    print_result("Ist ein Multigraph", currentGraph->isMultigraph());
}

void call_isRegular(const vector <string> &allArgs, Graph *currentGraph) {
    print_result("Ist regulär", currentGraph->isRegular());
}

void call_isSimple(const vector <string> &allArgs, Graph *currentGraph) {
    print_result("Ist einfach", currentGraph->isSimple());
}

void call_getInDeg(const vector <string> &allArgs, Graph *currentGraph) {
    const vector <string> currentValues = getValues("ideg", allArgs);
    for (int valIndex = 0; valIndex < currentValues.size(); valIndex++) {
        int val = str2int(currentValues[valIndex]);
        printf("ideg(%d) = %d\n", val, currentGraph->getInDeg(val));
    }
}

int str2int(string number) {
    if (hasOnlyDigits(number)) {
        return atoi(number.c_str());
    } else {
        throw invalid_argument("'" + number + "' is valid not a number ([0-9]*).");
    }
}

typedef list <string> WordList;

WordList splitTextIntoWords(const string &text) {
    WordList words;
    istringstream in(text);
    copy(istream_iterator<string>(in),
         istream_iterator<string>(),
         back_inserter(words));
    return words;
}

void justifyLine(string line, int pageWidth, int indent) {
    size_t pos = line.find_first_of(' ');
    if (pos != string::npos) {
        while (line.size() < pageWidth) {
            pos = line.find_first_not_of(' ', pos);
            line.insert(pos, " ");
            pos = line.find_first_of(' ', pos + 1);
            if (pos == string::npos) {
                pos = line.find_first_of(' ');
            }
        }
    }

    cout << left << setw(indent) << " "
         << line << endl;
}

void justifyText(const string &text, int pageWidth, int indent) {
    WordList words = splitTextIntoWords(text);

    string line;
    for (const string &word : words) {
        if (line.size() + word.size() + 1 > pageWidth) { // next word doesn't fit into the line.
            justifyLine(line, pageWidth, indent);
            line.clear();
            line = word;
        } else {
            if (!line.empty()) {
                line.append(" ");
            }
            line.append(word);
        }
    }
    cout << left << setw(indent) << " "
         << line << endl;
}

void showHelp(void) {

    // TODO (manpage style)

    // print options
    int numberOfOptions = sizeof(options) / sizeof(*options);
    for (int i = 0; i < numberOfOptions; i++) {
        cout << left
             << setw(4) << " "
             << "-" << setw(7) << options[i].shortName
             << "--" << setw(20) << options[i].longName
             << "\n";

        // print description if available
        if (options[i].description.length() > 0) {
            justifyText(options[i].description, 60, 16);
            cout << endl;
        }
    }
}

void checkNumberOfRequiredArguments(string option, vector <string> optionValues) {
// check if number of required arguments is reached
    int numberOfOptions = sizeof(options) / sizeof(*options);
    for (int i = 0; i < numberOfOptions; i++) {
        if (option == options[i].shortName && optionValues.size() < options[i].requiredArguments) {

            stringstream msg;
            msg << "Option '-"
                << options[i].shortName
                << "' requires "
                << options[i].requiredArguments
                << " arguments but has only "
                << optionValues.size()
                << ".";

            throw logic_error(msg.str());
        }
    }
}

vector <string> getValues(string option, vector <string> args) {

    vector <string> optionValues;
    bool collectData = false;

    for (int i = 0; i < args.size(); i++) {

        // new option starts ==> current option ends
        if (collectData && boost::starts_with(args[i], "-")) {
            collectData = false;
            checkNumberOfRequiredArguments(option, optionValues);
        }

        // collection arguments
        if (collectData) {
            optionValues.push_back(args[i]);
        }

        // option starts e.g "-o"
        if (args[i] == "-" + string(option)) {
            collectData = true;
        }
    }

    return optionValues;
}

string getFileExtension(string filename) {
    return filename.substr(filename.find_last_of('.'));
}

vector <string> replaceLongWithShortNames(vector <string> args) {

    vector <string> shortenOptions;
    int numberOfOptions = sizeof(options) / sizeof(*options);

    // check all arguments
    for (int argIndex = 0; argIndex < args.size(); argIndex++) {
        string currentArg = args[argIndex];
        boost::algorithm::to_lower(currentArg);

        // check only arguments which start with double "-"
        if (boost::algorithm::starts_with(currentArg, "--")) {

            for (int optIndex = 0; optIndex < numberOfOptions; optIndex++) {
                string currentOption = options[optIndex].longName;

                if (currentArg == string("--").append(currentOption)) {
                    // replace with short name
                    shortenOptions.push_back("-" + options[optIndex].shortName);
                }
            }

        } else {
            // already short or argument is not an option (starting with "-")
            shortenOptions.push_back(currentArg);
        }

    }

    return shortenOptions;
}

void printv(const char *fstr, ...) {
    if (verbose) {

        va_list args;
        va_start (args, fstr);

        string line = "* ";
        line.append(fstr).append("\n");
        vprintf(line.c_str(), args);

        va_end (args);
    }
}

vector <string> getUsedOptionsFromArg(const vector <string> &allArgs) {
    vector <string> tmpArgs;
    for (int i = 0; i < allArgs.size(); i++) {
        if (boost::algorithm::starts_with(allArgs[i], "-")) {
            tmpArgs.push_back(allArgs[i]);
        }
    }

    return tmpArgs;
}

bool hasOnlyDigits(const string s) {
    return s.find_first_not_of("0123456789") == string::npos;
}

vector <string> getAllArgs(int argc, char **argv) {
    vector <string> allArgs;

    // split **argv arguments into string array
    // argv[0] is the program call itself
    allArgs.assign(argv + 1, argv + argc);

    return replaceLongWithShortNames(allArgs);
}