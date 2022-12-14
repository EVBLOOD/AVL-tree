/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_body_old.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:16:14 by sakllam           #+#    #+#             */
/*   Updated: 2022/09/09 16:25:44 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>
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
        
        avl() : value(type_name()), right(NULL), left(NULL) {}
        avl(avl *right, avl *left, type_name value) : value(value), right(right), left(left) {}
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
        void balancing(avl<type_name> **root)
        {
            int sizer = size((*root)->right);
            int sizel = size((*root)->left);
            if (abs(sizer - sizel) > 1)
            {
               if (sizer > sizel)
               {
                   if ((*root)->right->right)
                        return left_rotation(root);
                    right_rotation(&((*root)->right));
                    return left_rotation(root);
               }
                if ((*root)->left->left)
                    return right_rotation(root);
                left_rotation(&((*root)->left));
                return right_rotation(root);
            }
        }
        void    insert(avl<type_name> **root, avl<type_name> *_new)
        {
            if (*root == NULL)
            {
                *root = _new;
                return;
            }
            if (cmp((*root)->value, _new->value))
                return (insert(&((*root)->right), _new), balancing(root));
            if (cmp(_new->value, (*root)->value))
                return (insert(&((*root)->left), _new), balancing(root));
            return;
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
                return 0;
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
        avl<T> *deepest(avl<T> *root)
        {
            if (root->right == NULL)
                return root;
            return deepest(root->right);
        }
        
        void remove(avl<T> **root, type_name value)
        {
            if (*root == NULL)
                return ;
            if (cmp((*root)->value, value))
                remove(&((*root)->right), value);
            else if (cmp(value, (*root)->value))
                remove(&((*root)->left), value);
            else
            {
                if ((*root)->left == NULL && (*root)->right == NULL)
                {
                    alloc.destroy(*root);
                    alloc.deallocate(*root, 1);
                    *root = NULL;
                    return ;
                }
                if ((*root)->left == NULL)
                {
                    avl<T> *right = (*root)->right;
                    alloc.destroy(*root);
                    alloc.deallocate(*root, 1);
                    *root = right;
                    balancing(root);
                    return;
                }
                if ((*root)->right == NULL)
                {
                    avl<T> *left = (*root)->left;
                    alloc.destroy(*root);
                    alloc.deallocate(*root, 1);
                    *root = left;
                    balancing(root);
                    return;
                }
                avl<T> *deep = deepest((*root)->left);
                (*root)->value = deep->value;
                remove(&((*root)->left), deep->value);
            }
            balancing(root);
        }
        bool find(avl<T> *root, T value)
        {
            if (root == NULL)
              return false;
            if (root->value ==  value)
                return true;
            return find(root->left, value) || find(root->right, value);
        }
        avl<T>    *newone(type_name value)
        {
            avl<T> *c = alloc.allocate(1);
            alloc.construct(c);
            c->value = value;
            c->left = NULL;
            c->right = NULL;
            return c;
        }
        public :
            AVL_body() : root(NULL) {}
            void    insert(type_name x)
            {
                insert(&root, newone(x));
            }
            int    size()
            {
                return size(this->root);
            }
            void printing()
            {
                printing(this->root, "root", 0);
            }
            void remove(type_name c)
            {
                remove(&(this->root), c);
            }
            bool find(type_name value)
            {
                return find(root, value);
            }
    };
}