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


map<pair<State, Symbol>, set<State>>  merged_start_Transitions ( NFA src,  NFA second_automat,  map <State, State> changed_states) {
    map<pair<State, Symbol>, set<State>> res;
    res = src.m_Transitions;
    for (auto itr:  second_automat.m_Transitions) {
        set<State> changed_set;
        for (auto itr2: itr.second) changed_set.insert(changed_states.find(itr2)->second);
        res.insert({{changed_states.find(itr.first.first)->second, itr.first.second}, changed_set});
    }
    return res;

}
map<pair<State, Symbol>, set<State>>  merged_Init_Transitions ( const map<pair<State, Symbol>, set<State>>& src,State  init1, State  init2, State  new_init) {
    map<pair<State, Symbol>, set<State>> res =src;
    for (auto itr: res) {

        if (itr.first.first == init1 || itr.first.first == init2) {
             auto itr2 = make_pair(make_pair(new_init, itr.first.second), itr.second);
                if (res.find( itr2.first) == res.end()) res.insert({itr2.first, itr2.second});
                else {
                   auto tmp_itr = res.find(itr2.first);
                    res[tmp_itr->first] = merge_state(itr2.second, tmp_itr->second);
                }
        }
    }
        return res;

}
set<State> merge_final_states(set<State> src, State  init1, State init2, State new_init) {
    set<State> res = src;
    for(auto itr :src)
    {
        if(itr == init1 || itr == init2)
        {
            res.insert(new_init);
            return res;
        }
    }
    return res;
}

