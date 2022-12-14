/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_body.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:28:49 by sakllam           #+#    #+#             */
/*   Updated: 2022/09/09 16:20:39 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <cstring>
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
        int             height; // to make it faster as posible I save height,
                                    //to avoid calculating it each time I need to check balancing!
        
        avl() : value(type_name()), right(NULL), left(NULL), height(int()) {}
        avl(type_name value) : value(value), right(NULL), left(NULL), height(1) {}
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

        int max(int a, int b)
        {
            if (a > b)
                return a;
            return b;
        }
        int get_size(avl<type_name> *root)
        {
            if (root == NULL)
                return 0;
            return root->height;
        }
        void balancing(avl<type_name> **root)
        {
            if (abs(get_size((*root)->left) - get_size((*root)->right)) > 1)
            {
               if (get_size((*root)->right) > get_size((*root)->left))
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
        avl<type_name>    *newone(type_name value)
        {
            avl<type_name> *c = alloc.allocate(1);
            alloc.construct(c, value);
            return c;
        }
        void    insert_helper(avl<type_name> **root, avl<type_name> *_new)
        {
            if (*root == NULL)
            {
                *root = _new;
                return;
            }
            if (cmp((*root)->value, _new->value))
               insert_helper(&((*root)->right), _new);
            else if (cmp(_new->value, (*root)->value))
                insert_helper(&((*root)->left), _new);
            else
                return;
            (*root)->height = heightcount(*root);
            balancing(root);
        }
        int heightcount(avl<type_name> *root)
        {
            return max(get_size(root->left), get_size(root->right)) + 1;
        }
        void    right_rotation(avl<type_name> **root)
        {
            avl<type_name> *roottmp = *root;
            *root = (*root)->left;
            avl<type_name> *righttmp = (*root)->right;
            (*root)->right = roottmp;
            roottmp->left = righttmp;
            (*root)->right->height = heightcount((*root)->right);
            (*root)->height = heightcount(*root);
        }
        void    left_rotation(avl<type_name> **root)
        {
            avl<type_name> *roottmp = *root;
            *root = (*root)->right;
            avl<type_name> *righttmp = (*root)->left;
            (*root)->left = roottmp;
            roottmp->right = righttmp;
            (*root)->left->height = heightcount((*root)->left);
            (*root)->height = heightcount(*root);
        }
        void printing(avl<T> *root, std::string name, int i)
        {
            if (!root)
                return;
            std::cout << i << "  " <<  name << " :" << root->value << " -> " << root->height << std::endl;
            printing(root->right, "right", i + 1);
            printing(root->left, "left", i + 1);
        }
        avl<T> *deepest(avl<T> *root)
        {
            if (root->right == NULL)
                return root;
            return deepest(root->right);
        }
        void remove_helper(avl<T> **root, type_name value)
        {
            if (*root == NULL)
                return ;
            if (cmp((*root)->value, value))
                remove_helper(&((*root)->right), value);
            else if (cmp(value, (*root)->value))
                remove_helper(&((*root)->left), value);
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
                    (*root)->height = heightcount(*root);
                    return;
                }
                if ((*root)->right == NULL)
                {
                    avl<T> *left = (*root)->left;
                    alloc.destroy(*root);
                    alloc.deallocate(*root, 1);
                    *root = left;
                    (*root)->height = heightcount(*root);
                    return;
                }
                avl<T> *deep = deepest((*root)->left);
                (*root)->value = deep->value;
                remove_helper(&((*root)->left), (*root)->value);
            }
            (*root)->height = heightcount(*root);
            balancing(root);
        }
        bool find_helper(avl<T> *root, T value)
        {
            if (root == NULL)
              return false;
            if (cmp(root->value, value))
                return  find_helper(root->right, value);
            else if (cmp(value, root->value))
                return find_helper(root->left, value);
            else
                return true;
        }
        void helperfree_tree(avl<type_name> *x)
        {
            if (x == NULL)
                return;
            helperfree_tree(x->right);
            helperfree_tree(x->left);
            alloc.deallocate(x, 1);
        }
        public :
            AVL_body() : root(NULL) {}
            ~AVL_body() { helperfree_tree(root); }
            void    insert(type_name x)
            {
                insert_helper(&root, newone(x));
            }
            void printing()
            {
                printing(this->root, "root", 0);
            }
            void remove(type_name c)
            {
                remove_helper(&(this->root), c);
            }
            bool find(type_name value)
            {
                return find_helper(root, value);
            }
    };
}