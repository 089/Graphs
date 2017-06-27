#include "main.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/format.hpp>
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
const int indention = 32;

/**
 * fill character
 */
const char separator = ' ';

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
                {"",      "",                      0, "EINGABE"},
                {"-i",    "--input-csv",           1, "Liest die Adjazenzmatrix des Graphen aus der angegebenen CSV-Datei aus."},
                {"-iml",  "--input-matlab",        1, "Erzeugt einen Graphen aus der in Matlab-Notation angegebenen Adjazenzmatrix."}, // -> Ctor (string matlabMatrix)
                {"-ima",  "--input-mathematica",   1, "Erzeugt einen Graphen aus der in Mathematica-Notation angegebenen Adjazenzmatrix."},
                {"-ivn",  "--input-vertices-name", 1, "Übergibt Namen der Knoten. Diese werden bei der Ausgabe anstelle der Knotennummer angegeben."}, // -> TODO: Die Knotennamen werden eingelesen, auf Anzahl überprüft und bei der Ausgabe übergeben

                // output
                {"",      "",                      0, "AUSGABE"},
                {"-o",    "--output-csv",          1, "Speichert die Adjazenzmatrix des Graphen in der angegebenen Datei "},
                {"-oj",   "--output-json",         1, "Speichert den Graphen - als JSON im Format von sigmajs.org - in der angegebenen Datei."},
                {"-og",   "--output-graphviz",     1, "Speichert den Graphen in der angegebenen Datei im Format von Graphviz (hier: DOT)."},
                {"-v",    "--verbose",             1, "Aktiviert den wortreichen Modus"},

                // functions with no arguments
                {"",      "",                      0, "FUNKTIONEN OHNE ARGUMENTE"},
                {"-h",    "--help",                0, "Zeigt die Hilfe an."},
                {"-na",   "--no-args",             0, "Ruft alle Funktionen auf, die keine Argumente benötigen und gibt die Ergebnisse aus."},
                {"-V",    "--vertices-count",      0, "Gibt die Anzahl der Knoten |V| aus."},
                {"-E",    "--edges-count",         0, "Gibt die Anzahl der Kanten |E| aus."},
                {"-d",    "--is-directed",         0, "Gibt an, ob der Graph gerichtet ist."},
                {"-c",    "--is-complete",         0, "Gibt an, ob der Graph vollstaendig ist. Ein vollständiger Graph ist ein Begriff aus der Graphentheorie und bezeichnet einen einfachen Graph, in dem jeder Knoten mit jedem anderen Knoten durch eine Kante verbunden ist (Wikipedia)."},
                {"-mg",   "--is-multigraph",       0, "Gibt an, ob der Graph ein Multigraph ist. In sogenannten Multigraphen können zwei Knoten auch durch mehrere Kanten verbunden sein, was in einfachen Graphen nicht erlaubt ist(Wikipedia)."},
                {"-r",    "--is-regular",          0, "Gibt an, ob der Graph regulaer ist. In der Graphentheorie heißt ein Graph regulär, falls alle seine Knoten gleich viele Nachbarn haben, also den gleichen Grad besitzen. Bei einem regulären gerichteten Graphen muss weiter die stärkere Bedingung gelten, dass alle Knoten den gleichen Eingangs- und Ausgangsgrad besitzen (Wikipedia)."},
                {"-s",    "--is-simple",           0, "Gibt an, ob der Graph einfach ist. Ein einfacher Graph (auch schlichter Graph) ist in der Graphentheorie ein ungerichteter Graph ohne Mehrfachkanten und ohne Schleifen (Wikipedia)."},
                {"-cy",   "--has-cycle",           0, "Gibt an, ob der gerichtete Graph einen Kreis hat."},
                {"-fol",  "--is-free-of-loops",    0, "Gibt an, ob der Graph schleifenfrei ist (z.B. von Knoten 1 zu Knoten 1)."},
                {"-for",  "--is-directed-forest",  0, "Gibt an, ob der Graph ein gerichteter Wald ist. Als Wald bezeichnet man in der Graphentheorie einen ungerichteten Graphen ohne Zyklus. Ist dieser zusammenhängend, so spricht man von einem (ungerichteten) Baum. Jede Zusammenhangskomponente eines Waldes ist ein Baum. Eine Verallgemeinerung auf gerichtete Graphen kann man erklären, indem man diese auf die zugrundeliegenden Ungerichteten zurückführt (Wikipedia)."},

                // functions with arguments
                {"",      "",                      0, "FUNKTIONEN MIT ARGUMENTEN"},
                {"-ideg", "--indegree",            1, "Gibt die Anzahl der eingehenden Kanten eines Knoten (Parameter = Nummern zwischen 0 und |V| - 1) aus."},
                {"-odeg", "--outdegree",           1, "Gibt die Anzahl der ausgehenden Kanten eines Knoten (Parameter = Nummern zwischen 0 und |V| - 1) aus."},
                {"-an",   "--are-neighbours",      2, "Gibt an, ob zwei Knoten (Parameter = Nummern zwischen 0 und |V| - 1) Nachbarn sind."},
                {"-hc",   "--has-connectivity",    2, "Gibt an, ob es zwischen den beiden Knoten (Parameter = Nummern zwischen 0 und |V| - 1) einen Weg gibt."},
                {"-he",   "--has-edge",            2, "Gibt an, ob es den Knoten mit der gegebenen Nummer zwischen 0 und |V| - 1 gibt."},
                {"-hp",   "--has-path",            1, "Gibt an, ob die übergebene Kantenfolge (Mindestens ein Parameter = Nummern zwischen 0 und |V| - 1) im Graph existiert."},
        };

