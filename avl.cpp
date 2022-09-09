/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:13:42 by sakllam           #+#    #+#             */
/*   Updated: 2022/09/08 19:01:07 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pro_one.hpp"
#include <algorithm>
#include <set>
#include <string>

// class joke
// {
//     public:
//   int i;
// //   joke &operator=(joke x);
// };
// bool operator<(joke const x, joke const y)
// {
//     return x.i < y.i;
// }

// bool operator>(joke const x, joke const y)
// {
//     return x.i < y.i;
// }
// //  joke& joke::operator=(joke x)
// //   {
// //       return *this;
// //   }
int main()
{
    // ft::AVL_body<joke> on_me;

    // for (int i = 0; i < 1000000; i++)
    // {
    //     joke haha;
    //     haha.i = i;
    //     on_me.insert(haha);
        
    // }
    ft::AVL_body<std::string> x;
    // std::set<int> x;

    // std::cout << x.size() << "\n";
    // for (int i = 0; i < 100000; i++)
    //     x.insert(i);
    std::string buffer = "a";
    for (int i = 0; i < 100000; i++)
    {
        buffer = buffer + "a";
    std::cout << i << " "<< buffer.length() << " " << sizeof(buffer) << std::endl;
        x.insert(buffer);
    }
    // for (int i = 100000; i > 0; i--)
    //     x.find(i);
    // x.printing();
    // x.insert(2);
    // x.insert(1);
    // // x.insert();
    // // x.insert(20);
    // // x.insert(10);
    // // x.insert(30);
    // // x.insert(50);
    // // x.insert(25);
    // // x.insert(55);
    // x.remove(3);
    // // std::cout << "go ahead and find ===> 10 that exists : " << x.find(10) << "\n";
    // std::cout << "go ahead and find ===> 54 that !exists : " << x.find(54) << "\n";
    // x.insert(1);
    // x.insert(-3);
    // x.insert(-2);
    // x.insert(-1);
    // x.insert(5);
    // on_me.printing();
}