NFA unification_automat(const NFA &first, const NFA &second) {
    NFA unit = first;
    map <State, State> changed_states_from_second;
    //copy second states
    for(auto itr: second.m_States)
    {
        unit.m_States.insert(*prev(end(unit.m_States))+1);
        changed_states_from_second.insert(make_pair( itr, *prev(end(unit.m_States))));
    }
    //copy second alphabet
    unit.m_Alphabet.insert( begin(second.m_Alphabet),end(second.m_Alphabet));
    //copy second final states
    for(auto itr: second.m_FinalStates) {
        auto changed = changed_states_from_second.find(itr);
        unit.m_FinalStates.insert(changed->second);
    }

        unit.m_Transitions = merged_start_Transitions(unit, second, changed_states_from_second);
        unit.m_States.insert(*prev(end(unit.m_States))+1);
        unit.m_InitialState = *prev(end(unit.m_States));
        unit.m_Transitions= merged_Init_Transitions(unit.m_Transitions, first.m_InitialState,
                                                    changed_states_from_second.find(second.m_InitialState)->second, unit.m_InitialState);
        unit.m_FinalStates = merge_final_states(unit.m_FinalStates, first.m_InitialState, changed_states_from_second.find(second.m_InitialState)->second, unit.m_InitialState);

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

NFA delete_unachievable_state( NFA src, set<State> achievable_state) {
    NFA res = src;
    //delete states
    for(auto itr = res.m_States.cbegin(); itr!=res.m_States.cend();)
    {
        if(achievable_state.find(*itr) == achievable_state.end()) res.m_States.erase(itr++);
        else itr++;
    }
    //delete transition
    for(auto itr= res.m_Transitions.cbegin(); itr!=res.m_Transitions.cend();)
    {
        if(achievable_state.find(itr->first.first) == achievable_state.end()) res.m_Transitions.erase( itr++);
        else ++itr;
    }
    return res;
}

NFA unachievable_state_remove(NFA src)
{
   NFA all_achievable;
   set<State> achievable_state;
    achievable_state.insert(src.m_InitialState);
   auto current_state = src.m_InitialState;
   achievable_state = find_all_achievable_state(current_state, src, achievable_state);
   if(achievable_state.size()!=src.m_States.size()) all_achievable =  delete_unachievable_state(src, achievable_state);
   else all_achievable=src;
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

NFA delete_useless_state(NFA  src, set<State> useful_states) {
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
    NFA all_useful;
    set<State> useful_state;
    useful_state.insert(src.m_FinalStates.begin(), src.m_FinalStates.end());
    for( auto itr : src.m_FinalStates) useful_state = find_all_useful_state(itr, src, useful_state);
    if(useful_state.size()!=src.m_States.size()) all_useful=delete_useless_state(src, useful_state);
    else all_useful=src;
    return all_useful;
}

map<pair<State, Symbol>, set<State>>  merge_transitions_determ ( const map<pair<State, Symbol>, set<State>>& src,
                                                                 const map<pair<State, Symbol>, set<State>>& multi_states,
                                                           set<State> state_to_copy, State state_num)
{
    map <::pair < State, Symbol>, set<State>> res = multi_states;
    for (auto itr: src) {
        if(state_to_copy.find(itr.first.first) == state_to_copy.end()) continue;

        if (src.find(make_pair(state_num, itr.first.second)) == src.end()) res.insert({make_pair(state_num, itr.first.second), itr.second});
        else {
            auto tmp_itr = src.find(make_pair(state_num, itr.first.second));
            set<State> tmp_set = merge_state(itr.second, tmp_itr->second);
            res[tmp_itr->first] = tmp_set;
        }
    }
    return res;
}

map<pair<State, Symbol>, set<State>>  remove_multistates ( map<pair<State, Symbol>, set<State>> multi_states,
                                                           map<pair<State, Symbol>, set<State>> src, bool & done, DFA & automat) {
    map<pair<State, Symbol>, set<State>> all_states;
    all_states.insert(src.begin(), src.end());
    if(done) return all_states;
    for (auto itr =  all_states.cbegin(); itr!= all_states.cend(); ) {
        if (itr->second.size() == 1)
        {
            ++itr;
            continue;
        }
        else {
            automat.m_States.insert(*prev(end(automat.m_States)) + 1);
            State new_state = *prev(end(automat.m_States));
            if(automat.m_FinalStates.find(itr->first.first) != automat.m_FinalStates.end()) automat.m_FinalStates.insert(new_state);
            set<State> tmp_set;
            tmp_set.insert(new_state);


            multi_states.insert({itr->first, tmp_set});
            tmp_set.clear();
            for (auto itr2: itr->second) {
                if (automat.m_FinalStates.find(itr2) != automat.m_FinalStates.end()) {
                    automat.m_FinalStates.insert(new_state);
                }
            }
            multi_states = merge_transitions_determ(all_states, multi_states,itr->second, new_state);
            all_states.erase(itr++);
        }
    }
    if(multi_states.empty())
    {
        done =1;
        return all_states;
    }
    all_states.insert(multi_states.begin(), multi_states.end());
    multi_states.clear();
    all_states = remove_multistates(multi_states, all_states, done, automat);
    return all_states;

}
DFA determinisation(NFA src) {
    DFA res;
    res.m_States=src.m_States;
    res.m_Alphabet=src.m_Alphabet;
    res.m_FinalStates=src.m_FinalStates;
    res.m_InitialState=src.m_InitialState;

    map<pair<State, Symbol>, set<State>> tmp_transition, multi_trans;
    tmp_transition.insert(src.m_Transitions.begin(), src.m_Transitions.end());
    bool done =0;
    tmp_transition = remove_multistates(multi_trans, tmp_transition, done, res);
    for(auto itr : tmp_transition) res.m_Transitions.insert(make_pair(itr.first, *itr.second.begin()));
    return res;
}

State find_first_not_final_state (DFA src )
{
    State not_Final;
    for(auto itr : src.m_States)
    {
        if(src.m_FinalStates.find(itr) == src.m_FinalStates.end())
        {
            not_Final = itr;
            break;
        }
    }
    return not_Final;
}
DFA minimization(DFA src) {
     DFA res;
     int count_of_symbol =  src.m_Alphabet.size();
    map<State, pair <State, vector<State>>> minimization_Table;
    map <State, State> renamed;
    map <Symbol, unsigned int> symbol_idx;
    State e = *prev(end(src.m_States))+1;

    int idx = 0;
    for(auto itr : src.m_Alphabet) symbol_idx.insert({itr, idx}), idx++;

    State not_Final = find_first_not_final_state(src);

    for(auto itr : src.m_States)
    {
        if(src.m_FinalStates.find(itr) != src.m_FinalStates.end()) renamed.insert({itr, *src.m_FinalStates.begin()});
        else renamed.insert({itr, not_Final});
    }


    for(auto itr: renamed)
    {
        vector<State> tmp_vector;
        tmp_vector.reserve(count_of_symbol);
        for(int i = 0; i<count_of_symbol;i++) tmp_vector.insert(tmp_vector.begin()+ i, e);
        for(auto itr2 : src.m_Transitions)
        {
            if(itr2.first.first == itr.first)   tmp_vector[symbol_idx.find(itr2.first.second)->second] = renamed.find(itr2.second)->second;
        }
        minimization_Table.insert({itr.first, {itr.second, tmp_vector}});
        tmp_vector.clear();
    }

    for(auto current = minimization_Table.begin(); current!=prev(end(minimization_Table)); current++) {
        for (auto itr = current; itr != minimization_Table.begin(); itr++) {
            if ((current->second.first == itr->second.first && current->second.second == itr->second.second) ||current==minimization_Table.begin()) {
                renamed[current->first] = itr->first;
                break;
            }
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
res = determinisation (tmp);
res = minimization(res);

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