/*                     __            __ ___    __
 * |\/|  /\  | |\ |   |_  /  \ |\ | /    |  | /  \ |\ |
 * |  | /--\ | | \|   |   \__/ | \| \__  |  | \__/ | \|
 */
int main(int argc, char **argv) {

    // get all args as an array
    const vector<string> allArgs = getAllArgs(argc, argv);

    // extract only options from **argv
    const vector<string> optionArgs = getUsedOptionsFromArg(allArgs);

    // (de)activates verbose mode in main
    verbose = boost::algorithm::any_of_equal(optionArgs, "-v")
              || boost::algorithm::any_of_equal(optionArgs, "--verbose");
    printv("Wortreicher Modus aktiviert.");

    bool showhelp = false;

    // argv[0] = program call
    if (argc > 1) {
        vector<Graph *> graphs;

        /*         __       ___
         * | |\ | |__) /  \  |
         * | | \| |    \__/  |
         */

        // Get input from csv file
        vector<string> inputCSV = getValues("-i", allArgs);
        for (int i = 0; i < inputCSV.size(); i++) {
            Graph *g = Graph::loadAdjacencyFile(inputCSV[i]);
            printv("Graph %d (CSV-Datei) \"%s\" hinzugefügt.", graphs.size(), inputCSV[i].c_str());
            graphs.push_back(g);
        }
        printv("%d CSV-Dateien gefunden.", inputCSV.size());

        // Get input from matlab string
        vector<string> inputMatlab = getValues("-iml", allArgs);
        for (int i = 0; i < inputMatlab.size(); i++) {
            Graph *g = new Graph(inputMatlab[i]);
            printv("Graph %d (Matlab-Notation) \"%s\" hinzugefügt.", graphs.size(), inputMatlab[i].c_str());
            graphs.push_back(g);
        }
        printv("%d Matlab Matrizen gefunden.", inputMatlab.size());

        // Get input from mathematica string
        // TODO: issue #42

        /*    __            __ ___    __        __          __       ___  __       ___
         *   |_  /  \ |\ | /    |  | /  \ |\ | (_    ()/   /  \ /  \  |  |__) /  \  |
         *   |   \__/ | \| \__  |  | \__/ | \| __)   (X    \__/ \__/  |  |    \__/  |
         *
         */
        // do actions for every single graph
        printv("Die %d ausgewählten Funktionen werden auf %d Graphen angewendet.", optionArgs.size(), graphs.size());
        for (int gIndex = 0; gIndex < graphs.size(); gIndex++) {
            Graph *currentGraph = graphs[gIndex];
            cout << "========================================" << endl;
            printf("|         Ergebnisse Graph %d.          |\n", gIndex);
            cout << "========================================" << endl;

            // call all selected functions on the single graph
            for (int argIndex = 0; argIndex < optionArgs.size(); argIndex++) {
                string currentOption = string(optionArgs[argIndex]);

                // check which options (only short names!) are selected
                // A) functions with no arguments
                if (currentOption == "-na") {
                    call_getNumberOfNodes(allArgs, currentGraph);
                    call_getNumberOfEdges(allArgs, currentGraph);
                    call_isDirected(allArgs, currentGraph);
                    call_isComplete(allArgs, currentGraph);
                    call_isMultigraph(allArgs, currentGraph);
                    call_isRegular(allArgs, currentGraph);
                    call_isSimple(allArgs, currentGraph);
                    call_hasCycle(allArgs, currentGraph);
                    call_isFreeOfLoops(allArgs, currentGraph);
                    call_isForest(allArgs, currentGraph);

                } else if (currentOption == "-n") {
                    call_getNumberOfNodes(allArgs, currentGraph);

                } else if (currentOption == "-m") {
                    call_getNumberOfEdges(allArgs, currentGraph);

                } else if (currentOption == "-d") {
                    call_isDirected(allArgs, currentGraph);

                } else if (currentOption == "-c") {
                    call_isComplete(allArgs, currentGraph);

                } else if (currentOption == "-mg") {
                    call_isMultigraph(allArgs, currentGraph);

                } else if (currentOption == "-r") {
                    call_isRegular(allArgs, currentGraph);

                } else if (currentOption == "-s") {
                    call_isSimple(allArgs, currentGraph);

                } else if (currentOption == "-cy") {
                    call_hasCycle(allArgs, currentGraph);

                } else if (currentOption == "-fol") {
                    call_isFreeOfLoops(allArgs, currentGraph);

                } else if (currentOption == "-h") {
                    showhelp = true;

                } else if (currentOption == "-for") {
                    call_isForest(allArgs, currentGraph);

                    // B) functions with no arguments
                } else if (currentOption == "-ideg") {
                    call_getInDeg(allArgs, currentGraph);

                } else if (currentOption == "-odeg") {
                    call_getOutDeg(allArgs, currentGraph);

                } else if (currentOption == "-an") {
                    call_areNeighbours(allArgs, currentGraph);

                } else if (currentOption == "-hc") {
                    call_hasConnectivity(allArgs, currentGraph);

                } else if (currentOption == "-he") {
                    call_hasEdge(allArgs, currentGraph);

                } else if (currentOption == "-hp") {
                    call_hasPath(allArgs, currentGraph);

                    // C) output into files
                } else if (currentOption == "-o") {
                    const string filename = to_string(gIndex) + "_" + getValues("-o", allArgs)[0];
                    // TODO @ForrestFalcon issue #11 currentGraph->exportFile(filename, currentGraph->exportCsv());

                } else if (currentOption == "-oj") {
                    const string filename = to_string(gIndex) + "_" + getValues("-oj", allArgs)[0];
                    currentGraph->exportFile(filename, currentGraph->graphToJson());

                } else if (currentOption == "-og") {
                    const string filename = to_string(gIndex) + "_" + getValues("-og", allArgs)[0];
                    currentGraph->exportFile(filename, currentGraph->exportDot());

                } else if (currentOption == "-") {
                    // TODO Vorlage für weitere Optionen; Bitte den verschiedenen Bereichen A), B), C) zuordnen
                }
            }
        }
        printv("Alle Funktionen wurden ausgeführt.");
    }

    // too less arguments or explicitly called
    if (argc <= 1 || showhelp) {
        showHelp();
    }

    exit(0);
}

