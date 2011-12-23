/*
 *  The private interface of basic_string.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

#ifndef _CSTL_BASIC_STRING_PRIVATE_H_
#define _CSTL_BASIC_STRING_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef struct _tagbasicstring
{
    vector_t _vec_base;
}basic_string_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create basic_string container.
 * @param s_typename     element type name.
 * @return if create basic_string successfully, then return basic_string pointer, else return NULL.
 * @remarks if s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name,
 *          libcstl builtin typename or registed user defined type name, otherwise the function will return NULL.
 */
extern basic_string_t* _create_basic_string(const char* s_typename);

/**
 * Create basic_string container auxiliary function.
 * @param pvec_basic_string  uncreated container.
 * @param s_typename         element type name.
 * @return if create basic_string successfully return true, otherwise return false.
 * @remarks if s_typename == NULL, then the behavior is undefined. s_typename should be C builtin type name,
 *          libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_basic_string_auxiliary(basic_string_t* pt_basic_string, const char* s_typename);

/**
 * Initialize basic_string with specified element.
 * @param pt_basic_string   uninitialized basic_string container.
 * @param t_count            element number.
 * @param ...                specificed element.
 * @return void
 * @remarks if pt_basic_string == NULL, then the behavior is undefined. the type of specificed element and basic_string element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. basic_string container must be created by create_basic_string, otherwise the behavior is undefined.
 */
extern void _basic_string_init_elem(basic_string_t* pt_basic_string, size_t t_count, ...);

/**
 * Initialize basic_string with variable argument list of specified element.
 * @param pt_basic_string  uninitialized basic_string container.
 * @param t_count          element number.
 * @param val_elemlist     variable argument list of specificed element.
 * @return void
 * @remarks if pt_basic_string == NULL, then the behavior is undefined. the type of specificed element and basic_string element
 *          type must be same, otherwise the behavior is undefined. the first specificed element is in use, others are
 *          not in use. basic_string container must be created by create_basic_string, otherwise the behavior is undefined.
 */
extern void _basic_string_init_elem_varg(basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist);

/**
 * Destroy basic_string container auxiliary function.
 * @param pvec_basic_string  basic_string container.
 * @return void.
 * @remarks if pvec_basic_string == NULL or basic_string is not created by create_basic_string() function, then the behavior
 *          is undefined. basic_string container must be create_basic_string, otherwise the behavior is undefined.
 */
extern void _basic_string_destroy_auxiliary(basic_string_t* pt_basic_string);

/**
 * Find a first occurrence of a elem
 * @param cpt_basic_string     basic_string container.
 * @param t_pos                search begin position.
 * @param ...                  specificed element.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then return
 *          NPOS.
 */
extern size_t _basic_string_find_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...);

/**
 * Find a first occurrence of a substring
 * @param cpt_basic_string     basic_string container.
 * @param t_pos                search begin position.
 * @param val_elemlist         specificed element.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then return
 *          NPOS.
 */
extern size_t _basic_string_find_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist);

/**
 * Find a last occurrence of a substring
 * @param cpt_basic_string     basic_string container.
 * @param t_pos                search begin position.
 * @param ...                  specificed element.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then search
 *          from the last element.
 */
extern size_t _basic_string_rfind_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...);

/**
 * Find a last occurrence of a substring
 * @param cpt_basic_string     basic_string container.
 * @param t_pos                search begin position.
 * @param val_elemlist         specificed element.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then search
 *          from the last element.
 */
extern size_t _basic_string_rfind_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist);

/**
 * Find a first occurrence of a character that is not equal to specificed element.
 * @param cpt_basic_string     basic_string container.
 * @param t_pos                search begin position.
 * @param ...                  specificed element.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then return
 *          NPOS.
 */
extern size_t _basic_string_find_first_not_of_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...);

/**
 * Find a first occurrence of a character that is not equal to specificed element.
 * @param cpt_basic_string     basic_string container.
 * @param t_pos                search begin position.
 * @param val_elemlist         specificed element.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then return
 *          NPOS.
 */
extern size_t _basic_string_find_first_not_of_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist);

/**
 * Find a last occurrence of a character that is not equal to specificed element.
 * @param cpt_basic_string     basic_string container.
 * @param t_pos                search begin position.
 * @param ...                  specificed element.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then search
 *          from the last element.
 */
extern size_t _basic_string_find_last_not_of_elem(const basic_string_t* cpt_basic_string, size_t t_pos, ...);

/**
 * Find a last occurrence of a character that is not equal to specificed element.
 * @param cpt_basic_string     basic_string container.
 * @param t_pos                search begin position.
 * @param val_elemlist         specificed element.
 * @return the index of first character of the substring when successful, otherwise NPOS.
 * @remarks if cpt_basic_string == NULL or uninitialized, the behavior is undefined. if t_pos is invalid position, then search
 *          from the last element.
 */
