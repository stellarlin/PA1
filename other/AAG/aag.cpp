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
map<pair<State, Symbol>, set<State>>  merged_Init_Transitions ( const map<pair<State, Symbol>, set<State>>& src,State  init1, State  init2, State  new_init) {
    map<pair<State, Symbol>, set<State>> res_map;
    res_map.insert(src.begin(), src.end());
    for (auto itr: res_map) {

        if (itr.first.first == init1 || itr.first.first == init2) {
             auto itr2 = make_pair(make_pair(new_init, itr.first.second), itr.second);
                if (res_map.find( itr2.first) == res_map.end()) res_map.insert({itr2.first, itr2.second});
                else {
                   auto tmp_itr = res_map.find(itr2.first);
                    res_map[tmp_itr->first] = merge_state(itr2.second, tmp_itr->second);
                }
        }
    }
        return res_map;

}
set<State> merge_final_states(set<State> src, State  init1, State init2, State new_init) {
    set<State> res;
    res.insert(src.begin(), src.end());
    for(auto itr :src)
    {
        if(itr == init1 || itr == init2)
        {
            res.insert(new_init);
          break;
        }

    }
    return res;
}

NFA unification_automat(const NFA &first, const NFA &second) {
    NFA unit;
    set_union(begin(first.m_States), end(first.m_States), begin(second.m_States),
              end(second.m_States), inserter(unit.m_States, begin(unit.m_States)));
    set_union(begin(first.m_Alphabet), end(first.m_Alphabet), begin(second.m_Alphabet),
              end(second.m_Alphabet), inserter(unit.m_Alphabet, begin(unit.m_Alphabet)));
    set_union(begin(first.m_FinalStates), end(first.m_FinalStates), begin(second.m_FinalStates),
              end(second.m_FinalStates), inserter(unit.m_FinalStates, begin(unit.m_FinalStates)));

    unit.m_Transitions = merged_Transitions(first.m_Transitions, second.m_Transitions);
    if(first.m_InitialState!=second.m_InitialState)
    {
        unit.m_States.insert(*prev(end(unit.m_States))+1);
        unit.m_InitialState = *prev(end(unit.m_States));
        unit.m_Transitions= merged_Init_Transitions(unit.m_Transitions, first.m_InitialState, second.m_InitialState, unit.m_InitialState);
        unit.m_FinalStates = merge_final_states(unit.m_FinalStates, first.m_InitialState, second.m_InitialState, unit.m_InitialState);

    }
    else unit.m_InitialState = first.m_InitialState;
    return unit;
}

set<State> find_all_achievable_state(State current, const NFA &src, const  set<State> & current_set)
{
   set<State> res =current_set;
    if(src.m_FinalStates.find(current) != src.m_FinalStates.end() && current!=src.m_InitialState ) return res;
    for(auto itr :src.m_Transitions)
    {
        if(current_set.size()==src.m_States.size()) return res;
        if(itr.first.first == current)
        {
            for(auto itr2 : itr.second)
            {
                if(itr2==current)continue;
                res.insert(itr2);
                res = find_all_achievable_state(itr2, src, res);
            }
            }
        }

    return res;
}

NFA delete_unachievable_state(const NFA &src, set<State> achievable_state) {
    NFA res =src;
    //delete states
    for(auto itr: res.m_States)
    {
        if(achievable_state.find(itr) == achievable_state.end()) res.m_States.erase(itr);
    }
    //delete transition
    for(auto itr= res.m_Transitions.cbegin(); itr!=res.m_Transitions.cend();)
    {
        if(achievable_state.find(itr->first.first) == achievable_state.end()) res.m_Transitions.erase( itr++);
        else ++itr;
    }
    return res;
}

NFA unachievable_state_remove(const NFA &src)
{
   NFA all_achievable=src;
   set<State> achievable_state;
    achievable_state.insert(src.m_InitialState);
   auto current_state = src.m_InitialState;
   achievable_state = find_all_achievable_state(current_state, src, achievable_state);
   if(achievable_state.size()!=src.m_States.size()) all_achievable =  delete_unachievable_state(src, achievable_state);
   return all_achievable;

}

set<State> find_all_useful_state(unsigned int current_state, NFA src, set<State> current_set) {
    set<State> res = current_set;
    if(current_state  == src.m_InitialState)return res;
    for(auto itr :src.m_Transitions)
    {
        if(current_set.size()==src.m_States.size()) return res;
        if(itr.second.find(current_state) !=itr.second.end())
        {
            //if(itr2==current)continue;
                if(itr.first.first==current_state)continue;
                res.insert(itr.first.first);
                res = find_all_useful_state(itr.first.first, src, res);
            }
        }
    return res;
}

NFA delete_useless_state(NFA src, set<State> useful_states) {
    NFA res =src;
    //delete states
    for(auto itr: res.m_States)
    {
        if(useful_states.find(itr) == useful_states.end()) res.m_States.erase(itr);
    }
    //delete transition
    for(auto itr= res.m_Transitions.cbegin(); itr!=res.m_Transitions.cend();)
    {
       if(useful_states.find(itr->first.first) == useful_states.end()) res.m_Transitions.erase( itr++);
          else   ++itr;
    }

    for(auto itr : res.m_Transitions)
    {
        for(auto itr2 : itr.second)
        {
            if(useful_states.find(itr2) !=useful_states.end()) itr.second.erase(itr2);
        }
    }
    return res;

}

NFA useless_state_remove(NFA src) {
    NFA all_useful=src;
    set<State> useful_state;
    useful_state.insert(src.m_FinalStates.begin(), src.m_FinalStates.end());
    for( auto itr : src.m_FinalStates) useful_state = find_all_useful_state(itr, src, useful_state);
    if(useful_state.size()!=src.m_States.size())delete_useless_state(src, useful_state);
    return all_useful;
}

NFA determinisation(NFA src) {
    NFA res = src;
    for( auto itr : src.m_Transitions)
    {
        if(itr.second.size()==1) continue;
        else
        {
            map<pair<State, Symbol>, set<State>> tmp_term;
            res.m_States.insert(*prev(end(res.m_States)));
        }
    }
    return res;
}

DFA unify(const NFA& a, const NFA& b)
{
NFA tmp;
DFA res;

tmp = unification_automat(a, b);
tmp = unachievable_state_remove(tmp);
tmp = useless_state_remove(tmp);
tmp = determinisation (tmp);
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