void print_result(string key, int value) {
    cout << left << setw(indention) << setfill(separator) << key << ": " << setw(indention) << setfill(separator)
         << value << endl;
}

void print_result(string key, string value) {
    cout << left << setw(indention) << setfill(separator) << key << ": " << setw(indention) << setfill(separator)
         << value << endl;
}

void print_result(string key, bool value) {
    cout << left << setw(indention) << setfill(separator) << key << ": " << setw(indention) << setfill(separator)
         << (value ? "ja" : "nein") << endl;
}

void call_getNumberOfNodes(const vector<string> &allArgs, Graph *currentGraph) {
    print_result("Anzahl Knoten", currentGraph->getNumberOfNodes());
}

void call_getNumberOfEdges(const vector<string> &allArgs, Graph *currentGraph) {
    print_result("Anzahl Kanten", currentGraph->getNumberOfEdges());
}

void call_hasCycle(const vector<string> &allArgs, Graph *currentGraph) {
    if (currentGraph->isDirected()) {
        print_result("Hat einen Kreis", currentGraph->hasCycle());
    } else {
        string niy_message = "Bisher nur für Digraphen implementiert.";
        print_result("Hat einen Kreis", niy_message);
    }
}

void call_isComplete(const vector<string> &allArgs, Graph *currentGraph) {
    print_result("Ist vollstaendig", currentGraph->isComplete());
}

