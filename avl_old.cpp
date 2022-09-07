/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_old.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:13:42 by sakllam           #+#    #+#             */
/*   Updated: 2022/09/07 21:30:21 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVL_body_old.hpp"
#include <algorithm>

int main()
{
    ft::AVL_body<int> x;

    // std::cout << x.size() << "\n";
    // for (int i = 0; i < 100000; i++)
    //     x.insert(i);
    for (int i = 0; i < 100000; i++)
        x.insert(i);
    for (int i = 100000; i > 0; i--)
        x.remove(i);
    x.printing();
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
    // x.printing();
}