/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:13:42 by sakllam           #+#    #+#             */
/*   Updated: 2022/09/09 16:27:34 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVL_body.hpp"
#include <algorithm>
#include <set>
#include <string>
#include <vector>

int main()
{

    // -------------------------------  strings tests : ---------------------------------------
    // ft::AVL_body<std::string> x;
    std::set<std::string> x;
    std::vector<std::string> cache;
    std::string buffer = "a";
    // _______________ insertion _____________ 
    for (int i = 0; i < 100000; i++)
    {
        x.insert(buffer);
        cache.push_back(buffer);
        buffer = buffer + "a";
    }
    // _______________ deletion _____________ 
    for (int i = 0; i < 100000; i++)
    {
        x.erase(cache[i]);
    }
    // -------------------------------  intger tests : ---------------------------------------
    // std::set<int> x;
    // ft::AVL_body<int> x;
    // // _______________ insertion _____________ 
    // for (int i = 0; i < 100000; i++)
    //     x.insert(i);
    // // _______________ deletion _____________ 
    // for (int i = 100000; i > 0; i--)
    //     x.remove(i);
}