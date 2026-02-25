#include <algorithm>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define INF INT_MAX
#define ll long long

using namespace std;

// Принимает две буквы - true если буква одна и та же, но разного регистра.
static bool pairing(char a, char b) {
  // костыльный комментарий чтоб форматировалось правильно
  return (abs(a - b) == 'a' - 'A');
}

// true - буква в верхнем регистре
static bool isBig(char a) {
  // костыльный комментарий чтоб форматировалось правильно
  return (a >= 'A' && a <= 'Z');
}

int ans[100001];
// для каждой буквы в строке хранит её номер в порядке обхода

int main() {
  string s;
  cin >> s;
  const size_t size = s.size();

  // В листе храним буквы и их индекс
  list<pair<char, int>> lst;

  // заполним лист. Индексы нужны чтобы в дальнейшем было проще формировать
  // ответ
  int auxCounter1 = 1;
  int auxCounter2 = 1;

  for (char c : s) {
    if (isBig(c)) {
      lst.emplace_back(c, auxCounter1++);
    } else {
      lst.emplace_back(c, auxCounter2++);
    }
  }

  // Ищем пары типа Aa и начинаем от них расширяться -> B(Aa)b
  for (auto it = lst.begin(); it != lst.end();) {
    auto next_it = next(it);
    if (next_it == lst.end()) {
      next_it = lst.begin();
    }
    if (pairing(it->first, next_it->first)) {
      if (isBig(it->first)) {
        ans[it->second] = next_it->second;
      } else {
        ans[next_it->second] = it->second;
      }
      lst.erase(next_it);
      it = lst.erase(it);
      if (it != lst.begin()) {
        it = prev(it);
      }
    } else {
      it++;
    }
  }
  if (!lst.empty()) {
    cout << "Impossible";
    return 0;
  }
  cout << "Possible\n";
  for (size_t i = 1; i <= size / 2; i++) {
    cout << ans[i] << ' ';
  }
}