void call_isDirected(const vector<string> &allArgs, Graph *currentGraph) {
    print_result("Ist gerichtet", currentGraph->isDirected());
}

void call_isFreeOfLoops(const vector<string> &allArgs, Graph *currentGraph) {
    print_result("Ist schleifenfrei", currentGraph->isFreeOfLoops());
}

void call_isMultigraph(const vector<string> &allArgs, Graph *currentGraph) {
    print_result("Ist ein Multigraph", currentGraph->isMultigraph());
}

void call_isRegular(const vector<string> &allArgs, Graph *currentGraph) {
    print_result("Ist regulaer", currentGraph->isRegular());
}

void call_isSimple(const vector<string> &allArgs, Graph *currentGraph) {
    print_result("Ist einfach", currentGraph->isSimple());
}

void call_getInDeg(const vector<string> &allArgs, Graph *currentGraph) {
    const vector<string> currentValues = getValues("-ideg", allArgs);
    for (int valIndex = 0; valIndex < currentValues.size(); valIndex++) {
        int val = str2int(currentValues[valIndex]);
        const string key = boost::str(boost::format("in degree(%d)") % val);
        print_result(key, currentGraph->getInDeg(val));
    }
}

void call_isForest(const vector<string> &allArgs, Graph *currentGraph) {
    if (currentGraph->isDirected()) {
        print_result("Ist Wald", currentGraph->isForest());
    } else {
        string niy_message = "Bisher nur für Digraphen implementiert.";
        print_result("Hat einen Kreis", niy_message);
    }
}

void call_getOutDeg(const vector<string> &allArgs, Graph *currentGraph) {
    const vector<string> currentValues = getValues("-odeg", allArgs);
    for (int valIndex = 0; valIndex < currentValues.size(); valIndex++) {
        int val = str2int(currentValues[valIndex]);
        const string key = boost::str(boost::format("out degree(%d)") % val);
        print_result(key, currentGraph->getOutDeg(val));
    }
}

void call_areNeighbours(const vector<string> &allArgs, Graph *currentGraph) {
    const vector<string> currentValues = getValues("-an", allArgs);
    const string key = boost::str(boost::format("Sind %d und %d Nachbarn") % currentValues[0] % currentValues[1]);
    print_result(key, currentGraph->areNeighbours(str2int(currentValues[0]), str2int(currentValues[1])));
}

void call_hasConnectivity(const vector<string> &allArgs, Graph *currentGraph) {
    const vector<string> currentValues = getValues("-hc", allArgs);
    const string key = boost::str(boost::format("Weg zw. %d und %d existiert") % currentValues[0] % currentValues[1]);
    print_result(key, currentGraph->hasConnectivity(str2int(currentValues[0]), str2int(currentValues[1])));
}

