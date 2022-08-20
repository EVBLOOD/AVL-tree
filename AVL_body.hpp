/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_body.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:16:14 by sakllam           #+#    #+#             */
/*   Updated: 2022/08/20 19:12:24 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdlib>
#include <algorithm>
#include <memory>
#include <iostream>
#include <system_error>

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

        
        void    right_rotation(avl<type_name> **root)
        {
            avl<type_name> *roottmp = *root;
            *root = (*root)->left;
            avl<type_name> *righttmp = (*root)->right;
            (*root)->right = roottmp;
            roottmp->left = righttmp;
        }
        void    left_rotation(avl<type_name> **root)
        {
            avl<type_name> *roottmp = *root;
            *root = (*root)->right;
            avl<type_name> *righttmp = (*root)->left;
            (*root)->left = roottmp;
            roottmp->right = righttmp;
        }

        void    insert(avl<type_name> **root, avl<type_name> *_new, avl<type_name> *parent)
        {
            if (*root == NULL)
            {
                *root = _new;
                return;
            }
            if (cmp((*root)->value, _new->value))
                insert(&((*root)->right), _new, *root);
            else
                insert(&((*root)->left), _new, *root);
            if (abs(size((*root)->right) - size((*root)->left)) > 1)
            {
                std::cerr << "right size : " << size((*root)->right) << ", left size : " << size((*root)->left) << "\n";
               if (size((*root)->right) > size((*root)->left))
               {
                   // right to fix
                    std::cout << "right to fix\n";
                   if (((*root)->right)->right) // well this is left rotation
                   {
                        std::cout << "well this is left rotation\n";
                        left_rotation(root);
                   }
                   else // well this is an right - left rotation
                   {
                    std::cout << "well this is an right - left rotation\n";
                    right_rotation(root);
                    left_rotation(root);
                   }
               }
               else
               {
                   // left to fix
                   std::cout << "left to fix\n";
                   if (((*root)->left)->left) // well this is right rotation
                   {
                       std::cout << "well this is right rotation\n";
                        right_rotation(root);
                   }
                   else  // well this is an left - right rotation
                   {
                        std::cout << "well this is an left - right rotation\n";
                        left_rotation(&((*root)->left));
                        right_rotation(root);
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
            return (max(size(root->left), size(root->right)) + 1);
        }
        void printing(avl<T> *root, std::string name, int i)
        {
            if (!root)
                return;
            std::cout << i << "  " <<  name << " :" << root->value << std::endl;
            printing(root->right, "right", i + 1);
            printing(root->left, "left", i + 1);
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
            void printing()
            {
                printing(this->root, "root", 0);
            }
    };
}