#ifndef __PROGTEST__

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <variant>
#include <vector>

using namespace std;
using State = unsigned int;
using Symbol = uint8_t;

struct NFA {
    set<State> m_States;
    set<Symbol> m_Alphabet;
    map<pair<State, Symbol>, set<State>> m_Transitions;
    State m_InitialState;
    set<State> m_FinalStates;
};

struct DFA {
    set<State> m_States;
    set<Symbol> m_Alphabet;
    map<pair<State, Symbol>, State> m_Transitions;
    State m_InitialState;
    set<State> m_FinalStates;
};

#endif
set<State> merge_state ( set<State>& set1,  set<State> set2)
{
    set<State> res_state;
   set_union(set1.begin(), set1.end(),
               set2.begin(), set2.end(), inserter(res_state, res_state.begin()));
    return res_state;
}

map<pair<State, Symbol>, set<State>>  merged_Transitions ( const map<pair<State, Symbol>, set<State>>& map1,
                                                          const map<pair<State, Symbol>, set<State>>& map2) {
    map<pair<State, Symbol>, set<State>> res_map;
    res_map.insert(map1.begin(), map1.end());
    for (auto itr: map2) {
        if (res_map.find(itr.first) == res_map.end()) res_map.insert({itr.first, itr.second});
        else {
            auto tmp_itr = res_map.find(itr.first);
            set<State> tmp_set = merge_state(itr.second, tmp_itr->second);
            res_map[itr.first] = tmp_set;
        }
    }
        return res_map;

}