extern size_t _basic_string_find_last_not_of_elem_varg(const basic_string_t* cpt_basic_string, size_t t_pos, va_list val_elemlist);

/**
 * Appends specificed element to basic string.
 * @param pt_basic_string      basic_string container.
 * @param ...                  specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine.
 */
extern void _basic_string_connect_elem(basic_string_t* pt_basic_string, ...);

/**
 * Appends specificed element to basic string.
 * @param pt_basic_string      basic_string container.
 * @param val_elemlist         specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine.
 */
extern void _basic_string_connect_elem_varg(basic_string_t* pt_basic_string, va_list val_elemlist);

/**
 * Adds an element to basic string.
 * @param pt_basic_string      basic_string container.
 * @param ...                  specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine.
 */
extern void _basic_string_push_back(basic_string_t* pt_basic_string, ...);

/**
 * Adds an element to basic string.
 * @param pt_basic_string      basic_string container.
 * @param val_elemlist         specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine.
 */
extern void _basic_string_push_back_varg(basic_string_t* pt_basic_string, va_list val_elemlist);

/**
 * Erase the last element.
 * @param pt_basic_string      basic_string container.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine. basic string container must not be
 *          empty, otherwise the behavior is undefined.
 */
extern void _basic_string_pop_back(basic_string_t* pt_basic_string);

/**
 * Reset the size of basic_string elements.
 * @param pt_basic_string   basic_string container.
 * @param t_resize          new size of basic_string elements.
 * @param ...               specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the type of specificed
 *          element and basic_string element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current basic_string size, then erase elmement from the end.
 *          if t_resize greater than current basic_string size, then append elements to the end, and the element is specificed
 *          element.
 */
extern void _basic_string_resize(basic_string_t* pt_basic_string, size_t t_resize, ...);

/**
 * Reset the size of basic_string elements, and filled element is from variable argument list.
 * @param pt_basic_string   basic_string container.
 * @param t_resize          new size of basic_string elements.
 * @param val_elemlist      specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the type of specificed
 *          element and basic_string element type must be same, otherwise the behavior is undefined. the first specificed is
 *          in use, others are not in use. if t_resize less than current basic_string size, then erase elmement from the end.
 *          if t_resize greater than current basic_string size, then append elements to the end, and the element is from
 *          variable argument list.
 */
extern void _basic_string_resize_varg(basic_string_t* pt_basic_string, size_t t_resize, va_list val_elemlist);

/**
 * Assign new element to basic_string.
 * @param pt_basic_string      basic_string container.
 * @param t_count              element number.
 * @param ...                  specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine.
 */
extern void _basic_string_assign_elem(basic_string_t* pt_basic_string, size_t t_count, ...);

/**
 * Assign new element to basic_string.
 * @param pt_basic_string      basic_string container.
 * @param t_count              element number.
 * @param val_elemlist         specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine.
 */
extern void _basic_string_assign_elem_varg(basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist);

/**
 * Appends characters to the end of basic string.
 * @param pt_basic_string      basic_string container.
 * @param t_count              element number.
 * @param ...                  specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine.
 */
extern void _basic_string_append_elem(basic_string_t* pt_basic_string, size_t t_count, ...);

/**
 * Appends characters to the end of basic string.
 * @param pt_basic_string      basic_string container.
 * @param t_count              element number.
 * @param val_elemlist         specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or uninitialized, then the bahavior is undefine.
 */
extern void _basic_string_append_elem_varg(basic_string_t* pt_basic_string, size_t t_count, va_list val_elemlist);

/**
 * Insert one copy of element befor specificed position.
 * @param pt_basic_string   basic_string container.
 * @param it_pos            insert position.
 * @param ...               specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the it_pos must be
 *          invalid iterator of basic_string container, otherwise the behavior is undefined. the type of specificed element
 *          and basic_string element type must be same, otherwise the behavior is undefined. the first specificed is in use,
 *          others are not in use.
 */
extern basic_string_iterator_t _basic_string_insert(basic_string_t* pt_basic_string, basic_string_iterator_t it_pos, ...);

/**
 * Insert multiple copys of element befor specificed position.
 * @param pt_basic_string   basic_string container.
 * @param it_pos            insert position.
 * @param t_count           element number.
 * @param ...               specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the it_pos must be
 *          invalid iterator of basic_string container, otherwise the behavior is undefined. the type of specificed element
 *          and basic_string element type must be same, otherwise the behavior is undefined. the first specificed is in use,
 *          others are not in use.
 */
extern basic_string_iterator_t _basic_string_insert_n(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos, size_t t_count, ...);

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 * @param pt_basic_string   basic_string container.
 * @param it_pos            insert position.
 * @param t_count           element number.
 * @param val_elemlist  specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the it_pos must be
 *          invalid iterator of basic_string container, otherwise the behavior is undefined. the type of specificed element
 *          and basic_string element type must be same, otherwise the behavior is undefined. the first specificed is in use,
 *          others are not in use. the inserted element is from variable argument list.
 */
