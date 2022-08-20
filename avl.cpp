/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:13:42 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/20 19:12:33 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVL_body.hpp"

int main()
{
    ft::AVL_body<int> x;

    // x.insert(3);
    // x.insert(1);
    // x.insert(2);
    x.insert(20);
    x.insert(10);
    x.insert(30);
    x.insert(50);
    x.insert(25);
    x.insert(55);
    // x.insert(1);
    // x.insert(-3);
    // x.insert(-2);
    // x.insert(-1);
    // x.insert(5);
    x.printing();
}