map<pair<State, Symbol>, set<State>>  merged_Init_Transitions ( const map<pair<State, Symbol>, set<State>>& src,
                                                                State & init1, State & init2, State & new_init) {
        map<pair<State, Symbol>, set<State>> res_map, tmp_map;
        auto new_init_tr_key = res_map.end();
        res_map.insert(src.begin(), src.end());
    for (auto itr: res_map) {

        if(itr.first.first == init1 || itr.first.first ==init2)
        {
            pair<State, Symbol> tmp_pair = {new_init, itr.first.second};
                if (res_map.find(make_pair(new_init, itr.first.second)) res_map.insert( {{new_init, itr.first.second}, itr.second});
            for(auto  tmp_itr = new_init_tr_key; tmp_itr!=res_map.end(); tmp_itr++)
            {

            }

            }

        }

        return res_map;

    }

NFA united_automat(const NFA &first, const NFA &second) {
    NFA unit;
    set_union(begin(first.m_States), end(first.m_States), begin(second.m_States),
              end(second.m_States), inserter(unit.m_States, begin(unit.m_States)));
    set_union(begin(first.m_Alphabet), end(first.m_Alphabet), begin(second.m_Alphabet),
              end(second.m_Alphabet), inserter(unit.m_Alphabet, begin(unit.m_Alphabet)));
    set_union(begin(first.m_FinalStates), end(first.m_FinalStates), begin(second.m_FinalStates),
              end(second.m_FinalStates), inserter(unit.m_FinalStates, begin(unit.m_FinalStates)));


    //????????????????//
    unit.m_Transitions = merged_Transitions(first.m_Transitions, second.m_Transitions);
    {
        //https://www.geeksforgeeks.org/merge-two-maps-of-array-into-one-sorted-map-of-array/
    }
    if(first.m_InitialState!=second.m_InitialState)
    {
        unit.m_States.insert(*prev(end(unit.m_States))+1);

        // unit.m_transition (unit.m_init) = first.m_Translition (...,first. m_init) U second.m_Translition (...,second. m_init)
        unit.m_InitialState = *prev(end(unit.m_States));
    }
    else unit.m_InitialState = first.m_InitialState;
    return unit;
}

DFA unify(const NFA& a, const NFA& b)
{
NFA tmp;
DFA res;

tmp = united_automat(a, b);

    return res;
}

//DFA intersect(const NFA& a, const NFA& b);

#ifndef __PROGTEST__

// You may need to update this function or the sample data if your state naming strategy differs.
bool operator==(const DFA& a, const DFA& b)
{
    return std::tie(a.m_States, a.m_Alphabet, a.m_Transitions, a.m_InitialState, a.m_FinalStates) == std::tie(b.m_States, b.m_Alphabet, b.m_Transitions, b.m_InitialState, b.m_FinalStates);
}

int main()
{
    NFA a1{
            {0, 1, 2},
            {'a', 'b'},
            {
                    {{0, 'a'}, {0, 1}},
                    {{0, 'b'}, {0}},
                    {{1, 'a'}, {2}},
            },
            0,
            {2},
    };
    NFA a2{
            {0, 1, 2},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{1, 'a'}, {2}},
                    {{2, 'a'}, {2}},
                    {{2, 'b'}, {2}},
            },
            0,
            {2},
    };
    DFA a{
            {0, 1, 2, 3, 4},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{1, 'a'}, {2}},
                    {{2, 'a'}, {2}},
                    {{2, 'b'}, {3}},
                    {{3, 'a'}, {4}},
                    {{3, 'b'}, {3}},
                    {{4, 'a'}, {2}},
                    {{4, 'b'}, {3}},
            },
            0,
            {2},
    };

    //assert(intersect(a1, a2) == a);

    NFA b1{
            {0, 1, 2, 3, 4},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{0, 'b'}, {2}},
                    {{2, 'a'}, {2, 3}},
                    {{2, 'b'}, {2}},
                    {{3, 'a'}, {4}},
            },
            0,
            {1, 4},
    };
    NFA b2{
            {0, 1, 2, 3, 4},
            {'a', 'b'},
            {
                    {{0, 'b'}, {1}},
                    {{1, 'a'}, {2}},
                    {{2, 'b'}, {3}},
                    {{3, 'a'}, {4}},
                    {{4, 'a'}, {4}},
                    {{4, 'b'}, {4}},
            },
            1,//0
            {4},
    };
    DFA b{
            {0, 1, 2, 3, 4, 5, 6, 7, 8},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{0, 'b'}, {2}},
                    {{2, 'a'}, {3}},
                    {{2, 'b'}, {4}},
                    {{3, 'a'}, {5}},
                    {{3, 'b'}, {6}},
                    {{4, 'a'}, {7}},
                    {{4, 'b'}, {4}},
                    {{5, 'a'}, {5}},
                    {{5, 'b'}, {4}},
                    {{6, 'a'}, {8}},
                    {{6, 'b'}, {4}},
                    {{7, 'a'}, {5}},
                    {{7, 'b'}, {4}},
                    {{8, 'a'}, {8}},
                    {{8, 'b'}, {8}},
            },
            0,
            {1, 5, 8},
    };
    assert(unify(b1, b2) == b);

    NFA c1{
            {0, 1, 2, 3, 4},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{0, 'b'}, {2}},
                    {{2, 'a'}, {2, 3}},
                    {{2, 'b'}, {2}},
                    {{3, 'a'}, {4}},
            },
            0,
            {1, 4},
    };
    NFA c2{
            {0, 1, 2},
            {'a', 'b'},
            {
                    {{0, 'a'}, {0}},
                    {{0, 'b'}, {0, 1}},
                    {{1, 'b'}, {2}},
            },
            0,
            {2},
    };
    DFA c{
            {0},
            {'a', 'b'},
            {},
            0,
            {},
    };
//    assert(intersect(c1, c2) == c);

    NFA d1{
            {0, 1, 2, 3},
            {'i', 'k', 'q'},
            {
                    {{0, 'i'}, {2}},
                    {{0, 'k'}, {1, 2, 3}},
                    {{0, 'q'}, {0, 3}},
                    {{1, 'i'}, {1}},
                    {{1, 'k'}, {0}},
                    {{1, 'q'}, {1, 2, 3}},
                    {{2, 'i'}, {0, 2}},
                    {{3, 'i'}, {3}},
                    {{3, 'k'}, {1, 2}},
            },
            0,
            {2, 3},
    };
    NFA d2{
            {0, 1, 2, 3},
            {'i', 'k'},
            {
                    {{0, 'i'}, {3}},
                    {{0, 'k'}, {1, 2, 3}},
                    {{1, 'k'}, {2}},
                    {{2, 'i'}, {0, 1, 3}},
                    {{2, 'k'}, {0, 1}},
            },
            0,
            {2, 3},
    };
    DFA d{
            {0, 1, 2, 3},
            {'i', 'k', 'q'},
            {
                    {{0, 'i'}, {1}},
                    {{0, 'k'}, {2}},
                    {{2, 'i'}, {3}},
                    {{2, 'k'}, {2}},
                    {{3, 'i'}, {1}},
                    {{3, 'k'}, {2}},
            },
            0,
            {1, 2, 3},
    };
 //  assert(intersect(d1, d2) == d);
}
#endif
