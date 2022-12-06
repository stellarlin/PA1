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

using namespace std;
#define UNIFY  true
#define INTERSECT  false

using Table = map<State, pair <State, vector<State>>>;

set<State> merge_state ( set<State>& set1,  set<State> set2)
{
    set<State> res_state;
   set_union(set1.begin(), set1.end(),
               set2.begin(), set2.end(), inserter(res_state, res_state.begin()));
    return res_state;
}
map<pair<State, Symbol>, set<State>>  merged_start_Transitions ( NFA src,  NFA second_automat,  map <State, State> changed_states, set<Symbol> alpha_inters, bool particular) {
    map<pair<State, Symbol>, set<State>> res;
    res.insert(src.m_Transitions.begin(), src.m_Transitions.end());
    for (auto itr:  second_automat.m_Transitions) {
        set<State> changed_set;
        if(alpha_inters.find(itr.first.second)!= alpha_inters.end()) {
            for (auto itr2: itr.second) changed_set.insert(changed_states.find(itr2)->second);
            res.insert({{changed_states.find(itr.first.first)->second, itr.first.second}, changed_set});
        }
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

//start
NFA unification_automat(const NFA &first, const NFA &second, const bool MODE,  map <State, pair<State, State>> & final_inter_state) {
    NFA unit;
    map <State, State> changed_states_from_second;
    set<Symbol> alpha_inters;
  bool particulary_transition = 0;

    //copy second states
    unit.m_States.insert(first.m_States.begin(), first.m_States.end());
    for(auto itr: second.m_States)
    {
        unit.m_States.insert(*prev(end(unit.m_States))+1);
        changed_states_from_second.insert(make_pair( itr, *prev(end(unit.m_States))));
    }
    //copy second alphabet
    unit.m_Alphabet.insert(first.m_Alphabet.begin(), first.m_Alphabet.end());
    unit.m_Alphabet.insert( begin(second.m_Alphabet),end(second.m_Alphabet));


    if (first.m_Alphabet!=second.m_Alphabet && MODE ==INTERSECT) {
        set_intersection(first.m_Alphabet.begin(), first.m_Alphabet.end(),
                         second.m_Alphabet.begin(), second.m_Alphabet.end(),
                         inserter(alpha_inters, alpha_inters.begin()));
        particulary_transition = 1;
        for(auto itr : first.m_Transitions)
        {
            if(alpha_inters.find(itr.first.second)!= alpha_inters.end())
            {
                unit.m_Transitions.insert(itr);
            }
        }

    }
    else   unit.m_Transitions.insert(first.m_Transitions.begin(), first.m_Transitions.end());

        unit.m_Transitions = merged_start_Transitions(unit, second, changed_states_from_second, alpha_inters, particulary_transition);
        unit.m_States.insert(*prev(end(unit.m_States))+1);
        unit.m_InitialState = *prev(end(unit.m_States));
        unit.m_Transitions= merged_Init_Transitions(unit.m_Transitions, first.m_InitialState,
                                                    changed_states_from_second.find(second.m_InitialState)->second, unit.m_InitialState);


        unit.m_FinalStates.insert(first.m_FinalStates.begin(), first.m_FinalStates.end());
        //copy second final states
        for (auto itr: second.m_FinalStates) {
            auto changed = changed_states_from_second.find(itr);
            unit.m_FinalStates.insert(changed->second);
        }
        unit.m_FinalStates = merge_final_states(unit.m_FinalStates, first.m_InitialState, changed_states_from_second.find(second.m_InitialState)->second, unit.m_InitialState);

    if (MODE == INTERSECT)
    {
        State idx = 0;
        for(auto itr = unit.m_FinalStates.begin(); itr != prev(unit.m_FinalStates.end()); itr++)
        {
            for (auto itr2 = next(itr); itr2!= unit.m_FinalStates.end(); itr2++)
            {
                final_inter_state.insert({idx, {*itr, *itr2}});
                idx++;
            }
        }
    }

    return unit;
}

//unachievable remove
set<State> find_all_achievable_state(State current, const DFA &src, const  set<State> & current_set, unsigned int prev_size)
{
   set<State> res;
   res.insert(current_set.begin(), current_set.end());
 //   if(src.m_FinalStates.find(current) != src.m_FinalStates.end() && current!=src.m_InitialState ) return res;
    for(auto itr :src.m_Transitions)
    {
        if(current_set.size()==src.m_States.size()) return res;
        if(itr.first.first == current)
        {
              if(itr.second==current)continue;
                res.insert(itr.second);
                if(prev_size==res.size())continue;
                prev_size=res.size();
                res = find_all_achievable_state(itr.second, src, res, prev_size);
                prev_size=res.size();

            }
    }
    return res;
}

DFA delete_unachievable_state( DFA src, set<State> achievable_state) {
    DFA res = src;
    //delete states
    for(auto itr = res.m_States.cbegin(); itr!=res.m_States.cend();)
    {
        if(achievable_state.find(*itr) == achievable_state.end()) res.m_States.erase(itr++);
        else itr++;
    }

    for(auto itr = res.m_FinalStates.cbegin(); itr!=res.m_FinalStates.cend();)
    {
        if(achievable_state.find(*itr) == achievable_state.end()) res.m_FinalStates.erase(itr++);
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

DFA unachievable_state_remove(DFA src)
{
   DFA all_achievable;
   set<State> achievable_state;
    achievable_state.insert(src.m_InitialState);
   auto current_state = src.m_InitialState;
   achievable_state = find_all_achievable_state(current_state, src, achievable_state, 1);
   if(achievable_state.size()!=src.m_States.size()) all_achievable =  delete_unachievable_state(src, achievable_state);
   else all_achievable=src;
   return all_achievable;

}

//useless remove
set<State> find_all_useful_state(unsigned int current_state, DFA src, set<State> current_set, unsigned int prev_size) {
    set<State> res;
    res.insert(current_set.begin(), current_set.end());
 //   if(current_state  == src.m_InitialState)return res;
    for(auto itr :src.m_Transitions)
    {
        if(current_set.size()==src.m_States.size()) return res;
        if(current_state ==itr.second)
        {
            //if(itr2==current)continue;
                if(itr.first.first==current_state)continue;
                res.insert(itr.first.first);
                if(prev_size==res.size())continue;
                else prev_size=res.size();
                res = find_all_useful_state(itr.first.first, src, res, prev_size);
                prev_size=res.size();
            }
        }
    return res;
}
DFA delete_useless_state(DFA  src, set<State> useful_states) {
    DFA res;
    res.m_Alphabet=src.m_Alphabet;;
    res.m_FinalStates=src.m_FinalStates;
    res.m_InitialState=src.m_InitialState;
    res.m_Transitions=src.m_Transitions;
    //delete states
    res.m_States.insert(useful_states.begin(), useful_states.end());
    //delete transition
    for(auto itr= res.m_Transitions.cbegin(); itr!=res.m_Transitions.cend();)
    {
       if(useful_states.find(itr->first.first) == useful_states.end()
       || useful_states.find(itr->second) ==useful_states.end()) res.m_Transitions.erase( itr++);
          else   ++itr;
    }

    return res;

}
DFA useless_state_remove(DFA src) {
    DFA all_useful;
    set<State> useful_state;
    useful_state.insert(src.m_FinalStates.begin(), src.m_FinalStates.end());
    for( auto itr : src.m_FinalStates) useful_state = find_all_useful_state(itr, src, useful_state, useful_state.size());
    if(useful_state.size()!=src.m_States.size()) all_useful=delete_useless_state(src, useful_state);
    else all_useful=src;
    return all_useful;
}

//determinisation
map<pair<State, Symbol>, set<State>>  merge_transitions_determ ( const map<pair<State, Symbol>, set<State>>& src,
                                                                 const map<pair<State, Symbol>, set<State>>& multi_states,
                                                           set<State> state_to_copy, State state_num)
{
    map <::pair < State, Symbol>, set<State>> res;
    res.insert(multi_states.begin(),multi_states.end());

    for (auto itr: src) {
        if(state_to_copy.find(itr.first.first) == state_to_copy.end()) continue;

        if (res.find(make_pair(state_num, itr.first.second)) == res.end()) res.insert({make_pair(state_num, itr.first.second), itr.second});
        else {
            auto tmp_itr = res.find(make_pair(state_num, itr.first.second));
            set<State> tmp_set = merge_state(itr.second, tmp_itr->second);
            res[tmp_itr->first] = tmp_set;
        }
    }
    return res;
}

void find_final_pair(State new_state, map<State, pair<State, State>> & final_pair, set<State> next_state_set, DFA &automat) {

    State new_idx = prev(final_pair.end())->first + 1;
    for (auto itr: next_state_set) {
        for (auto itr2: final_pair) {
            if ((itr2.second.first == itr && next_state_set.find(itr2.second.second) != next_state_set.end()) ||
                (itr2.second.second == itr && next_state_set.find(itr2.second.first) != next_state_set.end())) {
                for (auto itr3: automat.m_FinalStates) {
                    final_pair.insert({new_idx, {new_state, itr3}});
                    new_idx++;
                }
                automat.m_FinalStates.insert(new_state);
                return;
            }
        }
    }
}
map<pair<State, Symbol>, set<State>>  remove_multistates (map<pair<State, Symbol>, set<State>> multi_states,
                                                          map<pair<State, Symbol>, set<State>> src,
                                                          map <State, pair<State, State>> & final_inter_state, const bool MODE,
                                                          DFA & automat, map <State, set<State>>& state_consist) {
    map<pair<State, Symbol>, set<State>> all_states;
    all_states.insert(src.begin(), src.end());
    for (auto itr: all_states ) {
        if (itr.second.size() == 1) continue;
        else {
            bool was_in_prev = 0;
            set<State> tmp_set_consist;
            State new_state = *prev(end(automat.m_States))+1;
            for(auto itr2 : itr.second)
            {
                if(state_consist.find(itr2) ==state_consist.end()) tmp_set_consist.insert(itr2);
                else tmp_set_consist.insert(state_consist.find(itr2)->second.begin(), state_consist.find(itr2)->second.end());
            }
            for( auto itr2 : state_consist)
            {
                if(tmp_set_consist == itr2.second)
                {
                    was_in_prev = 1;
                    new_state=itr2.first;
                    break;
                }
            }

            set<State> tmp_set;
            tmp_set.insert(new_state);
            multi_states.insert({itr.first, tmp_set});
            tmp_set.clear();

            if(!was_in_prev) {
                automat.m_States.insert(*prev(end(automat.m_States)) + 1);
                state_consist.insert({new_state, tmp_set_consist});

                if(MODE ==UNIFY) {
                    for (auto itr2: itr.second) {
                        if (automat.m_FinalStates.find(itr2) != automat.m_FinalStates.end())
                            automat.m_FinalStates.insert(new_state);
                    }
                }
                else if (MODE == INTERSECT) find_final_pair(new_state, final_inter_state, itr.second, automat);
                multi_states = merge_transitions_determ(all_states, multi_states, itr.second, new_state);
            }

        }
    }
    if(multi_states.empty()) return all_states;


    for(auto itr : multi_states) {
        all_states[itr.first] = itr.second;
    }

    multi_states.clear();
    all_states = remove_multistates(multi_states, all_states, final_inter_state, MODE, automat, state_consist);
    return all_states;

}
DFA determinisation(NFA src, map <State, pair<State, State>> final_inter_state, const bool MODE) {
    DFA res;
    res.m_States=src.m_States;
    res.m_Alphabet=src.m_Alphabet;
    res.m_FinalStates=src.m_FinalStates;
    res.m_InitialState=src.m_InitialState;

    map <State, set<State>> state_consist;
    map<pair<State, Symbol>, set<State>> tmp_transition, multi_trans;
    tmp_transition.insert(src.m_Transitions.begin(), src.m_Transitions.end());
    tmp_transition = remove_multistates(multi_trans, tmp_transition, final_inter_state, MODE, res, state_consist);
    for(auto itr : tmp_transition) res.m_Transitions.insert(make_pair(itr.first, *itr.second.begin()));
    return res;
}


//minimization
State find_first_not_final_state (DFA src )
{
    State not_Final;
    for(auto itr : src.m_States)
    {
        if(src.m_FinalStates.find(itr) == src.m_FinalStates.end())
        {
            not_Final = itr;
            return not_Final;
        }
    }
    return *prev(end(src.m_States))+1;
}
Table create_minim_table ( DFA  src, map <State, State> &renamed, const  map <Symbol, unsigned int> symbol_idx,  unsigned int count_of_symbol )
{
    Table res;

    State e = *prev(end(src.m_States))+1;
    unsigned int changed_counter = 0;
    for(auto itr: renamed)
    {
        vector<State> tmp_vector;
        tmp_vector.reserve(count_of_symbol);
        for(unsigned int i = 0; i<count_of_symbol;i++) tmp_vector.insert(tmp_vector.begin()+ i, e);
        for(auto itr2 : src.m_Transitions)
        {
            if(itr2.first.first == itr.first)   tmp_vector[symbol_idx.find(itr2.first.second)->second] = renamed.find(itr2.second)->second;
        }
        res.insert({itr.first, {itr.second, tmp_vector}});
        tmp_vector.clear();
    }


    for(auto current = res.begin(); current!=res.end(); current++) {
        bool changed = 0;
        for (auto itr = res.begin(); itr != current; itr++) {
            if ((current->second.first == itr->second.first
                 && current->second.second == itr->second.second
                 && current != res.begin()))
            {
                if(renamed.find(current->first)->second != renamed.find(itr->first)->second) renamed[current->first] = renamed.find(itr->first)->second, changed_counter++;
                changed = 1;
                break;
            }
        }
        if(changed ==0)
        {
            if(renamed.find(current->first)->second != renamed.find(current->first)->first )renamed[current->first] = current->first, changed_counter++;
        }
    }
    if(changed_counter!=0) res = create_minim_table(src, renamed, symbol_idx, count_of_symbol);
    return res;

}
set<State> find_states_to_delete( map <State, State> renamed)
{
    set<State> ToDelete;
    for(auto current = renamed.begin(); current!=renamed.end(); current++) {
        {
            for (auto itr = renamed.begin(); itr != current; itr++) {
                if ((current->second == itr->second && current != renamed.begin())) {
                    ToDelete.insert(current->first);
                }
            }
        }
    }
    return ToDelete;
}
DFA delete_repeated_states(Table src_table, map <State, State> renamed,  DFA src_automat,  map <Symbol, unsigned int> symbol_idx) {

    DFA res;
    set<State> states_to_delete;
    states_to_delete = find_states_to_delete(renamed);
    res.m_InitialState=src_automat.m_InitialState;
    res.m_Alphabet.insert(src_automat.m_Alphabet.begin(), src_automat.m_Alphabet.end());
    for(auto itr : src_automat.m_States)
    {
        if(states_to_delete.find(itr)== states_to_delete.end()) res.m_States.insert(itr);
    }

    for(auto itr : src_automat.m_FinalStates)
    {
        if(states_to_delete.find(itr)== states_to_delete.end()) res.m_FinalStates.insert(itr);
    }

    for(auto itr : src_automat.m_Transitions)
    {
        if(states_to_delete.find(itr.first.first) == states_to_delete.end())
        {
            State next_state = src_table.find(itr.first.first)->second.second[symbol_idx.find(itr.first.second)->second];
            res.m_Transitions.insert({itr.first, next_state});
            }
        }



    return res;
}
DFA minimization(DFA src) {
     DFA res;
     unsigned int count_of_symbol =  src.m_Alphabet.size();
   Table minimization_Table;
    map <State, State> renamed;
    map <Symbol, unsigned int> symbol_idx;

    int idx = 0;
    for(auto itr : src.m_Alphabet) symbol_idx.insert({itr, idx}), idx++;

    State not_Final = find_first_not_final_state(src);

    for(auto itr : src.m_States)
    {
        if(src.m_FinalStates.find(itr) != src.m_FinalStates.end()) renamed.insert({itr, *src.m_FinalStates.begin()});
        else renamed.insert({itr, not_Final});
    }

    minimization_Table =  create_minim_table(src, renamed, symbol_idx, count_of_symbol);
    res = delete_repeated_states(minimization_Table, renamed, src, symbol_idx);
    return res;
}

DFA unify(const NFA& a, const NFA& b)
{
NFA tmp;
DFA res;
bool MODE = UNIFY;
map <State, pair<State, State>> final_inter_state;

tmp = unification_automat(a, b, MODE, final_inter_state);
res = determinisation (tmp, final_inter_state, MODE);
res = unachievable_state_remove(res);
res = useless_state_remove(res);
res = minimization(res);

    return res;
}


DFA empty_language(DFA src) {
    return {
            {src.m_InitialState},
            src.m_Alphabet,
            {},
            src.m_InitialState,
            {},
    };
}

DFA intersect(const NFA& a, const NFA& b)
{
    NFA tmp;
    DFA res;
    bool MODE = INTERSECT;
    map <State, pair<State, State>> final_inter_state;

    tmp = tmp = unification_automat(a, b, MODE, final_inter_state);
    res = determinisation (tmp, final_inter_state, MODE);
    res = unachievable_state_remove(res);
    if(res.m_FinalStates.size()==0) return empty_language(res);
    res = useless_state_remove(res);
    res = minimization(res);

    return res;

}

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
            {6, 8, 10, 11, 12},
            {'a', 'b'},
            {
                    {{6, 'a'}, {8}},
                    {{8, 'a'}, {10}},
                    {{10, 'a'}, {10}},
                    {{10, 'b'}, {11}},
                    {{11, 'a'}, {12}},
                    {{11, 'b'}, {11}},
                    {{12, 'a'}, {10}},
                    {{12, 'b'}, {11}},
            },
            6,
            {10},
    };

  //  assert(intersect(a1, a2) == a);

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
            0,//0
            {4},
    };
    DFA b{
            {10, 1, 12, 14, 2, 13, 15, 11, 16},
            {'a', 'b'},
            {
                    {{10, 'a'}, {1}},
                    {{10, 'b'}, {12}},
                    {{12, 'a'}, {14}},
                    {{12, 'b'}, {2}},
                    {{14, 'a'}, {13}},
                    {{14, 'b'}, {15}},
                    {{2, 'a'}, {11}},
                    {{2, 'b'}, {2}},
                    {{13, 'a'}, {13}},
                    {{13, 'b'}, {2}},
                    {{15, 'a'}, {16}},
                    {{15, 'b'}, {2}},
                    {{11, 'a'}, {13}},
                    {{11, 'b'}, {2}},
                    {{16, 'a'}, {16}},
                    {{16, 'b'}, {16}},
            },
            10,
            {1, 13, 16},
    };
  //  assert(unify(b1, b2) == b);

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
            {8},
            {'a', 'b'},
            {},
            8,
            {},
    };
  // assert(intersect(c1, c2) == c);

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
  assert(intersect(d1, d2) == d);
}
#endif
