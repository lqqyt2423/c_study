#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <set>
#include <map>

using std::vector;
using std::string;
using std::ifstream;
using std::shared_ptr;
using std::set;
using std::map;
using std::istringstream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;


class QueryResult;
class TextQuery {
public:
  using line_no = vector<string>::size_type;
  TextQuery(ifstream&);
  QueryResult query(const string&) const;
private:
  shared_ptr<vector<string>> file; // 输入文件
  // 每个单词到它所在的行号的集合的映射
  map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &is): file(new vector<string>) {
  string text;
  while (getline(is, text)) {
    file->push_back(text);
    int n = file->size() - 1;
    istringstream line(text);
    string word;
    while (line >> word) {
      auto &lines = wm[word];
      if (!lines)
        lines.reset(new set<line_no>);
      lines->insert(n);
    }
  }
}

class QueryResult {
friend ostream &print(ostream &, const QueryResult &);
public:
  QueryResult(string s,
    shared_ptr<set<TextQuery::line_no>> p,
    shared_ptr<vector<string>> f) :
    sought(s), lines(p), file(f) { }
private:
  string sought;
  shared_ptr<set<TextQuery::line_no>> lines;
  shared_ptr<vector<string>> file;
};

QueryResult TextQuery::query(const string &sought) const {
  static shared_ptr<set<line_no>> nodata(new set<line_no>);
  auto loc = wm.find(sought);
  if (loc == wm.end())
    return QueryResult(sought, nodata, file);
  else
    return QueryResult(sought, loc->second, file);
}

string make_plural(size_t ctr, const string &word, const string &ending) {
  return (ctr == 1) ? word : word + ending;
}

ostream &print(ostream & os, const QueryResult &qr) {
  os << qr.sought << " occurs " << qr.lines->size() << " "
    << make_plural(qr.lines->size(), "time", "s") << endl;
  for (auto num: *qr.lines)
    os << "\t(line " << num + 1 << ") "
      << *(qr.file->begin() + num) << endl;
  return os;
}

void runQueries(ifstream &infile) {
  TextQuery tq(infile);
  while (true) {
    cout << "enter word to look for, or q to quir: ";
    string s;
    if (!(cin >> s) || s == "q") break;
    print(cout, tq.query(s)) << endl;
  }
}

int main() {
  ifstream infile("1.txt");
  runQueries(infile);
}
