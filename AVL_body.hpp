/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_body.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:16:14 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/19 18:29:27 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdlib>
#include <algorithm>
#include <memory>
#include <iostream>

namespace ft
{
    template<class T>
        struct avl
    {
        typedef T type_name;

        type_name       value;
        avl<type_name>  *right;  
        avl<type_name>  *left;
        avl<type_name>  *parent;
        int             lhight;
        int             rhight;
        
        avl() : value(type_name()), right(NULL), left(NULL), parent(NULL), lhight(int()), rhight(int()) {}
        avl(avl *right, avl *left, type_name value, avl *parent, int lhight, int rhight, bool rightside) : value(value), right(right), left(left), parent(parent), lhight(lhight), rhight(rhight)
        {
            if (rightside)
                parent->rhight++;
            else
                parent->lhight++;
        }
    };

    template<class T, class Compare = std::less<T>, class Alloc = std::allocator<avl<T> > >
        class AVL_body
    {
        typedef T       type_name;
        typedef Alloc   allocator_type;
        typedef Compare compare_type;

        
        avl<T>          *root;
        allocator_type  alloc;
        compare_type    cmp;

        void    insert(avl<type_name> **root, avl<type_name> *_new, avl<type_name> *parent)
        {
            if (*root == NULL)
            {
                std::cout << "?????\n";
                // exit (1);
                *root = _new;
                return;
            }
            if (cmp(_new->value, (*root)->value))
                insert(&((*root)->right), _new, *root);
            else
                insert(&((*root)->left), _new, *root);
            if (abs(size((*root)->right) - size((*root)->left)) > 1)
            {
               if (size((*root)->right) > size((*root)->left))
               {
                   // right to fix
                    std::cout << "right to fix\n";
                   if (((*root)->right)->right) // well this is left rotation
                   {
                       std::cout << "well this is left rotation\n";
                        avl<type_name> *tmprot = *root;
                        (*root) = (*root)->left;
                        avl<type_name> *tmpl = (*root)->right;
                        (*root)->right = tmprot;
                        tmprot->left = tmpl;
                   }
                   else // well this is an right - left rotation
                   {
                    //    avl<type_name> *tmprot = *root;
                    std::cout << "well this is an right - left rotation\n";
                   }
               }
               else
               {
                   // left to fix
                   std::cout << "left to fix\n";
                   if (((*root)->left)->left) // well this is right rotation
                   {
                       std::cout << "well this is right rotation\n";
                       std::cerr << "start\n";
                       avl<type_name> *tmprot = *root;
                       (*root) = (*root)->right;
                        std::cerr << "end\n";
                       if ((*root)->left)
                       {
                        avl<type_name> *tmpl = (*root)->left;
                        (*root)->left = tmprot;
                           
                        if (tmprot->right)
                        tmprot->right = tmpl;
                       }
                   }
                   else  // well this is an left - right rotation
                   {
                       std::cout << "well this is an left - right rotation\n";
                   }
               }
            }
        }
        int max(int a, int b)
        {
            if (a > b)
                return a;
            return b;
        }
        int size(avl<T> *root)
        {
            if (root == NULL)
                return -1;
            return max(size(root->left), size(root->right)) + 1;
        }
        public :
            AVL_body() : root(NULL) {}
            avl<T>    *newone(T value)
            {
                avl<T> *c = alloc.allocate(1);
                c->value = value;
                c->left = NULL;
                c->right = NULL;
                return c;
            }
            void    insert(type_name x)
            {
                avl<type_name> *_new = newone(x); 
                insert(&root, _new, NULL);
            }
            int    size()
            {
                return size(this->root);
            }
    };
}