extern basic_string_iterator_t _basic_string_insert_n_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t t_pos, size_t t_count, va_list val_elemlist);

/**
 * Insert multiple copys of element befor specificed position.
 * @param pt_basic_string   basic_string container.
 * @param t_pos             insert position.
 * @param t_count           element number.
 * @param ...               specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the t_pos must be
 *          invalid iterator of basic_string container, otherwise the behavior is undefined. the type of specificed element
 *          and basic_string element type must be same, otherwise the behavior is undefined. the first specificed is in use,
 *          others are not in use.
 */
extern void _basic_string_insert_elem(basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, ...);

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 * @param pt_basic_string   basic_string container.
 * @param t_pos             insert position.
 * @param t_count           element number.
 * @param val_elemlist      specificed element.
 * @return position refereced the first inserted elements.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the t_pos must be
 *          invalid iterator of basic_string container, otherwise the behavior is undefined. the type of specificed element
 *          and basic_string element type must be same, otherwise the behavior is undefined. the first specificed is in use,
 *          others are not in use. the inserted element is from variable argument list.
 */
extern void _basic_string_insert_elem_varg(basic_string_t* pt_basic_string, size_t t_pos, size_t t_count, va_list val_elemlist);

/**
 * Replace elements at specificed posititon.
 * @param pt_basic_string   basic_string container.
 * @param it_begin          begin of replaced range.
 * @param it_end            end of replaced range.
 * @param t_count           element number.
 * @param ...               specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the [it_begin, it_end)
 *          must be invalid range of basic_string container, otherwise the behavior is undefined. the type of specificed element
 *          and basic_string element type must be same, otherwise the behavior is undefined. the first specificed is in use,
 *          others are not in use. the inserted element is from variable argument list.
 */
extern void _basic_string_range_replace_elem(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end, size_t t_count, ...);

/**
 * Replace elements at specificed posititon.
 * @param pt_basic_string   basic_string container.
 * @param it_begin          begin of replaced range.
 * @param it_end            end of replaced range.
 * @param t_count           element number.
 * @param val_elemlist      specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the [it_begin, it_end)
 *          must be invalid range of basic_string container, otherwise the behavior is undefined. the type of specificed element
 *          and basic_string element type must be same, otherwise the behavior is undefined. the first specificed is in use,
 *          others are not in use. the inserted element is from variable argument list.
 */
extern void _basic_string_range_replace_elem_varg(
    basic_string_t* pt_basic_string, basic_string_iterator_t it_begin, basic_string_iterator_t it_end,
    size_t t_count, va_list val_elemlist);

/**
 * Replace elements at specificed posititon.
 * @param pt_basic_string   basic_string container.
 * @param t_pos             specificed position.
 * @param t_len             replace length.
 * @param t_count           element number.
 * @param ...               specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the t_pos must be
 *          belong to basic_string, otherwise the behavior is undefined. if t_len == NPOS or t_pos + t_len >= basic_string_size(),
 *          then replace all remain string from t_pos. the type of specificed element and basic_string element type must be same,
 *          otherwise the behavior is undefined. the first specificed is in use, others are not in use. the inserted element is
 *          from variable argument list.
 */
extern void _basic_string_replace_elem(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_count, ...);

/**
 * Replace elements at specificed posititon.
 * @param pt_basic_string   basic_string container.
 * @param t_pos             specificed position.
 * @param t_len             replace length.
 * @param t_count           element number.
 * @param val_elemlist      specificed element.
 * @return void.
 * @remarks if pt_basic_string == NULL or basic_string is uninitialized, then the behavior is undefined. the t_pos must be
 *          belong to basic_string, otherwise the behavior is undefined. if t_len == NPOS or t_pos + t_len >= basic_string_size(),
 *          then replace all remain string from t_pos. the type of specificed element and basic_string element type must be same,
 *          otherwise the behavior is undefined. the first specificed is in use, others are not in use. the inserted element is
 *          from variable argument list.
 */
extern void _basic_string_replace_elem_varg(
    basic_string_t* pt_basic_string, size_t t_pos, size_t t_len, size_t t_count, va_list val_elemlist);

/**
 * Initialize element with basic_string element type auxiliary function.
 * @param pt_basic_string   basic_string container.
 * @param pv_elem           initialized element.
 * @return void.
 * @remarks if pt_basic_string == NULL or pv_elem == NULL, then the behavior is undefined. pt_basic_string must be initialized
 *          basic_string container or created by create_basic_string, otherwise the behavior is undefined.
 */
extern void _basic_string_init_elem_auxiliary(basic_string_t* pt_basic_string, void* pv_elem);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_BASIC_STRING_PRIVATE_H_ */
/** eof **/