void call_hasEdge(const vector<string> &allArgs, Graph *currentGraph) {
    const vector<string> currentValues = getValues("-he", allArgs);
    const string key = boost::str(boost::format("Kante zw. %d und %d existiert") % currentValues[0] % currentValues[1]);
    print_result(key, currentGraph->hasEdge(str2int(currentValues[0]), str2int(currentValues[1])));
}

void call_hasPath(const vector<string> &allArgs, Graph *currentGraph) {
    const vector<string> currentValues = getValues("-hp", allArgs);
    vector<int> vertices;
    for (int i = 0; i < currentValues.size(); i++) {
        vertices.push_back(str2int(currentValues[i]));
    }
    const string key = boost::str(boost::format("Pfad {%s} existiert") % boost::join(currentValues, ", "));
    print_result(key, currentGraph->hasPath(vertices));
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

    const string preOptions =
            "NAME\n"
                    "       graphs - Ein tolles Tool für und mit Graphen und <3 und magic.\n"
                    "\n"
                    "SYNOPSIS\n"
                    "       graphs [OPTIONS]\n"
                    "\n"
                    "DESCRIPTION\n"
                    "       Mit  diesem Tool können verschiedene Eigenschaften von Graphen ermittelt\n"
                    "       und ausgegeben werden. Die Ergebnisse werden übersichtlich dargestellt\n"
                    "       und können in verschiedenen Ausgabeformaten ausgegeben werden. Achte bei\n"
                    "       den Optionen auf Groß- und Kleinschreibung.\n"
                    "\n"
                    "OPTIONS";

    const string postOptions = "BUGS\n"
            "       Es gibt bestimmt einige Bugs. Finde sie und schreib sie uns!\n"
            "\n"
            "AUTHOR\n"
            "       Marianus Niggl (marianus.niggl@hm.edu) Andreas Reiser (areiser@hm.edu)\n"
            "       Kevin Stieglitz (k.stieglitz@hm.edu) Martin Zell (zell@hm.edu)";

    cout << "\n" << preOptions << endl;

    // print options
    int numberOfOptions = sizeof(options) / sizeof(*options);
    for (int i = 0; i < numberOfOptions; i++) {
        if (options[i].shortName.empty() && options[i].longName.empty()) {
            justifyText(options[i].description, 76, 4);
            cout << endl;
        } else {
            cout << left
                 << setw(4) << " "
                 << setw(7) << options[i].shortName
                 << setw(20) << options[i].longName
                 << " (" << options[i].requiredArguments << ")"
                 << "\n";

            // print description if available
            if (options[i].description.length() > 0) {
                justifyText(options[i].description, 60, 16);
                cout << endl;
            }
        }
    }

    cout << "\n" << postOptions << endl;
}

void checkNumberOfRequiredArguments(string option, vector<string> optionValues) {
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

vector<string> getValues(string option, vector<string> args) {

    vector<string> optionValues;
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
        if (args[i] == option) {
            collectData = true;
        }
    }

    return optionValues;
}

string getFileExtension(string filename) {
    return filename.substr(filename.find_last_of('.'));
}

vector<string> replaceLongWithShortNames(vector<string> args) {

    vector<string> shortenOptions;
    int numberOfOptions = sizeof(options) / sizeof(*options);

    // check all arguments
    for (int argIndex = 0; argIndex < args.size(); argIndex++) {
        string currentArg = args[argIndex];

        // check only arguments which start with double "-"
        if (boost::algorithm::starts_with(currentArg, "--")) {

            for (int optIndex = 0; optIndex < numberOfOptions; optIndex++) {
                string currentOption = options[optIndex].longName;

                if (currentArg == currentOption) {
                    // replace with short name
                    shortenOptions.push_back(options[optIndex].shortName);
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

vector<string> getUsedOptionsFromArg(const vector<string> &allArgs) {
    vector<string> tmpArgs;
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

vector<string> getAllArgs(int argc, char **argv) {
    vector<string> allArgs;

    // split **argv arguments into string array
    // argv[0] is the program call itself
    allArgs.assign(argv + 1, argv + argc);

    return replaceLongWithShortNames(allArgs);
}